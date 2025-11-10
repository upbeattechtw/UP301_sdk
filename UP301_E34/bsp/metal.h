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

#ifndef ASSEMBLY
#include "metal-platform.h"

#ifdef __METAL_MACHINE_MACROS

#ifndef MACROS_IF_METAL_H
#define MACROS_IF_METAL_H

#define __METAL_CLINT_NUM_PARENTS 2

#ifndef __METAL_CLINT_NUM_PARENTS
#define __METAL_CLINT_NUM_PARENTS 0
#endif
#define __METAL_PLIC_SUBINTERRUPTS 129

#define __METAL_PLIC_NUM_PARENTS 1

#ifndef __METAL_PLIC_SUBINTERRUPTS
#define __METAL_PLIC_SUBINTERRUPTS 0
#endif
#ifndef __METAL_PLIC_NUM_PARENTS
#define __METAL_PLIC_NUM_PARENTS 0
#endif
#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#endif /* MACROS_IF_METAL_H*/

#else /* ! __METAL_MACHINE_MACROS */

#ifndef MACROS_ELSE_METAL_H
#define MACROS_ELSE_METAL_H

#define __METAL_CLINT_2000000_INTERRUPTS 2

#define METAL_MAX_CLINT_INTERRUPTS 2

#define __METAL_CLINT_NUM_PARENTS 2

#define __METAL_INTERR_metal_CONTROLLER_C000000_INTERRUPTS 1

#define __METAL_PLIC_SUBINTERRUPTS 129

#define METAL_MAX_PLIC_INTERRUPTS 1

#define __METAL_PLIC_NUM_PARENTS 1

#define __METAL_CLIC_SUBINTERRUPTS 0
#define METAL_MAX_CLIC_INTERRUPTS 0

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 16

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 16

#define __METAL_GLOBAL_EXTERNAL_INTERRUPTS_INTERRUPTS 127

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 127

#define METAL_MAX_SIMUART_INTERRUPTS 0

// GPIO
#define ___metal_GPIO0_200B4000_INTERRUPTS 45

#define ___metal_GPIO1_20088000_INTERRUPTS 30

#define ___metal_GPIO2_20010000_INTERRUPTS 21

// UART
#define ___metal_SERIAL0_200A4000_INTERRUPTS 1

#define ___metal_SERIAL1_200A5000_INTERRUPTS 1

#define ___metal_SERIAL2_20080000_INTERRUPTS 1

#define ___metal_SERIAL3_20081000_INTERRUPTS 1

#define ___metal_SERIAL0_20005000_INTERRUPTS 1

// OSPI
#define ___metal_OSPI0_200A0000_INTERRUPTS 1

// Dual-timer
#define ___metal_GTIMER01_20096000_INTERRUPTS 2

#define ___metal_GTIMER23_20097000_INTERRUPTS 2

#define ___metal_GTIMER45_20098000_INTERRUPTS 2

#define ___metal_GTIMER67_20099000_INTERRUPTS 2

#define ___metal_GTIMER01_2000D000_INTERRUPTS 2

#define ___metal_GTIMER23_2000E000_INTERRUPTS 2

#define ___metal_GTIMER01_20025000_INTERRUPTS 2

#define ___metal_GTIMER01_20026000_INTERRUPTS 2

#define ___metal_GTIMER01_20028000_INTERRUPTS 1

// I2C
#define ___metal_I2C0_200A9000_INTERRUPTS 1

#define ___metal_I2C1_200AA000_INTERRUPTS 1

#define ___metal_I2C2_200AB000_INTERRUPTS 1

#define ___metal_I2C3_20084000_INTERRUPTS 1

#define ___metal_I2C4_20085000_INTERRUPTS 1

#define ___metal_I2C5_20086000_INTERRUPTS 1

#define ___metal_I2C6_20087000_INTERRUPTS 1

#define ___metal_I2C0_20008000_INTERRUPTS 1

#define ___metal_I2C1_20009000_INTERRUPTS 1

#define ___metal_I2C2_2000A000_INTERRUPTS 1

#define ___metal_I2C3_2000B000_INTERRUPTS 1

#define ___metal_I2C4_2000C000_INTERRUPTS 1

// PWM
#define ___metal_PWM0_20095000_INTERRUPTS 4

#define _metal_MAX_PWM0_20095000_NCMP 4

#define ___metal_PWM0_20024000_INTERRUPTS 1

#define _metal_MAX_PWM0_20024000_NCMP 1

// RTC
#define ___metal_RTC0_20021000_INTERRUPTS 1

#include "metal/drivers/riscv_clint0.h"
#include "metal/drivers/riscv_cpu.h"
#include "metal/drivers/riscv_plic0.h"
#include "metal/drivers/sifive_buserror0.h"
#include "metal/drivers/sifive_global-external-interrupts0.h"
#include "metal/drivers/sifive_local-external-interrupts0.h"
#include "metal/drivers/sifive_test0.h"
#include "metal/drivers/up_adc.h"
#include "metal/drivers/up_dma.h"
#include "metal/drivers/up_gpio.h"
#include "metal/drivers/up_gtimer.h"
#include "metal/drivers/up_i2c.h"
#include "metal/drivers/up_i2s.h"
#include "metal/drivers/up_img.h"
#include "metal/drivers/up_ospi.h"
#include "metal/drivers/up_pdm.h"
#include "metal/drivers/up_pwm.h"
#include "metal/drivers/up_rtc.h"
#include "metal/drivers/up_sif.h"
#include "metal/drivers/up_spi.h"
#include "metal/drivers/up_ts.h"
#include "metal/drivers/up_uart.h"
#include "metal/drivers/up_udl.h"
#include "metal/drivers/up_wdt.h"
#include "metal/drivers/up_dsp.h"
#include "metal/memory.h"
#include "metal/pmp.h"

extern struct metal_memory __metal_dt_mem_testram_20000000;

extern struct metal_memory __metal_dt_mem_testram_40000000;

extern struct metal_memory __metal_dt_mem_dtim_80000000;

extern struct metal_memory __metal_dt_mem_itim_1800000;

// From clint@2000000.
extern struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000;

// From cpu@0.
extern struct __metal_driver_cpu __metal_dt_cpu_0;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller;

// From interr_metal_controller@c000000.
extern struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000;

extern struct metal_pmp __metal_dt_pmp;

// From bus_error_unit@1700000.
extern struct metal_buserror __metal_dt_bus_error_unit_1700000;

// From local_external_interrupts_0.
extern struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0;

// From global_external_interrupts.
extern struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts;

// From teststatus@4000.
extern struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000;

// From sys_gpio@200B4000.
extern struct __metal_driver_up_gpio __metal_dt_gpio_200B4000;


// From peri_gpio@20088000.
extern struct __metal_driver_up_gpio __metal_dt_gpio_20088000;

// From aon_gpio@20010000.
extern struct __metal_driver_up_gpio __metal_dt_gpio_20010000;

// From rtcm_gpio@20020000.
extern struct __metal_driver_up_gpio __metal_dt_gpio_20020000;

// From serial@200A4000.
extern struct __metal_driver_up_uart __metal_dt_serial_200A4000;

// From serial@200A5000.
extern struct __metal_driver_up_uart __metal_dt_serial_200A5000;

// From serial@20080000.
extern struct __metal_driver_up_uart __metal_dt_serial_20080000;

// From serial@20081000.
extern struct __metal_driver_up_uart __metal_dt_serial_20081000;

// From serial@20005000.
extern struct __metal_driver_up_uart __metal_dt_serial_20005000;

// From ospi@200A0000.
extern struct __metal_driver_up_ospi __metal_dt_ospi_200A0000;

// From gtimer@20096000.
extern struct __metal_driver_up_gtimer __metal_dt_gtimer_20096000;	//NAON DUAL TIMER0,1

// From gtimer@20097000.
extern struct __metal_driver_up_gtimer __metal_dt_gtimer_20097000;	//NAON DUAL TIMER2,3

// From gtimer@20098000.
extern struct __metal_driver_up_gtimer __metal_dt_gtimer_20098000;	//NAON DUAL TIMER4,5

// From gtimer@20099000.
extern struct __metal_driver_up_gtimer __metal_dt_gtimer_20099000;	//NAON DUAL TIMER6,7

// From gtimer@2000D000.
extern struct __metal_driver_up_gtimer __metal_dt_gtimer_2000D000;	//DUAL AON_TIMER0,1

// From gtimer@2000E000.
extern struct __metal_driver_up_gtimer __metal_dt_gtimer_2000E000;		//DUAL AON_TIMER2,3

// From gtimer@20025000.
extern struct __metal_driver_up_gtimer __metal_dt_gtimer_20025000;		//DUAL AON_FW_TIMER0,1

// From gtimer@20026000.
extern struct __metal_driver_up_gtimer __metal_dt_gtimer_20026000;		//DUAL AON_FW_TIMER2,3

// From gtimer@20028000.
extern struct __metal_driver_up_gtimer __metal_dt_gtimer_20028000;		//DUAL RTCM_TICK_TIMER0,1

// From pwm@20095000.
extern struct __metal_driver_up_pwm __metal_dt_pwm_20095000;	//NAON PWM0,1,2,3

// From pwm@20024000.
extern struct __metal_driver_up_pwm __metal_dt_pwm_20024000;	//AON PWM0

// From rtc@20021000.
extern struct __metal_driver_up_rtc __metal_dt_rtc_20021000;

// From udl@58000000.
extern struct __metal_driver_up_udl __metal_dt_udl_58000000;

// From udl@58010000.
extern struct __metal_driver_up_dsp __metal_dt_dsp_58010000;

// From udl@20038000.
extern struct __metal_driver_up_udl __metal_dt_udl_20038000;


// From udl1-3@58008000.
extern struct __metal_driver_up_img __metal_dt_img_58008000;


// From spi@200A6000.
extern struct __metal_driver_up_spi __metal_dt_spi_200A6000;

// From spi@200A7000.
extern struct __metal_driver_up_spi __metal_dt_spi_200A7000;

// From spi@200A8000.
extern struct __metal_driver_up_spi __metal_dt_spi_200A8000;

// From spi@20082000.
extern struct __metal_driver_up_spi __metal_dt_spi_20082000;

// From spi@20083000.
extern struct __metal_driver_up_spi __metal_dt_spi_20083000;

// From spi@20006000.
extern struct __metal_driver_up_spi __metal_dt_spi_20006000;

// From spi@20007000.
extern struct __metal_driver_up_spi __metal_dt_spi_20007000;

// From i2c@200A9000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_200A9000;

// From i2c@200AA000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_200AA000;

// From i2c@200AB000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_200AB000;

// From i2c@20084000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_20084000;

// From i2c@20085000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_20085000;

// From i2c@20086000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_20086000;

// From i2c@20087000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_20087000;

// From i2c@20008000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_20008000;

// From i2c@20009000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_20009000;

// From i2c@2000A000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_2000A000;

// From i2c@2000B000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_2000B000;

// From i2c@2000C000.
extern struct __metal_driver_up_i2c __metal_dt_i2c_2000C000;

// From sif@20001000.
extern struct __metal_driver_up_sif __metal_dt_sif_20001000;

// From dma@200C0000.
extern struct __metal_driver_up_dma __metal_dt_dma_200C0000;

// From dma@200C1000.
extern struct __metal_driver_up_dma __metal_dt_dma_200C1000;

// From dma@200C2000.
extern struct __metal_driver_up_dma __metal_dt_dma_200C2000;

// From pdm@20090000.
extern struct __metal_driver_up_pdm __metal_dt_pdm_20090000;

// From pdm@20090000.
extern struct __metal_driver_up_pdm __metal_dt_pdm_20091000;

// From i2s@20092000.
extern struct __metal_driver_up_i2s __metal_dt_i2s_20092000;

// From i2s@20093000.
extern struct __metal_driver_up_i2s __metal_dt_i2s_20093000;

// From i2s@20094000.
extern struct __metal_driver_up_i2s __metal_dt_i2s_20094000;

// From adc@20002000.
extern struct __metal_driver_up_adc __metal_dt_adc_20002000;

// From ts@20003000.
extern struct __metal_driver_up_ts __metal_dt_ts_20003000;

// From wdt@20023000.
extern struct __metal_driver_up_wdt __metal_dt_wdt_20023000;

/* --------------------- sifive_clint0 ------------ */

#ifndef LOAD_SRAM_CODE
static __inline__ uint32_t __metal_driver_sifive_clint0_control_base(metal_interrupt_Type *controller) __attribute__ ((section (".FwHandler")));
#endif
static __inline__ uint32_t __metal_driver_sifive_clint0_control_base(metal_interrupt_Type *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_clint_2000000) {
		return METAL_RISCV_CLINT0_2000000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ uint32_t __metal_driver_sifive_clint0_control_size(metal_interrupt_Type *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_clint_2000000) {
		return METAL_RISCV_CLINT0_2000000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ uint32_t __metal_driver_sifive_clint0_num_interrupts(metal_interrupt_Type *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_clint_2000000) {
		return METAL_MAX_CLINT_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ metal_interrupt_Type * __metal_driver_sifive_clint0_interrupt_parents(metal_interrupt_Type *controller, uint32_t idx)
{
	if (idx == 0) {
		return (metal_interrupt_Type *)&__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else if (idx == 1) {
		return (metal_interrupt_Type *)&__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ uint32_t __metal_driver_sifive_clint0_interrupt_lines(metal_interrupt_Type *controller, uint32_t idx)
{
	if (idx == 0) {
		return 3;
	}
	else if (idx == 1) {
		return 7;
	}
	else {
		return 0;
	}
}

/* --------------------- cpu ------------ */
static __inline__ int32_t __metal_driver_cpu_hartid(metal_cpu_Type *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 0;
	}
	else {
		return -1;
	}
}

static __inline__ uint32_t __metal_driver_cpu_timebase(metal_cpu_Type *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 1000000;
	}
	else {
		return 0;
	}
}

#ifndef LOAD_SRAM_CODE
static __inline__ metal_interrupt_Type * __metal_driver_cpu_interrupt_controller(metal_cpu_Type *cpu) __attribute__ ((section (".FwHandler")));
#endif
static __inline__ metal_interrupt_Type * __metal_driver_cpu_interrupt_controller(metal_cpu_Type *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return &__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ uint32_t __metal_driver_cpu_num_pmp_regions(metal_cpu_Type *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 2;
	}
	else {
		return 0;
	}
}

static __inline__ metal_buserror_Type *__metal_driver_cpu_buserror(metal_cpu_Type *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return &__metal_dt_bus_error_unit_1700000;
	}
	else {
		return NULL;
	}
}

/* --------------------- sifive_plic0 ------------ */
#ifndef LOAD_SRAM_CODE
static __inline__ uint32_t __metal_driver_sifive_plic0_control_base(metal_interrupt_Type *controller) __attribute__ ((section (".FwHandler")));
#endif
static __inline__ uint32_t __metal_driver_sifive_plic0_control_base(metal_interrupt_Type *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ uint32_t __metal_driver_sifive_plic0_control_size(metal_interrupt_Type *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_SIZE;
	}
	else {
		return 0;
	}
}

#ifndef LOAD_SRAM_CODE
static __inline__ uint32_t __metal_driver_sifive_plic0_num_interrupts(metal_interrupt_Type *controller) __attribute__ ((section (".FwHandler")));
#endif
static __inline__ uint32_t __metal_driver_sifive_plic0_num_interrupts(metal_interrupt_Type *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_RISCV_NDEV;
	}
	else {
		return 0;
	}
}

#ifndef LOAD_SRAM_CODE
static __inline__ uint32_t __metal_driver_sifive_plic0_max_priority(metal_interrupt_Type *controller) __attribute__ ((section (".FwHandler")));
#endif
static __inline__ uint32_t __metal_driver_sifive_plic0_max_priority(metal_interrupt_Type *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_c000000) {
		return METAL_RISCV_PLIC0_C000000_RISCV_MAX_PRIORITY;
	}
	else {
		return 0;
	}
}

static __inline__ metal_interrupt_Type * __metal_driver_sifive_plic0_interrupt_parents(metal_interrupt_Type *controller, uint32_t idx)
{
	if (idx == 0) {
		return (metal_interrupt_Type *)&__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ uint32_t __metal_driver_sifive_plic0_interrupt_lines(metal_interrupt_Type *controller, uint32_t idx)
{
	if (idx == 0) {
		return 11;
	}
	else {
		return 0;
	}
}

#ifndef LOAD_SRAM_CODE
static __inline__ uint32_t __metal_driver_sifive_plic0_context_ids(uint32_t hartid) __attribute__ ((section (".FwHandler")));
#endif
static __inline__ uint32_t __metal_driver_sifive_plic0_context_ids(uint32_t hartid)
{
	if (hartid == 0) {
		return 0;
	}
	else {
		return -1;
	}
}

/* --------------------- sifive_buserror0 ------------ */
static __inline__ uintptr_t __metal_driver_sifive_buserror0_control_base(const metal_buserror_Type *buserror)
{
	if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1700000) {
		return METAL_SIFIVE_BUSERROR0_1700000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ metal_interrupt_Type * __metal_driver_sifive_buserror0_interrupt_parent(const metal_buserror_Type *buserror)
{
	if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1700000) {
		return (metal_interrupt_Type *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ uint32_t __metal_driver_sifive_buserror0_interrupt_id(const metal_buserror_Type *buserror)
{
	if ((uintptr_t)buserror == (uintptr_t)&__metal_dt_bus_error_unit_1700000) {
		return 128;
	}
	else {
		return 0;
	}
}

/* --------------------- sifive_local_external_interrupts0 ------------ */
static __inline__ metal_interrupt_Type * __metal_driver_sifive_local_external_interrupts0_interrupt_parent(metal_interrupt_Type *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_local_external_interrupts_0) {
		return (metal_interrupt_Type *)&__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ uint32_t __metal_driver_sifive_local_external_interrupts0_num_interrupts(metal_interrupt_Type *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_local_external_interrupts_0) {
		return METAL_MAX_LOCAL_EXT_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ uint32_t __metal_driver_sifive_local_external_interrupts0_interrupt_lines(metal_interrupt_Type *controller, uint32_t idx)
{
	if (idx == 0) {
		return 16;
	}
	else if (idx == 1) {
		return 17;
	}
	else if (idx == 2) {
		return 18;
	}
	else if (idx == 3) {
		return 19;
	}
	else if (idx == 4) {
		return 20;
	}
	else if (idx == 5) {
		return 21;
	}
	else if (idx == 6) {
		return 22;
	}
	else if (idx == 7) {
		return 23;
	}
	else if (idx == 8) {
		return 24;
	}
	else if (idx == 9) {
		return 25;
	}
	else if (idx == 10) {
		return 26;
	}
	else if (idx == 11) {
		return 27;
	}
	else if (idx == 12) {
		return 28;
	}
	else if (idx == 13) {
		return 29;
	}
	else if (idx == 14) {
		return 30;
	}
	else if (idx == 15) {
		return 31;
	}
	else {
		return 0;
	}
}

/* --------------------- sifive_global_external_interrupts0 ------------ */
static __inline__ uint32_t __metal_driver_sifive_global_external_interrupts0_init_done()
{
		return 0;
}

static __inline__ metal_interrupt_Type * __metal_driver_sifive_global_external_interrupts0_interrupt_parent(metal_interrupt_Type *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_global_external_interrupts) {
		return (metal_interrupt_Type *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ uint32_t __metal_driver_sifive_global_external_interrupts0_num_interrupts(metal_interrupt_Type *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_global_external_interrupts) {
		return METAL_MAX_GLOBAL_EXT_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ uint32_t __metal_driver_sifive_global_external_interrupts0_interrupt_lines(metal_interrupt_Type *controller, uint32_t idx)
{
	if (idx == 0) {
		return 1;
	}
	else if (idx == 1) {
		return 2;
	}
	else if (idx == 2) {
		return 3;
	}
	else if (idx == 3) {
		return 4;
	}
	else if (idx == 4) {
		return 5;
	}
	else if (idx == 5) {
		return 6;
	}
	else if (idx == 6) {
		return 7;
	}
	else if (idx == 7) {
		return 8;
	}
	else if (idx == 8) {
		return 9;
	}
	else if (idx == 9) {
		return 10;
	}
	else if (idx == 10) {
		return 11;
	}
	else if (idx == 11) {
		return 12;
	}
	else if (idx == 12) {
		return 13;
	}
	else if (idx == 13) {
		return 14;
	}
	else if (idx == 14) {
		return 15;
	}
	else if (idx == 15) {
		return 16;
	}
	else if (idx == 16) {
		return 17;
	}
	else if (idx == 17) {
		return 18;
	}
	else if (idx == 18) {
		return 19;
	}
	else if (idx == 19) {
		return 20;
	}
	else if (idx == 20) {
		return 21;
	}
	else if (idx == 21) {
		return 22;
	}
	else if (idx == 22) {
		return 23;
	}
	else if (idx == 23) {
		return 24;
	}
	else if (idx == 24) {
		return 25;
	}
	else if (idx == 25) {
		return 26;
	}
	else if (idx == 26) {
		return 27;
	}
	else if (idx == 27) {
		return 28;
	}
	else if (idx == 28) {
		return 29;
	}
	else if (idx == 29) {
		return 30;
	}
	else if (idx == 30) {
		return 31;
	}
	else if (idx == 31) {
		return 32;
	}
	else if (idx == 32) {
		return 33;
	}
	else if (idx == 33) {
		return 34;
	}
	else if (idx == 34) {
		return 35;
	}
	else if (idx == 35) {
		return 36;
	}
	else if (idx == 36) {
		return 37;
	}
	else if (idx == 37) {
		return 38;
	}
	else if (idx == 38) {
		return 39;
	}
	else if (idx == 39) {
		return 40;
	}
	else if (idx == 40) {
		return 41;
	}
	else if (idx == 41) {
		return 42;
	}
	else if (idx == 42) {
		return 43;
	}
	else if (idx == 43) {
		return 44;
	}
	else if (idx == 44) {
		return 45;
	}
	else if (idx == 45) {
		return 46;
	}
	else if (idx == 46) {
		return 47;
	}
	else if (idx == 47) {
		return 48;
	}
	else if (idx == 48) {
		return 49;
	}
	else if (idx == 49) {
		return 50;
	}
	else if (idx == 50) {
		return 51;
	}
	else if (idx == 51) {
		return 52;
	}
	else if (idx == 52) {
		return 53;
	}
	else if (idx == 53) {
		return 54;
	}
	else if (idx == 54) {
		return 55;
	}
	else if (idx == 55) {
		return 56;
	}
	else if (idx == 56) {
		return 57;
	}
	else if (idx == 57) {
		return 58;
	}
	else if (idx == 58) {
		return 59;
	}
	else if (idx == 59) {
		return 60;
	}
	else if (idx == 60) {
		return 61;
	}
	else if (idx == 61) {
		return 62;
	}
	else if (idx == 62) {
		return 63;
	}
	else if (idx == 63) {
		return 64;
	}
	else if (idx == 64) {
		return 65;
	}
	else if (idx == 65) {
		return 66;
	}
	else if (idx == 66) {
		return 67;
	}
	else if (idx == 67) {
		return 68;
	}
	else if (idx == 68) {
		return 69;
	}
	else if (idx == 69) {
		return 70;
	}
	else if (idx == 70) {
		return 71;
	}
	else if (idx == 71) {
		return 72;
	}
	else if (idx == 72) {
		return 73;
	}
	else if (idx == 73) {
		return 74;
	}
	else if (idx == 74) {
		return 75;
	}
	else if (idx == 75) {
		return 76;
	}
	else if (idx == 76) {
		return 77;
	}
	else if (idx == 77) {
		return 78;
	}
	else if (idx == 78) {
		return 79;
	}
	else if (idx == 79) {
		return 80;
	}
	else if (idx == 80) {
		return 81;
	}
	else if (idx == 81) {
		return 82;
	}
	else if (idx == 82) {
		return 83;
	}
	else if (idx == 83) {
		return 84;
	}
	else if (idx == 84) {
		return 85;
	}
	else if (idx == 85) {
		return 86;
	}
	else if (idx == 86) {
		return 87;
	}
	else if (idx == 87) {
		return 88;
	}
	else if (idx == 88) {
		return 89;
	}
	else if (idx == 89) {
		return 90;
	}
	else if (idx == 90) {
		return 91;
	}
	else if (idx == 91) {
		return 92;
	}
	else if (idx == 92) {
		return 93;
	}
	else if (idx == 93) {
		return 94;
	}
	else if (idx == 94) {
		return 95;
	}
	else if (idx == 95) {
		return 96;
	}
	else if (idx == 96) {
		return 97;
	}
	else if (idx == 97) {
		return 98;
	}
	else if (idx == 98) {
		return 99;
	}
	else if (idx == 99) {
		return 100;
	}
	else if (idx == 100) {
		return 101;
	}
	else if (idx == 101) {
		return 102;
	}
	else if (idx == 102) {
		return 103;
	}
	else if (idx == 103) {
		return 104;
	}
	else if (idx == 104) {
		return 105;
	}
	else if (idx == 105) {
		return 106;
	}
	else if (idx == 106) {
		return 107;
	}
	else if (idx == 107) {
		return 108;
	}
	else if (idx == 108) {
		return 109;
	}
	else if (idx == 109) {
		return 110;
	}
	else if (idx == 110) {
		return 111;
	}
	else if (idx == 111) {
		return 112;
	}
	else if (idx == 112) {
		return 113;
	}
	else if (idx == 113) {
		return 114;
	}
	else if (idx == 114) {
		return 115;
	}
	else if (idx == 115) {
		return 116;
	}
	else if (idx == 116) {
		return 117;
	}
	else if (idx == 117) {
		return 118;
	}
	else if (idx == 118) {
		return 119;
	}
	else if (idx == 119) {
		return 120;
	}
	else if (idx == 120) {
		return 121;
	}
	else if (idx == 121) {
		return 122;
	}
	else if (idx == 122) {
		return 123;
	}
	else if (idx == 123) {
		return 124;
	}
	else if (idx == 124) {
		return 125;
	}
	else if (idx == 125) {
		return 126;
	}
	else if (idx == 126) {
		return 127;
	}
	else {
		return 0;
	}
}

/* --------------------- sifive_test0 ------------ */
static __inline__ uint32_t __metal_driver_sifive_test0_base(const __metal_shutdown_Type *sd)
{
	if ((uintptr_t)sd == (uintptr_t)&__metal_dt_teststatus_4000) {
		return METAL_SIFIVE_TEST0_4000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ uint32_t __metal_driver_sifive_test0_size(const __metal_shutdown_Type *sd)
{
	if ((uintptr_t)sd == (uintptr_t)&__metal_dt_teststatus_4000) {
		return METAL_SIFIVE_TEST0_4000_SIZE;
	}
	else {
		return 0;
	}
}

/* --------------------- up_gpio ------------ */
static __inline__ unsigned long __metal_driver_up_gpio_base(metal_gpio_Type *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_200B4000) {
		return METAL_UP_GPIO_200B4000_BASE_ADDRESS;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20088000) {
			return METAL_UP_GPIO_20088000_BASE_ADDRESS;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20010000) {
			return METAL_UP_GPIO_20010000_BASE_ADDRESS;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20020000) {
			return (METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMSYS);
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_up_gpio_index(metal_gpio_Type *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_200B4000) {
		return 0;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20088000) {
		return 1;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20010000) {
		return 2;
	}
	else {
		return -1;
	}
}

static __inline__ int __metal_driver_up_gpio_devices(metal_gpio_Type *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_200B4000) {
		return 6;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20088000) {
		return 4;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20010000) {
		return 3;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_up_gpio_size(metal_gpio_Type *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_200B4000) {
		return METAL_UP_GPIO_200B4000_SIZE;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20088000) {
		return METAL_UP_GPIO_20088000_SIZE;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20010000) {
		return METAL_UP_GPIO_20010000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_up_gpio_num_interrupts(metal_gpio_Type *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_200B4000) {
		return ___metal_GPIO0_200B4000_INTERRUPTS;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20088000) {
			return ___metal_GPIO1_20088000_INTERRUPTS;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20010000) {
			return ___metal_GPIO2_20010000_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ metal_interrupt_Type * __metal_driver_up_gpio_interrupt_parent(metal_gpio_Type *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_200B4000) {
		return (metal_interrupt_Type *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20088000) {
		return (metal_interrupt_Type *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20010000) {
		return (metal_interrupt_Type *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return 0;
	}
}

extern const char gpio_interrupt_line_table[][___metal_GPIO0_200B4000_INTERRUPTS];
static __inline__ int __metal_driver_up_gpio_interrupt_lines(metal_gpio_Type *gpio, int idx)
{
	int gpio_dev = __metal_driver_up_gpio_index(gpio);

	return (int)gpio_interrupt_line_table[gpio_dev][idx];
}

/* --------------------- up_uart ------------ */
static __inline__ uint32_t __metal_driver_up_uart_control_base(metal_uart_Type *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_200A4000) {
		return METAL_UP_UART_200A4000_BASE_ADDRESS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_200A5000) {
		return METAL_UP_UART_200A5000_BASE_ADDRESS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20080000) {
		return METAL_UP_UART_20080000_BASE_ADDRESS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20081000) {
		return METAL_UP_UART_20081000_BASE_ADDRESS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20005000) {
		return METAL_UP_UART_20005000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ uint32_t __metal_driver_up_uart_control_size(metal_uart_Type *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_200A4000) {
		return METAL_UP_UART_200A4000_SIZE;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_200A5000) {
		return METAL_UP_UART_200A5000_SIZE;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20080000) {
		return METAL_UP_UART_20080000_SIZE;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20081000) {
		return METAL_UP_UART_20081000_SIZE;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20005000) {
		return METAL_UP_UART_20005000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int16_t __metal_driver_up_uart_num_interrupts(metal_uart_Type *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_200A4000) {
		return ___metal_SERIAL0_200A4000_INTERRUPTS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_200A5000) {
		return ___metal_SERIAL1_200A5000_INTERRUPTS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20080000) {
		return ___metal_SERIAL2_20080000_INTERRUPTS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20081000) {
		return ___metal_SERIAL3_20081000_INTERRUPTS;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20005000) {
		return ___metal_SERIAL0_20005000_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ metal_interrupt_Type * __metal_driver_up_uart_interrupt_parent(metal_uart_Type *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_200A4000) {
		return (metal_interrupt_Type *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_200A5000) {
		return (metal_interrupt_Type *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20080000) {
		return (metal_interrupt_Type *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20081000) {
		return (metal_interrupt_Type *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20005000) {
		return (metal_interrupt_Type *)&__metal_dt_interrupt_controller_c000000.controller;
	}
	else {
		return 0;
	}
}

static __inline__ int16_t __metal_driver_up_uart_interrupt_line(metal_uart_Type *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_200A4000) {
		return 5;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_200A5000) {
		return 121;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20080000) {
		return 121;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20081000) {
		return 121;
	}
	else if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20005000) {
		return 121;
	}
	else {
		return 0;
	}
}

/* --------------------- up_ospi ------------ */
#ifndef LOAD_SRAM_CODE
static __inline__ unsigned long __metal_driver_up_ospi_control_base(metal_ospi_Type *ospi) __attribute__ ((section (".FwHandler")));
#endif
static __inline__ unsigned long __metal_driver_up_ospi_control_base(metal_ospi_Type *ospi)
{
	if ((uintptr_t)ospi == (uintptr_t)&__metal_dt_ospi_200A0000) {
		return METAL_UP_OSPI_200A0000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_gtimer ------------ */
static __inline__ unsigned long __metal_driver_up_gtimer_control_base(metal_gtimer_Type *gtimer)
{
	if ((uintptr_t)gtimer == (uintptr_t)&__metal_dt_gtimer_20096000) {
		return METAL_UP_GTIMER_20096000_BASE_ADDRESS;
	}
	else if ((uintptr_t)gtimer == (uintptr_t)&__metal_dt_gtimer_20097000) {
		return METAL_UP_GTIMER_20097000_BASE_ADDRESS;
	}
	else if ((uintptr_t)gtimer == (uintptr_t)&__metal_dt_gtimer_20098000) {
		return METAL_UP_GTIMER_20098000_BASE_ADDRESS;
	}
	else if ((uintptr_t)gtimer == (uintptr_t)&__metal_dt_gtimer_20099000) {
		return METAL_UP_GTIMER_20099000_BASE_ADDRESS;
	}
	else if ((uintptr_t)gtimer == (uintptr_t)&__metal_dt_gtimer_2000D000) {
		return METAL_UP_GTIMER_2000D000_BASE_ADDRESS;
	}
	else if ((uintptr_t)gtimer == (uintptr_t)&__metal_dt_gtimer_2000E000) {
		return METAL_UP_GTIMER_2000E000_BASE_ADDRESS;
	}
	else if ((uintptr_t)gtimer == (uintptr_t)&__metal_dt_gtimer_20025000) {
		return METAL_UP_GTIMER_20025000_BASE_ADDRESS;
	}
	else if ((uintptr_t)gtimer == (uintptr_t)&__metal_dt_gtimer_20026000) {
		return METAL_UP_GTIMER_20026000_BASE_ADDRESS;
	}
	else if ((uintptr_t)gtimer == (uintptr_t)&__metal_dt_gtimer_20028000) {
		return METAL_UP_GTIMER_20028000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_pwm ------------ */
static __inline__ uint32_t __metal_driver_up_pwm_control_base(metal_pwm_Type *pwm)
{
	if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_20095000) {
		return METAL_UP_PWM_20095000_BASE_ADDRESS;
	}
	else if ((uintptr_t)pwm == (uintptr_t)&__metal_dt_pwm_20024000) {
		return METAL_UP_PWM_20024000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_rtc ------------ */
static __inline__ unsigned long __metal_driver_up_rtc_control_base(metal_rtc_Type *rtc)
{
	if ((uintptr_t)rtc == (uintptr_t)&__metal_dt_rtc_20021000) {
		return METAL_UP_RTC_20021000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_udl ------------ */
static __inline__ uint32_t __metal_driver_up_udl_control_base(metal_udl_Type *udl)
{
	if ((uintptr_t)udl == (uintptr_t)&__metal_dt_udl_58000000) {
		return METAL_UP_UDL_58000000_BASE_ADDRESS;
	}
	else if ((uintptr_t)udl == (uintptr_t)&__metal_dt_udl_20038000) {
		return METAL_UP_UDL_20038000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_udl_dsp ------------ */
static __inline__ uint32_t __metal_driver_up_dsp_control_base(metal_dsp_Type *dsp)
{
	if ((uintptr_t)dsp == (uintptr_t)&__metal_dt_dsp_58010000) {
		return METAL_UP_DSP_58010000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}




static __inline__ uint32_t __metal_driver_up_img_control_base(metal_img_Type *img)
{
	if ((uintptr_t)img == (uintptr_t)&__metal_dt_img_58008000) {
		return METAL_UP_IMG_58008000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_spi ------------ */
static __inline__ uint32_t __metal_driver_up_spi_control_base(metal_spi_Type *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_200A6000) {
		return METAL_UP_SPI_200A6000_BASE_ADDRESS;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_200A7000) {
		return METAL_UP_SPI_200A7000_BASE_ADDRESS;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_200A8000) {
			return METAL_UP_SPI_200A8000_BASE_ADDRESS;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20082000) {
			return METAL_UP_SPI_20082000_BASE_ADDRESS;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20083000) {
			return METAL_UP_SPI_20083000_BASE_ADDRESS;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20006000) {
			return METAL_UP_SPI_20006000_BASE_ADDRESS;
	}
	else if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20007000) {
			return METAL_UP_SPI_20007000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_i2c ------------ */
static __inline__ uint32_t __metal_driver_up_i2c_control_base(metal_i2c_Type *i2c)
{
	if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_200A9000) {
		return METAL_UP_I2C_200A9000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_200AA000) {
		return METAL_UP_I2C_200AA000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_200AB000) {
		return METAL_UP_I2C_200AB000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_20084000) {
		return METAL_UP_I2C_20084000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_20085000) {
		return METAL_UP_I2C_20085000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_20086000) {
		return METAL_UP_I2C_20086000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_20087000) {
		return METAL_UP_I2C_20087000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_20008000) {
		return METAL_UP_I2C_20008000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_20009000) {
		return METAL_UP_I2C_20009000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_2000A000) {
		return METAL_UP_I2C_2000A000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_2000B000) {
		return METAL_UP_I2C_2000B000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2c == (uintptr_t)&__metal_dt_i2c_2000C000) {
		return METAL_UP_I2C_2000C000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_sif ------------ */
static __inline__ unsigned long __metal_driver_up_sif_control_base(metal_sif_Type *sif)
{
	if ((uintptr_t)sif == (uintptr_t)&__metal_dt_sif_20001000) {
		return METAL_UP_SIF_20001000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_dma ------------ */
static __inline__ unsigned long __metal_driver_up_dma_control_base(metal_dma_Type *dma)
{
	if ((uintptr_t)dma == (uintptr_t)&__metal_dt_dma_200C0000) {
		return METAL_UP_DMA_200C0000_BASE_ADDRESS;
	}
	else if ((uintptr_t)dma == (uintptr_t)&__metal_dt_dma_200C1000) {
		return METAL_UP_DMA_200C1000_BASE_ADDRESS;
	}
	else if ((uintptr_t)dma == (uintptr_t)&__metal_dt_dma_200C2000) {
		return METAL_UP_DMA_200C2000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_pdm ------------ */
static __inline__ unsigned long __metal_driver_up_pdm_control_base(struct metal_pdm *pdm)
{
	if ((uintptr_t)pdm == (uintptr_t)&__metal_dt_pdm_20090000) {
		return METAL_UP_PDM_20090000_BASE_ADDRESS;
	}
	else if ((uintptr_t)pdm == (uintptr_t)&__metal_dt_pdm_20091000) {
		return METAL_UP_PDM_20091000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_i2s ------------ */
static __inline__ unsigned long __metal_driver_up_i2s_control_base(struct metal_i2s *i2s)
{
	if ((uintptr_t)i2s == (uintptr_t)&__metal_dt_i2s_20092000) {
		return METAL_UP_I2S_20092000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2s == (uintptr_t)&__metal_dt_i2s_20093000) {
		return METAL_UP_I2S_20093000_BASE_ADDRESS;
	}
	else if ((uintptr_t)i2s == (uintptr_t)&__metal_dt_i2s_20094000) {
		return METAL_UP_I2S_20094000_BASE_ADDRESS;
		}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_up_i2s_ipnum(struct metal_i2s *i2s)
{
	if ((uintptr_t)i2s == (uintptr_t)&__metal_dt_i2s_20092000) {
		return 0;
	}
	else if ((uintptr_t)i2s == (uintptr_t)&__metal_dt_i2s_20093000) {
		return 1;
	}
	else if ((uintptr_t)i2s == (uintptr_t)&__metal_dt_i2s_20094000) {
		return 2;
		}
	else {
		return 0;
	}
}

/* --------------------- up_adc ------------ */
static __inline__ unsigned long __metal_driver_up_adc_control_base(metal_adc_Type *adc)
{
	if ((uintptr_t)adc == (uintptr_t)&__metal_dt_adc_20002000) {
		return METAL_UP_ADC_20002000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_ts ------------ */
static __inline__ uint32_t __metal_driver_up_ts_control_base(metal_ts_Type *ts)
{
	if ((uintptr_t)ts == (uintptr_t)&__metal_dt_ts_20003000) {
		return METAL_UP_TS_20003000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

/* --------------------- up_wdt ------------ */
static __inline__ uint32_t __metal_driver_up_wdt_control_base(metal_wdt_Type *wdt)
{
	if ((uintptr_t)wdt == (uintptr_t)&__metal_dt_wdt_20023000) {
		return METAL_UP_WDT_20023000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

#define __METAL_DT_MAX_MEMORIES 4

struct metal_memory *__metal_memory_table[] __attribute__((weak)) = {
					&__metal_dt_mem_testram_20000000,
					&__metal_dt_mem_testram_40000000,
					&__metal_dt_mem_dtim_80000000,
					&__metal_dt_mem_itim_1800000};

// From clint@2000000.
#define __METAL_DT_RISCV_CLINT0_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_CLINT_2000000_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_MAX_HARTS 1

#define __METAL_CPU_0_ICACHE_HANDLE 1

struct __metal_driver_cpu *__metal_cpu_table[] __attribute__((weak))  = {
					&__metal_dt_cpu_0};

// Default for E34 cpu.
#define __METAL_DT_E34_CPU_HANDLE (&__metal_dt_cpu_0.cpu)

// From interrupt_controller@c000000.
#define __METAL_DT_RISCV_PLIC0_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_PMP_HANDLE (&__metal_dt_pmp)

// From global_external_interrupts.
#define __METAL_DT_SIFIVE_GLOBAL_EXINTR0_HANDLE (&__metal_dt_global_external_interrupts.irc)

#define __METAL_DT_GLOBAL_EXTERNAL_INTERRUPTS_HANDLE (&__metal_dt_global_external_interrupts.irc)


// Default for tty.c.
#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_dt_serial_200A4000.uart)

#define __METAL_DT_STDOUT_UART_BAUD 12000000

// Default for upt ospi handler.
#define __METAL_DT_IO_OSPI_HANDLE (&__metal_dt_ospi_200A0000.ospi)

// From teststatus@4000.
#define __METAL_DT_SHUTDOWN_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_TESTSTATUS_4000_HANDLE (&__metal_dt_teststatus_4000.shutdown)

#define __METAL_DT_MAX_GPIOS 4

__asm__ (".weak __metal_gpio_table");
struct __metal_driver_up_gpio *__metal_gpio_table[] = {
					&__metal_dt_gpio_200B4000,
					&__metal_dt_gpio_20088000,
					&__metal_dt_gpio_20010000,
					&__metal_dt_gpio_20020000};

#define __METAL_DT_MAX_UARTS 5

__asm__ (".weak __metal_uart_table");
struct __metal_driver_up_uart *__metal_uart_table[] = {
					&__metal_dt_serial_200A4000,
					&__metal_dt_serial_200A5000,
					&__metal_dt_serial_20080000,
					&__metal_dt_serial_20081000,
					&__metal_dt_serial_20005000};

#define __METAL_DT_MAX_OSPIS 1

__asm__ (".weak __metal_ospi_table");
struct __metal_driver_up_ospi *__metal_ospi_table[] = {
					&__metal_dt_ospi_200A0000};

#define __METAL_DT_MAX_GTIMERS 9

__asm__ (".weak __metal_gtimer_table");
struct __metal_driver_up_gtimer *__metal_gtimer_table[] = {
					&__metal_dt_gtimer_20096000,
					&__metal_dt_gtimer_20097000,
					&__metal_dt_gtimer_20098000,
					&__metal_dt_gtimer_20099000,
					&__metal_dt_gtimer_2000D000,
					&__metal_dt_gtimer_2000E000,
					&__metal_dt_gtimer_20025000,
					&__metal_dt_gtimer_20026000,
					&__metal_dt_gtimer_20028000};

#define __METAL_DT_MAX_PWMS 2

__asm__ (".weak __metal_pwm_table");
struct __metal_driver_up_pwm *__metal_pwm_table[] = {
					&__metal_dt_pwm_20095000,
					&__metal_dt_pwm_20024000};

#define __METAL_DT_MAX_RTCS 1

__asm__ (".weak __metal_rtc_table");
struct __metal_driver_up_rtc *__metal_rtc_table[] = {
					&__metal_dt_rtc_20021000};

#define __METAL_DT_MAX_UDLS 2

__asm__ (".weak __metal_udl_table");
struct __metal_driver_up_udl *__metal_udl_table[] = {
					&__metal_dt_udl_58000000,
					&__metal_dt_udl_20038000};

#define __METAL_DT_MAX_DSPS 1

__asm__ (".weak __metal_dsp_table");
struct __metal_driver_up_dsp *__metal_dsp_table[] = {
					&__metal_dt_dsp_58010000};


#define __METAL_DT_MAX_IMGS 1

__asm__ (".weak __metal_img_table");
struct __metal_driver_up_img *__metal_img_table[] = {
					&__metal_dt_img_58008000};


#define __METAL_DT_MAX_SPIS 7

__asm__ (".weak __metal_spi_table");
struct __metal_driver_up_spi *__metal_spi_table[] = {
					&__metal_dt_spi_200A6000,
					&__metal_dt_spi_200A7000,
					&__metal_dt_spi_200A8000,
					&__metal_dt_spi_20082000,
					&__metal_dt_spi_20083000,
					&__metal_dt_spi_20006000,
					&__metal_dt_spi_20007000};

#define __METAL_DT_MAX_I2CS 12

__asm__ (".weak __metal_i2c_table");
struct __metal_driver_up_i2c *__metal_i2c_table[] = {
					&__metal_dt_i2c_200A9000,
					&__metal_dt_i2c_200AA000,
					&__metal_dt_i2c_200AB000,
					&__metal_dt_i2c_20084000,
					&__metal_dt_i2c_20085000,
					&__metal_dt_i2c_20086000,
					&__metal_dt_i2c_20087000,
					&__metal_dt_i2c_20008000,
					&__metal_dt_i2c_20009000,
					&__metal_dt_i2c_2000A000,
					&__metal_dt_i2c_2000B000,
					&__metal_dt_i2c_2000C000};

#define __METAL_DT_MAX_SIFS 1

__asm__ (".weak __metal_sif_table");
struct __metal_driver_up_sif *__metal_sif_table[] = {
					&__metal_dt_sif_20001000};

#define __METAL_DT_MAX_DMAS 3

__asm__ (".weak __metal_dma_table");
struct __metal_driver_up_dma *__metal_dma_table[] = {
					&__metal_dt_dma_200C0000,
					&__metal_dt_dma_200C1000,
					&__metal_dt_dma_200C2000};

#define __METAL_DT_MAX_PDMS 2

__asm__ (".weak __metal_pdm_table");
struct __metal_driver_up_pdm *__metal_pdm_table[] = {
					&__metal_dt_pdm_20090000,
					&__metal_dt_pdm_20091000};

#define __METAL_DT_MAX_I2SS 3

__asm__ (".weak __metal_i2s_table");
struct __metal_driver_up_i2s *__metal_i2s_table[] = {
					&__metal_dt_i2s_20092000,
					&__metal_dt_i2s_20093000,
					&__metal_dt_i2s_20094000};

#define __METAL_DT_MAX_ADCS 1

__asm__ (".weak __metal_adc_table");
struct __metal_driver_up_adc *__metal_adc_table[] = {
					&__metal_dt_adc_20002000};

#define __METAL_DT_MAX_TSS 1

__asm__ (".weak __metal_ts_table");
struct __metal_driver_up_ts *__metal_ts_table[] = {
					&__metal_dt_ts_20003000};

#define __METAL_DT_MAX_WDTS 1

__asm__ (".weak __metal_wdt_table");
struct __metal_driver_up_wdt *__metal_wdt_table[] = {
					&__metal_dt_wdt_20023000};

#endif /* MACROS_ELSE_METAL_H*/

#endif /* ! __METAL_MACHINE_MACROS */

#endif /* ! ASSEMBLY */
