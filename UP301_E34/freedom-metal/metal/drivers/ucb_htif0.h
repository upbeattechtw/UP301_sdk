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
#ifndef METAL__DRIVERS__UCB_HTIF0_H
#define METAL__DRIVERS__UCB_HTIF0_H
#include "metal/compiler.h"
#include "metal/shutdown.h"
#include "metal/uart.h"

struct __metal_driver_vtable_ucb_htif0_shutdown {
    const struct __metal_shutdown_vtable shutdown;
};

struct __metal_driver_vtable_ucb_htif0_uart {
    const struct metal_uart_vtable uart;
};

struct __metal_driver_ucb_htif0;

void __metal_driver_ucb_htif0_exit(const struct __metal_shutdown *test,
                                   int code) __attribute__((noreturn));

void __metal_driver_ucb_htif0_init(struct metal_uart *uart, int baud_rate);
int __metal_driver_ucb_htif0_putc(struct metal_uart *uart, int c);
int __metal_driver_ucb_htif0_getc(struct metal_uart *uart, int *c);
int __metal_driver_ucb_htif0_get_baud_rate(struct metal_uart *guart);
int __metal_driver_ucb_htif0_set_baud_rate(struct metal_uart *guart,
                                           int baud_rate);
struct metal_interrupt *
__metal_driver_ucb_htif0_interrupt_controller(struct metal_uart *uart);
int __metal_driver_ucb_htif0_get_interrupt_id(struct metal_uart *uart);

__METAL_DECLARE_VTABLE(__metal_driver_vtable_ucb_htif0_shutdown)

__METAL_DECLARE_VTABLE(__metal_driver_vtable_ucb_htif0_uart)

struct __metal_driver_ucb_htif0_shutdown {
    struct __metal_shutdown shutdown;
    const struct __metal_driver_vtable_ucb_htif0_shutdown *vtable;
};

struct __metal_driver_ucb_htif0_uart {
    struct metal_uart uart;
    const struct __metal_driver_vtable_ucb_htif0_uart *vtable;
};

#endif
