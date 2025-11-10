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
 * @file  gtimer.h
 * @brief API for generic timer API header file
 */
#ifndef METAL_GTIMER_H
#define METAL_GTIMER_H
#include <stdbool.h>
#include <stdint.h>

#include "reg_sp804.h"

/**
 * @brief Number of timer device
 * @ingroup UP301_Controller_GTIMER
 */
typedef enum enum_gtimer_device {
	NAON_GTIMER_01		= 0,
	NAON_GTIMER_23,
	NAON_GTIMER_45,
	NAON_GTIMER_67,
	AON_GTIMER_01,
	AON_GTIMER_23,
	AON_FW_GTIMER_01,
	AON_FW_GTIMER_23,
	RTCM_TICK_GTIMER_01,
	GTIMER_DEVICE_NUMBER_LAST
} enum_gtimer_device_Type;

/**
 * @brief Timer instance
 * @ingroup UP301_Controller_GTIMER
 */
typedef enum enum_gtimer_inst {
	gtimer_first		= 0,
	gtimer_second
} enum_gtimer_inst_Type;

/**
 * @brief Timer interrupt sources
 * @ingroup UP301_Controller_GTIMER
 */
typedef enum enum_gtimer_intdes {
	gtimer_int_none 	= 0,
	gtimer_int_e34,
	gtimer_int_e21,
	gtimer_int_both
} enum_gtimer_intdes_Type;

/**
 * @brief Timer return error code.
 * @ingroup UP301_Controller_GTIMER
 */
typedef enum enum_gtimer_retcode {
    E_GTIMER_SUCCESS,	// Success.
	E_GTIMER_INVINIT,	// Initial fail or resource is unavailable.
	E_GTIMER_INVPARA,	// Invalid function parameter/argument.
    E_GTIMER_ERROR,		// Unspecific error.
} enum_gtimer_retcode_Type;

/** @brief Interrupt status: return value of upt_gtimer_get_status() */
#define GTIMER_INTST_COMPLETE	(0x1U << 0)

/**
 * @brief Handle for a general timer
 */
typedef struct metal_gtimer {
    const struct __metal_gtimer_vtable *vtable;
} metal_gtimer_Type;

struct __metal_gtimer_vtable {
	enum_gtimer_retcode_Type (*init)(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, sp804_en_osc_Type osc, sp804_en_tsize_Type tsize, sp804_en_tmode_Type tmode);
	enum_gtimer_retcode_Type (*clear_interrupt)(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst);
	enum_gtimer_retcode_Type (*enable_interrupt)(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, sp804_en_inten_Type param);
	enum_gtimer_retcode_Type (*set_load_value)(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, sp804_en_pscl_Type pscl, uint32_t tmrld);
	enum_gtimer_retcode_Type (*set_load_value_ms)(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, sp804_en_pscl_Type pscl, uint32_t ms);	
	enum_gtimer_retcode_Type (*enable_timer)(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, sp804_en_ten_Type param);
	uint32_t (*get_count)(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst);
	uint32_t (*is_interrupt_raw)(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst);
	uint32_t (*receipt_interrupt)(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst);
};

/**
 * @brief Get a handle for a timer
 * @param[in] device_num The index of the specific timer
 * @return A handle to a timer, or NULL if the device does not exist
 */
metal_gtimer_Type *upt_gtimer_get_device(enum_gtimer_device_Type device_num);

/**
 * @brief Initialize timer.
 * @param[in] gtimer The timer handle.
 * @param[in] chInst Instance of timer.
 * @param[in] tmrld load count.
 * @return enum_gtimer_retcode_Type value.
 */
__inline__ enum_gtimer_retcode_Type upt_gtimer_init(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, uint32_t tmrld) {
	enum_gtimer_retcode_Type ret = E_GTIMER_ERROR;

	ret = gtimer->vtable->init(gtimer, chInst, SP804_EN_OSC_WRAPPING, SP804_EN_TSIZE_32BIT, SP804_EN_TMODE_PERIODIC);
	if (ret == E_GTIMER_SUCCESS) {
		return gtimer->vtable->set_load_value(gtimer, chInst, SP804_EN_PSCL_DIV1, tmrld);
	}
	return ret;
}

/**
 * @brief Initialize the timer using milliseconds. Note: This API may introduce 
 * slight inaccuracies due to timing resolution or conversion rounding.
 * @param[in] gtimer The timer handle.
 * @param[in] chInst Instance of timer.
 * @param[in] ms load count (Unit in ms).
 * @return enum_gtimer_retcode_Type value.
 */
__inline__ enum_gtimer_retcode_Type upt_gtimer_init_ms(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, uint32_t ms) {
	enum_gtimer_retcode_Type ret = E_GTIMER_ERROR;

	ret = gtimer->vtable->init(gtimer, chInst, SP804_EN_OSC_WRAPPING, SP804_EN_TSIZE_32BIT, SP804_EN_TMODE_PERIODIC);
	if (ret == E_GTIMER_SUCCESS) {
		return gtimer->vtable->set_load_value_ms(gtimer, chInst, SP804_EN_PSCL_DIV1, ms);
	}
	return ret;
}

/**
 * @brief Activate timer.
 * @param[in] gtimer The timer handle.
 * @param[in] chInst Instance of timer.
 * @param[in] enable enable/disable timer.
 * @return enum_gtimer_retcode_Type value.
 */
__inline__ enum_gtimer_retcode_Type upt_gtimer_enable(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, bool enable) {
    if (enable)
    	return gtimer->vtable->enable_timer(gtimer, chInst, SP804_EN_TEN_START);
    else
    	return gtimer->vtable->enable_timer(gtimer, chInst, SP804_EN_TEN_STOP);
}

/**
 * @brief Enable/Disable timer interrupt
 * @param[in] gtimer The timer handle
 * @param[in] chInst Instance of timer
 * @param[in] enable enable/disable interrupt
 * @remarks No return value
 */
__inline__ enum_gtimer_retcode_Type upt_gtimer_isr_enable(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, enum_gtimer_intdes_Type enable) {
	int i;

	for (i = 0; i < GTIMER_DEVICE_NUMBER_LAST; i++) {
		if( gtimer == upt_gtimer_get_device((enum_gtimer_device_Type)i))
			break;
		if (i == RTCM_TICK_GTIMER_01)
			return E_GTIMER_INVINIT;
	}

	// TODO: To Enable E34 GTIEMR interrupt, use SCU function call instead
	if (enable == gtimer_int_none) {
		if(i == AON_GTIMER_01) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) &= ~(0x1 << (4 + chInst));
		} else if (i == AON_GTIMER_23) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) &= ~(0x1 << (6 + chInst));
		} else if (i == AON_FW_GTIMER_01) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) &= ~(0x1 << (0 + chInst));
		} else if (i == AON_FW_GTIMER_23) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) &= ~(0x1 << (2 + chInst));
		}
		return gtimer->vtable->enable_interrupt(gtimer, chInst, SP804_EN_INTEN_DISABLE);
	}
	else if ( (enable == gtimer_int_e34) || (enable == gtimer_int_both) ) {
		if (i == AON_GTIMER_01) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) |= (0x1 << (4 + chInst));
		} else if (i == AON_GTIMER_23) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) |= (0x1 << (6 + chInst));
		} else if (i == AON_FW_GTIMER_01) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) |= (0x1 << (0 + chInst));
		} else if (i == AON_FW_GTIMER_23) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) |= (0x1 << (2 + chInst));
		}
		return gtimer->vtable->enable_interrupt(gtimer, chInst, SP804_EN_INTEN_ENABLE);

	}
	else if (enable == gtimer_int_e21) {
		if(i == AON_GTIMER_01) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) &= ~(0x1 << (4 + chInst));
		} else if (i == AON_GTIMER_23) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) &= ~(0x1 << (6 + chInst));
		} else if (i == AON_FW_GTIMER_01) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) &= ~(0x1 << (0 + chInst));
		} else if (i == AON_FW_GTIMER_23) {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) &= ~(0x1 << (2 + chInst));
		}
		return gtimer->vtable->enable_interrupt(gtimer, chInst, SP804_EN_INTEN_ENABLE);
	}
	else {
		return E_GTIMER_INVPARA;
	}
}

/**
 * @brief Get status of timer
 * @param[in] gtimer The timer handle
 * @param[in] chInst Instance of timer
 * @return Status of timer
 */
__inline__ uint32_t upt_gtimer_get_status(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst) {
    return gtimer->vtable->is_interrupt_raw(gtimer, chInst);
}

/**
 * @brief Clear status of timer
 * @param[in] gtimer The timer handle
 * @param[in] chInst Instance of timer
 * @remarks No return valueset_load_value
 */
__inline__ enum_gtimer_retcode_Type upt_gtimer_clear_status(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst) {
    return gtimer->vtable->clear_interrupt(gtimer, chInst);
}

/**
 * @brief Check timer status and clear it
 * @param[in] gtimer The timer handle
 * @param[in] chInst Instance of timer
 * @return 1 if any status, 0 if otherwise
 */
__inline__ uint32_t upt_gtimer_receipt_status(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst) {
    return gtimer->vtable->receipt_interrupt(gtimer, chInst);
}


/**
 * @brief Get the current count of the timer
 * @param[in] gtimer The timer handle
 * @param[in] chInst Instance of timer
 * @return Current count value of the timer
 */
__inline__ uint32_t upt_gtimer_get_count(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst) {
	return gtimer->vtable->get_count(gtimer, chInst);
}

#endif
