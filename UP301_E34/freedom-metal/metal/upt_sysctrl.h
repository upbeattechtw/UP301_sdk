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

/**
 * @file upt_sysctrl.h
 * @brief API for UPT system control
 */
#ifndef __UPT_SYSCTRL_H__
#define __UPT_SYSCTRL_H__

#include <stdint.h>

/*
 * Shared data between bootloader and application.
 */

/* Reserved byte use */
#define RSVD_BYTE(n_byte)   uint8_t rsvd_##n_byte[n_byte]

typedef enum {
    FLASH_ID_INDEX,
    BOOT_TYPE,
    METAL_VERSION,
} Boot_shared_field_Type;

typedef struct {
    uint8_t  flash_id_index;    // 1 byte
    RSVD_BYTE(3);               // 3 1-bytes reserved
    uint32_t boot_type;         // 4 bytes
    uint32_t metal_version;     // 4 bytes
    RSVD_BYTE(244);             // reserved
} Boot_shared_data_Type;

#define BOOT_SHARED_DATA_ADDR   0x5017FE00UL
#define BOOT_SHARED_DATA_PTR    ((volatile Boot_shared_data_Type *) BOOT_SHARED_DATA_ADDR)

/*
 * Metal version number.
 */
#define METAL_VERSION_MAJOR     1   // 2 bytes
#define METAL_VERSION_MINOR     0   // 1 bytes
#define METAL_VERSION_PATCH     0   // 1 bytes
#define METAL_VERSION_NUM       ((METAL_VERSION_MAJOR << 16) | (METAL_VERSION_MINOR << 8) | METAL_VERSION_PATCH)
#define IS_SAME_METAL_VERSION   ((BOOT_SHARED_DATA_PTR)->metal_version == METAL_VERSION_NUM)

/*
 * UP301 memory access restriction workaround.
 */
#ifdef UP301_MEM_ACCESS_ISSUE
// Tail 256 bytes of L2 SRAM4, reserved for memory access restriction of peripherals.
#define	RSVD_TAIL_256B_PTR  0x5017FF00UL
#define FLASH_BASE_ADDR		0x60000000UL
#define FLASH_END_ADDR		0x70000000UL
#endif

/*
 * Attribute for `.FwHandler` section.
 */
#ifndef LOAD_SRAM_CODE
	#define SRAM_ATTR __attribute__ ((section (".FwHandler")))
#else
	#define SRAM_ATTR
#endif

#endif // __UPT_SYSCTRL_H__
