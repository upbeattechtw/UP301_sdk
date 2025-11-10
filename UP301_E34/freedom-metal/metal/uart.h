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

/**
 * @file  uart.h
 * @brief API for Universal Asynchronous Receiver/Transmitter
 */
#ifndef METAL__UART_H
#define METAL__UART_H
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define UART_TIMEOUT_MS 100000
/**
 * @brief Device number of UART engine
 * @ingroup UP301_Controller_UART
 */
typedef enum enum_uart_device{
	NAON_UART_0		= 0,
	NAON_UART_1,
	NAON_UART_2,
	NAON_UART_3,			// No flow control pin
	AON_UART,
	UART_DEVICE_NUMBER_LAST
} enum_uart_device_Type;

/**
 * @brief Enums to set up UART baud rate
 * @ingroup UP301_Controller_UART
 */
typedef enum enum_uart_br {
	uart_115200_baudrate 	= 0,
	uart_230400_baudrate,
	uart_460800_baudrate,
	uart_921600_baudrate,
	uart_2000000_baudrate,
	uart_3000000_baudrate,
	uart_6000000_baudrate,
	uart_12000000_baudrate,
	uart_undefined_baudrate
} enum_uart_br_Type;


/**
 * @brief UART function of flow control
 * @ingroup UP301_Controller_UART
 */
typedef enum enum_uart_fcnt {
	uart_flow_ctrl_dis 	= 0,
	uart_flow_ctrl_en
} enum_uart_fcnt_Type;

/**
 * @brief Enums to set up UART dma mode
 * @ingroup UP301_Controller_UART
 */
typedef enum enum_uart_dma_mode {
	uart_dma_disable		= 0,
	uart_dma_tx_enable,
	uart_dma_rx_enable,
	uart_dma_txrx_enable
} enum_uart_dma_mode_Type;

/**
 * @brief Enums to set up UART isr mode
 * @ingroup UP301_Controller_UART
 */
typedef enum enum_uart_isr_mode {
	uart_isr_disable		= 0,
	uart_isr_tx_enable,
	uart_isr_rx_enable,
	uart_isr_tx_rx_both_enable
}enum_uart_isr_mode_Type;

typedef enum enum_uart_isr_disable_mode {
	uart_isr_tx_disable = 0,
	uart_isr_rx_disable,
	uart_isr_tx_rx_both_disable
}enum_uart_isr_disable_mode_Type;

/**
 * @brief Enums to set up UART dma mode
 * @ingroup UP301_Controller_UART
 */
typedef enum enum_uart_watermark{
	uart_watermark_rx_1_tx_empty 	= 0,
	uart_watermark_quarter,
	uart_watermark_half,
	UART_watermark_last_2
} enum_uart_watermark_Type;
typedef enum enum_uart_rx_watermark {
	uart_watermark_rx_1 = 0,
	uart_watermark_rx_quarter,
	uart_watermark_rx_half,
	UART_watermark_rx_last_2
}uart_rx_watermark_Type;
typedef enum enum_uart_tx_watermark {
	uart_watermark_tx_empty = 0,
	uart_watermark_tx_2,
	uart_watermark_tx_quarter,
	uart_watermark_tx_half
}uart_tx_watermark_Type;
/**
 * @brief uart return error code.
 * @ingroup UP301_Controller_UART
 */
typedef enum enum_uart_retcode {
    E_UART_SUCCESS,     // Success.
	E_UART_INVINIT,	 	// Initial fail or resource is unavailable.
	E_UART_INVPARA,	 	// Invalid function parameter/argument.
	E_UART_TIMEOUT,		// Timeout.
    E_UART_ERROR     	// Unspecific error.
} enum_uart_retcode_Type;

/** @brief Interrupt status: return value of upt_uart_get_status() */
#define uart_modem_status 						(0x0U)
/** @brief Interrupt status: return value of upt_uart_get_status() */
#define uart_no_interrupt_pending 				(0x1U)
/** @brief Interrupt status: return value of upt_uart_get_status() */
#define uart_thr_empty 							(0x2U)
/** @brief Interrupt status: return value of upt_uart_get_status() */
#define uart_received_available 				(0x4U)
/** @brief Interrupt status: return value of upt_uart_get_status() */
#define uart_receiver_line_status 				(0x6U)
/** @brief Interrupt status: return value of upt_uart_get_status() */
#define uart_busy_detect		 				(0x7U)
/** @brief Interrupt status: return value of upt_uart_get_status() */
#define uart_character_timeout					(0xCU)

/** @brief Interrupt line status: return value of upt_uart_get_lst() */
#define uart_dr 						(0x1U << 0) /* Data ready */
/** @brief Interrupt line status: return value of upt_uart_get_lst() */
#define uart_oe 						(0x1U << 1) /* Overrun error */
/** @brief Interrupt line status: return value of upt_uart_get_lst() */
#define uart_pe 						(0x1U << 2) /* Parity error */
/** @brief Interrupt line status: return value of upt_uart_get_lst() */
#define uart_fe 						(0x1U << 3) /* Framing error */
/** @brief Interrupt line status: return value of upt_uart_get_lst() */
#define uart_bi 						(0x1U << 4) /* Break interrupt error */
/** @brief Interrupt line status: return value of upt_uart_get_lst() */
#define uart_thre 						(0x1U << 5) /* Transmit holding empty */
/** @brief Interrupt line status: return value of upt_uart_get_lst() */
#define uart_temt 						(0x1U << 6) /* Transmitter empty */
/** @brief Interrupt line status: return value of upt_uart_get_lst() */
#define uart_rfe 						(0x1U << 7) /* Receiver FIFO error */
/** @brief Interrupt line status: return value of upt_uart_get_lst() */
#define uart_addr_rcvd 					(0x1U << 8) /* Address received */

#undef getc
#undef putc

/**
 * @brief Handle for a UART serial device
 */
typedef struct metal_uart {
    const struct __metal_uart_vtable *vtable;
} metal_uart_Type;

struct __metal_uart_vtable {
	uint32_t (*read_usr)(metal_uart_Type *uart);
    int16_t (*init)(metal_uart_Type *uart, uint32_t brd_i, uint32_t brd_f, enum_uart_fcnt_Type autoflowctl);
    enum_uart_retcode_Type (*putc)(metal_uart_Type *uart, int16_t c);
	enum_uart_retcode_Type (*putc_nonblocking)(metal_uart_Type *uart, int16_t c);
    int16_t (*pprintf)(metal_uart_Type *uart, const char *f, ...);
    int16_t (*txready)(metal_uart_Type *uart);
    int16_t (*rxready)(metal_uart_Type *uart);
    enum_uart_retcode_Type (*getc)(metal_uart_Type *uart, int16_t *c);
	enum_uart_retcode_Type (*getc_nonblocking)(metal_uart_Type *uart, int16_t *c);
    int16_t (*getc_timeout)(metal_uart_Type *uart, int16_t *c, uint16_t timeout_cnt);
    int16_t (*get_baud_rate)(metal_uart_Type *uart);
    int16_t (*set_baudrate_div)(metal_uart_Type *uart, uint32_t brd_i, uint32_t brd_f);
    struct metal_interrupt *(*controller_interrupt)(metal_uart_Type *uart);
    int16_t (*get_interrupt_id)(metal_uart_Type *uart);
    enum_uart_retcode_Type (*interrupt_enable)(metal_uart_Type *uart, enum_uart_isr_mode_Type mode);
	enum_uart_retcode_Type (*interrupt_disable)(metal_uart_Type *uart, enum_uart_isr_disable_mode_Type mode);
	enum_uart_retcode_Type (*clear_fifo)(metal_uart_Type *uart);
    enum_uart_retcode_Type (*set_tx_watermark)(metal_uart_Type *uart, size_t level);
    size_t (*get_tx_watermark)(metal_uart_Type *uart);
    enum_uart_retcode_Type (*set_rx_watermark)(metal_uart_Type *uart, size_t level);
    size_t (*get_rx_watermark)(metal_uart_Type *uart);
    enum_uart_retcode_Type (*flowctl_enable)(metal_uart_Type *uart);
    enum_uart_retcode_Type (*flowctl_disable)(metal_uart_Type *uart);
    uint32_t (*get_status_iir)(metal_uart_Type *uart);
    uint32_t (*get_status_lsr)(metal_uart_Type *uart);
	enum_uart_retcode_Type (*set_timeout_ms)(metal_uart_Type *uart, uint64_t timeout_ms);
	uint64_t (*get_timeout_ms) (metal_uart_Type *uart);
};

/**
 * @brief Get a handle for a UART device
 * @param[in] device_num The index of the desired UART device
 * @return A handle to the UART device, or NULL if the device does not exist
 */
metal_uart_Type *upt_uart_get_device(uint16_t device_num);

/**
 * @brief read and clear uart status.
 * @param[in] uart The UART handle.
 * @return usr value.
 */
__inline__ uint32_t upt_uart_read_usr(metal_uart_Type *uart)
{
	return uart->vtable->read_usr(uart);
}

/**
 * @brief Initialize UART device
 * @details Initialize the UART device described by the UART handle. This function must
 * be called before any other method on the UART can be invoked.
 * @param[in] uart The UART handle
 * @param[in] baudrate The baud rate to be set
 * @param[in] autoflowctl Enable/Disable UART auto flow control
 * @return UART baudrate
 */
__inline__ enum_uart_br_Type upt_uart_init(metal_uart_Type *uart, enum_uart_br_Type baudrate, enum_uart_fcnt_Type autoflowctl) {
	int16_t i = 0x0000;
	uint32_t brd_i = 0x0000, brd_f = 0x0000;

	uint32_t NAON_baudrate_table[uart_undefined_baudrate][2] = {{120,0},//uart_115200_baudrate
																{60,0},//uart_230400_baudrate
																{30,0},//uart_460800_baudrate
																{15,0},//uart_921600_baudrate
																{6,29},//uart_2000000_baudrate
																{4,19},//uart_3000000_baudrate
																{2,10},//uart_6000000_baudrate
																{1,5}//uart_12000000_baudrate
														   };

	for(i = 0; i < UART_DEVICE_NUMBER_LAST; i++) {
		if( uart == upt_uart_get_device(i))
			break;
		else if (i == AON_UART)
			return uart_undefined_baudrate;
	}

	// AON UART src_clock = 1.8432MHz
	// 1.8432MHz /16 = 0.1152KHz
	if(i > NAON_UART_3) {
		if(baudrate == uart_115200_baudrate) {
			brd_i = 1; brd_f = 0;
		}
		else
			return uart_undefined_baudrate;
	}
	// AON UART src_clock = 221.184MHz
	else {

		if((baudrate>=uart_115200_baudrate)&&(baudrate<uart_undefined_baudrate)){
			brd_i = NAON_baudrate_table[baudrate][0];
			brd_f = NAON_baudrate_table[baudrate][1];
		}

	}
    return (enum_uart_br_Type)uart->vtable->init(uart, brd_i, brd_f, autoflowctl);
}

/**
 * @brief Output a character over the UART
 * @param[in] uart The UART handle
 * @param[in] c The character to send over the UART
 * @return enum_uart_retcode_Type value.
 */
__inline__ enum_uart_retcode_Type upt_uart_putc(metal_uart_Type *uart, int16_t c) {
	int16_t i;

	return uart->vtable->putc(uart, c);
}
__inline__ enum_uart_retcode_Type upt_uart_putc_nonblocking(metal_uart_Type *uart, int16_t c) {
	int16_t i;

	return uart->vtable->putc_nonblocking(uart, c);
}

/**
 * @brief Read a character over the UART without timeout
 * @param[in] uart The UART handle
 * @param[in] c The variable to hold the read character
 * @return 0 if get a char from FIFO successfully
 */
__inline__ enum_uart_retcode_Type upt_uart_getc(metal_uart_Type *uart, int16_t *c) {
    return uart->vtable->getc(uart, c);
}

__inline__ enum_uart_retcode_Type upt_uart_getc_nonblocking(metal_uart_Type *uart, int16_t *c) {
    return uart->vtable->getc_nonblocking(uart, c);
}
/**
 * @brief Read a character sent over the UART with timeout mechanism
 * @param[in] uart The UART handle
 * @param[in] c The variable to hold the read character
 * @param[in] timeout_cnt timeout value
 * @return 0 upon success, -1 means timeout
 */
__inline__ int16_t upt_uart_getc_timeout(metal_uart_Type *uart, int16_t *c, uint16_t timeout_cnt) {
    return uart->vtable->getc_timeout(uart, c, timeout_cnt);
}

/**
 * @brief Output string over the UART
 * @param[in] uart The UART handle
 * @param[in] *f The string to send over the UART
 * @return 0 upon success
 */
__inline__ int16_t upt_uart_printf(metal_uart_Type *uart, const char *f, ...) {
    return uart->vtable->pprintf(uart, f);
}

/**
 * @brief Presents UART TX FIFO is ready or not(empty)
 * @param[in] uart The UART handle
 * @return 1 if FIFO is available
 */
__inline__ int16_t upt_uart_txready(metal_uart_Type *uart) {
    return uart->vtable->txready(uart);
}

/**
 * @brief Presents UART RX FIFO is ready or not(full/busy)
 * @param[in] uart The UART handle
 * @return 1 FIFO is available
 */
__inline__ int16_t upt_uart_rxready(metal_uart_Type *uart) {
    return uart->vtable->rxready(uart);
}

/**
 * @brief Enable the UART transmit/receive interrupt
 * @param[in] uart The UART handle
 * @param[in] mode Set interrupt to UART tx/rx function
 * @return enum_uart_retcode_Type value.
 */
__inline__ enum_uart_retcode_Type upt_uart_isr_enable(metal_uart_Type *uart, enum_uart_isr_mode_Type mode) {
    return uart->vtable->interrupt_enable(uart, mode);
}

/**
 * @brief Disable the UART transmit/receive interrupt
 * @param[in] uart The UART handle
 * @param[in] mode Set interrupt to UART tx/rx function
 * @return enum_uart_retcode_Type value.
 */
__inline__ enum_uart_retcode_Type upt_uart_isr_disable(metal_uart_Type *uart, enum_uart_isr_disable_mode_Type mode) {
    return uart->vtable->interrupt_disable(uart, mode);
}

/**
 * @brief Reset UART FIFO
 * @param[in] uart The UART handle
 * @return enum_uart_retcode_Type value.
 */
__inline__ enum_uart_retcode_Type upt_uart_clear_fifo(metal_uart_Type *uart) {
	return uart->vtable->clear_fifo(uart);
}

/**
 * @brief Enable/Disable the UART transmit/receive interrupt
 * @param[in] uart The UART handle
 * @param[in] mode Set dma enable/disable to UART
 * @remarks No return value
 */
__inline__ void upt_uart_dma_enable(metal_uart_Type *uart, enum_uart_dma_mode_Type mode) {
	/* Not need to implement */
}

/**
 * @brief Set the transmit/receive watermark level to the UART controller
 * @param[in] uart The UART handle
 * @param[in] watermark The UART transmit watermark level
 * @return enum_uart_retcode_Type value.
 */
__inline__ enum_uart_retcode_Type upt_uart_set_watermark(metal_uart_Type *uart, enum_uart_watermark_Type watermark) {

	/* For RX */
	uart->vtable->set_rx_watermark(uart, watermark);

	/* For TX */
	if(watermark == UART_watermark_last_2) {
		return uart->vtable->set_tx_watermark(uart, 1);
	} else if(watermark != 0) {
		return uart->vtable->set_tx_watermark(uart, (watermark+1)&0x3);
	} else {
		return uart->vtable->set_tx_watermark(uart, watermark);
	}
}

__inline__ enum_uart_retcode_Type upt_uart_set_rx_watermark(metal_uart_Type *uart, uart_rx_watermark_Type watermark) {
	return uart->vtable->set_rx_watermark(uart, watermark);
}

__inline__ enum_uart_retcode_Type upt_uart_set_tx_watermark(metal_uart_Type *uart, uart_tx_watermark_Type watermark) {
	return uart->vtable->set_tx_watermark(uart, watermark);
}

/**
 * @brief Get all status of UART
 * @param uart The UART handle
 * @return Status of UART
 */
__inline__ uint32_t upt_uart_get_status(metal_uart_Type *uart) {
	return uart->vtable->get_status_iir(uart);
}

/**
 * @brief Get line status of UART
 * @param uart The UART handle
 * @return Line status of UART
 */
__inline__ uint32_t upt_uart_get_lsr(metal_uart_Type *uart) {
	return uart->vtable->get_status_lsr(uart);
}

/**
 * @brief Clear all status of UART
 * @param uart The UART handle
 * @remarks No return value
 */
__inline__ void upt_uart_clear_status(metal_uart_Type *uart) {
	/* Not need to implement */
}

/**
 * @brief set UART timeout ms
 * @param[in] uart The UART handle
 * @param[in] timeout UART timeout ms
 * @remarks No return value
 */
__inline__ enum_uart_retcode_Type upt_uart_set_timeout_ms(metal_uart_Type *uart, uint64_t timeout_ms) {
	return uart->vtable->set_timeout_ms(uart, timeout_ms);
}

/**
 * @brief get UART timeout ms
 * @param[in] uart The UART handle
 * @remarks UART timeout ms
 */
__inline__ uint64_t upt_uart_get_timeout_ms(metal_uart_Type *uart) {
	return uart->vtable->get_timeout_ms(uart);
}

#endif //#ifndef METAL__UART_H
