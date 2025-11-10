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

/**
 * @file  adc.h
 * @brief API for UPT controller unit logic-2
 */
#include "upt_up301.h"

/**
 * @brief Let watch dog timer function valid.
 * @param[in] wdt_cnt wdt count and source clock is from 32768Hz.
 * @return enum_upt_retcode_Type value.
 */
enum_upt_retcode_Type upt_wdt_activate(uint32_t wdt_cnt);

/**
 * @brief Let watch dog timer function invalid.
 * @return enum_upt_retcode_Type value.
 */
enum_upt_retcode_Type upt_wdt_deactivate(void);

/**
 * @brief Kick watch dog timer
 * @remarks No return value
 */
void upt_wdt_software_kick(void);
