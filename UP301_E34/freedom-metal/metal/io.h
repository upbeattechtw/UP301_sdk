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

#ifndef METAL__IO_H
#define METAL__IO_H

/* This macro enforces that the compiler will not elide the given access. */
#define __METAL_ACCESS_ONCE(x) (*(__typeof__(*x) volatile *)(x))

/* Allows users to specify arbitrary fences. */
#define __METAL_IO_FENCE(pred, succ)                                           \
    __asm__ volatile("fence " #pred "," #succ ::: "memory");

/* Types that explicitly describe an address as being used for memory-mapped
 * IO.  These should only be accessed via __METAL_ACCESS_ONCE. */
typedef unsigned char __metal_io_u8;
typedef unsigned short __metal_io_u16;
typedef unsigned int __metal_io_u32;
#if __riscv_xlen >= 64
typedef unsigned long __metal_io_u64;
#endif

#endif
