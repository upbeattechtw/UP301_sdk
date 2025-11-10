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

/*!
 * @file shutdown.h
 * @brief API for shutting down a machine
 */
#ifndef METAL_SHUTDOWN_H
#define METAL_SHUTDOWN_H
#include <stdint.h>

typedef struct __metal_shutdown {
    const struct __metal_shutdown_vtable *vtable;
} __metal_shutdown_Type;

struct __metal_shutdown_vtable {
    void (*exit)(const __metal_shutdown_Type *sd, uint32_t code)
        __attribute__((noreturn));
};


__inline__ void __metal_shutdown_exit(const __metal_shutdown_Type *sd,
                                      uint32_t code) __attribute__((noreturn));
__inline__ void __metal_shutdown_exit(const __metal_shutdown_Type *sd,
                                      uint32_t code) {
    sd->vtable->exit(sd, code);
}

/*!
 * @brief The public METAL shutdown interface
 *
 * Shuts down the machine, if the machine enables an interface for
 * shutting down. When no interface is provided, will cause the machine
 * to spin indefinitely.
 *
 * @param code The return code to set. 0 indicates program success.
 */
void metal_shutdown(uint32_t code) __attribute__((noreturn));

#endif
