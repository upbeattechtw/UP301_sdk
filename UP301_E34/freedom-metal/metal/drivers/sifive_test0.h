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
#ifndef METAL_DRIVERS_SIFIVE_TEST0_H
#define METAL_DRIVERS_SIFIVE_TEST0_H
#include "metal/compiler.h"
#include "metal/shutdown.h"

struct __metal_driver_vtable_sifive_test0 {
    const struct __metal_shutdown_vtable shutdown;
};

__METAL_DECLARE_VTABLE(__metal_driver_vtable_sifive_test0)

struct __metal_driver_sifive_test0 {
    __metal_shutdown_Type shutdown;
};

#endif
