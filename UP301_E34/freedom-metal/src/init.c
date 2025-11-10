/*
 * Copyright (C) 2025 UpbeatTech Inc. All Rights Reserved
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This file contains code derived from software originally developed by SiFive, Inc.
 * Copyright 2018 SiFive, Inc
 * SPDX-License-Identifier: Apache-2.0
 *
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
#include <stdint.h>

#include "metal/init.h"
#include "metal-platform.h"

/****************************************************************
 * Following Header information is for temporary develop phase	*
*****************************************************************/
/* Reserved byte use */
#define RESERVED_AREA_BYTE(n_byte) char reserved_##var1[n_byte]

#ifdef BOOTLOADER
#define WARM_ADDR		0x60001070	//TODO: not implement for now
#define LOADER_ADDR		0x60001070
#define MAGIC_NUMBER	0x31305055

/* Bootloader header content */
struct Header_info_t {
	unsigned int warmboot_addr;
	unsigned int bootloader_addr;
	unsigned int bootloader_size;
	unsigned int magic_num;
	RESERVED_AREA_BYTE(32);
	unsigned char header_tail[64];
};
const struct Header_info_t bootloader_hder_buf __attribute__ ((section (".SecHheader"))) ={
	.warmboot_addr = WARM_ADDR,
	.bootloader_addr = LOADER_ADDR,
	.magic_num = MAGIC_NUMBER
};

#else
#define IMAGE_HEADER_OFFSET		0x1000
#define IMAGE_MAGIC				0x96F3B83D
#define IMAGE_LOADADDR			0x00000000
#define IMAGE_TLV_SIZE			0x0
#define IMAGE_IMG_SIZE			0x8B3C
#define IMAGE_FLAGS				0x0
#define IMAGE_IV_MAJOR			0x1
#define IMAGE_IV_MINOR			0x0
#define IMAGE_IV_REVERSION		0x0
#define IMAGE_IV_BUILD_NUM		0x0
#define IMAGE_PAD1				0x0

struct image_version {
	unsigned char iv_major;
	unsigned char iv_minor;
	uint16_t iv_reversion;
	uint32_t iv_build_num;
};

/* Image header content */
struct Header_info_t {
	uint32_t ih_magic;
	uint32_t ih_load_addr;
	uint16_t ih_hdr_size;
	uint16_t ih_protect_tlv_size;
	uint32_t ih_img_size;
	uint32_t ih_flags;
	struct image_version ih_ver;
	uint32_t _pad1;
};
const struct Header_info_t bootloader_hder_buf __attribute__ ((section (".SecHheader"))) ={
	.ih_magic = IMAGE_MAGIC,
	.ih_load_addr = IMAGE_LOADADDR,
	.ih_hdr_size = IMAGE_HEADER_OFFSET,
	.ih_protect_tlv_size = IMAGE_TLV_SIZE,
	.ih_img_size = IMAGE_IMG_SIZE,
	.ih_flags = IMAGE_FLAGS,
	.ih_ver.iv_major = IMAGE_IV_MAJOR,
	.ih_ver.iv_minor = IMAGE_IV_MINOR,
	.ih_ver.iv_reversion = IMAGE_IV_REVERSION,
	.ih_ver.iv_build_num = IMAGE_IV_BUILD_NUM,
	._pad1 = IMAGE_PAD1
};
#endif

/*
 * These function pointers are created by the linker script
 * in the .init_array section. The arrays defined by these
 * and end points are the set of functions defined by instances
 * of METAL_CONSTRUCTOR() and METAL_DESTRUCTOR().
 */
extern metal_constructor_t metal_constructors_start;
extern metal_constructor_t metal_constructors_end;
extern metal_destructor_t metal_destructors_start;
extern metal_destructor_t metal_destructors_end;

enum_init_retcode_Type metal_init(void) {
    /* Make sure the constructors only run once */
    static uint32_t init_done = 0;
    if (init_done) {
        return E_INIT_SUCCESS;
    }
    init_done = 1;

#ifdef METAL_SIFIVE_PL2CACHE0
    sifive_pl2cache0_init();
#endif /* METAL_SIFIVE_PL2CACHE0 */

#ifdef METAL_SIFIVE_CCACHE0
    sifive_ccache0_init();
#endif /* METAL_SIFIVE_CCACHE0 */

#ifdef METAL_SIFIVE_L2PF1
    /* Do L2 Stride Prefetcher initialization. */
    sifive_l2pf1_init();
#endif /* METAL_SIFIVE_L2PF1 */

    if (&metal_constructors_end <= &metal_constructors_start) {
        return E_INIT_INVPARA;
    }

    metal_constructor_t *funcptr = &metal_constructors_start;
    while (funcptr != &metal_constructors_end) {
        metal_constructor_t func = *funcptr;

        func();

        funcptr += 1;
    }
}

enum_init_retcode_Type metal_fini(void) {
    /* Make sure the destructors only run once */
    static uint32_t fini_done = 0;
    if (fini_done) {
        return E_INIT_SUCCESS;
    }
    fini_done = 1;

    if (&metal_destructors_end <= &metal_destructors_start) {
        return E_INIT_INVPARA;
    }

    metal_destructor_t *funcptr = &metal_destructors_start;
    while (funcptr != &metal_destructors_end) {
        metal_destructor_t func = *funcptr;

        func();

        funcptr += 1;
    }
}

/*
 * metal_init_run() and metal_fini_run() are marked weak so that users
 * can redefine them for their own purposes, including to no-ops
 * in the case that users don't want the metal constructors or
 * destructors to run.
 */

void metal_init_run(void) __attribute__((weak));
void metal_init_run(void) { metal_init(); }

void metal_fini_run(void) __attribute__((weak));
void metal_fini_run(void) { metal_fini(); }
