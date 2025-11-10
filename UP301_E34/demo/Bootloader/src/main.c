/*
 * Copyright (C) 2025 UpbeatTech Inc. All Rights Reserved
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX short identifier: Apache-2.0
 */

#include <stdio.h>

#include "metal-platform.h"
#include "metal/upt_init.h"
#include "upt_up301.h"

#include "pufs_common.h"
#include "pufs_crypto.h"
#include "pufs_dma.h"
#include "pufs_ecp.h"
#include "pufs_hmac.h"
#include "pufs_memory_map.h"
#include "pufs_rt.h"
#include "pufs_sp38a.h"

#include "bootutil/bootutil.h"
#include "mbedtls/version.h"
#include "flash_map_backend/internal_flash.h"
#include "mcuboot_config/mcuboot_logging.h"

/* System-Specific */
#define SPI_BASE_ADDR	0x60000000UL
#define WDT_CNT_1SEC    32768 // Watchdog timer counts for 1 second at 32.768kHz clock.

/* XCPB-related registers */
// The preamble data.
#define PREAMBLE_DATA0	0x3749987EUL
#define PREAMBLE_DATA1	0x575B7DFFUL
#define PREAMBLE_DATA2	0xEAFFFFFEUL
#define PREAMBLE_DATA3	0xA7CAB53FUL
// SCU.
#define XCPB_PPROT          (0x1 << 3)
#define OTP_SECURE_XCPB_EN	(0x1 << 15)
// XCPB FESEQSTAT register bit definitions.
#define FESEQSTAT_CROM  (0x1 << 0)  // 0x1: sequence completed successfully.
#define FESEQSTAT_DBG   (0x1 << 1)  // 0x1: sequence was stopped.
#define FESEQSTAT_SVE   (0x1 << 2)  // 0x1: signature verification failed.
#define FESEQSTAT_CIE   (0x1 << 3)  // 0x1: encryption function disabled.
#define FESEQSTAT_RUN   (0x1 << 31) // Indicating the sequence is running or not.

#define REG32(addr) (*(volatile unsigned int *)(addr))

int config_decrypted_xip(void) {
    unsigned int reg_tmp;
    unsigned int preamble_data[4] = {
        PREAMBLE_DATA0, PREAMBLE_DATA1, PREAMBLE_DATA2, PREAMBLE_DATA3
    };

#ifdef FORCE_XCPB_WO_OTP
    if (1) {
#else
    /* Check OTP setting for secure XCPB. */
    if (REG32(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_OTPAUTOLD3) & OTP_SECURE_XCPB_EN) {
#endif
        /* Compare preamble data with SPI flash contents. */
        if (memcmp((void *)preamble_data, (void *)SPI_BASE_ADDR, 16) == 0) {
            MCUBOOT_LOG_DBG("Ready to activate XCPB on-the-fly decryption.\n");
        } else {
            MCUBOOT_LOG_DBG("XCPB preambles mismatch.\n");
            return -1;
        }

        /* Set AXI base address to 0x0 during verification stage. */
        REG32(METAL_UP_OSPI_200A0000_BASE_ADDRESS + METAL_UP_OSPI_AXI_BASE_ADDR0) = 0x0UL;

        /* Clear XCPB_PPROT in MISCCTRL register to allow non-secure access. */
        REG32(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_MISCCTRL) &= ~XCPB_PPROT;

        /* Start XCPB sequence. */
        REG32(METAL_UP_XCPB_200A3000_BASE_ADDRESS + METAL_UP_XCPB_FESEQSTART) = 1;

        /* Wait until the sequence is cleared (RUN=0x0: stop). */
        while (REG32(METAL_UP_XCPB_200A3000_BASE_ADDRESS + METAL_UP_XCPB_FESEQSTAT) & FESEQSTAT_RUN);

        /* Read and check the sequence status bits. */
        reg_tmp = REG32(METAL_UP_XCPB_200A3000_BASE_ADDRESS + METAL_UP_XCPB_FESEQSTAT);
        // Check error status bits.
        if (reg_tmp & (FESEQSTAT_CIE | FESEQSTAT_SVE | FESEQSTAT_DBG)) {
            MCUBOOT_LOG_DBG("Check sequence status bits failed: %x\n", reg_tmp);
            return -2;
        }
        // Check success flag.
        if ((reg_tmp & FESEQSTAT_CROM) == 0) {
            MCUBOOT_LOG_DBG("Check success flag failed.\n");
            return -3;
        }
    }

    /* Restore AXI base address to SPI_BASE_ADDR after initialization. */
    REG32(METAL_UP_OSPI_200A0000_BASE_ADDRESS + METAL_UP_OSPI_AXI_BASE_ADDR0) = SPI_BASE_ADDR;

    return 0;
}

void init_pufs_modules(void) {
    pufs_module_init(PUFIOT_ADDR_START, PUFIOT_MAP_SIZE);
    pufs_dma_module_init(DMA_ADDR_OFFSET);			// DMA
    pufs_rt_module_init(RT_ADDR_OFFSET);			// PUFrt
    pufs_ka_module_init(KA_ADDR_OFFSET);			// Key area
    pufs_kwp_module_init(KWP_ADDR_OFFSET);			// Import/Export key
    pufs_crypto_module_init(CRYPTO_ADDR_OFFSET);	// Crypto
	pufs_hmac_module_init(HMAC_HASH_ADDR_OFFSET);	// Hash
    pufs_sp38a_module_init(SP38A_ADDR_OFFSET);		// AES-CTR
    pufs_pkc_module_init(PKC_ADDR_OFFSET);			// ECDH, ECDSA
}

void do_boot(struct boot_rsp *rsp) {
#ifdef MCUBOOT_RAM_LOAD
	uint32_t address = (void *)(rsp->br_hdr->ih_load_addr + rsp->br_hdr->ih_hdr_size);
#else
	uint32_t address = (rsp->br_image_off) + ((rsp->br_hdr)->ih_hdr_size);
#endif

	/* Go to Application entry point. */
	MCUBOOT_LOG_DBG("Booting firmware image at 0x%x\n", (unsigned int)address);
	void (*application_start)(void) = (void *)(address);
	application_start();
}

/****************************************************************************
 * main
 ****************************************************************************/
int main() {
	/* Should initialize ISR handler */
	init_interrupts();
	e34_interrupt_enable();

#ifdef MCUBOOT_WDT_ENABLE
	upt_wdt_activate(2 * WDT_CNT_1SEC);
#endif

	/* Show mcuboot and mbedtls versions */
	char mbedtls_ver[9];
	mbedtls_version_get_string(mbedtls_ver);
    MCUBOOT_LOG_DBG("%s: STARTING MCUBOOT (Version: 2.2.0)\n", __func__);
    MCUBOOT_LOG_DBG("%s: Using Mbed TLS (Version: %s)\n", __func__, mbedtls_ver);

    /* Initialize PUFs modules */
	init_pufs_modules();

    /* Call `boot_go()` function to start the mcuboot */
    int ret;
    struct boot_rsp rsp;
#ifdef MP_BOOT
    ret = boot_go(&rsp);
    if (ret != 0) {
    	MCUBOOT_LOG_DBG("%s: Failed to start bootloader(MCUBOOT check error)\n", __func__);
    	FIH_PANIC;
    }
#else
    boot_go(&rsp);
#endif

    /* Speed up Flash */
    speedup_flash();

    /* Bootloader has successfully started. Show information */
#ifdef MP_BOOT
    MCUBOOT_LOG_DBG("%s: Bootloader started successfully\n", __func__);
#else
    MCUBOOT_LOG_DBG("%s: Bootloader started successfully(Develop/Debug only, not do MCUBOOT integrity check)\n", __func__);
#endif
    MCUBOOT_LOG_DBG("br_image_off = 0x%08x\n", (unsigned int)(rsp.br_image_off));
    MCUBOOT_LOG_DBG("ih_hdr_size = 0x%08x\n", rsp.br_hdr->ih_hdr_size);
	MCUBOOT_LOG_DBG("ih_ver = %d.%d.%d+%d\n", rsp.br_hdr->ih_ver.iv_major,
										      rsp.br_hdr->ih_ver.iv_minor,
										      rsp.br_hdr->ih_ver.iv_revision,
										      rsp.br_hdr->ih_ver.iv_build_num);

    ret =  config_decrypted_xip();
    if (ret != 0) {
    	MCUBOOT_LOG_DBG("%s: Failed to start bootloader(XCPB check error)\n", __func__);
    	MCUBOOT_LOG_DBG("METAL_UP_XCPB_FESEQSTAT: 0x%08x\n", REG32(METAL_UP_XCPB_200A3000_BASE_ADDRESS + METAL_UP_XCPB_FESEQSTAT));
    	FIH_PANIC;
    }

    do_boot(&rsp);

    FIH_PANIC;
}
