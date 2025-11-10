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

#ifndef METAL__COMPILER_H
#define METAL__COMPILER_H

#define __METAL_DECLARE_VTABLE(type) extern const struct type type;

#define __METAL_S_DECLARE_VTABLE(type) extern struct type type;

#define __METAL_DEFINE_VTABLE(type) const struct type type

#define __METAL_S_DEFINE_VTABLE(type) struct type type

#define ___METAL_BIT(n)	(0x1 << n)

#define __METAL_GET_FIELD(reg, mask)                                           \
    (((reg) & (mask)) / ((mask) & ~((mask) << 1)))

/* Set field with mask for a given value */
#define __METAL_SET_FIELD(reg, mask, val)                                      \
    (((reg) & ~(mask)) | (((val) * ((mask) & ~((mask) << 1))) & (mask)))

#define __METAL_MIN(a, b) ((a) < (b) ? (a) : (b))
#define __METAL_MAX(a, b) ((a) > (b) ? (a) : (b))

void _metal_trap(int ecode);

#endif /* METAL__COMPILER_H */
