/* Copyright 2024 Upbeat, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__DRIVERS__UP_UART_H
#define METAL__DRIVERS__UP_UART_H
#include "metal/compiler.h"
#include "metal/io.h"
#include "metal/uart.h"

struct __metal_driver_vtable_up_uart {
    const struct __metal_uart_vtable uart;
};

struct __metal_driver_up_uart;

__METAL_DECLARE_VTABLE(__metal_driver_vtable_up_uart)

struct __metal_driver_up_uart {
    metal_uart_Type uart;
    uint32_t baud_rate;
    uint64_t timeout_ms;
};

#endif
