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

#ifndef UPT_ARM_BASED_SP804_H
#define UPT_ARM_BASED_SP804_H
#include <stdint.h>

#ifdef RESERVED_AREA_DWORD
#undef RESERVED_AREA_DWORD
#endif

#define RESERVED_AREA_DWORD(var1, var2) volatile uint32_t (reserved_##var1##_##var2[(((var2)+1)-(var1))/sizeof(uint32_t)])

/**
 * @brief Timer OSC mode.
 * @ingroup UP301_Controller_GTIMER
 */
typedef	enum sp804_en_osc {
	SP804_EN_OSC_WRAPPING = 0,	// Wrapping mode
	SP804_EN_OSC_ONE_SHOT		// One-shot mode
} sp804_en_osc_Type;

/**
 * @brief Timer counter size select.
 * @ingroup UP301_Controller_GTIMER
 */
typedef enum sp804_en_tsize	{
	SP804_EN_TSIZE_16BIT = 0,	// 16bit counter
	SP804_EN_TSIZE_32BIT		// 32bit counter
} sp804_en_tsize_Type;

/**
 * @brief Timer pre-scale.
 * @ingroup UP301_Controller_GTIMER
 */
typedef	enum sp804_en_pscl {
	SP804_EN_PSCL_DIV1			= 0,
	SP804_EN_PSCL_DIV16,
	SP804_EN_PSCL_DIV256
} sp804_en_pscl_Type;

/**
 * @brief Timer ISR enable/disable.
 * @ingroup UP301_Controller_GTIMER
 */
typedef	enum sp804_en_inten {
	SP804_EN_INTEN_DISABLE = 0,
	SP804_EN_INTEN_ENABLE
} sp804_en_inten_Type;

/**
 * @brief Timer operating mode.
 * @ingroup UP301_Controller_GTIMER
 */
typedef	enum sp804_en_tmode {
	SP804_EN_TMODE_FREERUN = 0,	// Free-run mode
	SP804_EN_TMODE_PERIODIC		// Periodic mode
} sp804_en_tmode_Type;

/**
 * @brief Activate timer.
 * @ingroup UP301_Controller_GTIMER
 */
typedef	enum sp804_en_ten {
	SP804_EN_TEN_STOP = 0,
	SP804_EN_TEN_START
} sp804_en_ten_Type;

/**
 * @brief TimerX control register structure.
 * @ingroup UP301_Controller_GTIMER
 */
typedef union sp804_un_tmrxctl{
	uint32_t DATA;
	struct {
		uint32_t		osc				: 1;	// B00		One Shot Count			R/W		0
						// Selects one-shot or wrapping counter mode :
						// 0	wrapping mode.
						// 1	one-shot mode.
		uint32_t		tsize			: 1;	// B01		Timer Size				R/W		0
						// Selects 16/32 bit counter operation :
						// 0	16-bit counter.
						// 1	32-bit counter.
		uint32_t		pscl			: 2;	// B02-B03	Timer Pre-scale			R/W		00
						// Pre-scale bits:
						// 00	0 stages of pre-scale, clock is divided by 1.
						// 01	4 stages of pre-scale, clock is divided by 16.
						// 10	8 stages of pre-scale, clock is divided by 256.
						// 11	Not defined, do not use.
		uint32_t						: 1;	// B04		Reserved				R/W		0
						// Reserved bit, do not modify, and ignore on read.
		uint32_t		inten			: 1;	// B05		Interrupt Enable		R/W		1
						// Interrupt Enable bit:
						// 0	Timer Interrupt disabled.
						// 1	Timer Interrupt enabled.
		uint32_t		tmode			: 1;	// B06		Timer Mode				R/W		0
						// Mode bit:
						// 0	Timer is in free-running mode.
						// 1	Timer is in periodic mode.
		uint32_t		ten				: 1;	// B07		Timer Enable			R/W		0
						// Enable bit:
						// 0	Timer disabled.
						// 1	Timer enabled.
		uint32_t						: 24;	// B08-B31	Reserved				-		-
						// Read data is not defined, must read as zeros.
	} bit;
} sp804_un_tmrxctl_Type;

/**
 * @brief TimerX raw interrupt status register structure.
 * @ingroup UP301_Controller_GTIMER
 */
typedef union {
	uint32_t DATA;
	struct {
		uint32_t		rti				: 1;	// B00		Raw Timer Interrupt		R		0
						// This register indicates the raw interrupt status from the counter.
						// This value is ANDed with the timer interrupt enable bit from the
						// control register to create the masked interrupt, which is passed to
						// the interrupt output pin.
		uint32_t						: 31;	// B01-B31	Reserved				-		-
						// Read data is not defined, must read as zeros.
	} bit;
} SP804_un_tmrxris_Type;

/**
 * @brief TimerX mask interrupt status register structure.
 * @ingroup UP301_Controller_GTIMER
 */
typedef union {
	uint32_t DATA;
	struct {
		uint32_t		tis				: 1;	// B00		Timer Interrupt Status	R		0
						// This register indicates the masked interrupt status from the counter.
						// This value is the logical AND of the raw interrupt status with the
						// timer interrupt enable bit from the control register, and is the same
						// value which s passed to the interrupt output pin.
		uint32_t						: 31;	// B01-B31	Reserved				-		-
						// Read data is not defined, must read as zeros.
	} bit;
} SP804_UN_TMRxMIS;

/**
 * @brief Timer channel X group of registers structure.
 * @ingroup UP301_Controller_GTIMER
 */
typedef	struct {
	volatile uint32_t				tmrld;	// +00H		TMRxLD	Load value for Timer x.
	volatile uint32_t				tmrval;	// +04H		TMRxVAL	The current value of Timer x.
	volatile sp804_un_tmrxctl_Type	tmrctl;	// +08H		TMRxCTL	Timer x control register.
	volatile uint32_t				tmric;	// +0CH		TMRxIC	Timer x interrupt clear.
	volatile SP804_un_tmrxris_Type	tmrris;	// +10H		TMRxRIS	Timer x raw interrupt status.
	volatile SP804_UN_TMRxMIS		tmrmis;	// +14H		TMRxMIS	Timer x masked interrupt status.
	volatile uint32_t				tmrbgl;	// +18H		TMRxBGL	Background load value for Timer x.
	RESERVED_AREA_DWORD(0x01C, 0x01F);		// +1CH		Reserved for future expansion.
} sp804_st_ch_Type;

/**
 * @brief Timer IP registers structure.
 * @ingroup UP301_Controller_GTIMER
 */
typedef	struct {
	sp804_st_ch_Type			ch[2];	// +000h..+0x3F
	RESERVED_AREA_DWORD(0x040, 0x0FF);	// +040h-0FFh		Reserved for future expansion
	RESERVED_AREA_DWORD(0x100, 0xEFF);	// +100h-EFCh		Reserved for future expansion
	volatile uint32_t			tmitcr;	// +F00h
	volatile uint32_t			tmiop;	// +F04h
	RESERVED_AREA_DWORD(0xF08, 0xFDF);	// +F08h-FDCh		Reserved for future expansion
	volatile uint32_t			tmpid0;	// +FE0h
	volatile uint32_t			tmpid1;	// +FE4h
	volatile uint32_t			tmpid2;	// +FE8h
	volatile uint32_t			tmpid3;	// +FECh
	volatile uint32_t			tmpcid0;// +FF0h
	volatile uint32_t			tmpcid1;// +FF4h
	volatile uint32_t			tmpcid2;// +FF8h
	volatile uint32_t			tmpcid3;// +FFCh
} reg_st_sp804_Type;

#endif /* UPT_ARM_BASED_SP804_H */
