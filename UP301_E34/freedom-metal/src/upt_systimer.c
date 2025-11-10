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
#include <stdint.h>

#include "metal/cpu.h"
#include "metal/upt_systimer.h"

#define TIMEOUT_OCCURRED 1
#define TIMEOUT_NOT_YET  0 
static uint64_t __mtimer_current;
static uint64_t __mtimer_previous;

void upt_delay_us(uint64_t unit_us) {
	uint64_t diff;

	// Get MTIMER value.
    metal_cpu_Type *cpu = metal_cpu_get(0);
    if (cpu) {
		__mtimer_current = metal_cpu_get_mtime(cpu);
		__mtimer_previous = __mtimer_current;
		do {
			diff = __mtimer_current - __mtimer_previous;
			__mtimer_current = metal_cpu_get_mtime(cpu);
		} while(diff < ((unit_us>>5)+1));								// Minimum delay time is 30us.
    }
}

void upt_delay_ms(uint64_t unit_ms) {
	upt_delay_us(unit_ms*1000);
}

void upt_init_Tick(void) {
	// Get MTIMER value.
	metal_cpu_Type *cpu = metal_cpu_get(0);
    if (cpu) {
			__mtimer_current = metal_cpu_get_mtime(cpu);
			__mtimer_previous = __mtimer_current;
    }
}

uint8_t __upt_check_timeout_us(uint64_t unit_us) {
	uint64_t diff;

	metal_cpu_Type *cpu = metal_cpu_get(0);
	if (cpu) {
		__mtimer_current = metal_cpu_get_mtime(cpu);
	}
	diff = __mtimer_current - __mtimer_previous;
	if(diff < ((unit_us>>5)+1))
		return TIMEOUT_NOT_YET;     // not yet  0
	return TIMEOUT_OCCURRED; 		// timeout  1
}

uint8_t upt_check_timeout_ms(uint64_t unit_ms) {
	return upt_check_timeout_us(unit_ms*1000);
}
