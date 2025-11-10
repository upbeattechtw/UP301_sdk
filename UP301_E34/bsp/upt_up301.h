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
 * @file  upt_up301.h
 * @brief UP301 device (SCU) register header file
 */

#ifndef __UPT_UP301_H__
#define __UPT_UP301_H__
#include <stdint.h>

#include "upt_scuBitMap.h"
#include "upt_scuRegMap.h"

#define BIT0	(0x1 << 0)
#define BIT1	(0x1 << 1)
#define BIT2	(0x1 << 2)
#define BIT3	(0x1 << 3)
#define BIT4	(0x1 << 4)
#define BIT5	(0x1 << 5)
#define BIT6	(0x1 << 6)
#define BIT7	(0x1 << 7)
#define BIT8	(0x1 << 8)
#define BIT9	(0x1 << 9)
#define BIT10	(0x1 << 10)
#define BIT11	(0x1 << 11)
#define BIT12	(0x1 << 12)
#define BIT13	(0x1 << 13)
#define BIT14	(0x1 << 14)
#define BIT15	(0x1 << 15)
#define BIT16	(0x1 << 16)
#define BIT17	(0x1 << 17)
#define BIT18	(0x1 << 18)
#define BIT19	(0x1 << 19)
#define BIT20	(0x1 << 20)
#define BIT21	(0x1 << 21)
#define BIT22	(0x1 << 22)
#define BIT23	(0x1 << 23)
#define BIT24	(0x1 << 24)
#define BIT25	(0x1 << 25)
#define BIT26	(0x1 << 26)
#define BIT27	(0x1 << 27)
#define BIT28	(0x1 << 28)
#define BIT29	(0x1 << 29)
#define BIT30	(0x1 << 30)
#define BIT31	(0x1 << 31)

/**
 * @addtogroup UP301_GROUP
 * @{
 */
#define __UPT_ACCESS_ONCE(x) (*(__typeof__(*x) volatile *)(x))
#define UPT_REG(regName) __UPT_ACCESS_ONCE(SCU_##regName)
#define UPT_REG_OF(bitName) __UPT_ACCESS_ONCE(SCU_##bitName##_REG)
#define UPT_GET_BITSLICE(bitName) ((UPT_REG_OF(bitName) & SCU_##bitName##_MSK) >> SCU_##bitName##_POS)
#define UPT_SET_BITSLICE(bitName, val)				\
  ((UPT_REG_OF(bitName) & ~SCU_##bitName##_MSK) | ((val << SCU_##bitName##_POS) & SCU_##bitName##_MSK))
#define UPT_VARABLE_SET_BITSLICE(varable, bitName, val) \
  ((varable & ~SCU_##bitName##_MSK) | ((val << SCU_##bitName##_POS) & SCU_##bitName##_MSK))
#define UPT_SET_REG_BITS(bitName, val) \
  UPT_REG_OF(bitName) = UPT_SET_BITSLICE(bitName, val)
#define UPT_REG_BIT_SET(bitName) UPT_REG_OF(bitName) |= SCU_##bitName##_MSK
#define UPT_REG_BIT_CLEAR(bitName) UPT_REG_OF(bitName) &= ~SCU_##bitName##_MSK
#define UPT_WFI() __asm__ volatile("wfi")
#define UPT_SET_PINMUX(pinName, val) UPT_SET_REG_BITS(PINMUX_##pinName, val)
#define UPT_SET_PADDRV(pinName, val) UPT_SET_REG_BITS(PADDRV_##pinName, val)
#define UPT_SET_PADCTRL(pinName, val) UPT_SET_REG_BITS(PADCTRL_##pinName, val)

/**
 * @brief UPT return error code.
 */
typedef enum enum_upt_retcode {
    E_UPT_SUCCESS,		// Success.
	E_UPT_INVINIT,		// Initial fail or resource is unavailable.
	E_UPT_INVPARA,	 	// Invalid function parameter/argument.
	E_UPT_MEMFAULT,		// Memory access problem.
    E_UPT_ERROR,     	// Unspecific error.
} enum_upt_retcode_Type;

/** Pad driving strength enum */
enum {
  /** 4'b0000: 2mA driving */
  UPT_PADDRV_DS_2mA = 0x00,
   /** 4'b0001: 4mA driving */
  UPT_PADDRV_DS_4mA = 0x01,
  /** 4'b0010: 8mA driving */
  UPT_PADDRV_DS_8mA = 0x02,
  /** 4'b0011: 12mA driving */
  UPT_PADDRV_DS_12mA = 0x03,
  /** 4'b0100: high slew rate */
  UPT_PADDRV_SR_HIGH = 0x04,
  /** 4'b1000: schmitt trigger enable */
  UPT_PADDRV_IS_EN = 0x08
};

/** Pad control enum */
enum UPT_PADCTRL_TYPE {
  /** 3'b010: pad pull-up enable low  */
  UPT_PADCTRL_PULLUP_LOW = 0x02,
  /** 3'b011: pad pull-up enable high */
  UPT_PADCTRL_PULLUP_HIGH = 0x03,
  /** 3'b100: pad input enable */
  UPT_PADCTRL_INPUT_ENABLE = 0x04
};
/*! @} */

#endif //__UPT_UP301_H__
