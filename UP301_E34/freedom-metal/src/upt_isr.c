/*
 * Copyright (C) 2025 UpbeatTech Inc. All Rights Reserved
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
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

#include <stdio.h>

#include "metal.h"
#include "metal/cpu.h"
#include "metal/drivers/up_ospi.h"
#include "metal/ospi.h"
#include "metal-platform.h"
#include "metal/shutdown.h"
#include "metal/upt_powmod.h"
#include "metal/upt_isr.h"
#include "metal/upt_handler.h"
#include "upt_up301.h"

static metal_cpu_Type *__cpu;
static metal_interrupt_Type *__cpu_intr;
static metal_interrupt_Type *__clint;
static metal_interrupt_Type *__plic;
static void __register_default_ecall_handlers();
static void __register_default_cpu_handlers();
static void __register_default_clint_handlers();
static void __register_default_plic_handlers();

void __default_isr(uint32_t id, void *data) {
  metal_shutdown(300);
}

#ifndef LOAD_SRAM_CODE
void _upt_flash_dp(void) __attribute__ ((section (".FwHandler")));
#endif
void _upt_flash_dp(void) {
#ifdef NONE_DP

#endif
#ifdef MX25U1632F_1BIT_DP
	ospi_config_Type ospi_config;
	ospi_frame_info_Type stFrame;
	ospi_field_protocol_Type stProtocol;

	OSPI_INIT_CONFIG(ospi_config);
	upt_ospi_init(__METAL_DT_IO_OSPI_HANDLE, ospi_div_1, ospi_phase_180);
	upt_ospi_set_slave_en(__METAL_DT_IO_OSPI_HANDLE, ospi_slave_0_en);

	OSPI_INIT_FRAME_INFO(stFrame);
	stFrame.cmd = 0xB9;
	stFrame.cmd_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(stProtocol);
	stProtocol.f_code.io_width = ospi_io_single;
	stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(
			__METAL_DT_IO_OSPI_HANDLE,
			&ospi_config,
			ospi_transfer_nd,
			&stFrame,
			&stProtocol);
#if 1
	/* Reset flash */
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) =  ((0x1)<<26) | ((0x28)<<20);
#else
	/* Command ABh return to SPI mode */
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) |= ((((0x14)<<20) | ((0x01)<<18) | (0xAB)));
#endif
#endif
#ifdef MX25U1632F_DP
  /**
   * - Power down Flash (depends on different flash type the implementation will be different)
   *   - Set Flash command: 0xB9h -> deep power-down (DP) for MX25U1632F
   */
	ospi_config_Type ospi_config;
	ospi_frame_info_Type stFrame;
	ospi_field_protocol_Type stProtocol;

	OSPI_INIT_CONFIG(ospi_config);
	upt_ospi_init(__METAL_DT_IO_OSPI_HANDLE, 0, ospi_phase_180);
	upt_ospi_set_slave_en(__METAL_DT_IO_OSPI_HANDLE, ospi_slave_0_en);

	OSPI_INIT_FRAME_INFO(stFrame);
	stFrame.cmd = 0xB9;
	stFrame.cmd_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(stProtocol);
	stProtocol.f_code.io_width = ospi_io_quad;
	stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(
			__METAL_DT_IO_OSPI_HANDLE,
			&ospi_config,
			ospi_transfer_nd,
			&stFrame,
			&stProtocol);
#if 1
	/* Reset flash */
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) |= ((((0x1)<<26) | ((0x1F)<<20) | ((0x01)<<16)));
#else
	/* Command ABh return to SPI mode */
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) |= ((((0x1F)<<20) | ((0x01)<<18) | ((0x01)<<16) | (0xAB)));
#endif
#endif
#ifdef MX25U6345G_SDR_DP
  /**
   * - Power down Flash (depends on different flash type the implementation will be different)
   *   - Set Flash command: 0xB9h -> deep power-down (DP) for MX25U1632F
   */
	ospi_config_Type ospi_config;
	ospi_frame_info_Type stFrame;
	ospi_field_protocol_Type stProtocol;

	OSPI_INIT_CONFIG(ospi_config);
	upt_ospi_init(__METAL_DT_IO_OSPI_HANDLE, 0, ospi_phase_180);
	upt_ospi_set_slave_en(__METAL_DT_IO_OSPI_HANDLE, ospi_slave_0_en);

	OSPI_INIT_FRAME_INFO(stFrame);
	stFrame.cmd = 0xB946;
	stFrame.cmd_len = 2U;
	OSPI_INIT_FIELD_PROTOCOL(stProtocol);
	stProtocol.f_code.io_width = ospi_io_octal;
	stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(
			__METAL_DT_IO_OSPI_HANDLE,
			&ospi_config,
			ospi_transfer_nd,
			&stFrame,
			&stProtocol);
#if 1
	/* Reset flash */
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) |= ((((0x1)<<26) | ((0x1F)<<20) | ((0x02)<<16)));
#else
	/* Command ABh return to SPI mode */
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMMB3) |= ((((0x1F)<<20) | ((0x01)<<18) | ((0x02)<<16) | (0xAB54)));
#endif
#endif
}

uint32_t mem_read;
#ifndef LOAD_SRAM_CODE
void _upt_flash_resume(void) __attribute__ ((section (".FwHandler")));
#endif
void _upt_flash_resume(void) {
#ifdef NONE_DP

#endif
#ifdef MX25U1632F_1BIT_DP
	  /**
	   * - Power down Flash (depends on different flash type the implementation will be different)
	   *   - Set Flash command: 0xB9h -> deep power-down (DP) for MX25U1632F
	   */
	ospi_config_Type ospi_config;
	ospi_frame_info_Type stFrame;
	ospi_field_protocol_Type stProtocol;

	OSPI_INIT_CONFIG(ospi_config);
	upt_ospi_init(__METAL_DT_IO_OSPI_HANDLE, 0, ospi_phase_180);
	upt_ospi_set_slave_en(__METAL_DT_IO_OSPI_HANDLE, ospi_slave_0_en);

	OSPI_INIT_FRAME_INFO(stFrame);
	stFrame.cmd = 0xAB;
	stFrame.cmd_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(stProtocol);
	stProtocol.f_code.io_width = ospi_io_single;
	stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(
			__METAL_DT_IO_OSPI_HANDLE,
			&ospi_config,
			ospi_transfer_nd,
			&stFrame,
			&stProtocol);
#endif
#ifdef MX25U1632F_DP
  /**
   * - Power down Flash (depends on different flash type the implementation will be different)
   *   - Set Flash command: 0xB9h -> deep power-down (DP) for MX25U1632F
   */
	ospi_config_Type ospi_config;
	ospi_frame_info_Type stFrame;
	ospi_field_protocol_Type stProtocol;

	OSPI_INIT_CONFIG(ospi_config);
	upt_ospi_init(__METAL_DT_IO_OSPI_HANDLE, 0, ospi_phase_180);
	upt_ospi_set_slave_en(__METAL_DT_IO_OSPI_HANDLE, ospi_slave_0_en);

	OSPI_INIT_FRAME_INFO(stFrame);
	stFrame.cmd = 0xAB;
	stFrame.cmd_len = 1U;
	OSPI_INIT_FIELD_PROTOCOL(stProtocol);
	stProtocol.f_code.io_width = ospi_io_quad;
	stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(
			__METAL_DT_IO_OSPI_HANDLE,
			&ospi_config,
			ospi_transfer_nd,
			&stFrame,
			&stProtocol);
#endif
#ifdef MX25U6345G_SDR_DP
  /**
   * - Power down Flash (depends on different flash type the implementation will be different)
   *   - Set Flash command: 0xB9h -> deep power-down (DP) for MX25U1632F
   */
	ospi_config_Type ospi_config;
	ospi_frame_info_Type stFrame;
	ospi_field_protocol_Type stProtocol;

	OSPI_INIT_CONFIG(ospi_config);
	upt_ospi_init(__METAL_DT_IO_OSPI_HANDLE, 0, ospi_phase_180);
	upt_ospi_set_slave_en(__METAL_DT_IO_OSPI_HANDLE, ospi_slave_0_en);

	OSPI_INIT_FRAME_INFO(stFrame);
	stFrame.cmd = 0xAB54;
	stFrame.cmd_len = 2U;
	OSPI_INIT_FIELD_PROTOCOL(stProtocol);
	stProtocol.f_code.io_width = ospi_io_octal;
	stProtocol.f_code.data_rate = ospi_data_rate_sdr;
	upt_ospi_transfer(
			__METAL_DT_IO_OSPI_HANDLE,
			&ospi_config,
			ospi_transfer_nd,
			&stFrame,
			&stProtocol);
#endif

	/* Delay at least 30us */
#if 0
	//TODO: move code to SRAM, now not fixed yet
	unsigned long long nowmtime, nowmtime_;
	nowmtime = __metal_driver_cpu_mtime_get(__METAL_DT_E34_CPU_HANDLE);
	do {
		nowmtime_ = __metal_driver_cpu_mtime_get(__METAL_DT_E34_CPU_HANDLE);
	}while((nowmtime == nowmtime_) || ((nowmtime+1) == nowmtime_));
#else
	//Dummy instructions (every instruction is taking 30us)
	int temp;
	temp = *(volatile unsigned int *)0x20021004;
	temp = *(volatile unsigned int *)0x20021004;
#endif
}

#ifndef LOAD_SRAM_CODE
void __weak_symbol exception_ecall_handler(metal_cpu_Type *cpu, uint32_t ecode) __attribute__ ((section (".FwHandler")));
#endif
void __weak_symbol exception_ecall_handler(metal_cpu_Type *cpu, uint32_t ecode) {
	uint32_t ret_addr;

	if( (ecode == METAL_ECALL_U_EXCEPTION_CODE) || (ecode == METAL_ECALL_M_EXCEPTION_CODE)) {
		__asm__ volatile("csrr %0, mepc" : "=r"(ret_addr));
		__asm__ volatile("csrw mepc, %0" ::"r"(ret_addr+4));
		_upt_flash_dp();
		_upt_enter_sleep();
		_upt_flash_resume();
	}
}

void __weak_symbol scu_e34_powermode_isr(uint32_t id, void *data){
  //
  // Clean-up RESUME_CLK_INT_STATR bit
  // : the resume clock (AxSCtoAx) sequence finish
  //
  UPT_REG_BIT_SET(RESUME_CLK_INT_STATR);
}

void __weak_symbol scu_e34_bootup_isr(uint32_t id, void *data){

  //
  // Check and cleanup bootup events
  //
  upt_power_check_bootup();

}

void __weak_symbol scu_e34_sw_isr(uint32_t id, void *data){

  // Do nothing
  // No Clean-up SW_TO_E34_INT_STATR bit
  // Leave it to SW to handle
  // UPT_REG_BIT_SET(SW_TO_E34_INT_STATR);
}

/* SW interrupt handler */
void __weak_symbol default_sw_isr(uint32_t id, void *priv) {
    upt_uart_printf(__METAL_DT_STDOUT_UART_HANDLE, "SW interrupt triggered.\n");

    // Clear MSIP bit to avoid continuous triggering.
    metal_cpu_software_clear_ipi(__cpu, 0);
}

/* Initialize register and enable software interrupt */
void init_sw_interrupt(void *sw_isr_handler) {
	if (sw_isr_handler == NULL) {
		sw_isr_handler = default_sw_isr;
	}

    // Register SW interrupt handler
	metal_interrupt_register_handler(__cpu_intr, METAL_INTERRUPT_ID_SW, (metal_interrupt_handler_t)sw_isr_handler, NULL);

    // Enable SW interrupt
	metal_interrupt_enable(__cpu_intr, METAL_INTERRUPT_ID_SW);
}

/* Trigger software interrupt */
void trigger_sw_interrupt(void) {
	metal_cpu_software_set_ipi(__cpu, 0);
}

#define INFORM_WDT_CHECK_IN 0x40
void __weak_symbol aon_wdt_isr(uint32_t id, void *data){
	UPT_REG(AONMB0) |= INFORM_WDT_CHECK_IN;
}

void init_interrupts(void) {
  __cpu = metal_cpu_get(metal_cpu_get_current_hartid());

  __cpu_intr = metal_cpu_interrupt_controller(__cpu);
  metal_interrupt_init(__cpu_intr);

  __clint = metal_interrupt_get_controller(METAL_CLINT_CONTROLLER,
                                           metal_cpu_get_current_hartid());
  metal_interrupt_init(__clint);

  __plic = metal_interrupt_get_controller(METAL_PLIC_CONTROLLER,
                                          metal_cpu_get_current_hartid());
  metal_interrupt_init(__plic);

  metal_interrupt_set_threshold(__plic, 1);

  // Register default exception ecall handlers
  __register_default_ecall_handlers();

    // Register default clint handlers
  __register_default_cpu_handlers();

  // Register default clint handlers
  __register_default_clint_handlers();

  // Register default plic handlers
  __register_default_plic_handlers();

  // Initialize software interrupt
  init_sw_interrupt(NULL);
}

int32_t e34_interrupt_enable(){//TODO: need to debug
  return metal_interrupt_enable(__cpu_intr, 0);
}

int32_t e34_interrupt_disable(){
  return metal_interrupt_disable(__cpu_intr, 0);
}

int32_t __clint_interrupt_enable(uint32_t id){
  return metal_interrupt_enable(__cpu_intr, id);
}

int32_t __clint_interrupt_disable(uint32_t id){
  return metal_interrupt_disable(__cpu_intr, id);
}

#ifndef LOAD_SRAM_CODE
int32_t __plic_interrupt_set_priority(uint32_t id, uint32_t priority) __attribute__ ((section (".FwHandler")));
#endif
int32_t __plic_interrupt_set_priority(uint32_t id, uint32_t priority){
  return metal_interrupt_set_priority(__plic, id, priority);
}

#ifndef LOAD_SRAM_CODE
int32_t __plic_interrupt_enable(uint32_t id) __attribute__ ((section (".FwHandler")));
#endif
int32_t __plic_interrupt_enable(uint32_t id){
  return metal_interrupt_enable(__plic, id);
}

int32_t __plic_interrupt_disable(uint32_t id){
  return metal_interrupt_disable(__plic, id);
}

#ifndef LOAD_SRAM_CODE
uint32_t __is_plic(uint32_t id) __attribute__ ((section (".FwHandler")));
#endif
uint32_t __is_plic(uint32_t id){
  return (id & UPT_PLIC_ID_FLAG) ? 1 : 0;
}

#ifndef LOAD_SRAM_CODE
int32_t upt_interrupt_enable(uint32_t id) __attribute__ ((section (".FwHandler")));
#endif
int32_t upt_interrupt_enable(uint32_t id){

  if( __is_plic(id) ){
    return __plic_interrupt_enable(UPT_PLIC_INTERRUPT_ID(id));
  }
  else{
    return __clint_interrupt_enable(id);
  }

}

int32_t upt_interrupt_disable(uint32_t id){

  if( __is_plic(id) ){
    return __plic_interrupt_disable(UPT_PLIC_INTERRUPT_ID(id));
  }
  else{
    return __clint_interrupt_disable(id);
  }

}

#ifndef LOAD_SRAM_CODE
int32_t upt_interrupt_set_priority(uint32_t id, uint32_t priority) __attribute__ ((section (".FwHandler")));
#endif
int32_t upt_interrupt_set_priority(uint32_t id, uint32_t priority){

  if( __is_plic(id) ){
    return __plic_interrupt_set_priority(UPT_PLIC_INTERRUPT_ID(id), priority);
  }
  else{
    return -1;
  }

}

#ifndef LOAD_SRAM_CODE
int32_t upt_interrupt_register_handle(uint32_t id, metal_interrupt_handler_t handler, void *priv_data)  __attribute__ ((section (".FwHandler")));
#endif
int32_t upt_interrupt_register_handle(uint32_t id, metal_interrupt_handler_t handler, void *priv_data)
{
  if( __is_plic(id) ){
	  return metal_interrupt_register_handler(__plic, UPT_PLIC_INTERRUPT_ID(id), handler, priv_data);
  }
  return metal_interrupt_register_handler(__cpu_intr, id, handler, priv_data);
}

//
// CPU ISR
//
__weak_reference(__default_isr, cpu_software_isr);
__weak_reference(__default_isr, cpu_mtime_isr);

//
// CLINT ISR
//
//__weak_reference(__default_isr, scu_e34_powermode_isr);
//__weak_reference(__default_isr, scu_e34_bootup_isr);
//__weak_reference(__default_isr, scu_e34_sw_isr);
__weak_reference(__default_isr, scu_pllx_stable_change_isr);
__weak_reference(__default_isr, aon_timer2to3_isr);
__weak_reference(__default_isr, fw_timer2to3_isr);
__weak_reference(__default_isr, sys_timer_7_isr);
__weak_reference(__default_isr, udl2_isr);
__weak_reference(__default_isr, udl1_isr);
__weak_reference(__default_isr, nema_irq_isr);
__weak_reference(__default_isr, nema_syserror_irq_isr);
__weak_reference(__default_isr, nema_freeze_isr);
__weak_reference(__default_isr, nemadc_irq_isr);
__weak_reference(__default_isr, dmac2_isr);
__weak_reference(__default_isr, dmac1_isr);
__weak_reference(__default_isr, dmac0_isr);

//
// System GPIO ISR
//
__weak_reference(__default_isr, sys_gpio_0_isr);
__weak_reference(__default_isr, sys_gpio_1_isr);
__weak_reference(__default_isr, sys_gpio_2_isr);
__weak_reference(__default_isr, sys_gpio_3_isr);
__weak_reference(__default_isr, sys_gpio_4_isr);
__weak_reference(__default_isr, sys_gpio_5_isr);
__weak_reference(__default_isr, sys_gpio_6_isr);
__weak_reference(__default_isr, sys_gpio_7_isr);
__weak_reference(__default_isr, sys_gpio_8_isr);
__weak_reference(__default_isr, sys_gpio_9_isr);
__weak_reference(__default_isr, sys_gpio_10_isr);
__weak_reference(__default_isr, sys_gpio_11_isr);
__weak_reference(__default_isr, sys_gpio_12_isr);
__weak_reference(__default_isr, sys_gpio_13_isr);
__weak_reference(__default_isr, sys_gpio_14_isr);
__weak_reference(__default_isr, sys_gpio_15_isr);
__weak_reference(__default_isr, sys_gpio_16_isr);
__weak_reference(__default_isr, sys_gpio_17_isr);
__weak_reference(__default_isr, sys_gpio_18_isr);
__weak_reference(__default_isr, sys_gpio_19_isr);
__weak_reference(__default_isr, sys_gpio_20_isr);
__weak_reference(__default_isr, sys_gpio_21_isr);
__weak_reference(__default_isr, sys_gpio_22_isr);
__weak_reference(__default_isr, sys_gpio_23_isr);
__weak_reference(__default_isr, sys_gpio_24_isr);
__weak_reference(__default_isr, sys_gpio_25_isr);
__weak_reference(__default_isr, sys_gpio_26_isr);
__weak_reference(__default_isr, sys_gpio_27_isr);
__weak_reference(__default_isr, sys_gpio_28_isr);
__weak_reference(__default_isr, sys_gpio_29_isr);
__weak_reference(__default_isr, sys_gpio_30_isr);
__weak_reference(__default_isr, sys_gpio_31_isr);
__weak_reference(__default_isr, sys_gpio_32_isr);
__weak_reference(__default_isr, sys_gpio_33_isr);
__weak_reference(__default_isr, sys_gpio_34_isr);
__weak_reference(__default_isr, sys_gpio_35_isr);
__weak_reference(__default_isr, sys_gpio_36_isr);
__weak_reference(__default_isr, sys_gpio_37_isr);
__weak_reference(__default_isr, sys_gpio_38_isr);
__weak_reference(__default_isr, sys_gpio_39_isr);
__weak_reference(__default_isr, sys_gpio_40_isr);
__weak_reference(__default_isr, sys_gpio_41_isr);
__weak_reference(__default_isr, sys_gpio_42_isr);
__weak_reference(__default_isr, sys_gpio_43_isr);
__weak_reference(__default_isr, sys_gpio_44_isr);

//
// Peripheral GPIO ISR
//
__weak_reference(__default_isr, peri_gpio_0_isr);
__weak_reference(__default_isr, peri_gpio_1_isr);
__weak_reference(__default_isr, peri_gpio_2_isr);
__weak_reference(__default_isr, peri_gpio_3_isr);
__weak_reference(__default_isr, peri_gpio_4_isr);
__weak_reference(__default_isr, peri_gpio_5_isr);
__weak_reference(__default_isr, peri_gpio_6_isr);
__weak_reference(__default_isr, peri_gpio_7_isr);
__weak_reference(__default_isr, peri_gpio_8_isr);
__weak_reference(__default_isr, peri_gpio_9_isr);
__weak_reference(__default_isr, peri_gpio_10_isr);
__weak_reference(__default_isr, peri_gpio_11_isr);
__weak_reference(__default_isr, peri_gpio_12_isr);
__weak_reference(__default_isr, peri_gpio_13_isr);
__weak_reference(__default_isr, peri_gpio_14_isr);
__weak_reference(__default_isr, peri_gpio_15_isr);
__weak_reference(__default_isr, peri_gpio_16_isr);
__weak_reference(__default_isr, peri_gpio_17_isr);
__weak_reference(__default_isr, peri_gpio_18_isr);
__weak_reference(__default_isr, peri_gpio_19_isr);
__weak_reference(__default_isr, peri_gpio_20_isr);
__weak_reference(__default_isr, peri_gpio_21_isr);
__weak_reference(__default_isr, peri_gpio_22_isr);
__weak_reference(__default_isr, peri_gpio_23_isr);
__weak_reference(__default_isr, peri_gpio_24_isr);
__weak_reference(__default_isr, peri_gpio_25_isr);
__weak_reference(__default_isr, peri_gpio_26_isr);
__weak_reference(__default_isr, peri_gpio_27_isr);
__weak_reference(__default_isr, peri_gpio_28_isr);
__weak_reference(__default_isr, peri_gpio_29_isr);

//
// System Timer ISR
//
__weak_reference(__default_isr, sys_timer_0_isr);
__weak_reference(__default_isr, sys_timer_1_isr);
__weak_reference(__default_isr, sys_timer_2_isr);
__weak_reference(__default_isr, sys_timer_3_isr);
__weak_reference(__default_isr, sys_timer_4_isr);
__weak_reference(__default_isr, sys_timer_5_isr);
__weak_reference(__default_isr, sys_timer_6_isr);

//
// OSPI, SPI ISR
//
__weak_reference(__default_isr, ospi_isr);
__weak_reference(__default_isr, spi0_master_slave_isr);
__weak_reference(__default_isr, spi1_master_isr);
__weak_reference(__default_isr, spi2_master_isr);
__weak_reference(__default_isr, spi3_master_isr);

//
// DSI controller
//
__weak_reference(__default_isr, dsi_controller_isr);

//
// UART ISR
//
__weak_reference(__default_isr, uart0_isr);
__weak_reference(__default_isr, uart1_isr);
__weak_reference(__default_isr, uart2_isr);
__weak_reference(__default_isr, uart3_isr);

//
// I2C ISR
//
__weak_reference(__default_isr, i2c0_isr);
__weak_reference(__default_isr, i2c1_isr);
__weak_reference(__default_isr, i2c2_isr);
__weak_reference(__default_isr, i2c3_isr);
__weak_reference(__default_isr, i2c4_isr);
__weak_reference(__default_isr, i2c5_isr);
__weak_reference(__default_isr, i2c6_isr);

//
// PUF ISR
//
__weak_reference(__default_isr, pufiot_isr);

//
// NemaDC ISR
//
__weak_reference(__default_isr, nemadc_isr);

//
// audio ISR
//
__weak_reference(__default_isr, pdmtopcm0_isr);
__weak_reference(__default_isr, pdmtopcm1_isr);
__weak_reference(__default_isr, i2s0_master_isr);
__weak_reference(__default_isr, i2s1_master_slave_isr);

//
// PWM ISR
//
__weak_reference(__default_isr, peri_pwm_0_isr);
__weak_reference(__default_isr, peri_pwm_1_isr);
__weak_reference(__default_isr, peri_pwm_2_isr);
__weak_reference(__default_isr, peri_pwm_3_isr);

//
// SDC ISR
//
__weak_reference(__default_isr, sdc_isr);

//
// RTCM GPIO ISR
//
__weak_reference(__default_isr, rtcm_gpio_isr);

//
// RTC ISR
//
__weak_reference(__default_isr, rtc_isr);
__weak_reference(__default_isr, tick_timer_isr);

__weak_reference(__default_isr, pmu_isr);
__weak_reference(__default_isr, wdt_isr);
__weak_reference(__default_isr, aon_pwm_isr);
__weak_reference(__default_isr, fw_timer0to1_isr);
__weak_reference(__default_isr, sif_isr);
__weak_reference(__default_isr, tempsensor_isr);

//
// AON Domain
//
__weak_reference(__default_isr, aon_uart_isr);
__weak_reference(__default_isr, aon_spi0to1_isr);
__weak_reference(__default_isr, aon_i2c0to4_isr);
__weak_reference(__default_isr, aon_timer0to1_isr);
__weak_reference(__default_isr, adc_audio0to3_isr);
__weak_reference(__default_isr, adc_general0to5_isr);
__weak_reference(__default_isr, aon_gpio_0to20_isr);

#define CPU_INTERRUPT_REGISTER_HANDLER(src_name, priv_data)           \
  metal_interrupt_register_handler(__cpu_intr, upt_##src_name##_int_id, src_name##_isr, priv_data)
#define CLINT_INTERRUPT_REGISTER_HANDLER(src_name, priv_data)           \
  metal_interrupt_register_handler(__cpu_intr, upt_##src_name##_int_id, src_name##_isr, priv_data)
#define PLIC_INTERRUPT_REGISTER_HANDLER(src_name, priv_data)            \
  metal_interrupt_register_handler(__plic, UPT_PLIC_INTERRUPT_ID(upt_##src_name##_int_id), src_name##_isr, priv_data)


static void __register_default_ecall_handlers(){
  metal_cpu_exception_register(__cpu, METAL_ECALL_U_EXCEPTION_CODE, exception_ecall_handler);
  metal_cpu_exception_register(__cpu, METAL_ECALL_M_EXCEPTION_CODE, exception_ecall_handler);
}

static void __register_default_cpu_handlers(){
  CPU_INTERRUPT_REGISTER_HANDLER(cpu_software, NULL);
  CPU_INTERRUPT_REGISTER_HANDLER(cpu_mtime, NULL);
}

static void __register_default_clint_handlers(){
  CLINT_INTERRUPT_REGISTER_HANDLER(scu_e34_powermode, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(scu_e34_bootup, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(scu_e34_sw, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(scu_pllx_stable_change, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(aon_timer2to3, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(fw_timer2to3, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(sys_timer_7, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(udl2, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(udl1, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(nema_irq, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(nema_syserror_irq, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(nema_freeze, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(nemadc_irq, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(dmac2, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(dmac1, NULL);
  CLINT_INTERRUPT_REGISTER_HANDLER(dmac0, NULL);
}

static void __register_default_plic_handlers(){
  PLIC_INTERRUPT_REGISTER_HANDLER(ospi, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(dsi_controller, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(uart0, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(uart1, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(spi0_master_slave, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(spi1_master, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(i2c0, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(i2c1, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(i2c2, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(pufiot, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_0, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_1, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_2, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_3, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_4, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_5, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_6, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_7, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_8, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_9, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_10, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_11, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_12, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_13, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_14, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_15, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_16, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_17, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_18, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_19, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_20, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_21, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_22, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_23, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_24, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_25, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_26, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_27, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_28, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_29, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_30, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_31, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_32, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_33, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_34, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_35, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_36, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_37, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_38, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_39, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_40, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_41, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_42, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_43, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_gpio_44, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(nemadc, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(spi2_master, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(spi3_master, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(i2c3, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(i2c4, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(i2c5, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(i2c6, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_0, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_1, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_2, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_3, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_4, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_5, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_6, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_7, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_8, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_9, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_10, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_11, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_12, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_13, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_14, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_15, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_16, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_17, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_18, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_19, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_20, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_21, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_22, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_23, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_24, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_25, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_26, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_27, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_28, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_gpio_29, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(uart2, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(uart3, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(pdmtopcm0, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(pdmtopcm1, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(i2s0_master, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(i2s1_master_slave, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_pwm_0, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_pwm_1, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_pwm_2, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(peri_pwm_3, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_timer_0, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_timer_1, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_timer_2, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_timer_3, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_timer_4, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_timer_5, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sys_timer_6, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sdc, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(rtcm_gpio, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(rtc, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(tick_timer, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(pmu, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(aon_wdt, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(aon_pwm, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(fw_timer0to1, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(sif, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(tempsensor, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(aon_uart, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(aon_spi0to1, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(aon_i2c0to4, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(aon_timer0to1, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(adc_audio0to3, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(adc_general0to5, NULL);
  PLIC_INTERRUPT_REGISTER_HANDLER(aon_gpio_0to20, NULL);
}
