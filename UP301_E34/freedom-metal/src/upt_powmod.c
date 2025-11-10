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

#include "metal.h"
#include "metal/upt_sysctrl.h"
#include "metal/uart.h"
#include "metal/upt_isr.h"
#include "metal/upt_powmod.h"
#include "upt_up301.h"

#ifdef ROM_CODE
#include "flash_map_backend/internal_flash.h"
#endif

#ifdef STDOUT_BAUD_12000000
#define STDOUT_BRD	uart_12000000_baudrate
#elif STDOUT_BAUD_6000000
#define STDOUT_BRD	uart_6000000_baudrate
#elif STDOUT_BAUD_3000000
#define STDOUT_BRD	uart_3000000_baudrate
#else /* STDOUT_BAUD_921600 */
#define STDOUT_BRD	uart_921600_baudrate
#endif

enum_pwmode_retcode_Type __attribute__((weak)) __upt_sleep_init_essentially(void) {
	return 0;
}

enum_pwmode_retcode_Type __attribute__((weak)) __upt_wramboot_init_essentially(void) {
	if (!(STDOUT_BRD == upt_uart_init(__METAL_DT_STDOUT_UART_HANDLE, STDOUT_BRD, uart_flow_ctrl_dis)))
		return E_PWMODE_INVINIT;
	/**
	 * - Clean-up all E34 boot-up events
	 * - Read then Write @ref SCU_BOOTSTAT register
	 */
	upt_power_check_bootup();
	return 0;
}
enum_pwmode_retcode_Type __attribute__((weak)) upt_wramboot_init_hook(void) {
	return E_PWMODE_SUCCESS;
}

void upt_power_Ax_AxSc_Ax(
		uint32_t n_intSrc,
		upt_powermode_AxSc2Ax_int_src_Type* intSrcList,
		uint32_t* axsc_hclk_en) {
	uint32_t backup_mie;

	/**
	 * - Enable SCU to E34 interrupt
	 * 	- Set @ref SCU_RESUME_CLK_INT_EN bit
	 */
	UPT_REG_BIT_SET(RESUME_CLK_INT_EN);

	/**
	 * - Set interrupts allowed to trigger AxSCtoAx
	 *	- Write @ref SCU_RESCLKEN0 ~ @ref SCU_RESCLKEN4 registers
	 */
	uint32_t e34LocalIntEn0 = 0;
	uint32_t e34GlobalIntEn[4];
	uint32_t id;
	e34GlobalIntEn[0] = e34GlobalIntEn[1] = e34GlobalIntEn[2] = e34GlobalIntEn[3] = 0;

	for (int i = 0; i < n_intSrc; ++i) {
		id = intSrcList[i].id;
		intSrcList[i].status = 0;
		if (__is_plic(id)) {
			id = UPT_PLIC_INTERRUPT_ID(id);

			int jndex = id / 32;
			int kndex = id % 32;
			e34GlobalIntEn[jndex] |= ( 1 << kndex );
		}
		else {
			e34LocalIntEn0 |= (1 << (id - CLINT_INT_ID_OFFSET));
		}
	}

	UPT_REG(RESCLKEN0) =  e34LocalIntEn0;
	UPT_REG(RESCLKEN1) =  e34GlobalIntEn[0];
	UPT_REG(RESCLKEN2) =  e34GlobalIntEn[1];
	UPT_REG(RESCLKEN3) =  e34GlobalIntEn[2];
	UPT_REG(RESCLKEN4) =  e34GlobalIntEn[3];

	/**
	 * - Set clock enable settings for GCK on NON-AON PLL1/2 HCLK clock tree in AxSC
	 *	- Write @ref SCU_AXSC_HCLK_EN0 and @ref SCU_AXSC_HCLK_EN1 bits
	 */
	uint32_t axsc_hclk_en0, axsc_hclk_en1;
	if ( axsc_hclk_en == NULL){
		axsc_hclk_en0 =  UPT_REG(HCLKEN0);
		axsc_hclk_en1 = UPT_REG(HCLKEN1);
	}
	else {
		axsc_hclk_en0 = axsc_hclk_en[0];
		axsc_hclk_en1 = axsc_hclk_en[1];
	}

	UPT_SET_REG_BITS(AXSC_HCLK_EN0, axsc_hclk_en0);
	UPT_SET_REG_BITS(AXSC_HCLK_EN1, axsc_hclk_en1);
#if 0
	// TODO: Need to check with SNI, bug????
	/**
	 * - Disable all E34 local and global interrupts except SCU_E34_PowerMode
	 * - Clear @ref SCU_E34_LOCAL_INT_EN and @ref SCU_E34_GLOBAL_INT_EN bit
	 */
  UPT_REG_BIT_CLEAR(E34_LOCAL_INT_EN);
  UPT_REG_BIT_CLEAR(E34_GLOBAL_INT_EN);
#else
	/**
	 * - Disable all E34 local and global interrupts except SCU_E34_PowerMode
	 * - Disable via E34 CSR interrupt enable
	 */
	__asm__ volatile("csrr %0, mie" : "=r"(backup_mie));
	__asm__ volatile("csrw mie, %0" ::"r"(0x10000));
#endif
	/**
	 * - AxtoAxSC
	 * - Set @ref SCU_ENTER_STOP_CLOCK bit
	 */
	UPT_REG_BIT_SET(ENTER_STOP_CLOCK);

	/**
	 * - WFI
 	 */
	UPT_WFI();

	/**
	 * - esume clock (AxSC to Ax) sequence finish IRQ handling
	 */

	/**
	 * - Clean-up INT status
	 *   - Set @ref SCU_RESUME_CLK_INT_STATR bit
	 */
	UPT_REG_BIT_SET(RESUME_CLK_INT_STATR);

	/**
	 * - Check wake up source and clean-up status
	 *   - Read then Write @ref SCU_RESUME_EVNT_STATUS0 ~ @ref SCU_RESUME_EVNT_STATUS4 bits
	 */
	uint32_t ui32Status;
	for (int i = 0; i < n_intSrc; ++i){
		id = intSrcList[i].id;
		ui32Status = 0;
		if (__is_plic(id)) {
			id = UPT_PLIC_INTERRUPT_ID(id);

			int jndex = id / 32;
			int kndex = id % 32;

			switch (jndex) {
			case 0:
				ui32Status = UPT_GET_BITSLICE(RESUME_EVNT_STATUS1) << SCU_RESUME_EVNT_STATUS1_POS;
				break;
			case 1:
				ui32Status = UPT_GET_BITSLICE(RESUME_EVNT_STATUS2) << SCU_RESUME_EVNT_STATUS2_POS;
				break;
			case 2:
				ui32Status = UPT_GET_BITSLICE(RESUME_EVNT_STATUS3) << SCU_RESUME_EVNT_STATUS3_POS;
				break;
			case 3:
				ui32Status = UPT_GET_BITSLICE(RESUME_EVNT_STATUS4) << SCU_RESUME_EVNT_STATUS4_POS;
				break;
			}

			if ( ui32Status & (1 << (kndex)) ){
				intSrcList[i].status = 1;
			}
		}
		else {
			ui32Status = UPT_GET_BITSLICE(RESUME_EVNT_STATUS0) << SCU_RESUME_EVNT_STATUS0_POS;
			if( ui32Status & (1 << (id - CLINT_INT_ID_OFFSET)) ){
				intSrcList[i].status = 1;
			}
		}
	}

	/**
	 * - W1C RESUME_EVNT_STATUS0~4
 	 */
	// RESUME_EVNT_STATUS0
	ui32Status = UPT_GET_BITSLICE(RESUME_EVNT_STATUS0);
	UPT_SET_REG_BITS(RESUME_EVNT_STATUS0, ui32Status);
	// RESUME_EVNT_STATUS1
	ui32Status = UPT_GET_BITSLICE(RESUME_EVNT_STATUS1);
	UPT_SET_REG_BITS(RESUME_EVNT_STATUS1, ui32Status);
	// RESUME_EVNT_STATUS2
	ui32Status = UPT_GET_BITSLICE(RESUME_EVNT_STATUS2);
	UPT_SET_REG_BITS(RESUME_EVNT_STATUS2, ui32Status);
	// RESUME_EVNT_STATUS3
	ui32Status = UPT_GET_BITSLICE(RESUME_EVNT_STATUS3);
	UPT_SET_REG_BITS(RESUME_EVNT_STATUS3, ui32Status);
	// RESUME_EVNT_STATUS4
	ui32Status = UPT_GET_BITSLICE(RESUME_EVNT_STATUS4);
	UPT_SET_REG_BITS(RESUME_EVNT_STATUS4, ui32Status);
#if 0
	// TODO: Need to check with SNI, bug????
	/**
	 * - Enable all E34 loal and global interrupts except local 0 SCU_E34_PowerMode
	 *   - Set @ref SCU_E34_LOCAL_INT_EN and @ref SCU_E34_GLOBAL_INT_EN bit
	 */
	UPT_REG_BIT_SET(E34_LOCAL_INT_EN);
	UPT_REG_BIT_SET(E34_GLOBAL_INT_EN);
#else
  __asm__ volatile("csrw mie, %0" ::"r"(backup_mie));
#endif
}

void upt_power_Ax_to_Sx(
		uint32_t sleep_cycle,
		enum_upt_sram_pwr_ctrl_Type l2sram_domain_pwr,
		enum_upt_l0_volt_Type volt,
		enum_upt_sleep_Type slp_sel) {
	struct metal_gtimer *slp_timer01;
	uint32_t is_cpuinten;

	// TODO: To set PMU power control, use SCU function call instead
	*(volatile int *)(0x20022040) = 0x4;	// PMU [2]=>NAON, [1]=>L2SRAM, [0]=>AON. set NAON is off power
	*(volatile int *)(0x20022008) = 0x20;	// PMU interrupt enable

	/**
	 * - Disable I-Cache invalidation
	 *   - Clear @ref SCU_ICACHE_VALIDBIT_RESET_EN bit
	 */
	UPT_REG_BIT_CLEAR(ICACHE_VALIDBIT_RESET_EN);

	/**
	 * - Clean-up all E34 boot-up events
	 *   - Read then Write @ref SCU_BOOTSTAT register
	 */
	upt_power_check_bootup();

	/**
	 * - SRAM retention and shut-down mode setting
	 *   - Configure @ref SCU_L2SRAM_DOMAIN_PWR bit
	 */
	UPT_REG(AONMB0) &= ~UPT_SHUTDN_SRAM_ALL;
	UPT_REG(AONMB0) |= l2sram_domain_pwr;

	/**
	 * - S/L mode voltage setting
	 */
	switch (volt){
	case UPT_L0_VOLT_RATING_0:
	  break;
	case UPT_L0_VOLT_RATING_1:
	  break;
	case UPT_L0_VOLT_RATING_2:
	  break;
	}

	/**
	 * - Send mailbox message to E21
	 *   - Different mode will be set
	 */
	UPT_REG(AONMB0) &= ~0b110111;
	UPT_REG(AONMB1) &= ~0b10;
	if (slp_sel == UPT_SLP_TO_PSL)
	  UPT_REG(AONMB0) |= 0b100000;
	else if (slp_sel == UPT_SLP_TO_S0)
	  UPT_REG(AONMB0) |= 0b1;
	else if (slp_sel == UPT_SLP_TO_S1)
	  UPT_REG(AONMB0) |= 0b10;
	else if (slp_sel == UPT_SLP_TO_L0)
	  UPT_REG(AONMB0) |= 0b100;

	/**
	 * - Enable interrupt E34 in SCU
	 *  - Set @ref SW_TO_E34_INT_EN bit
	 */
	UPT_REG_BIT_SET(SW_TO_E34_INT_EN);

	/**
	 * - Interrupt E21
	 *  - Set @ref SCU_SW_TO_E21_INT bit
	 */
	UPT_REG_BIT_SET(SW_TO_E21_INT);

	/**
	 * - Wait for @ref SCU_SW_TO_E34_INT_STAT bit set
	 *  - Set @ref SCU_SW_TO_E34_INT_STATR bit to clear the status
	 */
	do {
	__asm__ volatile("nop");
	} while( UPT_GET_BITSLICE(SW_TO_E34_INT_STATR) == 0 );
	UPT_REG_BIT_SET(SW_TO_E34_INT_STATR);

	/**
	 * - Set sleep cycles
	 * - Use tick timer to count down
	 */
	if (slp_sel == UPT_SLP_TO_L0) {
	  slp_timer01 = upt_gtimer_get_device(RTCM_TICK_GTIMER_01);
	}
	else {
	  slp_timer01 = upt_gtimer_get_device(AON_GTIMER_01);
	}
	upt_gtimer_init(slp_timer01, gtimer_first, sleep_cycle);
	upt_gtimer_clear_status(slp_timer01, gtimer_first);
	upt_gtimer_enable(slp_timer01, gtimer_first, 1);
	upt_gtimer_isr_enable(slp_timer01, gtimer_first, gtimer_int_e21);

    // Check mstatus.MIE state.
    __asm__ volatile("csrr %0, mstatus" : "=r"(is_cpuinten));
    is_cpuinten = (is_cpuinten & METAL_MIE_INTERRUPT)? 1 : 0;

	/**
	* - Keep some SOC settings
	*   - Set UTP_init() & IP configurations
	*/
	__upt_sleep_init_essentially();

	/**
	* - Doing up201/301 E34 power-off regular routine in M-mode
	*  - Enter Sleep and context switching here
	*/
	__asm__ volatile("li a0, 0x2000d000");
	__asm__ volatile("ecall");
	__asm__ volatile ("nop");

	/**
	* - Disable tick timer when finished R0 mode
	*  - Use tick timer to count down
	*/
	if (slp_sel == UPT_SLP_TO_L0) {
	   upt_gtimer_enable(slp_timer01, gtimer_first, 0);
	   upt_gtimer_clear_status(slp_timer01, gtimer_first);
	}

	/**
	* - Re-initialize SOC settings
	*   - Set UTP_init() & IP configurations
	*/
	__upt_wramboot_init_essentially();
	upt_wramboot_init_hook();

    // Enable mstatus.MIE.
	if(is_cpuinten) e34_interrupt_enable();
}

#ifndef LOAD_SRAM_CODE
void upt_enter_R0(void) __attribute__ ((section (".FwHandler")));
#endif
void upt_enter_R0(void) {
	/**
	 * - Retention I/O pads
	 *   - Set @ref SCU_XIP_IO_RET_EN bit
	 *   - Set @ref SCU_NAON_IO_RET_EN bit
	 *   - Set @ref SCU_AON_IO_RET_EN bit
	 */
	UPT_REG_BIT_SET(XIP_IO_RET_EN);
	UPT_REG_BIT_SET(NAON_IO_RET_EN);
	UPT_REG_BIT_SET(AON_IO_RET_EN);

	/**
	 * - Start AxtoR0 sequence
	 *   - Set @ref ENTER_RTCM bit
	 */
	UPT_REG_BIT_SET(ENTER_RTCM);

	/**
	 * - WFI
	 */
	UPT_WFI();
}

void upt_power_Ax_to_R0(
		uint32_t n_intSrc,
		enum_upt_rtcm_int_Type* rtcmIntSrcList) {

	// TODO: To set PMU power control, use SCU function call instead
	*(volatile int *)(0x20022040) = 0x7;	// PMU [2]=>NAON, [1]=>L2SRAM, [0]=>AON. set all domains power off
	*(volatile int *)(0x20022008) = 0x20;	// PMU interrupt enable

	upt_power_check_bootup();

	uint32_t ui32Stat = UPT_REG(RTCMRIS);
	/**
	 * - Clean up RTC/RTCM_GPIO interrupt status
	 *   - Set RTCM_STATUS bit
	 */
	UPT_REG(RTCMRIS) = ui32Stat;

	/**
	 * - R0 to Ax wakeup interrupt configuration
	 *   - Tick Timer: @ref SCU_TICK_BOOTUP_EN
	 *   - RTC: @ref SCU_RTC_BOOTUP_EN and @ref SCU_RTC_INT_EN
	 *   - RTCM_GPIO: @ref SCU_GPIO_BOOTUP_EN and @ref SCU_RTCM_GPIO_INT_EN
	 */
	uint32_t id;
	uint32_t rtcm_gpio_int_en = 0;
	for (int i = 0; i < n_intSrc; ++i) {
		id = rtcmIntSrcList[i];

		switch (id) {
		case UPT_RTCM_GPIO_0:
		case UPT_RTCM_GPIO_1:
		case UPT_RTCM_GPIO_2:
		case UPT_RTCM_GPIO_3:
			rtcm_gpio_int_en |= (1 << id);
			break;
		case UPT_RTC:
			//UPT_REG_BIT_SET(RTC_INT_EN);
			UPT_REG_BIT_SET(RTC_BOOTUP_EN);
			break;
		case UPT_TICK_TIMER:
			UPT_REG_BIT_SET(TICK_BOOTUP_EN);
			break;
		}
	}

	if (rtcm_gpio_int_en) {
	  //UPT_SET_REG_BITS(RTCM_GPIO_INT_EN, rtcm_gpio_int_en);
	  UPT_SET_REG_BITS(GPIO_BOOTUP_EN, rtcm_gpio_int_en);
	}

	/**
	 * - Send mailbox message to E21
	 *   - Different mode will be set
	 */
	UPT_REG(AONMB0) &= ~0b110111;
	UPT_REG(AONMB0) |= 0b010000;


	/**
	 * - Enable interrupt E34 in SCU
	 * - Set @ref SW_TO_E34_INT_EN bit
	 */
	UPT_REG_BIT_SET(SW_TO_E34_INT_EN);

	/**
	 * - Interrupt E21
	 * - Set @ref SCU_SW_TO_E21_INT bit
	 **/
	UPT_REG_BIT_SET(SW_TO_E21_INT);

	/**
	 * - Wait for @ref SCU_SW_TO_E34_INT_STAT bit set
	 * - Set @ref SCU_SW_TO_E34_INT_STATR bit to clear the status
	 */
	do {
	__asm__ volatile("nop");
	} while( UPT_GET_BITSLICE(SW_TO_E34_INT_STAT) == 0 );
	UPT_REG_BIT_SET(SW_TO_E34_INT_STATR);

	upt_enter_R0();
}

enum_pwmode_retcode_Type upt_power_enable_bootup(enum_upt_boot_Type BootType, bool enable) {
	if(enable)
		UPT_REG(BOOTEN) |= BootType;
	else
		UPT_REG(BOOTEN) &= ~BootType;
	return E_PWMODE_SUCCESS;
}

uint32_t upt_power_check_bootup(void){

  uint32_t ui32BootStat = UPT_REG(BOOTSTAT);

  if (ui32BootStat){

    /**
     * - Store the boot-up status
     */
#ifdef ROM_CODE
	mcuboot_update_shared_data(BOOT_TYPE, &ui32BootStat);
#endif

    /**
     * - Clean-up all E34 boot-up events
     * - Read then Write @ref SCU_BOOTSTAT register
     */
    UPT_REG(BOOTSTAT) = ui32BootStat;
  }

  return ui32BootStat;
}

bool upt_power_is_bootup_from(enum_upt_boot_Type src) {
  return ((BOOT_SHARED_DATA_PTR->boot_type & src) ? 1 : 0);
}

enum_pwmode_retcode_Type upt_power_set_power_ok_wait_cycle(uint32_t waitcycle) {
	UPT_SET_REG_BITS(POWER_OK_WAIT, waitcycle);
	return E_PWMODE_SUCCESS;
}

enum_pwmode_retcode_Type upt_power_set_gpio_ctrl_wait_cycle(uint32_t waitcycle, bool enable) {
	if (enable) {
		UPT_SET_REG_BITS(GPIO_PWRCTRL_WAIT, waitcycle);
		UPT_SET_REG_BITS(GPIO_PWRCTRL_EN, 1);
	}
	else {
		UPT_SET_REG_BITS(GPIO_PWRCTRL_EN, 0);
	}
	return E_PWMODE_SUCCESS;
}

upt_rtcm_int_stat_Type upt_power_rtcm_interrupt_status(void) {
	return UPT_REG(RTCMRIS);
}

enum_pwmode_retcode_Type upt_power_rtcm_clear_interrupt(upt_rtcm_int_stat_Type int_event) {
	UPT_REG(RTCMRIS) = int_event;
	return E_PWMODE_SUCCESS;
}

enum_pwmode_retcode_Type upt_power_rtcm_enable_interrupt(upt_rtcm_int_stat_Type interrupt, bool enable) {
	(enable)? (UPT_REG(RTCMIE) |= interrupt) : (UPT_REG(RTCMIE) &= ~interrupt);
	return E_PWMODE_SUCCESS;
}

upt_aon_int_stat_Type upt_power_aon_interrupt_status(void) {
	return UPT_REG(AONRIS);
}

enum_pwmode_retcode_Type upt_power_aon_clear_interrupt(upt_aon_int_stat_Type int_event) {
	UPT_REG(AONRIS) = int_event;
	return E_PWMODE_SUCCESS;
}

enum_pwmode_retcode_Type upt_power_aon_enable_interrupt(upt_aon_int_stat_Type interrupt, bool enable) {
	(enable)? (UPT_REG(AONIE) |= interrupt) : (UPT_REG(AONIE) &= ~interrupt);
	return E_PWMODE_SUCCESS;
}

enum_pwmode_retcode_Type upt_power_sif_pmic_trigger(
		enum_upt_sif_tri_src_Type trigger_src,
		enum_upt_sif_tri_Type type) {
	// Set PMIC reset mask condition(s).
	UPT_REG_BIT_CLEAR(SIF_EVENT_MSK);
	UPT_SET_REG_BITS(SIF_EVENT_MSK, ~trigger_src);

	// Use SIF as PMIC trigger.
	UPT_SET_REG_BITS(SWITCH_GPIO_SIF, 1);

	if (type == UPT_SIF_TRI_INTERNAL_0) {
		UPT_SET_REG_BITS(SET_PMIC_UP, 1);
	}
	else if (type == UPT_SIF_TRI_INTERNAL_1) {
		UPT_SET_REG_BITS(SET_PMIC_SIF, 1);
	}
	else if (type == UPT_SIF_TRI_EXTERNAL) {
	}
	else {
		return E_PWMODE_INVPARA;
	}
	return E_PWMODE_SUCCESS;
}

enum_pwmode_retcode_Type upt_power_gpio_pmic_trigger(
		enum_upt_sif_tri_src_Type trigger_src,
		enum_upt_sif_tri_Type type,
		enum_upt_gpio_tri_val_Type org_data,
		enum_upt_gpio_tri_val_Type tri_data) {
	// Set PMIC reset mask condition(s).
	UPT_SET_REG_BITS(SIF_EVENT_MSK, 0x1F);
	UPT_SET_REG_BITS(SIF_EVENT_MSK, ~trigger_src);

	// Use PMIC_GPIOs as PMIC trigger.
	UPT_SET_REG_BITS(SWITCH_GPIO_SIF, 0);

	UPT_SET_REG_BITS(PMIC_CTRL_VALUE, org_data);
	UPT_SET_REG_BITS(PMIC_CTRL_PRESET, tri_data);

	if (type == UPT_SIF_TRI_INTERNAL_0) {
		UPT_SET_REG_BITS(SET_PMIC_UP, 1);
	}
	else if (type == UPT_SIF_TRI_INTERNAL_1) {
		UPT_SET_REG_BITS(SET_PMIC_GPIO, 1);
	}
	else if (type == UPT_SIF_TRI_EXTERNAL) {
		}
	else {
		return E_PWMODE_INVPARA;
	}
	return E_PWMODE_SUCCESS;
}

enum_pwmode_retcode_Type upt_power_sw_to_e34_interrupt(bool enable) {
	if(enable) {
		UPT_SET_REG_BITS(SW_TO_E34_INT_EN, true);
		UPT_SET_REG_BITS(SW_TO_E34_INT, true);
	}
	else {
		UPT_SET_REG_BITS(SW_TO_E34_INT_EN, false);
	}
	return E_PWMODE_SUCCESS;
}

bool upt_power_sw_to_e34_interrupt_status(void) {
	return UPT_GET_BITSLICE(SW_TO_E34_INT_STATR);
}


enum_pwmode_retcode_Type upt_power_sw_to_e34_clear_interrupt(void) {
	UPT_REG_BIT_CLEAR(SW_TO_E34_INT_STATR);
	return E_PWMODE_SUCCESS;
}

enum_pwmode_retcode_Type upt_power_sw_to_e21_interrupt(bool enable) {
	if(enable) {
		UPT_SET_REG_BITS(SW_TO_E21_INT_EN, true);
		UPT_SET_REG_BITS(SW_TO_E21_INT, true);
	}
	else {
		UPT_SET_REG_BITS(SW_TO_E21_INT_EN, false);
	}
	return E_PWMODE_SUCCESS;
}

bool upt_power_sw_to_e21_interrupt_status(void) {
	return UPT_GET_BITSLICE(SW_TO_E21_INT_STATR);
}


enum_pwmode_retcode_Type upt_power_sw_to_e21_clear_interrupt(void) {
	UPT_REG_BIT_CLEAR(SW_TO_E34_INT_STATR);
	return E_PWMODE_SUCCESS;
}

void _upt_power_sw_reset(
		enum_upt_remap_Type remap,
		bool reset_group2_msk,
		uint32_t* reset_group_msk) {
	/* If reset EXREG_RESET_MSK == 0, it will reset all clock tree and IPs */
	UPT_SET_REG_BITS(EXREG_RESET_MSK, reset_group2_msk);
	/* Reset Group mask */
	if(reset_group_msk != NULL) {
		UPT_REG(SWRSTMSK0) = reset_group_msk[0];
		UPT_REG(SWRSTMSK1) = reset_group_msk[1];
		UPT_REG(SWRSTMSK2) = reset_group_msk[2];
	}

	/* Set software reset remap */
	UPT_SET_REG_BITS(SW_REMAP, remap);

	/* Enable software reset */
	UPT_SET_REG_BITS(SW_RESET_EN, true);
	UPT_SET_REG_BITS(SW_RESET, true);
	UPT_WFI();
}
