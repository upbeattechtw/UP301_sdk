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

#ifndef METAL_INLINE_H
#define METAL_INLINE_H
#include "metal.h"

/* --------------------- sifive_clint0 ------------ */
extern __inline__ uint32_t __metal_driver_sifive_clint0_control_base(metal_interrupt_Type *controller);
extern __inline__ uint32_t __metal_driver_sifive_clint0_control_size(metal_interrupt_Type *controller);
extern __inline__ uint32_t __metal_driver_sifive_clint0_num_interrupts(metal_interrupt_Type *controller);
extern __inline__ metal_interrupt_Type * __metal_driver_sifive_clint0_interrupt_parents(metal_interrupt_Type *controller, uint32_t idx);
extern __inline__ uint32_t __metal_driver_sifive_clint0_interrupt_lines(metal_interrupt_Type *controller, uint32_t idx);

/* --------------------- cpu ------------ */
extern __inline__ int32_t __metal_driver_cpu_hartid(metal_cpu_Type *cpu);
extern __inline__ uint32_t __metal_driver_cpu_timebase(metal_cpu_Type *cpu);
extern __inline__ metal_interrupt_Type * __metal_driver_cpu_interrupt_controller(metal_cpu_Type *cpu);
extern __inline__ uint32_t __metal_driver_cpu_num_pmp_regions(metal_cpu_Type *cpu);
extern __inline__ metal_buserror_Type *__metal_driver_cpu_buserror(metal_cpu_Type *cpu);

/* --------------------- sifive_plic0 ------------ */
extern __inline__ uint32_t __metal_driver_sifive_plic0_control_base(metal_interrupt_Type *controller);
extern __inline__ uint32_t __metal_driver_sifive_plic0_control_size(metal_interrupt_Type *controller);
extern __inline__ uint32_t __metal_driver_sifive_plic0_num_interrupts(metal_interrupt_Type *controller);
extern __inline__ uint32_t __metal_driver_sifive_plic0_max_priority(metal_interrupt_Type *controller);
extern __inline__ metal_interrupt_Type * __metal_driver_sifive_plic0_interrupt_parents(metal_interrupt_Type *controller, uint32_t idx);
extern __inline__ uint32_t __metal_driver_sifive_plic0_interrupt_lines(metal_interrupt_Type *controller, uint32_t idx);
extern __inline__ uint32_t __metal_driver_sifive_plic0_context_ids(uint32_t hartid);

/* --------------------- sifive_buserror0 ------------ */
extern __inline__ uintptr_t __metal_driver_sifive_buserror0_control_base(const metal_buserror_Type *beu);
extern __inline__ metal_interrupt_Type * __metal_driver_sifive_buserror0_interrupt_parent(const metal_buserror_Type *beu);
extern __inline__ uint32_t __metal_driver_sifive_buserror0_interrupt_id(const metal_buserror_Type *beu);

/* --------------------- sifive_local_external_interrupts0 ------------ */
extern __inline__ metal_interrupt_Type * __metal_driver_sifive_local_external_interrupts0_interrupt_parent(metal_interrupt_Type *controller);
extern __inline__ uint32_t __metal_driver_sifive_local_external_interrupts0_num_interrupts(metal_interrupt_Type *controller);
extern __inline__ uint32_t __metal_driver_sifive_local_external_interrupts0_interrupt_lines(metal_interrupt_Type *controller, uint32_t idx);

/* --------------------- sifive_global_external_interrupts0 ------------ */
extern __inline__ uint32_t __metal_driver_sifive_global_external_interrupts0_init_done( );
extern __inline__ metal_interrupt_Type * __metal_driver_sifive_global_external_interrupts0_interrupt_parent(metal_interrupt_Type *controller);
extern __inline__ uint32_t __metal_driver_sifive_global_external_interrupts0_num_interrupts(metal_interrupt_Type *controller);
extern __inline__ uint32_t __metal_driver_sifive_global_external_interrupts0_interrupt_lines(metal_interrupt_Type *controller, uint32_t idx);

/* --------------------- sifive_test0 ------------ */
extern __inline__ uint32_t __metal_driver_sifive_test0_base(const __metal_shutdown_Type *sd);
extern __inline__ uint32_t __metal_driver_sifive_test0_size(const __metal_shutdown_Type *sd);

/* --------------------- up_gpio ------------ */
extern __inline__ unsigned long __metal_driver_up_gpio_base(metal_gpio_Type *gpio);
extern __inline__ int __metal_driver_up_gpio_index(metal_gpio_Type *gpio);
extern __inline__ int __metal_driver_up_gpio_devices(metal_gpio_Type *gpio);
extern __inline__ unsigned long __metal_driver_up_gpio_size(metal_gpio_Type *gpio);
extern __inline__ int __metal_driver_up_gpio_num_interrupts(metal_gpio_Type *gpio);
extern __inline__ metal_interrupt_Type * __metal_driver_up_gpio_interrupt_parent(metal_gpio_Type *gpio);
extern __inline__ int __metal_driver_up_gpio_interrupt_lines(metal_gpio_Type *gpio, int idx);

/* --------------------- up_uart ------------ */
extern __inline__ uint32_t __metal_driver_up_uart_control_base(metal_uart_Type *uart);
extern __inline__ uint32_t __metal_driver_up_uart_control_size(metal_uart_Type *uart);
extern __inline__ int16_t __metal_driver_up_uart_num_interrupts(metal_uart_Type *uart);
extern __inline__ metal_interrupt_Type * __metal_driver_up_uart_interrupt_parent(metal_uart_Type *uart);
extern __inline__ int16_t __metal_driver_up_uart_interrupt_line(metal_uart_Type *uart);

/* --------------------- up_ospi ------------ */
extern __inline__ unsigned long __metal_driver_up_ospi_control_base(metal_ospi_Type *ospi);

/* --------------------- up_gtimer ------------ */
extern __inline__ unsigned long __metal_driver_up_gtimer_control_base(metal_gtimer_Type *gtimer);

/* --------------------- up_pwm ------------ */
extern __inline__ uint32_t __metal_driver_up_pwm_control_base(metal_pwm_Type *pwm);

/* --------------------- up_rtc ------------ */
extern __inline__ unsigned long __metal_driver_up_rtc_control_base(metal_rtc_Type *rtc);

/* --------------------- up_udl ------------ */
extern __inline__ uint32_t __metal_driver_up_udl_control_base(metal_udl_Type *udl);

/* --------------------- up_dsp ------------ */
extern __inline__ uint32_t __metal_driver_up_dsp_control_base(metal_dsp_Type *dsp);

/* --------------------- up_img ------------ */
extern __inline__ uint32_t __metal_driver_up_img_control_base(metal_img_Type *img);

/* --------------------- up_spi ------------ */
extern __inline__ uint32_t __metal_driver_up_spi_control_base(metal_spi_Type *spi);

/* --------------------- up_i2c ------------ */
extern  __inline__ uint32_t __metal_driver_up_i2c_control_base(metal_i2c_Type *i2c);

/* --------------------- up_sif ------------ */
extern __inline__ unsigned long __metal_driver_up_sif_control_base(metal_sif_Type *sif);

/* --------------------- up_dma ------------ */
extern __inline__ unsigned long __metal_driver_up_dma_control_base(metal_dma_Type *dma);

/* --------------------- up_pdm ------------ */
extern __inline__ unsigned long __metal_driver_up_pdm_control_base(struct metal_pdm *pdm);

/* --------------------- up_i2s ------------ */
extern __inline__ unsigned long __metal_driver_up_i2s_control_base(struct metal_i2s *i2s);
extern __inline__ int __metal_driver_up_i2s_ipnum(struct metal_i2s *i2s);

/* --------------------- up_adc ------------ */
extern __inline__ unsigned long __metal_driver_up_adc_control_base(metal_adc_Type *adc);

/* --------------------- up_ts ------------ */
extern __inline__ uint32_t __metal_driver_up_ts_control_base(metal_ts_Type *ts);

/* --------------------- up_wdt ------------ */
extern __inline__ uint32_t __metal_driver_up_wdt_control_base(metal_wdt_Type *wdt);

struct metal_memory __metal_dt_mem_testram_20000000 = {
    ._base_address = 536870912UL,
    ._size = 536870911UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_testram_40000000 = {
    ._base_address = 1073741824UL,
    ._size = 536870911UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_dtim_80000000 = {
    ._base_address = 2147483648UL,
    ._size = 32768UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};

struct metal_memory __metal_dt_mem_itim_1800000 = {
    ._base_address = 25165824UL,
    ._size = 16384UL,
    ._attrs = {
        .R = 1,
        .W = 1,
        .X = 1,
        .C = 1,
        .A = 1},
};


// From clint@2000000.
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000 = {
    .controller.vtable = &__metal_driver_vtable_riscv_clint0.clint_vtable,
    .init_done = 0,
};

// From cpu@0.
struct __metal_driver_cpu __metal_dt_cpu_0 = {
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .hpm_count = 0,
};

// From interrupt_controller.
struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller = {
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
};

// From interrupt_controller@c000000.
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000 = {
    #ifndef CONFIG_UPBEAT_HAL
    .controller.vtable = &__metal_driver_vtable_riscv_plic0.plic_vtable,
    #endif /* CONFIG_UPBEAT_HAL */
    .init_done = 0,
};

struct metal_pmp __metal_dt_pmp;

// From bus_error_unit@1700000.
metal_buserror_Type __metal_dt_bus_error_unit_1700000 = {
	.__no_empty_structs = 0,
};

// From local_external_interrupts_0.
struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0 = {
    .irc.vtable = &__metal_driver_vtable_sifive_local_external_interrupts0.local0_vtable,
    .init_done = 0,
};

// From global_external_interrupts.
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts = {
    .irc.vtable = &__metal_driver_vtable_sifive_global_external_interrupts0.global0_vtable,
    .init_done = 0,
};

// From teststatus@4000.
struct __metal_driver_sifive_test0 __metal_dt_teststatus_4000 = {
    .shutdown.vtable = &__metal_driver_vtable_sifive_test0.shutdown,
};

// From sys_gpio@200B4000.
struct __metal_driver_up_gpio __metal_dt_gpio_200B4000 = {
    .gpio.vtable = &__metal_driver_vtable_up_gpio.gpio,
};

// From peri_gpio@20088000.
struct __metal_driver_up_gpio __metal_dt_gpio_20088000 = {
    .gpio.vtable = &__metal_driver_vtable_up_gpio.gpio,
};

// From aon_gpio@20010000.
struct __metal_driver_up_gpio __metal_dt_gpio_20010000 = {
    .gpio.vtable = &__metal_driver_vtable_up_gpio.gpio,
};

// From aon_gpio@20020000.
struct __metal_driver_up_gpio __metal_dt_gpio_20020000 = {
    .gpio.vtable = &__metal_driver_vtable_up_gpio.gpio,
};

// From serial@200A4000.
struct __metal_driver_up_uart __metal_dt_serial_200A4000 = {
    .uart.vtable = &__metal_driver_vtable_up_uart.uart,
};

// From serial@200A5000.
struct __metal_driver_up_uart __metal_dt_serial_200A5000 = {
    .uart.vtable = &__metal_driver_vtable_up_uart.uart,
};

// From serial@20080000.
struct __metal_driver_up_uart __metal_dt_serial_20080000 = {
    .uart.vtable = &__metal_driver_vtable_up_uart.uart,
};

// From serial@20081000.
struct __metal_driver_up_uart __metal_dt_serial_20081000 = {
    .uart.vtable = &__metal_driver_vtable_up_uart.uart,
};

/* From serial@20005000 */
struct __metal_driver_up_uart __metal_dt_serial_20005000 = {
    .uart.vtable = &__metal_driver_vtable_up_uart.uart,
};

// From ospi@200A0000.
struct __metal_driver_up_ospi __metal_dt_ospi_200A0000 = {
    .ospi.vtable = &__metal_driver_vtable_up_ospi.ospi,
};

// From gtimer@20096000.
struct __metal_driver_up_gtimer __metal_dt_gtimer_20096000 = {
    .gtimer.vtable = &__metal_driver_vtable_up_gtimer.gtimer,
};

// From gtimer@20097000.
struct __metal_driver_up_gtimer __metal_dt_gtimer_20097000 = {
    .gtimer.vtable = &__metal_driver_vtable_up_gtimer.gtimer,
};

// From gtimer@20098000.
struct __metal_driver_up_gtimer __metal_dt_gtimer_20098000 = {
    .gtimer.vtable = &__metal_driver_vtable_up_gtimer.gtimer,
};

// From gtimer@20099000.
struct __metal_driver_up_gtimer __metal_dt_gtimer_20099000 = {
    .gtimer.vtable = &__metal_driver_vtable_up_gtimer.gtimer,
};

// From aon_gtimer@2000D000.
struct __metal_driver_up_gtimer __metal_dt_gtimer_2000D000 = {
    .gtimer.vtable = &__metal_driver_vtable_up_gtimer.gtimer,
};

// From aon_gtimer@2000E000.
struct __metal_driver_up_gtimer __metal_dt_gtimer_2000E000 = {
    .gtimer.vtable = &__metal_driver_vtable_up_gtimer.gtimer,
};

// From aon_fw_gtimer@20025000.
struct __metal_driver_up_gtimer __metal_dt_gtimer_20025000 = {
    .gtimer.vtable = &__metal_driver_vtable_up_gtimer.gtimer,
};

// From aon_fw_gtimer@20026000.
struct __metal_driver_up_gtimer __metal_dt_gtimer_20026000 = {
    .gtimer.vtable = &__metal_driver_vtable_up_gtimer.gtimer,
};

// From rtcm_tick_gtimer@20028000.
struct __metal_driver_up_gtimer __metal_dt_gtimer_20028000 = {
    .gtimer.vtable = &__metal_driver_vtable_up_gtimer.gtimer,
};

// From pwm@20095000.
struct __metal_driver_up_pwm __metal_dt_pwm_20095000 = {
    .pwm.vtable = &__metal_driver_vtable_up_pwm.pwm,
};

// From pwm@20024000.
struct __metal_driver_up_pwm __metal_dt_pwm_20024000 = {
    .pwm.vtable = &__metal_driver_vtable_up_pwm.pwm,
};

// From rtc@20021000.
struct __metal_driver_up_rtc __metal_dt_rtc_20021000 = {
    .rtc.vtable = &__metal_driver_vtable_up_rtc.rtc,
};

// From udl@58000000.
struct __metal_driver_up_udl __metal_dt_udl_58000000 = {
    .udl.vtable = &__metal_driver_vtable_up_udl.udl,
};

// From udl@58010000.
struct __metal_driver_up_dsp __metal_dt_dsp_58010000 = {
    .dsp.vtable = &__metal_driver_vtable_up_dsp.dsp,
};



// From udl@20038000.
struct __metal_driver_up_udl __metal_dt_udl_20038000 = {
    .udl.vtable = &__metal_driver_vtable_up_udl.udl,
};

// From img@58008000.
struct __metal_driver_up_img __metal_dt_img_58008000 = {
    .img.vtable = &__metal_driver_vtable_up_img.img,
};
// From spi@200A6000.
struct __metal_driver_up_spi __metal_dt_spi_200A6000 = {
    .spi.vtable = &__metal_driver_vtable_up_spi.spi,
};

// From spi@200A7000.
struct __metal_driver_up_spi __metal_dt_spi_200A7000 = {
    .spi.vtable = &__metal_driver_vtable_up_spi.spi,
};

// From spi@200A8000.
struct __metal_driver_up_spi __metal_dt_spi_200A8000 = {
    .spi.vtable = &__metal_driver_vtable_up_spi.spi,
};

// From spi@20082000.
struct __metal_driver_up_spi __metal_dt_spi_20082000 = {
    .spi.vtable = &__metal_driver_vtable_up_spi.spi,
};

// From spi@20083000.
struct __metal_driver_up_spi __metal_dt_spi_20083000 = {
    .spi.vtable = &__metal_driver_vtable_up_spi.spi,
};

//From spi@20006000.
struct __metal_driver_up_spi __metal_dt_spi_20006000 = {
    .spi.vtable = &__metal_driver_vtable_up_spi.spi,
};

// From spi@20007000.
struct __metal_driver_up_spi __metal_dt_spi_20007000 = {
    .spi.vtable = &__metal_driver_vtable_up_spi.spi,
};

// From i2c@200A9000.
struct __metal_driver_up_i2c __metal_dt_i2c_200A9000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From i2c@200AA000.
struct __metal_driver_up_i2c __metal_dt_i2c_200AA000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From i2c@200AB000.
struct __metal_driver_up_i2c __metal_dt_i2c_200AB000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From i2c@20084000.
struct __metal_driver_up_i2c __metal_dt_i2c_20084000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From i2c@20085000.
struct __metal_driver_up_i2c __metal_dt_i2c_20085000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From i2c@20086000.
struct __metal_driver_up_i2c __metal_dt_i2c_20086000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From i2c@20087000.
struct __metal_driver_up_i2c __metal_dt_i2c_20087000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From i2c@20008000.
struct __metal_driver_up_i2c __metal_dt_i2c_20008000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From i2c@20009000.
struct __metal_driver_up_i2c __metal_dt_i2c_20009000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From i2c@2000A000.
struct __metal_driver_up_i2c __metal_dt_i2c_2000A000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From i2c@2000B000.
struct __metal_driver_up_i2c __metal_dt_i2c_2000B000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From i2c@2000C000.
struct __metal_driver_up_i2c __metal_dt_i2c_2000C000 = {
    .i2c.vtable = &__metal_driver_vtable_up_i2c.i2c,
};

// From sif@20001000.
struct __metal_driver_up_sif __metal_dt_sif_20001000 = {
    .sif.vtable = &__metal_driver_vtable_up_sif.sif,
};

// From dma@200C0000.
struct __metal_driver_up_dma __metal_dt_dma_200C0000 = {
    .dma.vtable = &__metal_driver_vtable_up_dma.dma,
};

// From dma@200C1000.
struct __metal_driver_up_dma __metal_dt_dma_200C1000 = {
    .dma.vtable = &__metal_driver_vtable_up_dma.dma,
};

// From dma@200C2000.
struct __metal_driver_up_dma __metal_dt_dma_200C2000 = {
    .dma.vtable = &__metal_driver_vtable_up_dma.dma,
};

// From pdm@20090000.
struct __metal_driver_up_pdm __metal_dt_pdm_20090000 = {
    .pdm.vtable = &__metal_driver_vtable_up_pdm.pdm,
};

// From pdm@20091000.
struct __metal_driver_up_pdm __metal_dt_pdm_20091000 = {
    .pdm.vtable = &__metal_driver_vtable_up_pdm.pdm,
};

// From i2s@20092000.
struct __metal_driver_up_i2s __metal_dt_i2s_20092000 = {
    .i2s.vtable = &__metal_driver_vtable_up_i2s.i2s,
};

// From i2s@20093000.
struct __metal_driver_up_i2s __metal_dt_i2s_20093000 = {
    .i2s.vtable = &__metal_driver_vtable_up_i2s.i2s,
};

// From i2s@20094000.
struct __metal_driver_up_i2s __metal_dt_i2s_20094000 = {
    .i2s.vtable = &__metal_driver_vtable_up_i2s.i2s,
};

// From adc@20002000.
struct __metal_driver_up_adc __metal_dt_adc_20002000 = {
    .adc.vtable = &__metal_driver_vtable_up_adc.adc,
};

// From ts@20003000.
struct __metal_driver_up_ts __metal_dt_ts_20003000 = {
    .ts.vtable = &__metal_driver_vtable_up_ts.ts,
};

// From wdt@20023000.
struct __metal_driver_up_wdt __metal_dt_wdt_20023000 = {
    .wdt.vtable = &__metal_driver_vtable_up_wdt.wdt,
};

#endif /* METAL_INLINE_H */
#endif /* ! ASSEMBLY */
