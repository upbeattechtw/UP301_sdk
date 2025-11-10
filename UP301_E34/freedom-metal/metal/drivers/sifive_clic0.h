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

#ifndef METAL_DRIVERS_SIFIVE_CLIC0_H
#define METAL_DRIVERS_SIFIVE_CLIC0_H
#include "metal/compiler.h"
#include "metal/drivers/riscv_cpu.h"

#define METAL_CLIC_MAX_NMBITS 2
#define METAL_CLIC_MAX_NLBITS 8
#define METAL_CLIC_MAX_NVBITS 1

#define METAL_SIFIVE_CLIC0_CLICCFG_NMBITS_MMODE 0x00
#define METAL_SIFIVE_CLIC0_CLICCFG_NMBITS_SMODE1 0x20
#define METAL_SIFIVE_CLIC0_CLICCFG_NMBITS_SMODE2 0x40
#define METAL_SIFIVE_CLIC0_CLICCFG_NMBITS_MASK 0x60
#define METAL_SIFIVE_CLIC0_CLICCFG_NLBITS_MASK 0x1E
#define METAL_SIFIVE_CLIC0_CLICCFG_NVBIT_MASK 0x01

#define METAL_CLIC_ICTRL_SMODE1_MASK 0x7F /* b8 set imply M-mode */
#define METAL_CLIC_ICTRL_SMODE2_MASK 0x3F /* b8 set M-mode, b7 clear U-mode */

#define METAL_MAX_INTERRUPT_LEVEL ((1 << METAL_CLIC_MAX_NLBITS) - 1)

struct __metal_driver_vtable_sifive_clic0 {
    struct metal_interrupt_vtable clic_vtable;
};

__METAL_DECLARE_VTABLE(__metal_driver_vtable_sifive_clic0)

#define __METAL_MACHINE_MACROS
#include "metal.h"
struct __metal_driver_sifive_clic0 {
    metal_interrupt_Type controller;
    uint32_t init_done;
    struct {
    } __attribute__((aligned(64)));
    metal_interrupt_vector_handler_t
        metal_mtvt_table[__METAL_CLIC_SUBINTERRUPTS];
    __metal_interrupt_data_Type metal_exint_table[__METAL_CLIC_SUBINTERRUPTS];
};
#undef __METAL_MACHINE_MACROS

uint32_t __metal_driver_sifive_clic0_command_request(
    metal_interrupt_Type *controller, uint32_t command, void *data);

#endif
