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
 * @file  gpio.h
 * @brief API for General-purpose input/output
 */
#ifndef METAL_GPIO_H
#define METAL_GPIO_H
#include <stdbool.h>
#include <stdint.h>

#include "metal-platform.h"

/**
 * @brief Device number of GPIO.
 * @ingroup UP301_Controller_GPIO
 */
typedef enum enum_gpio_device {
	NAON_SYS_GPIOS		= 0,		// 0~44.
	NAON_PERI_GPIOS,				// 0~29.
	AON_GPIOS,						// 0~20.
	RTCM_GPIOS,						// 0~3.
	GPIO_DEVICE_NUMBER_LAST
} enum_gpio_device_Type;

/**
 * @brief GPIO data.
 * @ingroup UP301_Controller_GPIO
 */
typedef enum enum_gpio_value {
	gpio_level_low		= 0,
	gpio_level_high
} enum_gpio_value_Type;

/**
 * @brief GPIO direction.
 * @ingroup UP301_Controller_GPIO
 */
typedef enum enum_gpio_dir {
	gpio_dir_in		= 0,
	gpio_dir_out
} enum_gpio_dir_Type;

/**
 * @brief GPIO trigger mode.
 * @ingroup UP301_Controller_GPIO
 */
typedef enum enum_gpio_tri {
	gpio_int_disable		= 0,
	gpio_int_rising,
	gpio_int_falling,
	gpio_int_both_edge,
	gpio_int_low,
	gpio_int_high
} enum_gpio_tri_Type;

/**
 * @brief GPIOs return error code.
 * @ingroup UP301_Controller_GPIO
 */
typedef enum enum_gpio_retcode{
    E_GPIO_SUCCESS,     // Success.
	E_GPIO_INVINIT,	 	// Initial fail or resource is unavailable.
	E_GPIO_INVPARA,	 	// Invalid function parameter/argument.
    E_GPIO_ERROR,     	// Unspecific error.
} enum_gpio_retcode_Type;

/** @brief Interrupt status: return value of upt_gpio_get_status(). */
#define GPIO_PIN_TRIGGERED	(0x1U << 0)

/**
 * @brief Handle for a GPIO interface.
 */
typedef struct metal_gpio {
    const struct __metal_gpio_vtable *vtable;
} metal_gpio_Type;

struct __metal_gpio_vtable {
	enum_gpio_retcode_Type (*init)(metal_gpio_Type *gpio);
	enum_gpio_retcode_Type (*set_bit)(metal_gpio_Type *gpio, uint32_t pin, enum_gpio_value_Type value);
	enum_gpio_value_Type (*get_bit)(metal_gpio_Type *gpio, uint32_t pin);
	enum_gpio_retcode_Type (*set_direction)(metal_gpio_Type *gpio, uint32_t pin, enum_gpio_dir_Type direction);
    enum_gpio_dir_Type (*get_direction)(metal_gpio_Type *gpio, uint32_t pin);
    enum_gpio_retcode_Type (*output_toggle)(metal_gpio_Type *gpio, uint32_t pin);
    enum_gpio_retcode_Type (*config_interrupt)(metal_gpio_Type *gpio, uint32_t pin, enum_gpio_tri_Type intr_type);
    uint32_t (*raw_status)(metal_gpio_Type *gpio, uint32_t pin);
    uint32_t (*status)(metal_gpio_Type *gpio, uint32_t pin);
    enum_gpio_retcode_Type (*clear_interrupt)(metal_gpio_Type *gpio, uint32_t pin);
    enum_gpio_retcode_Type (*rtcm_init)(void);
	enum_gpio_retcode_Type (*rtcm_set_bit)(uint32_t pin, enum_gpio_value_Type value);
	enum_gpio_value_Type (*rtcm_get_bit)(uint32_t pin);
	enum_gpio_retcode_Type (*rtcm_set_direction)(uint32_t pin, enum_gpio_dir_Type direction);
    enum_gpio_dir_Type (*rtcm_get_direction)(uint32_t pin);
    enum_gpio_retcode_Type (*rtcm_output_toggle)(uint32_t pin);
    enum_gpio_retcode_Type (*rtcm_config_interrupt)(uint32_t pin, enum_gpio_tri_Type intr_type);
    uint32_t (*rtcm_raw_status)(uint32_t pin);
    uint32_t (*rtcm_status)(uint32_t pin);
    enum_gpio_retcode_Type (*rtcm_clear_interrupt)(uint32_t pin);
    enum_gpio_retcode_Type (*rtcm_interrupt_enable)(uint32_t pin);
    enum_gpio_retcode_Type (*rtcm_interrupt_disable)(uint32_t pin);
	enum_gpio_retcode_Type (*rtcm_set_bit_S_L_R)(uint32_t pin, bool value);
	enum_gpio_retcode_Type (*rtcm_S_L_R_output_enable)(uint32_t pin);
	enum_gpio_retcode_Type (*rtcm_S_L_R_output_disable)(uint32_t pin);
};

/**
 * @brief Get a handle for a GPIO.
 * @param[in] device_num The index of the desired GPIO device.
 * @return The GPIO device handle, or NULL if there is no device at that index.
 */
metal_gpio_Type *upt_gpio_get_device(enum_gpio_device_Type device_num);

/**
 * @brief Initialize GPIO.
 * @param[in] gpio The GPIO handle.
 * @return enum_gpio_retcode_Type value.
 */
__inline__ enum_gpio_retcode_Type upt_gpio_init(metal_gpio_Type *gpio) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if ( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		else if (i == RTCM_GPIOS)
			return E_GPIO_INVINIT;
	}

	if (i > AON_GPIOS)
		return gpio->vtable->rtcm_init();
	else
		return gpio->vtable->init(gpio);
}

/**
 * @brief Set output pin to GPIO.
 * @param[in] gpio The GPIO handle.
 * @param[in] pin The pin number index from 0.
 * @param[in] value pin value to the output pin.
 * @return enum_gpio_retcode_Type value.
 */
__inline__ enum_gpio_retcode_Type upt_gpio_set_bit(metal_gpio_Type *gpio, uint32_t pin, enum_gpio_value_Type value) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if ( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		else if (i == RTCM_GPIOS)
			return E_GPIO_INVINIT;
	}

	if (i > AON_GPIOS)
		return gpio->vtable->rtcm_set_bit(pin, value);
	else
		return gpio->vtable->set_bit(gpio, pin, value);
}

/**
 * @brief Get GPIO input on a pin.
 * @param[in] gpio The GPIO handle.
 * @param[in] pin The pin number index from 0.
 * @return GPIO pin value.
 */
__inline__ enum_gpio_value_Type upt_gpio_get_bit(metal_gpio_Type *gpio, uint32_t pin) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if ( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		// TODO: Error handling.
	}

	if (i > AON_GPIOS)
		return gpio->vtable->rtcm_get_bit(pin);
	else
		return gpio->vtable->get_bit(gpio, pin);
}

/**
 * @brief Set GPIO direction on a pin.
 * @param[in] gpio The GPIO handle.
 * @param[in] pin The pin number index from 0.
 * @param[in] direction Set input/output.
 * @return enum_gpio_retcode_Type value.
 */
__inline__ enum_gpio_retcode_Type upt_gpio_set_direction(metal_gpio_Type *gpio, uint32_t pin, enum_gpio_dir_Type direction) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if ( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		else if (i == RTCM_GPIOS)
			return E_GPIO_INVINIT;
	}

	if (i > AON_GPIOS)
		return gpio->vtable->rtcm_set_direction(pin, direction);
	else
		return gpio->vtable->set_direction(gpio, pin, direction);
}

/**
 * @brief Get GPIO direction on a pin.
 * @param[in] gpio The GPIO handle.
 * @param[in] pin The pin number index from 0.
 * @return direction of the GPIO pin.
 */
__inline__ enum_gpio_dir_Type upt_gpio_get_direction(metal_gpio_Type *gpio, uint32_t pin) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if ( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		else {
		// TODO: Error handling.
		}
	}

	if (i > AON_GPIOS)
		return gpio->vtable->rtcm_get_direction(pin);
	else
		return gpio->vtable->get_direction(gpio, pin);
}

/**
 * @brief Toggle GPIO on a pin.
 * @param[in] gpio The GPIO handle.
 * @param[in] pin The pin number index from 0.
 * @return enum_gpio_retcode_Type value.
 */
__inline__ enum_gpio_retcode_Type upt_gpio_output_toggle(metal_gpio_Type *gpio, uint32_t pin) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if ( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		else if (i == RTCM_GPIOS)
			return E_GPIO_INVINIT;
	}

	if (i > AON_GPIOS)
		return gpio->vtable->rtcm_output_toggle(pin);
	else
		return gpio->vtable->output_toggle(gpio, pin);
}

/**
 * @brief Configure interrupt type.
 * @param[in] gpio The GPIO handle.
 * @param[in] pin The pin number index from 0.
 * @param[in] intr_type method of GPIO pin to be interrupted.
 * @return 0 if interrupt type set successfully.
 */
__inline__ enum_gpio_retcode_Type upt_gpio_isr_enable(metal_gpio_Type *gpio, uint32_t pin, enum_gpio_tri_Type intr_type) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if ( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		else if (i == RTCM_GPIOS)
			return E_GPIO_INVINIT;
	}

	if (i > AON_GPIOS) {
		if (intr_type > gpio_int_falling)
			return E_GPIO_INVPARA;
		if (intr_type == gpio_int_disable) {
			// TODO: To disable E34 RTCM GPIO interrupt, use SCU function call instead.
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34GPIE) &= ~(0x1 << pin);
			gpio->vtable->rtcm_interrupt_disable(pin);
		}
		else {
			// TODO: To enable E34 RTCM GPIO interrupt, use SCU function call instead.
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34GPIE) |= (0x1 << pin);
			gpio->vtable->rtcm_config_interrupt(pin, intr_type);
			gpio->vtable->rtcm_interrupt_enable(pin);
		}
	}
	else if (i == AON_GPIOS) {
		// TODO: To enable E34 AON_GPIO interrupt, use SCU function call instead.
		if (intr_type == gpio_int_disable) {
			*(volatile uint32_t *)(0x20000000 + METAL_UP_SCU_E34GPIE) &= ~(0x1 << (8 + pin));
		}
		else
			*(volatile uint32_t *)(0x20000000 + METAL_UP_SCU_E34GPIE) |= (0x1 << (8 + pin));
		gpio->vtable->config_interrupt(gpio, pin, intr_type);
	}
	else {
		gpio->vtable->config_interrupt(gpio, pin, intr_type);
	}

	return E_GPIO_SUCCESS;
}

/**
 * @brief Get raw status of the GPIO pin.
 * @param[in] gpio The GPIO handle.
 * @param[in] pin The pin number index from 0.
 * @return Raw status of GPIO pin.
 */
__inline__ uint32_t upt_gpio_get_raw_status(metal_gpio_Type *gpio, uint32_t pin) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if ( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		// TODO: Error handling.
	}

	if (i > AON_GPIOS)
		return gpio->vtable->rtcm_raw_status(pin);
	else if (i == AON_GPIOS)
		return gpio->vtable->raw_status(gpio, pin);
	else
		return gpio->vtable->raw_status(gpio, pin);
}

/**
 * @brief Get interrupt status of the GPIO pin.
 * @param[in] gpio The GPIO handle.
 * @param[in] pin The pin number index from 0.
 * @return Status of GPIO pin.
 */
__inline__ uint32_t upt_gpio_get_status(metal_gpio_Type *gpio, uint32_t pin) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		// TODO: Error handling
	}

	if (i > AON_GPIOS)
		//TODO: To get E34 RTCM_GPIO interrupt, use SCU function call instead.
		return gpio->vtable->rtcm_status(pin) & ( ((*(volatile uint32_t *)(0x20000000 + METAL_UP_SCU_E34GPIS))&(0x1 << pin))? 1 : 0 );
	else if (i == AON_GPIOS)
		//TODO: To get E34 AON_GPIO interrupt, use SCU function call instead.
		return gpio->vtable->status(gpio, pin) & ( ((*(volatile uint32_t *)(0x20000000 + METAL_UP_SCU_E34GPIS))&(0x1 << (8 + pin)))? 1 : 0 );
	else
		return gpio->vtable->status(gpio, pin);
}

/**
 * @brief Clear status of GPIO pin.
 * @param[in] gpio The GPIO handle.
 * @param[in] pin  The pin number index from 0.
 * @return enum_gpio_retcode_Type value.
 */
__inline__ enum_gpio_retcode_Type upt_gpio_clear_status(metal_gpio_Type *gpio, uint32_t pin) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if ( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		else if (i == RTCM_GPIOS)
			return E_GPIO_INVINIT;
	}

	if (i > AON_GPIOS) {
		gpio->vtable->rtcm_clear_interrupt(pin);
		//TODO: To clear E34 RTCM_GPIO interrupt, use SCU function call instead.
		*(volatile uint32_t *)(0x20000000 + METAL_UP_SCU_E34GPIS) = (0x1 << pin);
	}
	else if (i == AON_GPIOS) {
		gpio->vtable->clear_interrupt(gpio, pin);
		//TODO: To clear E34 AON_GPIO interrupt, use SCU function call instead.
		*(volatile uint32_t *)(0x20000000 + METAL_UP_SCU_E34GPIS) = (0x1 << (8 + pin));
	}
	else {
		gpio->vtable->clear_interrupt(gpio, pin);
	}
	return E_GPIO_SUCCESS;
}

/**
 * @brief Set RTCM GPIO pin S/L/R value.
 * @param[in] gpio The GPIO handle.
 * @param[in] pin  The pin number index from 0.
 * @param[in] value pin value to be set.
 * @return enum_gpio_retcode_Type value.
 */
__inline__ enum_gpio_retcode_Type upt_gpio_rtcm_set_bit_S_L_R(metal_gpio_Type *gpio, uint32_t pin, enum_gpio_value_Type value) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if ( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		else if (i == RTCM_GPIOS)
			return E_GPIO_INVINIT;
	}

	if (i == RTCM_GPIOS) {
		return gpio->vtable->rtcm_set_bit_S_L_R(pin, value);
	}
	return E_GPIO_INVINIT;
}

/**
 * @brief Enable/Disable RTCM GPIO pin S/L/R Special function.
 * @param[in] gpio The GPIO handle.
 * @param[in] pin  The pin number index from 0.
 * @param[in] enable Output data in S/L/R mode.
 * @return enum_gpio_retcode_Type value.
 */
__inline__ enum_gpio_retcode_Type upt_gpio_rtcm_S_L_R_output_enable(metal_gpio_Type *gpio, uint32_t pin, bool enable) {
	int i;

	for (i = 0; i < GPIO_DEVICE_NUMBER_LAST; i++) {
		if ( gpio == upt_gpio_get_device((enum_gpio_device_Type)i))
			break;
		else if (i == RTCM_GPIOS)
			return E_GPIO_INVINIT;
	}

	if (i == RTCM_GPIOS) {
		if (enable)
			return gpio->vtable->rtcm_S_L_R_output_enable(pin);
		else
			return gpio->vtable->rtcm_S_L_R_output_disable(pin);
	}
	return E_GPIO_INVINIT;
}

#endif /* METAL_GPIO_H */
