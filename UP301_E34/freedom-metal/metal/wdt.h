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

#ifndef METAL_WDT_H
#define METAL_WDT_H

/**
 * @file wdt.h
 * @brief API for configuring watchdog timer
 */

/**
 * @brief Number of wdt device
 * @ingroup UP301_Controller_WDT
 */
typedef enum enum_wdt_device {
	AON_WDT = 0,
	WDT_DEVICE_NUMBER_LAST
} enum_wdt_device_Type;

/**
 * @brief Timer return error code.
 * @ingroup UP301_Controller_GTIMER
 */
typedef enum enum_wdt_retcode {
    E_WDT_SUCCESS,		// Success.
	E_WDT_INVINIT,		// Initial fail or resource is unavailable.
	E_WDT_INVPARA,		// Invalid function parameter/argument.
    E_WDT_ERROR,		// Unspecific error.
} enum_wdt_retcode_Type;

/**
 * @brief Handle for a watchdog timer
 */
typedef struct metal_wdt {
    const struct __metal_wdt_vtable *vtable;
} metal_wdt_Type;

struct __metal_wdt_vtable {
	enum_wdt_retcode_Type (*start)(metal_wdt_Type *wdt);
	enum_wdt_retcode_Type (*stop)(metal_wdt_Type *wdt);
	enum_wdt_retcode_Type (*clear)(metal_wdt_Type *wdt);
	enum_wdt_retcode_Type (*interrupt_enable)(metal_wdt_Type *wdt, bool enable);
	enum_wdt_retcode_Type (*kick)(metal_wdt_Type *wdt);
	enum_wdt_retcode_Type (*set_value)(metal_wdt_Type *wdt, uint32_t nLoad);
    uint32_t (*get_value)(metal_wdt_Type *wdt);
};

/**
 * @brief Get a handle for a timer
 * @param[in] device_num The index of the specific timer
 * @return A handle to a timer, or NULL if the device does not exist
 */
metal_wdt_Type *upt_wdt_get_device(enum_wdt_device_Type device_num);

/**
 * @brief Initialize watchdog timer.
 * @param[in] wdt The timer handle.
 * @param[in] nLoad Load count.
 * @return enum_wdt_retcode_Type value.
 */
__inline__ enum_wdt_retcode_Type upt_wdt_init(metal_wdt_Type *wdt, uint32_t nLoad) {
	return wdt->vtable->set_value(wdt, nLoad);
}

/**
 * @brief Start/Stop watchdog timer.
 * @param[in] wdt The timer handle.
 * @param[in] enable Enable/Disable WDT.
 * @return enum_wdt_retcode_Type value.
 */
__inline__ enum_wdt_retcode_Type upt_wdt_enable(metal_wdt_Type *wdt, bool enable) {
	if (enable)
		return wdt->vtable->start(wdt);
	else
		return wdt->vtable->stop(wdt);
}

/**
 * @brief Enable/Disable watchdog timer.
 * @param[in] wdt The timer handle.
 * @param[in] enable Enable/Disable WDT interrupt.
 * @return enum_wdt_retcode_Type value.
 */
inline enum_wdt_retcode_Type upt_wdt_isr_enable(metal_wdt_Type *wdt, bool enable) {
	return wdt->vtable->interrupt_enable(wdt, enable);
}

/**
 * @brief Kick watchdog timer.
 * @param[in] wdt The timer handle.
 * @return enum_wdt_retcode_Type value.
 */
__inline__ enum_wdt_retcode_Type upt_wdt_kick(metal_wdt_Type *wdt) {
	enum_wdt_retcode_Type ret = E_WDT_SUCCESS;
	ret = wdt->vtable->kick(wdt);
	if (ret != E_WDT_SUCCESS)
		return ret;
    return wdt->vtable->clear(wdt);
}

/**
 * @brief Get watchdog timer load value.
 * @param[in] wdt The timer handle.
 * @return Load value.
 */
__inline__ uint32_t upt_wdt_get_count(metal_wdt_Type *wdt) {
    return wdt->vtable->get_value(wdt);
}

/**
 * @brief Set watchdog timer load count.
 * @param[in] wdt The timer handle.
 * @param[in] nLoad Load count.
 * @return enum_wdt_retcode_Type value.
 */
__inline__ enum_wdt_retcode_Type upt_wdt_set_count(metal_wdt_Type *wdt, uint32_t nLoad) {
    return wdt->vtable->set_value(wdt, nLoad);
}

#endif /* METAL_WATCHDOG_H */
