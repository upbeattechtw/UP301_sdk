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

/**
 * @file  rtc.h
 * @brief API for Real-Time Clock
 */
#ifndef METAL_RTC_H
#define METAL_RTC_H
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief API for Real-Time Clock
 * @ingroup UP301_Controller_RTC
 */
typedef enum enum_rtc_device {
	RTCM_RTC = 0
} enum_rtc_device_Type;

/**
 * @brief RTC return error code.
 * @ingroup UP301_Controller_GPIO
 */
typedef enum enum_rtc_retcode {
    E_RTC_SUCCESS,     // Success.
	E_RTC_INVINIT,	 	// Initial fail or resource is unavailable.
	E_RTC_INVPARA,	 	// Invalid function parameter/argument.
    E_RTC_ERROR,     	// Unspecific error.
} enum_rtc_retcode_Type;

/**
 * @brief The real time structure
 * @ingroup UP301_Controller_RTC
 */
typedef struct rtc_real_time_info {
	uint32_t sec;
	uint32_t min;
	uint32_t hour;
	uint32_t day;
	uint32_t week;
	uint32_t month;
	uint32_t year;
} rtc_real_time_info_Type;

/**
 * @brief The alarm time structure
 * @ingroup UP301_Controller_RTC
 */
typedef struct rtc_alarm_time_info {
	uint32_t min;
	uint32_t hour;
	uint32_t day;
	uint32_t week;
} rtc_alarm_time_info_Type;

/** @brief Interrupt status: return value of upt_rtc_get_status(), match minute. */
#define RTC_AL1 						(0x1U << 1)
/** @brief Interrupt status: return value of upt_rtc_get_status(), match hour */
#define RTC_AL2 						(0x1U << 2)
/** @brief Interrupt status: return value of upt_rtc_get_status(), match day */
#define RTC_AL3 						(0x1U << 3)
/** @brief Interrupt status: return value of upt_rtc_get_status(), match day of week */
#define RTC_AL4 						(0x1U << 4)
/** @brief Interrupt status: return value of upt_rtc_get_status(), perfect match. */
#define RTC_ALM							(0x1U << 7)

/**
 * @brief Handle for a Real-Time Clock
 */
typedef struct metal_rtc {
    const struct metal_rtc_vtable *vtable;
} metal_rtc_Type;

struct metal_rtc_vtable {
	enum_rtc_retcode_Type (*get_alarm)(metal_rtc_Type *rtc, rtc_alarm_time_info_Type *alatime);
	enum_rtc_retcode_Type (*set_alarm)(metal_rtc_Type *rtc, rtc_alarm_time_info_Type *alatime);
	enum_rtc_retcode_Type (*get_time)(metal_rtc_Type *rtc, rtc_real_time_info_Type *realtime);
	enum_rtc_retcode_Type (*set_time)(metal_rtc_Type *rtc, rtc_real_time_info_Type *realtime);
	enum_rtc_retcode_Type (*init)(metal_rtc_Type *rtc);
	enum_rtc_retcode_Type (*interrupt_en)(metal_rtc_Type *rtc, bool enable);
    uint32_t (*interrupt_raw)(metal_rtc_Type *rtc);
    enum_rtc_retcode_Type (*interrupt_clr)(metal_rtc_Type *rtc);
};

/**
 * @brief Get the handle for an RTC by index
 * @param[in] index The index of the RTC
 * @return The RTC handle, or NULL if none is available at that index
 */
metal_rtc_Type *upt_rtc_get_device(enum_rtc_device_Type index);

/**
 * @brief initialize the RTC.
 * @param[in] rtc The RTC handle.
 * @return enum_rtc_retcode_Type value.
 */
inline enum_rtc_retcode_Type upt_rtc_init(metal_rtc_Type *rtc) {
    return rtc->vtable->init(rtc);
}

/**
 * @brief Set the current time of the RTC.
 * @param[in] rtc The RTC handle.
 * @param[in] realtime Configuration parameters for RTC information.
 * @return enum_rtc_retcode_Type value.
 */
inline enum_rtc_retcode_Type upt_rtc_set_time(metal_rtc_Type *rtc, rtc_real_time_info_Type *realtime) {
    return rtc->vtable->set_time(rtc, realtime);
}

/**
 * @brief Get the current time of the RTC.
 * @param[in] rtc The RTC handle.
 * @param[out] realtime Get real time information.
 * @return enum_rtc_retcode_Type value.
 */
inline enum_rtc_retcode_Type upt_rtc_get_time(metal_rtc_Type *rtc, rtc_real_time_info_Type *realtime) {
    return rtc->vtable->get_time(rtc, realtime);
}

/**
 * @brief Set the alarm time of the RTC.
 * @param[in] rtc The RTC handle.
 * @param[in] alatime Configuration parameters for RTC alarm time information.
 * @return enum_rtc_retcode_Type value.
 */
inline enum_rtc_retcode_Type upt_rtc_set_alarm(metal_rtc_Type *rtc, rtc_alarm_time_info_Type *alatime) {
    return rtc->vtable->set_alarm(rtc, alatime);
}

/**
 * @brief Get the alarm time of the RTC.
 * @param[in] rtc The RTC handle.
 * @param[out] alatime Get alarm time information.
 * @return enum_rtc_retcode_Type value.
 */
inline enum_rtc_retcode_Type upt_rtc_get_alarm(metal_rtc_Type *rtc, rtc_alarm_time_info_Type *alatime) {
    return rtc->vtable->get_alarm(rtc, alatime);
}

/**
 * @brief Enable/Disable of RTC
 * @param[in] rtc The RTC handle
 * @param[in] enable Enable/Disable the RTC function
 * @return enum_rtc_retcode_Type value.
 */
inline enum_rtc_retcode_Type upt_rtc_enable(metal_rtc_Type *rtc, bool enable) {
	return E_RTC_SUCCESS;
}

/**
 * @brief Enable the interrupt for the RTC.
 * @param[in] rtc The RTC handle.
 * @param[in] enable Enable/Disable the RTC interrupt.
 * @return enum_rtc_retcode_Type value.
 */
inline enum_rtc_retcode_Type upt_rtc_isr_enable(metal_rtc_Type *rtc, bool enable) {
    // TODO: To Enable E34 RTC interrupt, use SCU function call instead.
    *(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMIE) = (0x1 << 4);
    return rtc->vtable->interrupt_en(rtc, enable);
}

/**
 * @brief Read status of RTC
 * @param[in] rtc The RTC handle
 * @return RTC Interrupt status bit.
 */
inline uint32_t upt_rtc_get_status(metal_rtc_Type *rtc) {
    return rtc->vtable->interrupt_raw(rtc);
}

/**
 * @brief Clear the status of RTC.
 * @param[in] rtc The RTC handle.
 * @return enum_rtc_retcode_Type value.
 */
inline enum_rtc_retcode_Type upt_rtc_clear_status(metal_rtc_Type *rtc) {
    enum_rtc_retcode_Type ret;

    ret = rtc->vtable->interrupt_clr(rtc);
	// TODO: To enable E34 RTC interrupt clear status, use SCU function call instead.
	*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_RTCMRIS) = 0x10;
	return ret;
}

#endif /* METAL_RTC_H */
