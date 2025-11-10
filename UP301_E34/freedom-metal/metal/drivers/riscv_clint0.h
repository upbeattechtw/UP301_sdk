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
#ifndef METAL_DRIVERS_RISCV_CLINT0_H
#define METAL_DRIVERS_RISCV_CLINT0_H
#include "metal.h"
#include "metal/compiler.h"
#include "metal/drivers/riscv_cpu.h"
#include "metal/interrupt.h"

struct __metal_driver_vtable_riscv_clint0 {
    struct metal_interrupt_vtable clint_vtable;
};

__METAL_S_DECLARE_VTABLE(__metal_driver_vtable_riscv_clint0)

/**
 * @brief RISCV_CLINT return error code.
 * @ingroup UP301_Controller_RISCV_CLINT
 */
typedef enum enum_riscv_clint_retcode{
    E_RISCV_CLINT_SUCCESS,     // Success.
	E_RISCV_CLINT_INVINIT,	 	// Initial fail or resource is unavailable.
	E_RISCV_CLINT_INVPARA,	 	// Invalid function parameter/argument.
    E_RISCV_CLINT_ERROR,     	// Unspecific error.
} enum_riscv_clint_retcode_Type;

#define __METAL_MACHINE_MACROS
struct __metal_driver_riscv_clint0 {
    metal_interrupt_Type controller;
    int32_t init_done;
};
#undef __METAL_MACHINE_MACROS

#ifndef LOAD_SRAM_CODE
int32_t __metal_driver_riscv_clint0_command_request(
    metal_interrupt_Type *controller, uint32_t command, void *data) __attribute__ ((section (".FwHandler")));
#else
int32_t __metal_driver_riscv_clint0_command_request(
    metal_interrupt_Type *controller, uint32_t command, void *data);
#endif

#endif
