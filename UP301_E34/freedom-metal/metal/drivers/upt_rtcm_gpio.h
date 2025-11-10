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
 * @file  upt_rtcm_gpio.h
 * @brief UP301 RTCM_GPIO driver
 */

#ifndef UPT_RTCM_GPIO_H
#define UPT_RTCM_GPIO_H
#include <stdbool.h>

#include "metal/gpio.h"

/**
 * @brief Initialize RTCM_GPIO.
 * @return enum_gpio_retcode_Type value.
 */
enum_gpio_retcode_Type upt_rtcm_gpio_init(void);

/**
 * @brief Set output pin to RTCM_GPIO in Ax/AxSc mode.
 * @param pin The pin number indexed from 0 to 3.
 * @param value pin value to the output pin.
 * @return enum_gpio_retcode_Type value.
 */
enum_gpio_retcode_Type upt_rtcm_gpio_set_bit(uint32_t pin, enum_gpio_value_Type value);

/**
 * @brief Get RTCM_GPIO input on a pin in Ax/AxSc mode.
 * @param pin The pin number indexed from 0 t0 3.
 * @return RTCM_GPIO pin value.
 */
enum_gpio_value_Type upt_rtcm_gpio_get_bit(uint32_t pin);

/**
 * @brief Set RTCM_GPIO function for the input/output on a pin.
 * @param pin The pin number indexed from 0 to 3.
 * @param direction 0 for input, 1 for output.
 * @return enum_gpio_retcode_Type value.
 */
enum_gpio_retcode_Type upt_rtcm_gpio_set_direction(uint32_t pin, enum_gpio_dir_Type direction);

/**
 * @brief Get RTCM_GPIO function for the input/output on a pin.
 * @param pin The pin number indexed from 0 to 3.
 * @return direction of the RTCM_GPIO pin.
 */
enum_gpio_dir_Type upt_rtcm_gpio_get_direction(uint32_t pin);


/**
 * @brief Toggle RTCM_GPIO pin.
 * @param pin The pin number indexed from 0 to 3.
 * @return enum_gpio_retcode_Type value.
 */
enum_gpio_retcode_Type upt_rtcm_gpio_output_toggle(uint32_t pin);

/**
 * @brief Configure interrupt type.
 * @param pin The pin number indexed from 0 to 3.
 * @param intr_type method of trigger RTCM_GPIO pin to interrupt: 1 for rising edge, 2 for falling edge.
 * @return enum_gpio_retcode_Type value.
 */
enum_gpio_retcode_Type upt_rtcm_gpio_config_interrupt(uint32_t pin, enum_gpio_tri_Type intr_type);

/**
 * @brief Get raw status of the RTCM_GPIO pin.
 * @param pin The pin number indexed from 0 to 3.
 * @return Raw status of RTCM_GPIO pin.
 */
uint32_t upt_rtcm_gpio_raw_status(uint32_t pin);

/**
 * @brief Get status of the RTCM_GPIO pin.
 * @param pin The pin number indexed from 0 to 3.
 * @return Status of RTCM_GPIO pin.
 */
uint32_t upt_rtcm_gpio_status(uint32_t pin);

/**
 * @brief Clear status of RTCM_GPIO pin.
 * @param pin The pin number indexed from 0 to 3.
 * @return enum_gpio_retcode_Type value.
 */
enum_gpio_retcode_Type upt_rtcm_gpio_clear_interrupt(uint32_t pin);

/**
 * @brief Enable RTCM_GPIO pin interrupt.
 * @param pin The pin number indexed from 0 to 3.
 * @return enum_gpio_retcode_Type value.
 */
enum_gpio_retcode_Type upt_rtcm_gpio_interrupt_enable(uint32_t pin);

/**
 * @brief Disable RTCM_GPIO pin interrupt.
 * @param pin The pin number indexed from 0 to 3.
 * @return enum_gpio_retcode_Type value.
 */
enum_gpio_retcode_Type upt_rtcm_gpio_interrupt_disable(uint32_t pin);

/**
 * @brief Set output pin to RTCM_GPIO in S/L/R mode.
 * @param pin The pin number indexed from 0 to 3.
 * @return enum_gpio_retcode_Type value.
 */
enum_gpio_retcode_Type upt_rtcm_gpio_set_bit_S_L_R(uint32_t pin, bool value);

/**
 * @brief Enable RTCM_GPIO pin S/L/R output mode.
 * @param pin The pin number indexed from 0 to 3.
 * @return enum_gpio_retcode_Type value.
 */
enum_gpio_retcode_Type upt_rtcm_gpio_S_L_R_output_enable(uint32_t pin);

/**
 * @brief Disable RTCM_GPIO pin interrupt.
 * @param pin The pin number indexed from 0 to 3.
 * @return enum_gpio_retcode_Type value.
 */
enum_gpio_retcode_Type upt_rtcm_gpio_S_L_R_output_disable(uint32_t pin);

#endif /* UPT_RTCM_GPIO_H */
