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
#ifndef METAL_DRIVERS_RISCV_PLIC0_H
#define METAL_DRIVERS_RISCV_PLIC0_H
#include "metal.h"
#include "metal/compiler.h"
#include "metal/drivers/riscv_cpu.h"

#define METAL_PLIC_SOURCE_MASK 0x1F
#define METAL_PLIC_SOURCE_SHIFT 5
#define METAL_PLIC_SOURCE_PRIORITY_SHIFT 2
#define METAL_PLIC_SOURCE_PENDING_SHIFT 0

struct __metal_driver_vtable_riscv_plic0 {
    struct metal_interrupt_vtable plic_vtable;
};

__METAL_S_DECLARE_VTABLE(__metal_driver_vtable_riscv_plic0)

/**
 * @brief RISCV_PLIC return error code.
 * @ingroup UP301_Controller_RISCV_PLIC
 */
typedef enum enum_riscv_plic_retcode{
    E_RISCV_PLIC_SUCCESS,     // Success.
	E_RISCV_PLIC_INVINIT,	 	// Initial fail or resource is unavailable.
	E_RISCV_PLIC_INVPARA,	 	// Invalid function parameter/argument.
    E_RISCV_PLIC_ERROR,     	// Unspecific error.
} enum_riscv_plic_retcode_Type;

#define __METAL_MACHINE_MACROS
struct __metal_driver_riscv_plic0 {
    metal_interrupt_Type controller;
    uint32_t init_done;
    metal_interrupt_handler_t metal_exint_table[__METAL_PLIC_SUBINTERRUPTS];
    __metal_interrupt_data_Type metal_exdata_table[__METAL_PLIC_SUBINTERRUPTS];
};
#undef __METAL_MACHINE_MACROS

#endif
