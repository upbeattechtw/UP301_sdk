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
#include "metal/uart.h"

extern __inline__ uint32_t upt_uart_read_usr(metal_uart_Type *uart);

extern __inline__ enum_uart_br_Type upt_uart_init(metal_uart_Type *uart, enum_uart_br_Type baudrate, enum_uart_fcnt_Type autoflowctl);

extern __inline__ enum_uart_retcode_Type upt_uart_putc(metal_uart_Type *uart, int16_t c);

extern __inline__ enum_uart_retcode_Type upt_uart_putc_nonblocking(metal_uart_Type *uart, int16_t c);

extern __inline__ enum_uart_retcode_Type upt_uart_getc_nonblocking(metal_uart_Type *uart, int16_t *c);

extern __inline__ enum_uart_retcode_Type upt_uart_getc(metal_uart_Type *uart, int16_t *c);

extern __inline__ int16_t upt_uart_getc_timeout(metal_uart_Type *uart, int16_t *c, uint16_t timeout_cnt);

extern __inline__ int16_t upt_uart_printf(metal_uart_Type *uart, const char *f, ...);

extern __inline__ int16_t upt_uart_txready(metal_uart_Type *uart);

extern __inline__ int16_t upt_uart_rxready(metal_uart_Type *uart);

extern __inline__ enum_uart_retcode_Type upt_uart_isr_enable(metal_uart_Type *uart, enum_uart_isr_mode_Type mode);

extern __inline__ enum_uart_retcode_Type upt_uart_isr_disable(metal_uart_Type *uart, enum_uart_isr_disable_mode_Type mode);

extern __inline__ enum_uart_retcode_Type upt_uart_clear_fifo(metal_uart_Type *uart);

extern __inline__ void upt_uart_dma_enable(metal_uart_Type *uart, enum_uart_dma_mode_Type mode);

extern __inline__ enum_uart_retcode_Type upt_uart_set_watermark(metal_uart_Type *uart, enum_uart_watermark_Type watermark);

extern __inline__ enum_uart_retcode_Type upt_uart_set_rx_watermark(metal_uart_Type *uart, uart_rx_watermark_Type watermark);

extern __inline__ enum_uart_retcode_Type upt_uart_set_tx_watermark(metal_uart_Type *uart, uart_tx_watermark_Type watermark);

extern __inline__ uint32_t upt_uart_get_status(metal_uart_Type *uart);

extern __inline__ uint32_t upt_uart_get_lsr(metal_uart_Type *uart);

extern __inline__ void upt_uart_clear_status(metal_uart_Type *uart);

extern __inline__ enum_uart_retcode_Type upt_uart_set_timeout_ms(metal_uart_Type *uart, uint64_t timeout_ms); 

extern __inline__ uint64_t upt_uart_get_timeout_ms(metal_uart_Type *uart); 

metal_uart_Type *upt_uart_get_device(uint16_t device_num) {
#if __METAL_DT_MAX_UARTS > 0
    if (device_num < __METAL_DT_MAX_UARTS) {
        return (metal_uart_Type *)__metal_uart_table[device_num];
    }
#endif

    return NULL;
}
