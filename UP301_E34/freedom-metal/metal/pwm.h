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
 * @file  pwm.h
 * @brief API for Pulse-width modulation module
 */
#ifndef METAL_PWM_H
#define METAL_PWM_H
#include <stdbool.h>
#include <stdint.h>

#include "rom_debug.h"

/**
 * @brief Device number of PWM
 * @ingroup UP301_Controller_PWM
 */
typedef enum enum_pwm_device {
	NAON_PERI_PWM = 0,		// 0~3
	AON_PWM					// 0
} enum_pwm_device_Type ;

/**
 * @brief Enums for PWM running modes.
 * @ingroup UP301_Controller_PWM
 */
typedef enum metal_pwm_run_mode {
    pwm_continuous = 0,
    pwm_one_shot = 1
} metal_pwm_run_mode_Type;

/**
 * @brief Enums for Interrupts enable/disable.
 * @ingroup UP301_Controller_PWM
 */
typedef enum metal_pwm_interrupt {
    pwm_interrupt_disable = 0,
    pwm_interrupt_enable
} metal_pwm_interrupt_Type;

/**
 * @brief PWM return error code.
 * @ingroup UP301_Controller_PWM
 */
typedef enum enum_pwm_retcode {
    E_PWM_SUCCESS,     // Success.
	E_PWM_INVINIT,	 	// Initial fail or resource is unavailable.
	E_PWM_INVPARA,	 	// Invalid function parameter/argument.
    E_PWM_ERROR,     	// Unspecific error.
} enum_pwm_retcode_Type;

/** @brief Interrupt status: return value of upt_pwm_get_status() */
#define pwm_ch_triggered			(0x1U << 0)

/**
 * @brief Handle for a PWM interface.
 */
typedef struct metal_pwm {
    const struct metal_pwm_vtable *vtable;
} metal_pwm_Type;
struct metal_pwm_vtable {
    enum_pwm_retcode_Type (*enable)(metal_pwm_Type *pwm, uint8_t pwm_ch, 
									metal_pwm_run_mode_Type mode);
    enum_pwm_retcode_Type (*disable)(metal_pwm_Type *pwm, uint8_t pwm_ch);
    enum_pwm_retcode_Type (*set_output_timing)(metal_pwm_Type *gpwm,
    						   uint8_t pwm_ch,
			   	   	   	   	   uint32_t base_clock,
							   uint32_t phase,
							   uint32_t duty,
							   uint32_t pulse);
    enum_pwm_retcode_Type (*trigger)(metal_pwm_Type *pwm,
    							uint8_t pwm_ch,
								uint32_t count);
    enum_pwm_retcode_Type (*cfg_interrupt)(metal_pwm_Type *pwm, uint8_t pwm_ch,
	 									   metal_pwm_interrupt_Type flag);
    uint32_t (*status_interrupt)(metal_pwm_Type *pwm, uint8_t pwm_ch);
    enum_pwm_retcode_Type (*clr_interrupt)(metal_pwm_Type *pwm, uint8_t pwm_ch);
};

/**
 * @brief Handle for a PWM device.
 */

/**
 * @brief Gets a PWM device handle.
 * @param[in] device_num The index of the desired PWM device.
 * @return A handle to the PWM device, or NULL if the device does not exist.
 */
metal_pwm_Type *upt_pwm_get_device(enum_pwm_device_Type device_num);

/**
 * @brief Sets frequency in Hz for a given PWM instance.
 * @param[in] pwm The PWM handle
 * @param[in] pwm_ch PWM channel
 * @param[in] base_clock // Depends on IP source_clock (NAON:55.296MHz / AON:32.768KHz), where base_clock corresponds to a specific number of source clock cycles.
 * @param[in] phase Clock phase 
 * @param[in] duty Clock duty
 * @param[in] pulse Total pulse period from 2 to 65535 based on base_clock (Should be at least greater than/equal to Phase + Duty)
 * @remarks No return value
 */
inline enum_pwm_retcode_Type upt_pwm_set_output_timing(metal_pwm_Type *pwm,
									   uint8_t pwm_ch,
		   	   	   	   	   	   	   	   uint32_t base_clock,
									   uint32_t phase,
									   uint32_t duty,
									   uint32_t pulse) {
	if (phase == 0) {
		UP_DEBUG_WARN("Error: Phase cannot be 0.\n");
		return E_PWM_INVPARA; 
	}
	if (duty == 0) {
		UP_DEBUG_WARN("Error: Duty cannot be 0.\n");
		return E_PWM_INVPARA; 
	}
	if (phase + duty > pulse) {
		UP_DEBUG_WARN("Error: Phase + Duty (%u + %u) cannot be greater than Pulse (%u).\n", phase, duty, pulse);
		return E_PWM_INVPARA; 
	}
    pwm->vtable->set_output_timing(pwm, pwm_ch, base_clock, phase, duty, pulse);
	
	return E_PWM_SUCCESS;
}

/**
 * @brief Set PWM a trigger count
 * @param[in] pwm PWM The PWM handle
 * @param[in] pwm_ch PWM channel
 * @param count Load count be be trigger
 * @remarks No return value
 */
inline enum_pwm_retcode_Type upt_pwm_trigger(metal_pwm_Type *pwm,
							uint8_t pwm_ch,
							uint32_t count) {
    return pwm->vtable->trigger(pwm, pwm_ch, count);
}


/**
 * @brief Enable PWM operation
 * @param[in] pwm The PWM handle
 * @param[in] pwm_ch PWM channel
 * @param[in] enable Enable/Disable PWM
 * @remarks No return value
 */
inline enum_pwm_retcode_Type upt_pwm_enable(metal_pwm_Type *pwm,
						   uint8_t pwm_ch,
						   metal_pwm_run_mode_Type enable) {
	if(enable)
		return pwm->vtable->enable(pwm, pwm_ch, pwm_continuous);
	else
		return pwm->vtable->disable(pwm, pwm_ch);
}

/**
 * @brief Enable/Disable PWM interrupts
 * @param[in] pwm The PWM handle
 * @param[in] pwm_ch PWM channel
 * @param[in] enable Enable/Disable PWM interrupt
 * @remarks No return value
 */
inline enum_pwm_retcode_Type upt_pwm_isr_enable(metal_pwm_Type *pwm,
							   uint8_t pwm_ch,
							   metal_pwm_interrupt_Type enable) {
    return pwm->vtable->cfg_interrupt(pwm, pwm_ch, enable);
}

/**
 * @brief Get status of PWM
 * @param[in] pwm The PWM handle
 * @param[in] pwm_ch PWM channel
 * @return PWM status
 */
inline uint32_t upt_pwm_get_status(metal_pwm_Type *pwm,
								   uint8_t pwm_ch) {
    return pwm->vtable->status_interrupt(pwm, pwm_ch);
}

/**
 * @brief Clears status of PWM
 * @param[in] pwm The PWM handle
 * @param[in] pwm_ch PWM channel
 * @remarks No return value
 */
inline enum_pwm_retcode_Type upt_pwm_clear_status(metal_pwm_Type *pwm,
								 uint8_t pwm_ch) {
    return pwm->vtable->clr_interrupt(pwm, pwm_ch);
}

#endif
