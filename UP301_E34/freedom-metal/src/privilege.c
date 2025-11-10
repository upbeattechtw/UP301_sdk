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
#include <metal/privilege.h>

#include <stddef.h>

#define METAL_MSTATUS_MIE_OFFSET 3
#define METAL_MSTATUS_MPIE_OFFSET 7
#define METAL_MSTATUS_SIE_OFFSET 1
#define METAL_MSTATUS_SPIE_OFFSET 5
#define METAL_MSTATUS_UIE_OFFSET 0
#define METAL_MSTATUS_UPIE_OFFSET 4

#define METAL_MSTATUS_MPP_OFFSET 11
#define METAL_MSTATUS_MPP_MASK 3

enum_privilege_retcode_Type metal_privilege_drop_to_mode(enum metal_privilege_mode mode,
                                  struct metal_register_file regfile,
                                  metal_privilege_entry_point_t entry_point) {
    uintptr_t mstatus;
    __asm__ volatile("csrr %0, mstatus" : "=r"(mstatus));

    /* Set xPIE bits based on current xIE bits */
    if (mstatus & (1 << METAL_MSTATUS_MIE_OFFSET)) {
        mstatus |= (1 << METAL_MSTATUS_MPIE_OFFSET);
    }
    else {
        mstatus &= ~(1 << METAL_MSTATUS_MPIE_OFFSET);
    }
    if (mstatus & (1 << METAL_MSTATUS_SIE_OFFSET)) {
        mstatus |= (1 << METAL_MSTATUS_SPIE_OFFSET);
    }
    else {
        mstatus &= ~(1 << METAL_MSTATUS_SPIE_OFFSET);
    }
    if (mstatus & (1 << METAL_MSTATUS_UIE_OFFSET)) {
        mstatus |= (1 << METAL_MSTATUS_UPIE_OFFSET);
    }
    else {
        mstatus &= ~(1 << METAL_MSTATUS_UPIE_OFFSET);
    }

    /* Set MPP to the requested privilege mode */
    mstatus &= ~(METAL_MSTATUS_MPP_MASK << METAL_MSTATUS_MPP_OFFSET);
    mstatus |= (mode << METAL_MSTATUS_MPP_OFFSET);

    __asm__ volatile("csrw mstatus, %0" ::"r"(mstatus));

    /* Set the entry point in MEPC */
    __asm__ volatile("csrw mepc, %0" ::"r"(entry_point));

    /* Set the register file */
    __asm__ volatile("mv ra, %0" ::"r"(regfile.ra));
    __asm__ volatile("mv sp, %0" ::"r"(regfile.sp));

    __asm__ volatile("mret");
    return E_PRIVILEGE_SUCCESS;
}
