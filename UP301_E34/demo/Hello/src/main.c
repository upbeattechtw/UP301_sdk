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
#include "metal/upt_init.h"
#include "metal/upt_isr.h"
#include "metal/upt_powmod.h"

void Show_debug_msg_lvl(){
	printf("\n");
	printf("\n");

#ifdef STDOUT_BAUD_12000000
		printf("NAON_UART0 Initialized : 12M\n");
#elif STDOUT_BAUD_6000000
		printf("NAON_UART0 Initialized : 6M\n");
#elif STDOUT_BAUD_3000000
		printf("NAON_UART0 Initialized : 3M\n");
#else /* STDOUT_BAUD_921600 */
		printf("NAON_UART0 Initialized : 0.9M\n");
#endif

	printf("Show the debug level: \n");
	UP_DEBUG_TRACE("TRACE\n");
	UP_DEBUG_INFO("INFO\n");
	UP_DEBUG_WARN("WARN\n");
	UP_DEBUG_ERROR("ERROR\n");
	printf("\n");
}

/**
 * @brief Show bootup condition
 * @param[in] void No parameter.
 * @return NULL
 */
void bootUpHandling(){

	if ( upt_power_is_bootup_from(UPT_POWERON_BOOT) ){
	printf("POWERON_BOOT\n");
	}

	if ( upt_power_is_bootup_from(UPT_E21_ECC_RESET) ){
	printf("E21_ECC_RESET\n");
	}

	if ( upt_power_is_bootup_from(UPT_E34_ECC_RESET) ){
	printf("E34_ECC_RESET\n");
	}

	if ( upt_power_is_bootup_from(UPT_HW_RESET) ){
	printf("UPT_HW_RESET\n");
	}

	if ( upt_power_is_bootup_from(UPT_GPIO_0_BOOTUP) ){
	printf("GPIO_0_BOOTUP\n");
	}

	if ( upt_power_is_bootup_from(UPT_GPIO_1_BOOTUP) ){
	printf("GPIO_1_BOOTUP\n");
	}

	if ( upt_power_is_bootup_from(UPT_GPIO_2_BOOTUP) ){
	printf("GPIO_2_BOOTUP\n");
	}

	if ( upt_power_is_bootup_from(UPT_GPIO_3_BOOTUP) ){
	printf("GPIO_3_BOOTUP\n");
	}

	if ( upt_power_is_bootup_from(UPT_RTC_BOOTUP) ){
	printf("RTC_BOOTUP\n");
	}

	if ( upt_power_is_bootup_from(UPT_TICK_BOOTUP) ){
	printf("TICK_BOOTUP\n");
	}

	if ( upt_power_is_bootup_from(UPT_WDT_RESET) ){
	printf("WDT_RESET\n");
	}

	if ( upt_power_is_bootup_from(UPT_WARM_BOOT) ){
	printf("WARM_BOOT\n");
	}

	if ( upt_power_is_bootup_from(UPT_SW_RESET_BOOT) ){
	printf("SW_RESET_BOOT\n");
	}
}

/**
 * @brief Bara metal entry function
 * @param[in] void No parameter.
 * @return NULL
 */
int main() {
	
	/* Should initialize ISR handler */
	init_interrupts();
	e34_interrupt_enable();
	
	Show_debug_msg_lvl();
	bootUpHandling();


	printf("Hello, World(E34)!\n");

	while(1);
	
	return 0;
}
