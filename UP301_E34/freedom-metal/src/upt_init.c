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
#include <string.h>

#include "metal.h"
#include "metal/init.h"
#include "metal/i2c.h"
#include "metal/upt_init.h"
#include "metal/upt_isr.h"
#include "metal/upt_handler.h"
#include "metal/upt_powmod.h"
#include "metal/rtc.h"
#include "metal/wdt.h"

#ifdef LOAD_E21_CODE
#include "upt_up301_e21.h"
#endif /* LOAD_E21_CODE */

static metal_wdt_Type *__sys_wdt;

static enum_upt_retcode_Type __initial_aon_wdt_interrupts() {
    upt_interrupt_set_priority(UPT_INTERRUPT_ID(aon_wdt), 2);
    upt_interrupt_enable(UPT_INTERRUPT_ID(aon_wdt));
    return E_UPT_SUCCESS;
}


enum_upt_retcode_Type upt_wdt_activate(uint32_t wdt_cnt) {
	__sys_wdt = upt_wdt_get_device(AON_WDT);
	upt_wdt_init(__sys_wdt, wdt_cnt);

#ifdef WDT_ISR_ALWAYS_KICK
	upt_wdt_isr_enable(__sys_wdt, 1);
#else
	upt_wdt_isr_enable(__sys_wdt, 0);
#endif

	upt_wdt_enable(__sys_wdt, 1);

	#ifndef CONFIG_UPBEAT_HAL
		// Enable E34 ISR
		return __initial_aon_wdt_interrupts();
	#else 
		return 0;
	#endif
	
}

enum_upt_retcode_Type upt_wdt_deactivate(void) {
	__sys_wdt = upt_wdt_get_device(AON_WDT);
	upt_wdt_enable(__sys_wdt, 0);

	#ifndef CONFIG_UPBEAT_HAL
		// Disable E34 ISR
		upt_interrupt_disable(UPT_INTERRUPT_ID(aon_wdt));
	#endif

	return E_UPT_SUCCESS;
}

#define INFORM_WDT_CHECK_IN 0x40
void upt_wdt_software_kick(void) {
	UPT_REG(AONMB0) |= INFORM_WDT_CHECK_IN;
}

#ifndef CONFIG_UPBEAT_HAL
static enum_upt_retcode_Type __initial_dtimsram() {
	for (int i=0; i<0x8000; i+=4) {
		*(volatile uint32_t *)(0x80000000+i) = 0;
	};
	for (int i=0; i<0x8000; i+=4) {
		*(volatile uint32_t *)(0x30000000+i) = 0;
	};
	return E_UPT_SUCCESS;
}

static enum_upt_retcode_Type __clear_booup_event(void) {

	// All reset is cleared. This function should be called one-time only.
	upt_power_check_bootup();

	// All reset is enabled.
	upt_power_enable_bootup(UPT_POWERON_BOOT_ENABLE_ALL, 1);

	// Clear pseudo warmboot event flag.
	UPT_REG(AONMB1) &= ~0x2;
	return E_UPT_SUCCESS;

}

static enum_upt_retcode_Type __rcosc_auto_trimming(void) {
	UPT_SET_REG_BITS(RCOSC_AUTOTRIM_EN, true);

	if ( (UPT_GET_BITSLICE(RCOSC_TRIM_COUNT) < UPT_GET_BITSLICE(RCOSC_AUTOTRIM_UP)) && (UPT_GET_BITSLICE(RCOSC_TRIM_COUNT) > UPT_GET_BITSLICE(RCOSC_AUTOTRIM_LO)) ) {
		UPT_SET_REG_BITS(RCOSC_AUTOTRIM_EN, false);
	}
	return E_UPT_SUCCESS;
}

#define RTCM_GPIO_CNT 		4
#define A0_VOTAGE_SHIFT 	0
#define S0_VOTAGE_SHIFT 	8
#define S1_VOTAGE_SHIFT 	16
#define L0_VOTAGE_SHIFT 	24
#if defined(PMIC_TPS628604) // For MCU Board
#define PMIC_SLAVE_ADDRESS 	0x40
#define TPS628604_VOUT 		0x01
#define TPS628604_VOUT2 	0x02
#define TPS628604_CONTROL 	0x03
#define TPS628604_STATUS 	0x05

#define VOUT_0_4V     0x00
#define VOUT_0_4125V  0x01
#define VOUT_0_425V   0x02
#define VOUT_0_4375V  0x03
#define VOUT_0_45V    0x04
#define VOUT_0_4625V  0x05
#define VOUT_0_475V   0x06
#define VOUT_0_4875V  0x07
#define VOUT_0_5V     0x08
#define VOUT_0_5125V  0x09
#define VOUT_0_525V   0x0A
#define VOUT_0_5375V  0x0B
#define VOUT_0_55V    0x0C
#define VOUT_0_5625V  0x0D
#define VOUT_0_575V   0x0E
#define VOUT_0_5875V  0x0F
#define VOUT_0_6V     0x10
#define VOUT_0_6125V  0x11
#define VOUT_0_625V   0x12
#define VOUT_0_6375V  0x13
#define VOUT_0_65V    0x14
#define VOUT_0_6625V  0x15
#define VOUT_0_675V   0x16
#define VOUT_0_6875V  0x17
#define VOUT_0_7V     0x18
#define VOUT_0_7125V  0x19
#define VOUT_0_725V   0x1A
#define VOUT_0_7375V  0x1B
#define VOUT_0_75V    0x1C
#define VOUT_0_7625V  0x1D
#define VOUT_0_775V   0x1E
#define VOUT_0_7875V  0x1F
#define VOUT_0_8V     0x20
#define VOUT_0_8125V  0x21
#define VOUT_0_825V   0x22
#define VOUT_0_8375V  0x23
#define VOUT_0_85V    0x24
#define VOUT_0_8625V  0x25
#define VOUT_0_875V   0x26
#define VOUT_0_8875V  0x27
#define VOUT_0_9V     0x28
#define VOUT_0_9125V  0x29
#define VOUT_0_925V   0x2A
#define VOUT_0_9375V  0x2B
#define VOUT_0_95V    0x2C
#define VOUT_0_9625V  0x2D
#define VOUT_0_975V   0x2E
#define VOUT_0_9875V  0x2F
#define VOUT_1V       0x30
#define VOUT_1_0125V  0x31
#define VOUT_1_025V   0x32
#define VOUT_1_0375V  0x33
#define VOUT_1_05V    0x34
#define VOUT_1_0625V  0x35
#define VOUT_1_075V   0x36
#define VOUT_1_0875V  0x37
#define VOUT_1_1V     0x38
#define VOUT_1_1125V  0x39
#define VOUT_1_125V   0x3A
#define VOUT_1_1375V  0x3B
#define VOUT_1_15V    0x3C
#define VOUT_1_1625V  0x3D
#define VOUT_1_175V   0x3E
#define VOUT_1_1875V  0x3F
#define VOUT_1_2V     0x40
#define VOUT_1_2125V  0x41
#define VOUT_1_225V   0x42
#define VOUT_1_2375V  0x43
#define VOUT_1_25V    0x44
#define VOUT_1_2625V  0x45
#define VOUT_1_275V   0x46
#define VOUT_1_2875V  0x47
#define VOUT_1_3V     0x48
#define VOUT_1_3125V  0x49
#define VOUT_1_325V   0x4A
#define VOUT_1_3375V  0x4B
#define VOUT_1_35V    0x4C
#define VOUT_1_3625V  0x4D
#define VOUT_1_375V   0x4E
#define VOUT_1_3875V  0x4F
#define VOUT_1_4V     0x50
#define VOUT_1_4125V  0x51
#define VOUT_1_425V   0x52
#define VOUT_1_4375V  0x53
#define VOUT_1_45V    0x54
#define VOUT_1_4625V  0x55
#define VOUT_1_475V   0x56
#define VOUT_1_4875V  0x57
#define VOUT_1_5V     0x58
#define VOUT_1_5125V  0x59
#define VOUT_1_525V   0x5A
#define VOUT_1_5375V  0x5B
#define VOUT_1_55V    0x5C
#define VOUT_1_5625V  0x5D
#define VOUT_1_575V   0x5E
#define VOUT_1_5875V  0x5F
#define VOUT_1_6V     0x60
#define VOUT_1_6125V  0x61
#define VOUT_1_625V   0x62
#define VOUT_1_6375V  0x63
#define VOUT_1_65V    0x64
#define VOUT_1_6625V  0x65
#define VOUT_1_675V   0x66
#define VOUT_1_6875V  0x67
#define VOUT_1_7V     0x68
#define VOUT_1_7125V  0x69
#define VOUT_1_725V   0x6A
#define VOUT_1_7375V  0x6B
#define VOUT_1_75V    0x6C
#define VOUT_1_7625V  0x6D
#define VOUT_1_775V   0x6E
#define VOUT_1_7875V  0x6F
#define VOUT_1_8V     0x70
#define VOUT_1_8125V  0x71
#define VOUT_1_825V   0x72
#define VOUT_1_8375V  0x73
#define VOUT_1_85V    0x74
#define VOUT_1_8625V  0x75
#define VOUT_1_875V   0x76
#define VOUT_1_8875V  0x77
#define VOUT_1_9V     0x78
#define VOUT_1_9125V  0x79
#define VOUT_1_925V   0x7A
#define VOUT_1_9375V  0x7B
#define VOUT_1_95V    0x7C
#define VOUT_1_9625V  0x7D
#define VOUT_1_975V   0x7E
#define VOUT_1_9875V  0x7F

#elif defined(PMIC_TPS65023) // For UP201/UP301 EVB
#define PMIC_SLAVE_ADDRESS 	0x48

#define TPS65023_MASK				0x02
#define TPS65023_REG_CTRL			0x03		// Enable or disable power supplies
#define TPS65023_CTRL1				0x04		// Phase shift control by table 9
#define TPS65023_CTRL2				0x05		// BIT6 enable I2C setting output voltage
	#define TPS65023_GO						0x80
	#define CORE_ADJ_ALLOWED				0x40
#define TPS65023_DEFCORE			0x06		// DCDC with table 11/12

// TPS65023 DCDC1 DVS Voltage
#define	VDCDC1_0_8V						0x0
#define	VDCDC1_0_825V					0x1
#define	VDCDC1_0_85V					0x2
#define	VDCDC1_0_875V					0x3
#define	VDCDC1_0_9V						0x4
#define	VDCDC1_0_925V					0x5
#define	VDCDC1_0_95V					0x6
#define	VDCDC1_0_975V					0x7
#define	VDCDC1_1V						0x8
#define	VDCDC1_1_025V					0x9
#define	VDCDC1_1_05V					0xA
#define	VDCDC1_1_075V					0xB
#define	VDCDC1_1_1V						0xC
#define	VDCDC1_1_125V					0xD
#define	VDCDC1_1_15V					0xE
#define	VDCDC1_1_175V					0xF
#define	VDCDC1_1_2V						0x10
#define	VDCDC1_1_225V					0x11
#define	VDCDC1_1_25V					0x12
#define	VDCDC1_1_275V					0x13
#define	VDCDC1_1_3V						0x14
#define	VDCDC1_1_325V					0x15
#define	VDCDC1_1_35V					0x16
#define	VDCDC1_1_375V					0x17
#define	VDCDC1_1_4V						0x18
#define	VDCDC1_1_425V					0x19
#define	VDCDC1_1_45V					0x1A
#define	VDCDC1_1_475V					0x1B
#define	VDCDC1_1_5V						0x1C
#define	VDCDC1_1_525V					0x1D
#define	VDCDC1_1_55V					0x1E
#define	VDCDC1_1_6V						0x1F
#else
	// No use of PMIC control power.
#endif

static enum_upt_retcode_Type __power_mode_ctrl(void) {
	metal_gpio_Type *rtc_gpio_handle;
	metal_rtc_Type *rtc_handle;
	metal_gtimer_Type *ticktimer0_handle;
	metal_i2c_Type *pmic_i2c_handle;
	metal_sif_Type *pmic_sif_handle;

	// Warmboot address.
	UPT_REG(AONMB2) = (uint32_t)_upt_warmboot;

	// Clear RTC event.
	rtc_handle = upt_rtc_get_device(RTCM_RTC);
	upt_rtc_enable(rtc_handle, 0);
	upt_rtc_clear_status(rtc_handle);
	*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMRIS) = BIT4;

	// Clear Tick-timer event.
	ticktimer0_handle = upt_gtimer_get_device(RTCM_TICK_GTIMER_01);
	upt_gtimer_enable(ticktimer0_handle, gtimer_first, 0);
	upt_gtimer_clear_status(ticktimer0_handle, gtimer_first);

	// Clear RTCM_GPIOn event.
	rtc_gpio_handle = upt_gpio_get_device(RTCM_GPIOS);
	upt_gpio_init(rtc_gpio_handle);
	for(uint32_t i = 0; i < RTCM_GPIO_CNT; i ++)
		upt_gpio_clear_status(rtc_gpio_handle, i);

	// Set power control of PMIC.
	pmic_i2c_handle = upt_i2c_get_device(AON_I2C_0);
	upt_i2c_init(pmic_i2c_handle, i2c_fast, i2c_master, false);
	upt_i2c_set_slave(pmic_i2c_handle, PMIC_SLAVE_ADDRESS);
	upt_i2c_set_watermark(pmic_i2c_handle, i2c_watermark_1);
	upt_i2c_isr_enable(pmic_i2c_handle, 1);
	upt_i2c_dma_enable(pmic_i2c_handle, i2c_dma_tx_enable);

	// PMIC power mode voltages.
#if defined(PMIC_TPS628604) // For MCU Board
	UPT_REG(AONMB3) |= (((VOUT_0_875V&0xFF) << A0_VOTAGE_SHIFT) + \
						((VOUT_0_8V&0xFF) << S0_VOTAGE_SHIFT) + \
						((VOUT_0_8V&0xFF) << S1_VOTAGE_SHIFT) + \
						((VOUT_0_8V&0xFF) << L0_VOTAGE_SHIFT));
#elif defined(PMIC_TPS65023) // For UP201/UP301 EVB
	/* Sx/L0 to A0 voltage is invalid when using PMIC SIF!!*/
	UPT_REG(AONMB3) |= (((VDCDC1_0_875V&0xFF) << A0_VOTAGE_SHIFT) + \
					   ((VDCDC1_0_8V&0xFF) << S0_VOTAGE_SHIFT) + \
					   ((VDCDC1_0_8V&0xFF) << S1_VOTAGE_SHIFT) + \
					   ((VDCDC1_0_8V&0xFF) << L0_VOTAGE_SHIFT));
#endif

	// Set PMIC GPIO default value to 0.
	upt_power_gpio_pmic_trigger(UPT_SIF_PMIC_TRIGGER_ALL, UPT_SIF_TRI_EXTERNAL, UPT_GPIO_VALUE_000, UPT_GPIO_VALUE_111);

	// Set PMIC SIF Command queue.
	pmic_sif_handle = upt_sif_get_device(AON_SIF);
#if defined(PMIC_TPS628604) // For MCU Board
	upt_sif_write_command_queue(pmic_sif_handle, 0, IC_ENABLE, SIF_CMD_WRITE, SIF_I2C_ENABLE, 0);
	upt_sif_write_command_queue(pmic_sif_handle, 1, IC_DATA_CMD, SIF_CMD_WRITE, TPS628604_VOUT, 0);
	upt_sif_write_command_queue(pmic_sif_handle, 2, IC_DATA_CMD, SIF_CMD_WRITE, (SIF_STOP_ENABLE|VOUT_0_85V), 0);
	upt_sif_write_command_queue(pmic_sif_handle, 3, IC_STATUS, SIF_CMD_READ, (SIF_MST_ACTIVITY|SIF_TFE|SIF_TFE_EMPTY)&SIF_MST_ACTIVITY_IDLE, 0);
	upt_sif_write_command_queue(pmic_sif_handle, 4, IC_ENABLE, SIF_CMD_WRITE, SIF_I2C_DISABLE, 1);
#elif defined(PMIC_TPS65023) // For UP201/UP301 EVB
	upt_sif_write_command_queue(pmic_sif_handle, 0, IC_ENABLE, SIF_CMD_WRITE, SIF_I2C_ENABLE, 0);
	upt_sif_write_command_queue(pmic_sif_handle, 1, IC_DATA_CMD, SIF_CMD_WRITE, TPS65023_DEFCORE, 0);
	upt_sif_write_command_queue(pmic_sif_handle, 2, IC_DATA_CMD, SIF_CMD_WRITE, (SIF_STOP_ENABLE|VDCDC1_0_875V), 0);
	upt_sif_write_command_queue(pmic_sif_handle, 3, IC_DATA_CMD, SIF_CMD_WRITE, TPS65023_CTRL2, 0);
	upt_sif_write_command_queue(pmic_sif_handle, 4, IC_DATA_CMD, SIF_CMD_WRITE, (SIF_STOP_ENABLE|TPS65023_GO), 0);
	upt_sif_write_command_queue(pmic_sif_handle, 5, IC_STATUS, SIF_CMD_READ, (SIF_MST_ACTIVITY|SIF_TFE|SIF_TFE_EMPTY)&SIF_MST_ACTIVITY_IDLE, 0);
	upt_sif_write_command_queue(pmic_sif_handle, 6, IC_ENABLE, SIF_CMD_WRITE, SIF_I2C_DISABLE, 1);
#endif
	// Trigger SIF immediately.
	upt_sif_trigger(pmic_sif_handle, SIF_EXTERNAL);

	// PMIC SIF trigger condition is enabled.
	upt_power_sif_pmic_trigger(UPT_SIF_PMIC_TRIGGER_ALL, UPT_SIF_TRI_EXTERNAL);

	// Set PMIC/Flash power waiting time.
	upt_power_set_power_ok_wait_cycle(0);
	upt_power_set_gpio_ctrl_wait_cycle(0, 0);
	return E_UPT_SUCCESS;
}


static enum_upt_retcode_Type __enable_e21(const uint8_t* image, uint32_t image_size) {
    // Reset E21 core reset.
    *(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E21CTRL) &= ~BIT1;
    // Load E21 code to E21 TIM memory area.
    memcpy((void *)0x30000000, image, image_size);
    // Release E21 core reset.
    *(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E21CTRL) = BIT1;

    if(memcmp((void *)0x30000000, image, image_size) == 0) {
    	return E_UPT_SUCCESS;
    } else {
    	return E_UPT_MEMFAULT;
    }
}

extern void initPinMux();
#define __initPinMux	initPinMux
static enum_upt_retcode_Type __upt_initialize() {
#ifdef BOOTLOADER
	// Clear all boot-up event.
	__clear_booup_event();
	
	// Should initialize DTIM SRAM partition.
	__initial_dtimsram();
#else
	// RCOSC trimming task.
	__rcosc_auto_trimming();

	// Initialize pin mux.
	__initPinMux();

	// For the power mode initialize.
#if defined(PMIC_TPS628604) || defined(PMIC_TPS65023) // For MCU Board or UP201/UP301 EVB.
	__power_mode_ctrl();
#endif
#endif /* BOOTLOADER */

#ifdef LOAD_E21_CODE
	// Download E21 code and activate E21 core.
	if (__enable_e21(e21_image, e21_image_size) != E_UPT_SUCCESS) {
		return E_UPT_MEMFAULT;
	}
#endif /* LOAD_E21_CODE */

	return E_UPT_SUCCESS;
}

METAL_CONSTRUCTOR(upt_up301_init) {
	__upt_initialize();
}

#endif //CONFIG_UPBEAT_HAL
