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

#ifndef __UPT_SYSTIMER_H__
#define __UPT_SYSTIMER_H__

#ifndef LOAD_SRAM_CODE
void upt_delay_us(uint64_t unit_us) __attribute__ ((section (".FwHandler")));
#else
void upt_delay_us(uint64_t unit_us);
#endif

#ifndef LOAD_SRAM_CODE
void upt_delay_ms(uint64_t unit_ms) __attribute__ ((section (".FwHandler")));
#else
void upt_delay_ms(uint64_t unit_ms);
#endif

#ifndef LOAD_SRAM_CODE
void upt_init_Tick(void) __attribute__ ((section (".FwHandler")));
#else
void upt_init_Tick(void);
#endif

#ifndef LOAD_SRAM_CODE
uint8_t __upt_check_timeout_us(uint64_t unit_us) __attribute__ ((section (".FwHandler")));
#else
uint8_t __upt_check_timeout_us(uint64_t unit_us);
#endif
#define upt_check_timeout_us(us) __upt_check_timeout_us((uint64_t)(us))

#ifndef LOAD_SRAM_CODE
uint8_t upt_check_timeout_ms(uint64_t unit_ms) __attribute__ ((section (".FwHandler")));
#else
uint8_t upt_check_timeout_ms(uint64_t unit_ms);
#endif

#endif // __UPT_SYSTIMER_H__