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
#include "metal.h"
#include "metal/shutdown.h"

extern __inline__ void __metal_shutdown_exit(const __metal_shutdown_Type *sd,
                                             uint32_t code);

#if defined(__METAL_DT_SHUTDOWN_HANDLE)
void metal_shutdown(uint32_t code) {
    __metal_shutdown_exit(__METAL_DT_SHUTDOWN_HANDLE, code);
}
#else
#pragma message(                                                               \
    "There is no defined shutdown mechanism, metal_shutdown() will spin.")
void metal_shutdown(uint32_t code) {
    while (1) {
        __asm__ volatile("nop");
    }
}
#endif
