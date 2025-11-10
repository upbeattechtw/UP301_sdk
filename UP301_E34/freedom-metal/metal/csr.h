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
#ifndef METAL__CSR_H
#define METAL__CSR_H
#include <stddef.h>
#include <stdint.h>

#include <metal/compiler.h>

/*!
 * @file csr.h
 * @brief A collection of APIs for get and set CSR registers
 */

/*!
 * @brief Read a given CSR register without checking validity of CSR offset
 * @param reg Register label or hex value offset to read from
 * @param value Variable name of uintprt_t type to get the value
 */
#define METAL_CPU_GET_CSR(reg, value)                                          \
    __asm__ volatile("csrr %0, " #reg : "=r"(value));

/*!
 * @brief Write to a given CSR register without checking validity of CSR offset
 * @param reg Register label or hex value offset to write to
 * @param value Variable name of uintprt_t type to set the value
 */
#define METAL_CPU_SET_CSR(reg, value)                                          \
    __asm__ volatile("csrw " #reg ", %0" : : "r"(value));

#endif // METAL__CSR_H
