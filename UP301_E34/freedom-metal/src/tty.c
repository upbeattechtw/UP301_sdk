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
#include "metal/init.h"
#include "metal/tty.h"
#include "metal/uart.h"

/* UART baudrate table and struct */
struct uart_strap_t {
    unsigned int strap_value;
    enum_uart_br_Type std_br;
};
static const struct uart_strap_t uart_div_table[] = {
		{0x0, uart_12000000_baudrate},	// 12M
		{0x1, uart_6000000_baudrate},	// 6M
		{0x2, uart_3000000_baudrate},	// 3M
		{0x3, uart_921600_baudrate}	// 0.921600M
};

unsigned int JTAG_SEL_SETTING;

/* SCU OTPAUTOLD3 */
#define OTP_UARTBAUD_EN				(0x1<<9)
#define OTP_UARTBAUD_BIT0 			(0x1<<10)
#define OTP_UARTBAUD_BIT1 			(0x1<<11)

/* SCU HWSTRAP */
#define REMAP_STRAP_BIT0 			(0x1)
#define REMAP_STRAP_BIT1 			(0x1<<1)
#define UART_STRAP_BIT0 			(0x1<<2)
#define UART_STRAP_BIT1 			(0x1<<3)
#define JTAG_STRAP					(0x1<<4)

#if defined(__METAL_DT_STDOUT_UART_HANDLE)
/* This implementation serves as a small shim that interfaces with the first
 * UART on a system. */
int metal_tty_putc(int c) {
#ifdef ROM_CODE 
#ifdef JTAG_UART_EN
    if(!JTAG_SEL_SETTING)
    	return 0;
#endif
    return upt_uart_putc(__METAL_DT_STDOUT_UART_HANDLE, c);
#else
    return upt_uart_putc(__METAL_DT_STDOUT_UART_HANDLE, c);
#endif
}

int metal_tty_getc(int *c) {
    do {
        upt_uart_getc(__METAL_DT_STDOUT_UART_HANDLE, (int16_t*)c);
        /* -1 means no key pressed, getc waits */
    } while (-1 == *c);
    return 0;
}

#ifndef __METAL_DT_STDOUT_UART_BAUD
#define __METAL_DT_STDOUT_UART_BAUD 115200
#endif

#ifdef ROM_CODE 
METAL_CONSTRUCTOR(metal_tty_init) {
	unsigned int uart_br_seting;
	/*** Check debug UART baudrate ***/
	if( (*(volatile unsigned int *)(METAL_UP_SCU_0_BASE_ADDRESS + METAL_UP_SCU_OTPAUTOLD3)) & OTP_UARTBAUD_EN ) {
		// Get OTP value and set baud-rate.
		uart_br_seting = ( (*(volatile unsigned int *)(METAL_UP_SCU_0_BASE_ADDRESS + METAL_UP_SCU_OTPAUTOLD3)) & (OTP_UARTBAUD_BIT0 + OTP_UARTBAUD_BIT1) )>>10;
	}
	else {
		// Get strap pin value and set baud-rate.
		uart_br_seting = ( (*(volatile unsigned int *)(METAL_UP_SCU_0_BASE_ADDRESS + METAL_UP_SCU_HWSTRAP)) & (UART_STRAP_BIT0 + UART_STRAP_BIT1) )>>2;
	}

	// Get strap pin value: 0=MP, 1=jtag
	JTAG_SEL_SETTING = ( (*(volatile unsigned int *)(METAL_UP_SCU_0_BASE_ADDRESS + METAL_UP_SCU_HWSTRAP)) & JTAG_STRAP)>>4;

	/***************************************************Debug configuration*******************************************************/
#ifdef UP_DEBUG
#ifdef JTAG_UART_EN
	if(JTAG_SEL_SETTING)
#endif
	{
		// Pin-mux to UART0 for sure
		(*(volatile unsigned int *)(METAL_UP_SCU_0_BASE_ADDRESS + METAL_UP_SCU_PINMUX3)) &= ~0x00FFFF00;
		// Look-up table: set baudrate.
		upt_uart_init(__METAL_DT_STDOUT_UART_HANDLE, uart_div_table[uart_br_seting].std_br, uart_flow_ctrl_dis);
	}
#endif
#else
#ifdef STDOUT_BAUD_12000000
#define STDOUT_BRD	uart_12000000_baudrate
#elif STDOUT_BAUD_6000000
#define STDOUT_BRD	uart_6000000_baudrate
#elif STDOUT_BAUD_3000000
#define STDOUT_BRD	uart_3000000_baudrate
#else /* STDOUT_BAUD_921600 */
#define STDOUT_BRD	uart_921600_baudrate
#endif

METAL_CONSTRUCTOR(metal_tty_init) {
    upt_uart_init(__METAL_DT_STDOUT_UART_HANDLE, STDOUT_BRD, uart_flow_ctrl_dis);
#endif
}
#else
/* This implementation of putc doesn't actually do anything, it's just there to
 * provide a shim that eats all the characters so we can ensure that everything
 * can link to metal_tty_putc. */
int nop_putc(int c) __attribute__((section(".text.metal.nop.putc")));
// Use a customizable NOP hint instruction so that a post-processor parser can
// look for this instruction, and use the value in a0 as the character to be
// printed.
int nop_putc(int c) {
    // The ABI states that c will be passed in a0. However, under an LTO
    // (link-time-optimizer), it may choose to optimize in ways that would
    // break this assumption.  We want to ensure that the passed argument is
    // truly in a0, for easier post-processing, and so there is a single
    // 32-bit opcode to match against.
    // So explicitly ensure that the argument is placed into a0 first.
    __asm__ volatile("mv a0, %0; slli x0,a0,0x11" ::"r"(c));
    return -1;
}
int metal_tty_putc(int c) __attribute__((weak, alias("nop_putc")));
#pragma message(                                                               \
    "There is no default output device, metal_tty_putc() will throw away all input.")
#endif
