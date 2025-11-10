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

/*!
 * @file timer.h
 * @brief API for reading and manipulating the machine timer
 */
#ifndef METAL__TIMER_H
#define METAL__TIMER_H
#include <stdint.h>

/*!
 * @brief timer's return error code.
 */
typedef enum enum_timer_retcode{
    E_TIMER_SUCCESS,     // Success.
	E_TIMER_INVINIT,	 	// Initial fail or resource is unavailable.
	E_TIMER_INVPARA,	 	// Invalid function parameter/argument.
    E_TIMER_ERROR,     	// Unspecific error.
} enum_timer_retcode_Type;


/*!
 * @brief Read the machine cycle count
 * @param hartid The hart ID to read the cycle count of
 * @param cyclecount The variable to hold the value
 * @return enum_timer_retcode_Type error call.
 */
enum_timer_retcode_Type metal_timer_get_cyclecount(uint32_t hartid, uint64_t *cyclecount);

/*!
 * @brief Get the machine timebase frequency
 * @param hartid The hart ID to read the timebase of
 * @param timebase The variable to hold the value
 * @return enum_timer_retcode_Type error call.
 */
enum_timer_retcode_Type metal_timer_get_timebase_frequency(uint32_t hartid, uint64_t *timebase);

/*!
 * @brief Set the machine timer tick interval in seconds
 * @param hartid The hart ID to read the timebase of
 * @param second The number of seconds to set the tick interval to
 * @return 0 upon success
 */
uint32_t metal_timer_set_tick(uint32_t hartid, uint32_t second);

#endif /* METAL__TIMER_H */
