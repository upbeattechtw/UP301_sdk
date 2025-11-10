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
 * @file  ts.h
 * @brief API for Temperature Sensor
 */
#ifndef METAL_TS_H
#define METAL_TS_H
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Device number of Temperature Sensor
 * @ingroup UP301_Controller_TS
 */
typedef enum enum_ts_device {
	AON_TS = 0
} enum_ts_device_Type;


typedef enum enum_ts_retcode {
    E_TS_SUCCESS,     // Success.
	E_TS_INVINIT,	 	// Initial fail or resource is unavailable.
	E_TS_INVPARA,	 	// Invalid function parameter/argument.
    E_TS_ERROR,     	// Unspecific error.
} enum_ts_retcode_Type;


/** @brief Interrupt status: return value of upt_ts_get_status() */
#define ts_interrupted (0x1U << 0)

/**
 * @brief Handle for a temperature sensor
 */
typedef struct metal_ts {
    const struct metal_ts_vtable *vtable;
} metal_ts_Type;
struct metal_ts_vtable {
	enum_ts_retcode_Type (*measure)(metal_ts_Type *ts);
	int16_t (*read_temp)(metal_ts_Type *ts);
	enum_ts_retcode_Type (*enable)(metal_ts_Type *ts);
	enum_ts_retcode_Type (*disable)(metal_ts_Type *ts);
	enum_ts_retcode_Type (*measure_async)(metal_ts_Type *ts, bool enable);
	uint32_t (*get_status)(metal_ts_Type *ts);
	enum_ts_retcode_Type (*clear_status)(metal_ts_Type *ts);
};



/**
 * @brief Get the handle for an TS by index
 * @param[in] device_num The index of the desired SPI device
 * @return The TS handle, or NULL if none is available at that index
 */
metal_ts_Type *upt_ts_get_device(enum_ts_device_Type device_num);

/**
 * @brief Enable TS
 * @param[in] ts The TS handle
 * @param[in] enable Enable/Disable TS function
 * @remarks No return value
 */
inline enum_ts_retcode_Type upt_ts_enable(metal_ts_Type *ts, bool enable) {
	if(enable)
		return ts->vtable->enable(ts);
	else
		return ts->vtable->disable(ts);
}

/**
 * @brief Measure IC junction temperature
 * @details This call will block execution until the temperature measurement is
 * done. Make sure the temperature sensor is enabled, i.e. by calling
 * upt_ts_enable(), before taking measurement. After return of this call, read
 * temperature by calling upt_ts_read_temp().
 * @param[in] ts The TS handle
 * @remarks No return value
 */
inline enum_ts_retcode_Type upt_ts_measure(metal_ts_Type *ts) {
    return ts->vtable->measure(ts);
}

/**
 * @brief Read temperature measurement result
 * @details Make sure the temperature measurement is done before calling this
 * function.
 * @param[in] ts The TS handle
 * @return Temperature reading. To convert to temperature in Celcius, divide
 * this reading by 8.
 */
inline int16_t upt_ts_read_temp(metal_ts_Type *ts) {
    return ts->vtable->read_temp(ts);
}

/**
 * @brief Enable interrupt of TS and then measure temperature
 * @param[in] ts The TS handle
 * @param[in] enable Enable/Disable TS asynchronous mode
 * @remarks No return value
 */
inline enum_ts_retcode_Type upt_ts_measure_async(metal_ts_Type *ts, bool enable) {
	return ts->vtable->measure_async(ts, enable);
}

/**
 * @brief Get all status of TS
 * @param[in] ts The TS handle
 * @return Status of TS
 */
__inline__ uint32_t upt_ts_get_status(metal_ts_Type *ts) {
	return ts->vtable->get_status(ts);
}

/**
 * @brief Clear all status of TS
 * @param[in] ts The TS handle
 * @remarks No return value
 */
__inline__ enum_ts_retcode_Type upt_ts_clear_status(metal_ts_Type *ts) {
	return ts->vtable->clear_status(ts);
}

#endif
