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

#include <stddef.h>
#include <string.h>

#include "metal-platform.h"
#include "metal/upt_sysctrl.h"
#include "metal/ospi.h"

#include "flash_map_backend/internal_flash.h"
#include "mcuboot_config/mcuboot_logging.h"

/*******************************************
 * for spi flash id definition
 ********************************************/
#define FLASH_WB_DEV            0xEF
#define FLASH_GD_DEV            0xC8
#define FLASH_MXIC_DEV          0xC2

#define MX_MX25U6345G_ID        0x3784 			/* For UP301 169 pin OPI type */
#define MX_MX25U1632F_ID        0x3525 			/* For UP301/201 QPI type */
#define MX_MX25U6435F_ID        0x3725			/* For UP101 QPI type */
//#define MX_MX25UW6345G_ID       0x3784
//#define MX_MX25U16356_ID        0x3525

#define WB_W25Q64FWSS_ID	    0x1760
#define WB_W25Q64JW_ID	        0x1780          /* For UP301 QSPI DTR type*/

#define GD_GD25LQ64CSI_ID       0x1760

#define FLASH_SIZE_32MB_ID      0x19
#define FLASH_SIZE_16MB_ID      0x18
#define FLASH_SIZE_8MB_ID       0x17
#define FLASH_SIZE_4MB_ID       0x16
#define FLASH_SIZE_2MB_ID       0x15
#define FLASH_SIZE_1MB_ID       0x14


#define WB_W25Q64FWSS_ID_	0x0
#define WB_W25Q64JW_ID_		0x1
#define GD_GD25LQ64CSI_ID_	0x2
#define MX_MX25U6345G_ID_	0x3
#define MX_MX25U1632F_ID_	0x4
#define MX_MX25U6435F_ID_	0x5
#define UN_UNKNOW_ID_		0xFF

/*******************************************
 * for spi flash command definition
 ********************************************/
// Write enable
#define CHIP_MXIC_MX25U1632F_WREN	0x06
#define CHIP_MXIC_MX25U6345G_WREN	0x06F9
// Write
#define CHIP_MXIC_MX25U1632F_WRITE	0x02
#define CHIP_MXIC_MX25U6345G_WRITE	0x12ED
// Read status register
#define CHIP_MXIC_MX25U1632F_RDSR	0x05
#define CHIP_MXIC_MX25U6345G_RDSR	0x05FA
// Read
#define CHIP_MXIC_MX25U1632F_QREAD	0xEB
#define CHIP_MXIC_MX25U6345G_SOREAD	0xEC13
#define OSPI_ADDRESS_3BYTE_MASK		0x00FFFFFF
#define OSPI_ADDRESS_4BYTE_MASK 	0xFFFFFFFF

/*******************************************
 * shared data area from mcuboot to app image
 ********************************************/
ospi_config_Type ospi_config;
static ospi_frame_info_Type __stFrame;
static ospi_field_protocol_Type __stProtocol;

metal_ospi_Type *up_ospi;
bool fospi_init_done = 0;
uint8_t flash_table_seq_num;

/* For system information. Be careful, this must be 4 alignment */
typedef struct _flash_info {
    uint8_t   reserved;     /*  */
    uint8_t   manufacturer; /* Manufacturer id */
    uint16_t  flash_id;     /* device id */
    uint32_t  flash_size;   /* flash size in byte */
    uint8_t   width_mode;   /* flash support SPI/QPI/OPI mode or not */
    uint8_t   sys_version;  /* system version, get from SYS_VERSION_ADDR */
    uint8_t   dev_mode;     /* current usb link type, 0/1/2/3 for unknow/SS/HS/FS */
    uint8_t   vender_specific; /* specific purpose for vendor */
} SPI_Flash_Type;

SPI_Flash_Type flash_info;

/* Flash ID type table and struct */
struct _flash_id_table_t {
	uint8_t flash_id_index;
	uint8_t manufacturer;
	uint16_t device_id;
};
const struct _flash_id_table_t flash_id_table[] = {
		{0, FLASH_WB_DEV, WB_W25Q64FWSS_ID},
		{1, FLASH_WB_DEV, WB_W25Q64JW_ID},
		{2, FLASH_GD_DEV, GD_GD25LQ64CSI_ID},
		{3, FLASH_MXIC_DEV, MX_MX25U6345G_ID},
		{4, FLASH_MXIC_DEV, MX_MX25U1632F_ID},
		{5, FLASH_MXIC_DEV, MX_MX25U6435F_ID},
};

static uint32_t __find_flash_id(void) {
	return BOOT_SHARED_DATA_PTR->flash_id_index;
}

static void __flash_soft_reset(void) {

    // OPI mode SDR mode
	OSPI_INIT_FRAME_INFO(__stFrame);
    OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
    __stFrame.cmd = 0x6699U;
    __stFrame.cmd_len = 2U;
    __stProtocol.f_code.io_width = ospi_io_octal;
    __stProtocol.f_code.data_rate = ospi_data_rate_sdr;
    upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);

    OSPI_INIT_FRAME_INFO(__stFrame);
    OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
    __stFrame.cmd = 0x9966U;
    __stFrame.cmd_len = 2U;
    __stProtocol.f_code.io_width = ospi_io_octal;
    __stProtocol.f_code.data_rate = ospi_data_rate_sdr;
    upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);

    // QPI mode
    OSPI_INIT_FRAME_INFO(__stFrame);
    OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
    __stFrame.cmd = 0x66U;
    __stFrame.cmd_len = 1U;
    __stProtocol.f_code.io_width = ospi_io_quad;
    __stProtocol.f_code.data_rate = ospi_data_rate_sdr;
    upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);

    OSPI_INIT_FRAME_INFO(__stFrame);
    OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
    __stFrame.cmd = 0x99U;
    __stFrame.cmd_len = 1U;
    __stProtocol.f_code.io_width = ospi_io_quad;
    __stProtocol.f_code.data_rate = ospi_data_rate_sdr;
    upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);

    // SPI mode
    OSPI_INIT_FRAME_INFO(__stFrame);
    OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
    __stFrame.cmd = 0x66U;
    __stFrame.cmd_len = 1U;
    __stProtocol.f_code.io_width = ospi_io_single;
    __stProtocol.f_code.data_rate = ospi_data_rate_sdr;
    upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);

    OSPI_INIT_FRAME_INFO(__stFrame);
    OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
    __stFrame.cmd = 0x99U;
    __stFrame.cmd_len = 1U;
    __stProtocol.f_code.io_width = ospi_io_single;
    __stProtocol.f_code.data_rate = ospi_data_rate_sdr;
    upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);
}

static uint32_t __fospi_flash_probe(void) {
    uint8_t  chip_id[3];
    uint32_t  probe_90_instruction = 0;

    // Read Manufacturer and Device Identification by JEDEC ID(0x9F)
    OSPI_INIT_FRAME_INFO(__stFrame);
    OSPI_INIT_FIELD_PROTOCOL(__stProtocol);

    __stFrame.cmd = 0x9FU;
    __stFrame.cmd_len = 1U;
    __stFrame.dat = (uintptr_t)chip_id;
    __stFrame.dat_len = 3U;

    __stProtocol.f_code.io_width = ospi_io_single;
    __stProtocol.f_data.io_width = ospi_io_single;
    __stProtocol.f_code.data_rate = ospi_data_rate_sdr;
    __stProtocol.f_data.data_rate = ospi_data_rate_sdr;

    upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_read,
						&__stFrame,
						&__stProtocol);

    flash_info.manufacturer = chip_id[0];
    if (flash_info.manufacturer == 0x00 || flash_info.manufacturer == 0xFF) {

       //Read Manufacturer and Device Identification by 0x90
    	OSPI_INIT_FRAME_INFO(__stFrame);
    	__stFrame.cmd = 0x90U;
    	__stFrame.cmd_len = 1U;
        __stFrame.adr = 0U;
        __stFrame.adr_len = 3U;
    	__stFrame.dat = (uintptr_t)chip_id;
    	__stFrame.dat_len = 2U;

    	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
    	__stProtocol.f_code.io_width = ospi_io_single;
    	__stProtocol.f_addr.io_width = ospi_io_single;
    	__stProtocol.f_data.io_width = ospi_io_single;
    	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
    	__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
    	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;

    	upt_ospi_transfer(up_ospi,
    						&ospi_config, ospi_transfer_read,
    						&__stFrame,
    						&__stProtocol);

        flash_info.manufacturer = chip_id[0];
        probe_90_instruction = 1;
    }
    flash_info.flash_id = chip_id[1];
    flash_info.flash_id |= (chip_id[2]<<8);

    return probe_90_instruction;
}

static void __find_flash_table(void) {

	flash_table_seq_num = 0xff;

	for( int i=0; i<(sizeof(flash_id_table)/4); i++ ) {
		if ( (flash_info.manufacturer == flash_id_table[i].manufacturer) && (flash_info.flash_id == flash_id_table[i].device_id)) {
			flash_table_seq_num = flash_id_table[i].flash_id_index;
			return;
		}
	}
}

SRAM_ATTR static void __init_fospi(void) {
	if(fospi_init_done) {
		return;
	}

#ifdef BOOTLOADER
	char *flash_manu;

	up_ospi = upt_ospi_get_device(NAON_OSPI);

	/*** OSPI reference clock is divided by 1(value=00) (50MHz). PLL2 is default 597M ***/
	upt_ospi_init(up_ospi, ospi_div_1, ospi_phase_180);
	upt_ospi_set_slave_en(up_ospi, ospi_slave_0_en);
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_PINMUX0) &= ~0x00FFFFF0;

	// Reset Flash.
	__flash_soft_reset();
	// Get flash information.
	__fospi_flash_probe();

	// Show the Flash manufacture
    switch (flash_info.manufacturer) {
        case FLASH_WB_DEV:
            flash_manu = "WINBOND";
            break;
        case FLASH_MXIC_DEV:
            flash_manu = "MXIC";
            break;
        case FLASH_GD_DEV:
            flash_manu = "GigaDevice";
            break;
        default:
            flash_manu = "Unknown";
            return;
    }
    MCUBOOT_LOG_DBG("%s: Manufacturer ID = 0x%02X (%s)\n", __func__, flash_info.manufacturer, flash_manu);
    MCUBOOT_LOG_DBG("%s: Device ID       = 0x%04X\n", __func__, flash_info.flash_id);

    __find_flash_table();

    fospi_init_done = 1;
#else
	up_ospi = upt_ospi_get_device(NAON_OSPI);

	/*** OSPI reference clock is divided by 1(value=00) (50MHz). PLL2 is default 597M ***/
	enum_ospi_div_Type ospi_div = (__find_flash_id() == MX_MX25U6345G_ID_) ? ospi_div_4 : ospi_div_1;
	upt_ospi_init(up_ospi, ospi_div, ospi_phase_180);
	upt_ospi_set_slave_en(up_ospi, ospi_slave_0_en);

	fospi_init_done = 1;
#endif
}

SRAM_ATTR static void __fospi_write_control(uint8_t enable) {
    OSPI_INIT_FRAME_INFO(__stFrame);
    OSPI_INIT_FIELD_PROTOCOL(__stProtocol);

#ifdef BOOTLOADER
    if(enable) {
        __stFrame.cmd = 0x06U;
        __stFrame.cmd_len = 1U;
    }
    else {
        __stFrame.cmd = 0x04U;
        __stFrame.cmd_len = 1U;
    }
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
#else
	// NOTE: only support write-enable now.
	uint32_t flash_id = __find_flash_id();
	if (flash_id == MX_MX25U1632F_ID_) {
		__stFrame.cmd = CHIP_MXIC_MX25U1632F_WREN;
		__stFrame.cmd_len = 1U;

		__stProtocol.f_code.io_width = ospi_io_quad;
		__stProtocol.f_addr.io_width = ospi_io_quad;
		__stProtocol.f_data.io_width = ospi_io_quad;
	}
	else if (flash_id == MX_MX25U6345G_ID_) {
		__stFrame.cmd = CHIP_MXIC_MX25U6345G_WREN;
		__stFrame.cmd_len = 2U;

		__stProtocol.f_code.io_width = ospi_io_octal;
		__stProtocol.f_addr.io_width = ospi_io_octal;
		__stProtocol.f_data.io_width = ospi_io_octal;
	}

	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
#endif

	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);
}

SRAM_ATTR static void __fospi_write_data(size_t dest_addr, const void *src, size_t size) {
	OSPI_INIT_FRAME_INFO(__stFrame);
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);

#ifdef BOOTLOADER
	if ((flash_info.manufacturer == FLASH_MXIC_DEV) && (flash_info.flash_id == MX_MX25U6345G_ID)) {
		__stFrame.cmd = 0x12U;
		__stFrame.adr_len = 4U;
	}
	else {
	__stFrame.cmd = 0x02U;
	__stFrame.adr_len = 3U;
	}
	__stFrame.cmd_len = 1U;

	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_addr.io_width = ospi_io_single;
	__stProtocol.f_data.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
#else
	uint32_t flash_id = __find_flash_id();
	if (flash_id == MX_MX25U1632F_ID_) {
		__stFrame.cmd = CHIP_MXIC_MX25U1632F_WRITE;
		__stFrame.cmd_len = 1U;
		__stFrame.adr_len = 3U;

		__stProtocol.f_code.io_width = ospi_io_quad;
		__stProtocol.f_addr.io_width = ospi_io_quad;
		__stProtocol.f_data.io_width = ospi_io_quad;
	}
	else if (flash_id == MX_MX25U6345G_ID_) {
		__stFrame.cmd = CHIP_MXIC_MX25U6345G_WRITE;
		__stFrame.cmd_len = 2U;
		__stFrame.adr_len = 4U;

		__stProtocol.f_code.io_width = ospi_io_octal;
		__stProtocol.f_addr.io_width = ospi_io_octal;
		__stProtocol.f_data.io_width = ospi_io_octal;
	}

	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
#endif

	__stFrame.adr = dest_addr;
	__stFrame.dat = (uintptr_t)src;
	__stFrame.dat_len = size;

	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_write,
						&__stFrame,
						&__stProtocol);
}

SRAM_ATTR static void __fospi_check_wip_status_til_ready(void) {
    uint8_t status_reg;

    OSPI_INIT_FRAME_INFO(__stFrame);
    OSPI_INIT_FIELD_PROTOCOL(__stProtocol);

#ifdef BOOTLOADER
	__stFrame.cmd = 0x05U;
    __stFrame.cmd_len = 1U;
    __stFrame.dat = (uintptr_t)&status_reg;
    __stFrame.dat_len = 1U;

    __stProtocol.f_code.io_width = ospi_io_single;
    __stProtocol.f_data.io_width = ospi_io_single;
    __stProtocol.f_code.data_rate = ospi_data_rate_sdr;
    __stProtocol.f_data.data_rate = ospi_data_rate_sdr;
#else
	uint32_t flash_id = __find_flash_id();
	if (flash_id == MX_MX25U1632F_ID_) {
		__stFrame.cmd = CHIP_MXIC_MX25U1632F_RDSR;
		__stFrame.cmd_len = 1U;
		__stFrame.dat = (uintptr_t)&status_reg;
		__stFrame.dat_len = 1U;

		__stProtocol.f_code.io_width = ospi_io_quad;
		__stProtocol.f_data.io_width = ospi_io_quad;

		__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
	}
	else if (flash_id == MX_MX25U6345G_ID_) {
		__stFrame.cmd = CHIP_MXIC_MX25U6345G_RDSR;
		__stFrame.cmd_len = 2U;
		__stFrame.adr = 0;
		__stFrame.adr_len = 4U;
		__stFrame.dat = (uintptr_t)&status_reg;
		__stFrame.dat_len = 1U;
		__stFrame.dmy_cyc = 4U;

		__stProtocol.f_code.io_width = ospi_io_octal;
		__stProtocol.f_addr.io_width = ospi_io_octal;
		__stProtocol.f_data.io_width = ospi_io_octal;

		__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
	}
#endif

    do {
    	upt_ospi_transfer(
			up_ospi,
			&ospi_config, ospi_transfer_read,
			&__stFrame,
			&__stProtocol
		);
    } while (status_reg & 0x01U);
}

void fospi_4kerase(size_t offset) {

	__init_fospi();

	// Send write enabled.
	__fospi_write_control(1);

    OSPI_INIT_FRAME_INFO(__stFrame);
    OSPI_INIT_FIELD_PROTOCOL(__stProtocol);

    if ((flash_info.manufacturer == FLASH_MXIC_DEV) && (flash_info.flash_id == MX_MX25U6345G_ID)) {
        __stFrame.cmd = 0x21U;
        __stFrame.adr_len = 4U;
    }
    else {
        __stFrame.cmd = 0x20U;
        __stFrame.adr_len = 3U;
    }
    __stFrame.cmd_len = 1U;
    __stFrame.adr = offset;

    __stProtocol.f_code.io_width = ospi_io_single;
    __stProtocol.f_addr.io_width = ospi_io_single;
    __stProtocol.f_code.data_rate = ospi_data_rate_sdr;
    __stProtocol.f_addr.data_rate = ospi_data_rate_sdr;

    upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);

    __fospi_check_wip_status_til_ready();
}

#define PAGE_WARITE_SIZE 256
#define min_len(x, y) 	(x < y) ? (x) : (y)
void fospi_write(size_t dest_addr, const void *src, size_t size) {
	// Write one page (256 bytes) each time.
	while(size != 0) {
		int trans_size = min_len(size, PAGE_WARITE_SIZE);
		
		__init_fospi();
		
		// Send write enabled.
		__fospi_write_control(1);
		
		__fospi_write_data(dest_addr, src, trans_size);

		__fospi_check_wip_status_til_ready();

		size -= trans_size;
		dest_addr += trans_size;
		src += trans_size;
	}
}

void fospi_read(void * dest_addr, const size_t src, size_t size) {
	__init_fospi();

	OSPI_INIT_FRAME_INFO(__stFrame);
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);

	uint32_t flash_id = __find_flash_id();
	if (flash_id == MX_MX25U1632F_ID_) {
		__stFrame.cmd = CHIP_MXIC_MX25U1632F_QREAD;
		__stFrame.cmd_len = 1U;
		__stFrame.adr = OSPI_ADDRESS_3BYTE_MASK & src;
		__stFrame.adr_len = 3U;
		__stFrame.dmy_cyc = 10U;

		__stProtocol.f_code.io_width = ospi_io_quad;
		__stProtocol.f_addr.io_width = ospi_io_quad;
		__stProtocol.f_data.io_width = ospi_io_quad;
	}
	else if (flash_id == MX_MX25U6345G_ID_) {
		__stFrame.cmd = CHIP_MXIC_MX25U6345G_SOREAD;
		__stFrame.cmd_len = 2U;
		__stFrame.adr = OSPI_ADDRESS_4BYTE_MASK & src;
		__stFrame.adr_len = 4U;
		__stFrame.dmy_cyc = 20U;

		__stProtocol.f_code.io_width = ospi_io_octal;
		__stProtocol.f_addr.io_width = ospi_io_octal;
		__stProtocol.f_data.io_width = ospi_io_octal;
	}
	__stFrame.dat = (uintptr_t)dest_addr;
	__stFrame.dat_len = size;

	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;

	upt_ospi_transfer(up_ospi, &ospi_config, ospi_transfer_read, &__stFrame, &__stProtocol);
}

static void __MX_MX25U6345G_enterOPI() {
#ifdef MX25U6345G_DDR
	uint8_t cmd_data[1] = {0x02};	// DTR
#else
	uint8_t cmd_data[1] = {0x01};	// STR
#endif

	// Write configuration register 2 address=0x0 (OPI STR/DTR, W/O DQS).
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0x72;
	__stFrame.cmd_len = 1U;
	__stFrame.adr = 0x0U;
	__stFrame.adr_len = 4U;
	__stFrame.dat = (uintptr_t)cmd_data;
	__stFrame.dat_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_addr.io_width = ospi_io_single;
	__stProtocol.f_data.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_write,
						&__stFrame,
						&__stProtocol);
#ifdef MX25U6345G_DDR
	upt_ospi_dll_enable(up_ospi, 1, ospi_dll_45_degree);

	/* Keep setting to RTCMMB2/RTCMMB3 */
	/* Set DDR-OPI with DQS */
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB2) = (((0x01)<<24) | (0x728D));
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) = (((0x01)<<25) | ((0x1F)<<20) | ((0x01)<<19) | ((0x02)<<16));
	ospi_config.dqs_enable = 1;
#else
	/* Keep setting to RTCMMB2/RTCMMB3 */
	/* Set STR-OPI W/O DQS */
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB2) = (((0x01)<<24) | (0x728D));
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) = (((0x1F)<<20) | ((0x02)<<16));
#endif
}

static void __MX_MX25U6435F_enterQPI(void) {
	uint8_t cmd_data[1] = {0x40};

	// WRSR (Enable QE bit = 1).
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0x01;
	__stFrame.cmd_len = 1U;
	__stFrame.dat = (uintptr_t)cmd_data;
	__stFrame.dat_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_data.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_write,
						&__stFrame,
						&__stProtocol);

	__fospi_check_wip_status_til_ready();

	// EQIO.
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0x35U;	// MXIC enter QPI command
	__stFrame.cmd_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_io_single;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);

	// Keep setting to RTCMMB2/RTCMMB3.
	// Set SDR-QPI W/O DQS.
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB2) = 0xF5;							// MXIC leave QPI command
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) = (((0x1F)<<20) | ((0x01)<<16));	// Set QPI
}

static void __MX_MX25U1632F_enterQPI(void) {

	uint8_t cmd_data[2] = {0x40, 0xC0};

	// WRSR (Enable QE bit = 1 && DC0/DC1 = 11 for 133MHz 10 dummy cycles).
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0x01;
	__stFrame.cmd_len = 1U;
	__stFrame.dat = (uintptr_t)&cmd_data;
	__stFrame.dat_len = 2U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_data.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_write,
						&__stFrame,
						&__stProtocol);

	__fospi_check_wip_status_til_ready();

	// EQIO.
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0x35U;	// MXIC enter QPI command
	__stFrame.cmd_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);

	// Keep setting to RTCMMB2/RTCMMB3.
	// Set SDR-QPI W/O DQS.
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB2) = 0xF5;							// MXIC leave QPI command
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) = (((0x1F)<<20) | ((0x01)<<16));	// Set QPI
}

static void __WB_W25Q64FWSS_enterQPI(void) {

	uint8_t cmd_data[1] = {0x02};

	/* WRSR (Enable QE bit = 1) */
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0x31;
	__stFrame.cmd_len = 1U;
	__stFrame.dat = (uintptr_t)cmd_data;
	__stFrame.dat_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_data.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_write,
						&__stFrame,
						&__stProtocol);

	__fospi_check_wip_status_til_ready();

	// EQIO.
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0x38U;	// Windbond enter QPI command
	__stFrame.cmd_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);
	// Set read parameter P5/P4 = 11 for 104M 8 dummy cycles.
	cmd_data[0] = 0x30;
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0xC0U;	// Windbond enter Set read parameter command
	__stFrame.cmd_len = 1U;
	__stFrame.dat = (uintptr_t)cmd_data;
	__stFrame.dat_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_quad;
	__stProtocol.f_data.io_width = ospi_io_quad;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_write,
						&__stFrame,
						&__stProtocol);

	// Keep setting to RTCMMB2/RTCMMB3.
	// Set SDR-QPI W/O DQS.
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB2) = 0xFF;							// Windbond leave QPI command
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) = (((0x1F)<<20) | ((0x01)<<16));	// Set QPI
}

static void __WB_W25Q64JW_enterQPI(void) {
	uint8_t cmd_data[1] = {0x02};

	// WRSR (Enable QE bit = 1).
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0x31;
	__stFrame.cmd_len = 1U;
	__stFrame.dat = (uintptr_t)cmd_data;
	__stFrame.dat_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_data.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_write,
						&__stFrame,
						&__stProtocol);

	__fospi_check_wip_status_til_ready();

	// EQIO.
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0x38U;	// Windbond enter QPI command
	__stFrame.cmd_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);

	// Set read parameter P5/P4 = 11 for 104M 8 dummy cycles.
	cmd_data[0] = 0x30;
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0xC0U;	// Windbond enter Set read parameter command
	__stFrame.cmd_len = 1U;
	__stFrame.dat = (uintptr_t)cmd_data;
	__stFrame.dat_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_quad;
	__stProtocol.f_data.io_width = ospi_io_quad;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_write,
						&__stFrame,
						&__stProtocol);

	// Keep setting to RTCMMB2/RTCMMB3.
	// Set SDR-QPI W/O DQS.
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB2) = 0xFF;							// Windbond leave QPI command
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) = (((0x1F)<<20) | ((0x01)<<16));	// Set QPI
}

static void __GD_GD25LQ64CSI_enterQPI(void) {

	uint8_t cmd_data[2] = {0x00, 0x02};

	// WRSR (Enable QE bit = 1).
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0x01;
	__stFrame.cmd_len = 1U;
	__stFrame.dat = (uintptr_t)&cmd_data;
	__stFrame.dat_len = 2U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_data.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_write,
						&__stFrame,
						&__stProtocol);

	__fospi_check_wip_status_til_ready();

	// EQIO.
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0x38U;	// Windbond enter QPI command
	__stFrame.cmd_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_single;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_nd,
						&__stFrame,
						&__stProtocol);

	// Set read parameter P5/P4 = 11 for 133M 8 dummy cycles.
	cmd_data[0] = 0x30;
	OSPI_INIT_FRAME_INFO(__stFrame);
	__stFrame.cmd = 0xC0U;	// Windbond enter Set read parameter command
	__stFrame.cmd_len = 1U;
	__stFrame.dat = (uintptr_t)&cmd_data;
	__stFrame.dat_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
	__stProtocol.f_code.io_width = ospi_io_quad;
	__stProtocol.f_data.io_width = ospi_io_quad;
	__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(up_ospi,
						&ospi_config, ospi_transfer_write,
						&__stFrame,
						&__stProtocol);

	// Keep setting to RTCMMB2/RTCMMB3.
	// Set SDR-QPI W/O DQS.
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB2) = 0xFF;							// Windbond leave QPI command
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) = (((0x1F)<<20) | ((0x01)<<16));	// Set QPI
}

/* DO NOT FIX THE CODE SEQUENCE!!! */
void speedup_flash(void) {
	unsigned int dummy;

	__init_fospi();

	/* Write flash_id_index and metal_version to the shared data area. */
	MCUBOOT_LOG_DBG("%s: Writing shared data.", __func__);
	mcuboot_update_shared_data(FLASH_ID_INDEX, &flash_table_seq_num);
	mcuboot_update_shared_data(METAL_VERSION, &(uint32_t){ METAL_VERSION_NUM });

	// Slave0 base address is 0x60000000.
	unsigned int mmBaseAddress[4] = {0x60000000, 0, 0, 0};

	__fospi_write_control(1);/* Send write enabled */

	switch(flash_table_seq_num) {

	// WB/QPI/SDR/104M/8MB.
	case WB_W25Q64FWSS_ID_:
		/* AXI read settings */
		OSPI_INIT_FRAME_INFO(__stFrame);
		__stFrame.cmd = 0xEB;
		__stFrame.cmd_len = 1;
		__stFrame.adr_len = 3;
		__stFrame.dmy_cyc = 8;
		__stFrame.dat_len = 1U;
		OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
		__stProtocol.f_code.io_width = ospi_io_quad;
		__stProtocol.f_addr.io_width = ospi_io_quad;
		__stProtocol.f_data.io_width = ospi_io_quad;
		__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
		// 16MB size as default.
		upt_ospi_set_xip_conf(up_ospi,
								&ospi_config,
								ospi_mode_AXI_read,
								&__stFrame,
								&__stProtocol,
								(uint32_t *)mmBaseAddress,
								0xFC000000);
		__WB_W25Q64FWSS_enterQPI();
		// TODO: Adjust PLL to reach 104MHz.
		break;

	// WB/QPI/SDR/133M/2MB.
	case WB_W25Q64JW_ID_:
		/* AXI read settings */
		OSPI_INIT_FRAME_INFO(__stFrame);
		__stFrame.cmd = 0xEB;
		__stFrame.cmd_len = 1;
		__stFrame.adr_len = 3;
		__stFrame.dmy_cyc = 8;
		__stFrame.dat_len = 1U;
		OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
		__stProtocol.f_code.io_width = ospi_io_quad;
		__stProtocol.f_addr.io_width = ospi_io_quad;
		__stProtocol.f_data.io_width = ospi_io_quad;
		__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
		// 16MB size as default.
		upt_ospi_set_xip_conf(up_ospi,
								&ospi_config,
								ospi_mode_AXI_read,
								&__stFrame,
								&__stProtocol,
								(uint32_t *)mmBaseAddress,
								0xFC000000);
		__WB_W25Q64JW_enterQPI();

		// TODO: Adjust PLL to reach 133MHz.
		break;

	// GD/QPI/SDR/133M/8MB.
	case GD_GD25LQ64CSI_ID_:
		// AXI read settings.
		OSPI_INIT_FRAME_INFO(__stFrame);
		__stFrame.cmd = 0xEB;
		__stFrame.cmd_len = 1;
		__stFrame.adr_len = 3;
		__stFrame.dmy_cyc = 8;
		__stFrame.dat_len = 1U;
		OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
		__stProtocol.f_code.io_width = ospi_io_quad;
		__stProtocol.f_addr.io_width = ospi_io_quad;
		__stProtocol.f_data.io_width = ospi_io_quad;
		__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
		// 16MB size as default.
		upt_ospi_set_xip_conf(up_ospi,
								&ospi_config,
								ospi_mode_AXI_read,
								&__stFrame,
								&__stProtocol,
								(uint32_t *)mmBaseAddress,
								0xFC000000);
		__GD_GD25LQ64CSI_enterQPI();

		// TODO: Adjust PLL to reach 133MHz.
		break;

	// MXIC/OPI/DDR/DQS/150MHz/8MB.
	// MXIC/OPI/SDR/200MHz/8MB.
	// MXIC/OPI/SDR/150MHz/8MB.
	case MX_MX25U6345G_ID_:
		OSPI_INIT_FRAME_INFO(__stFrame);
#ifdef MX25U6345G_DDR
		__stFrame.cmd = 0xEE11;
#else
		__stFrame.cmd = 0xEC13;
#endif
		__stFrame.cmd_len = 2;
		__stFrame.adr_len = 4;
		__stFrame.dmy_cyc = 20;
		__stFrame.dat_len = 1U;
		OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
		__stProtocol.f_code.io_width = ospi_io_octal;
		__stProtocol.f_addr.io_width = ospi_io_octal;
		__stProtocol.f_data.io_width = ospi_io_octal;
#ifdef MX25U6345G_DDR
		__stProtocol.f_code.data_rate = ospi_data_rate_ddr;
		__stProtocol.f_addr.data_rate = ospi_data_rate_ddr;
		__stProtocol.f_data.data_rate = ospi_data_rate_ddr;
		ospi_config.dqs_enable = 1;
#else
		__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
#endif
		// 16MB size as default.
		upt_ospi_set_xip_conf(up_ospi,
								&ospi_config,
								ospi_mode_AXI_read,
								&__stFrame,
								&__stProtocol,
								(uint32_t *)mmBaseAddress,
								0xFC000000);
		ospi_config.dqs_enable = 0;
		__MX_MX25U6345G_enterOPI();

#ifndef MX25U6345G_SDR
		// Adjust PLL to reach 150MHz(Actually 149MHz).
		// PLL2 input clock is (11.0592MHz x N / n). OSPI is belong to GCRG1.
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_PLLFREQ1) = 53;	// N: Multiply by (53+1)
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_CMDEN) = 0x4;		// BIT2 FREQ incremental change
		dummy = *(volatile unsigned int *)0x20021004;																// Dummy instruction: Delay 30us
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_ODIVCH0) = 0x100;	// BIT7:enable bit, n: Divided by (0+1)
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_CMDEN) = 0x2;		// BIT1 change output clock
		dummy = *(volatile unsigned int *)0x20021004;
#ifdef MX25U6345G_DDR
		// Change.
		upt_ospi_init(up_ospi, ospi_div_4, ospi_phase_90);
#else
		upt_ospi_init(up_ospi, ospi_div_4, ospi_phase_180);
#endif
#else
		// Adjust PLL to reach 200MHz(Actually 199MHz).
		// PLL2 input clock is (11.0592MHz x N / n). OSPI is belong to GCRG1.
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_PLLFREQ1) = 35;	// N: Multiply by (35+1)
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_CMDEN) = 0x4;		// BIT2 FREQ incremental change
		dummy = *(volatile unsigned int *)0x20021004;																// Dummy instruction: Delay 30us
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_ODIVCH0) = 0x101;	// BIT7:enable bit, n: Divided by (1+1)
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_CMDEN) = 0x2;		// BIT1 change output clock
		dummy = *(volatile unsigned int *)0x20021004;
#endif
		break;

	// MXIC/QPI/SDR/133M/2MB.
	case MX_MX25U1632F_ID_:
		// AXI read settings.
		OSPI_INIT_FRAME_INFO(__stFrame);
		__stFrame.cmd = 0xEB;
		__stFrame.cmd_len = 1;
		__stFrame.adr_len = 3;
		__stFrame.dmy_cyc = 10;
		__stFrame.dat_len = 1U;
		OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
		__stProtocol.f_code.io_width = ospi_io_quad;
		__stProtocol.f_addr.io_width = ospi_io_quad;
		__stProtocol.f_data.io_width = ospi_io_quad;
		__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
		// 16MB size as default.
		upt_ospi_set_xip_conf(up_ospi,
								&ospi_config,
								ospi_mode_AXI_read,
								&__stFrame,
								&__stProtocol,
								(uint32_t *)mmBaseAddress,
								0xFC000000);
		__MX_MX25U1632F_enterQPI();

		// Adjust PLL to reach 133MHz(Actually 132MHz).
		// PLL2 input clock is (11.0592MHz x N / n). OSPI is belong to GCRG1.
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_PLLFREQ1) = 47;	// N: Multiply by (47+1)
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_CMDEN) = 0x4;		// BIT2 FREQ incremental change
		dummy = *(volatile unsigned int *)0x20021004;																// Dummy instruction: Delay 30us
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_ODIVCH0) = 0x103;	// BIT7:enable bit, n: Divided by (3+1)
		*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_GCRG1 + GCRG_CMDEN) = 0x2;		// BIT1 change output clock
		dummy = *(volatile unsigned int *)0x20021004;																// Dummy instruction: Delay 30us
		break;

	// MXIC/QPI/SDR/104M/8MB.
	case MX_MX25U6435F_ID_:
		// AXI read settings.
		OSPI_INIT_FRAME_INFO(__stFrame);
		__stFrame.cmd = 0xEB;
		__stFrame.cmd_len = 1;
		__stFrame.adr_len = 3;
		__stFrame.dmy_cyc = 6;
		__stFrame.dat_len = 1U;
		OSPI_INIT_FIELD_PROTOCOL(__stProtocol);
		__stProtocol.f_code.io_width = ospi_io_quad;
		__stProtocol.f_addr.io_width = ospi_io_quad;
		__stProtocol.f_data.io_width = ospi_io_quad;
		__stProtocol.f_code.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_addr.data_rate = ospi_data_rate_sdr;
		__stProtocol.f_data.data_rate = ospi_data_rate_sdr;
		// 16MB size as default.
		upt_ospi_set_xip_conf(up_ospi,
								&ospi_config,
								ospi_mode_AXI_read,
								&__stFrame,
								&__stProtocol,
								(uint32_t *)mmBaseAddress,
								0xFC000000);
		__MX_MX25U6435F_enterQPI();

		// TODO: Adjust PLL to reach 104MHz.
		break;

	case UN_UNKNOW_ID_:
		// Do nothing and return.
		return;
		break;

	default:
		// Do nothing and return.
		return;
		break;
	}
	upt_ospi_set_xip_boot_enable(up_ospi, 0);
}

int mcuboot_update_shared_data(Boot_shared_field_Type field, void *data) {
    if (data == NULL) {
        return -1; // null pointer input
    }

    // Update the target field
    switch (field) {
        case FLASH_ID_INDEX:
            BOOT_SHARED_DATA_PTR->flash_id_index = *(uint8_t *)data;
            break;

        case BOOT_TYPE:
            BOOT_SHARED_DATA_PTR->boot_type = *(uint32_t *)data;
            break;

		case METAL_VERSION:
            BOOT_SHARED_DATA_PTR->metal_version = *(uint32_t *)data;
            break;

        default:
            return -2; // invalid field
    }

    return 0;
}