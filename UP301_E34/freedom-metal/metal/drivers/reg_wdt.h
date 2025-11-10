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

#ifndef		__REG_WDT_H__
#define		__REG_WDT_H__
#include	<stdint.h>

#ifdef		RESERVED_AREA_DWORD
#undef		RESERVED_AREA_DWORD
#endif

#define		RESERVED_AREA_DWORD(var1, var2)	volatile uint32_t (reserved_##var1##_##var2[(((var2)+1)-(var1))/sizeof(uint32_t)])

typedef	union wdog_un_control {
	volatile uint32_t data;
	struct {
		volatile uint32_t inten				:  1;	// [0]
		volatile uint32_t resen				:  1;	// [1]
		volatile uint32_t					: 30;	// [31:2]
	} bit;
} wdog_un_control_Type;

typedef	union wdog_un_ris {
	volatile uint32_t data;
	struct {
		volatile uint32_t ris				:  1;	// [0]
		volatile uint32_t					: 31;	// [31:1]
	} bit;
} wdog_un_ris_Type;

typedef	union wdog_un_mis {
	volatile uint32_t data;
	struct {
		volatile uint32_t mis				:  1;	// [0]
		volatile uint32_t					: 31;	// [31:1]
	} bit;
} wdog_un_mis_Type;

typedef union wdog_un_itcr {
	volatile uint32_t data;
	struct {
		volatile uint32_t iten				:  1;	// [0]
		volatile uint32_t					: 31;	// [31:1]
	} bit;
} wdog_un_itcr_Type;

typedef union wdog_un_itop {
	volatile uint32_t data;
	struct {
		volatile uint32_t res				:  1;	// [0]
		volatile uint32_t inte				:  1;	// [1]
		volatile uint32_t					: 30;	// [31:2]
	} bit;
} wdog_un_itop_Type;

typedef	union wdog_un_periph_id {
	volatile uint32_t data;
	struct {
		volatile uint32_t part_number		: 12;	// [11:0]
		volatile uint32_t designer_id		:  8;	// [19:12]
		volatile uint32_t revision			:  4;	// [23:20]
		volatile uint32_t configuration		:  8;	// [31:24]
	} bit;
} wdog_un_periph_id_Type;

typedef	union wdog_un_p_cell_id {
	volatile uint32_t DATA;
	struct {
		volatile uint32_t P_CELL_ID			:  8;	// [7:0]
		volatile uint32_t					: 24;	// [31:8]
	} bit;
} wdog_un_p_cell_id_Type;

typedef	struct reg_st_wdog {
	volatile uint32_t		load;					// +000H
	volatile uint32_t		value;					// +004H
	wdog_un_control_Type	control;				// +008H
	volatile uint32_t		int_clr;				// +00CH
	wdog_un_ris_Type		ris;					// +010H
	wdog_un_mis_Type		mis;					// +014H
	RESERVED_AREA_DWORD(0x18, 0xBFF);
	volatile uint32_t	lock;						// +C00H
	RESERVED_AREA_DWORD(0xC04, 0xEFF);
	wdog_un_itcr_Type		itcr;					// +F00H
	wdog_un_itop_Type		itop;					// +F04H
	RESERVED_AREA_DWORD(0xF08, 0xFDF);
	wdog_un_periph_id_Type	periph_id0;				// +FE0H
	wdog_un_periph_id_Type	periph_id1;				// +FE4H
	wdog_un_periph_id_Type	periph_id2;				// +FE8H
	wdog_un_periph_id_Type	periph_id3;				// +FECH
	wdog_un_p_cell_id_Type	p_cell_id0;				// +FF0H
	wdog_un_p_cell_id_Type	p_cell_id1;				// +FF4H
	wdog_un_p_cell_id_Type	p_cell_id2;				// +FF8H
	wdog_un_p_cell_id_Type	p_cell_id3;				// +FFCH
} reg_st_wdog_Type;

#endif
