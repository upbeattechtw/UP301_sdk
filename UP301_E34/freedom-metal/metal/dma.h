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
 * @file  dma.h
 * @brief API for Direct Memory Access
 */
#ifndef METAL__DMA_H
#define METAL__DMA_H
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Device number of DMA engine
 * @ingroup UP301_Controller_DMA
 */
enum naon_dma_sel {
	NAON_DMA_0		= 0,
	NAON_DMA_1,
	NAON_DMA_2
};

/**
 * @brief DMA channels
 * @ingroup UP301_Controller_DMA
 */
typedef enum enum_dma_channel_Type {
	dma_ch0 = 0,
	dma_ch1,
	dma_ch2,
	dma_ch3,
	dma_ch4,
	dma_ch5,
	dma_ch6,
	dma_ch7
} enum_dma_channel_Type;

/**
 * @brief DMA interrupt status
 * @ingroup UP301_Controller_DMA
 */
typedef enum enum_dma_stauts_Type {
    dma_tc 			= 0,
	dma_error
} enum_dma_stauts_Type;

/**
 * @brief DMA transfer width
 * @ingroup UP301_Controller_DMA
 */
typedef enum enum_dma_wd_Type {
	dma_width_8bit 			= 0,
	dma_width_16bit,
	dma_width_32bit
} enum_dma_wd_Type;

/**
 * @brief DMA transfer burst size
 * @ingroup UP301_Controller_DMA
 */
typedef enum enum_dma_bsize_Type {
	dma_bsize_1		 		= 0,
	dma_bsize_4,
	dma_bsize_8,
	dma_bsize_16,
	dma_bsize_32,
	dma_bsize_64,
	dma_bsize_128,
	dma_bsize_256,
} enum_dma_bsize_Type;

/**
 * @brief DMA flow control type
 * @ingroup UP301_Controller_DMA
 */
typedef enum enum_dma_ctrltype_Type {
	memory_2_memory 	= 0,
	memory_2_peripheral,
	peripheral_2_memory,
	peripheral_2_peripheral,
	peripheral_2_peripheral_p,
	memory_2_peripheral_p,
	peripheral_2_memory_p,
	peripheral_2_peripheral_sp
} enum_dma_ctrltype_Type;

/*!
 * @brief dma return error code.
 * @ingroup UP301_Metal constructors & destructors
 */
typedef enum enum_dma_status{
    E_DMA_SUCCESS,       //Success.
    E_DMA_INVINIT,       //Initial fail or resource is unavailable.
    E_DMA_INVPARA,       //Invalid function parameter/argument.
    E_DMA_ERROR,         //Unspecific error.
} enum_dma_retcode_Type;

/** @brief DMA 0 request */
#define		UART_0_RX						0
/** @brief DMA 0 request */
#define		UART_0_TX						1
/** @brief DMA 0 request */
#define		UART_1_RX						2
/** @brief DMA 0 request */
#define		UART_1_TX						3
/** @brief DMA 0 request */
#define		SPI_0_M_RX_ALT_SPI_0_S_RX		4
/** @brief DMA 0 request */
#define		SPI_0_M_TX_ALT_SPI_0_S_TX		5
/** @brief DMA 0 request */
#define		SPI_1_RX						6
/** @brief DMA 0 request */
#define		SPI_1_TX						7
/** @brief DMA 0 request */
#define		I2C_0_RX						8
/** @brief DMA 0 request */
#define		I2C_0_TX						9
/** @brief DMA 0 request */
#define		I2C_1_RX_ALT_I2C_1_TX			10
/** @brief DMA 0 request */
#define		I2C_2_RX_ALT_I2C_2_TX			11
/** @brief DMA 0 request */
#define		I2S_0_RX						12
/** @brief DMA 0 request */
#define		I2S_0_TX						13
/** @brief DMA 0 request */
#define		I2S_M_1_RX_ALT_I2S_S_1_RX		14
/** @brief DMA 0 request */
#define		I2S_M_1_TX_ALT_I2S_S_1_TX		15

/** @brief DMA 1 request */
#define		UART_2_RX						0
/** @brief DMA 1 request */
#define		UART_2_TX						1
/** @brief DMA 1 request */
#define		UART_3_RX						2
/** @brief DMA 1 request */
#define		UART_3_TX						3
/** @brief DMA 1 request */
#define		SPI_2_RX						4
/** @brief DMA 1 request */
#define		SPI_2_TX						5
/** @brief DMA 1 request */
#define		SPI_3_RX						6
/** @brief DMA 1 request */
#define		SPI_3_TX						7
/** @brief DMA 1 request */
#define		I2C_3_RX_ALT_I2C_3_TX			8
/** @brief DMA 1 request */
#define		I2C_4_RX_ALT_I2C_4_TX			9
/** @brief DMA 1 request */
#define		I2C_5_RX_ALT_I2C_5_TX			10
/** @brief DMA 1 request */
#define		I2C_6_RX_ALT_I2C_6_TX			11
/** @brief DMA 1 request */
#define		AON_I2C_1_RX_ALT_AON_I2C_1_TX	12
/** @brief DMA 1 request */
#define		AON_I2C_2_RX_ALT_AON_I2C_2_TX	13
/** @brief DMA 1 request */
#define		AON_I2C_3_RX_ALT_AON_I2C_3_TX	14
/** @brief DMA 1 request */
#define		AON_I2C_4_RX_ALT_AON_I2C_4_TX	15

/** @brief DMA 2 request */
#define		AUDIO_ADC_0						0
/** @brief DMA 2 request */
#define		AUDIO_ADC_1						1
/** @brief DMA 2 request */
#define		AUDIO_ADC_2						2
/** @brief DMA 2 request */
#define		AUDIO_ADC_3						3
/** @brief DMA 2 request */
#define		ADC_0							4
/** @brief DMA 2 request */
#define		ADC_1							5
/** @brief DMA 2 request */
#define		ADC_2							6
/** @brief DMA 2 request */
#define		ADC_3							7
/** @brief DMA 2 request */
#define		AON_UART_RX						8
/** @brief DMA 2 request */
#define		AON_UART_TX						9
/** @brief DMA 2 request */
#define		AON_I2C_0_RX					10
/** @brief DMA 2 request */
#define		AON_I2C_0_TX					11
/** @brief DMA 2 request */
#define		AON_SPI_0_RX					12
/** @brief DMA 2 request */
#define		AON_SPI_0_TX					13
/** @brief DMA 2 request */
#define		AON_SPI_1_RX					14
/** @brief DMA 2 request */
#define		AON_SPI_1_TX					15

/** @brief Interrupt status: return value of upt_dma_get_status() */
#define dma_ch0_interrupt			(0x1U << 0)
#define dma_ch1_interrupt			(0x1U << 1)
#define dma_ch2_interrupt			(0x1U << 2)
#define dma_ch3_interrupt			(0x1U << 3)
#define dma_ch4_interrupt			(0x1U << 4)
#define dma_ch5_interrupt			(0x1U << 5)
#define dma_ch6_interrupt			(0x1U << 6)
#define dma_ch7_interrupt			(0x1U << 7)

/**
* @brief Informations of DMA n-th link list mode
* @ingroup UP301_Controller_DMA
*/
typedef	union {
	uint32_t data;
	struct {
		uint32_t transfersize:			12;
		enum_dma_bsize_Type src_bsize:			3;
		enum_dma_bsize_Type dst_bsize:			3;
		enum_dma_wd_Type src_width:				3;
		enum_dma_wd_Type dst_width:				3;
		uint32_t reserved_2:			2;
		uint32_t src_increment_en: 		1;
		uint32_t dst_increment_en:		1;
		uint32_t reserved_1:			4;
	}bit;
} DMA_CH_CTRL_Type;

/**
 * @brief structures of DMA link list mode
 * @ingroup UP301_Controller_DMA
 */
typedef struct dma_lli{
	uint32_t *src_addr;
	uint32_t *dst_addr;
	struct dma_lli *next_lli;
	DMA_CH_CTRL_Type cx_ctrlrg;
} DMA_LLI_Type;

/**
 * @brief DMA configuration structures
 * @ingroup UP301_Controller_DMA
 */
typedef struct {
	uint32_t *src_addr;
	uint32_t *dst_addr;
	uint32_t src_increment_en;
	uint32_t dst_increment_en;
	enum_dma_wd_Type src_width;
	enum_dma_wd_Type dst_width;
	enum_dma_bsize_Type src_bsize;
	enum_dma_bsize_Type dst_bsize;
	uint32_t transfersize;
	uint32_t src_req;
	uint32_t dst_req;
	enum_dma_ctrltype_Type flow_ctrl;
} DMA_CONFIG_INFO_Type;

/**
 * @brief Handle for a DMA engine
 */
typedef struct metal_dma {
    const struct __metal_dma_vtable *vtable;
} metal_dma_Type;

struct __metal_dma_vtable {
	enum_dma_retcode_Type (*enable)(metal_dma_Type *dma, int32_t enable);
	enum_dma_retcode_Type (*enable_channel)(metal_dma_Type *dma, int32_t channel, int32_t enable);
	enum_dma_retcode_Type (*config)(metal_dma_Type *dma, int32_t channel, DMA_LLI_Type *lli_ptr, int32_t lli_len, DMA_CONFIG_INFO_Type *dma_config);
    int32_t (*tc_complete)(metal_dma_Type *dma, int32_t channel);
    enum_dma_retcode_Type (*interrupt_enable)(metal_dma_Type *dma, int32_t channel, int32_t enable);
    int32_t (*read_status)(metal_dma_Type *dma, int32_t channel, enum_dma_stauts_Type status_category);
    enum_dma_retcode_Type (*clear_interrupt_status)(metal_dma_Type *dma, int32_t channel, enum_dma_stauts_Type status_category);
	enum_dma_retcode_Type (*reload)(metal_dma_Type *dma, uint32_t channel, uint32_t src_addr, uint32_t dst_addr, uint32_t size);
	enum_dma_retcode_Type (*suspend)(metal_dma_Type *dma, uint32_t channel);
	enum_dma_retcode_Type (*resume)(metal_dma_Type *dma, uint32_t channel);
};

/**
 * @brief Get a handle for a DMA
 * @param[in] device_num The index of the desired DMA engine
 * @return A handle to the DMA device, or NULL if the engine does not exist
 */
metal_dma_Type *upt_dma_get_device(uint32_t device_num);

/**
 * @brief Perform a DMA transfer configurations/initialization with certain channel
 * @param[in] dma The DMA handle
 * @param[in] channel DMA channel number
 * @param[in] lli_ptr A pointer to the DMA scatter gather function
 * @param[in] lli_len Segments to the scatter gather function
 * @param[in] dma_config The configurations for the DMA transfer.
 * @remarks No return value
 */
__inline__ enum_dma_retcode_Type upt_dma_config(metal_dma_Type *dma, enum_dma_channel_Type channel, DMA_LLI_Type *lli_ptr, int32_t lli_len, DMA_CONFIG_INFO_Type *dma_config) {
	dma->vtable->config(dma, channel, lli_ptr, lli_len, dma_config);
	return E_DMA_SUCCESS;
}


/**
 * @brief Enable a DMA engine
 * @param[in] dma The DMA handle
 * @param[in] enable DMA engine enable/disable
 * @remarks No return value
 */
__inline__ enum_dma_retcode_Type upt_dma_enable(metal_dma_Type *dma, bool enable) {
	dma->vtable->enable(dma, enable);
	return E_DMA_SUCCESS;
}

/**
 * @brief Enable a DMA with certain channel
 * @param[in] dma The DMA handle
 * @param[in] channel DMA channel number
 * @param[in] enable DMA channel enable/disable
 * @remarks No return value
 */
__inline__ enum_dma_retcode_Type upt_dma_enable_channel(metal_dma_Type *dma, enum_dma_channel_Type channel, bool enable) {
	dma->vtable->enable_channel(dma, channel, enable);
	return E_DMA_SUCCESS;
}

/**
 * @brief Enable/Disable DMA interrupt with certain channel
 * @param[in] dma The DMA handle
 * @param[in] channel DMA channel number
 * @param[in] enable Enable/disable of DMA
 * @remarks No return value
 */
__inline__ enum_dma_retcode_Type upt_dma_isr_enable(metal_dma_Type *dma, enum_dma_channel_Type channel, bool enable) {
	dma->vtable->interrupt_enable(dma, channel, enable);
	return E_DMA_SUCCESS;
}

/**
 * @brief Get status of DMA with certain channel
 * @param[in] dma The DMA handle
 * @param[in] channel DMA channel number
 * @param[in] status_category DMA TC/Error status selection
 * @return Status of DMA with Channel(x)
 */
__inline__ uint32_t upt_dma_get_status(metal_dma_Type *dma, enum_dma_channel_Type channel, enum_dma_stauts_Type status_category) {
	return dma->vtable->read_status(dma, channel, status_category);
}

/**
 * @brief Clear status of DMA with certain channel
 * @param[in] dma The DMA handle
 * @param[in] channel DMA channel number
 * @param[in] status_category DMA TC/Error status selection
 */
__inline__ enum_dma_retcode_Type upt_dma_clear_status(metal_dma_Type *dma, enum_dma_channel_Type channel, enum_dma_stauts_Type status_category) {
	dma->vtable->clear_interrupt_status(dma, channel, status_category);
	return E_DMA_SUCCESS;
}

/**
 * @brief Check TC complete of DMA with certain channel
 * @param[in] dma The DMA handle
 * @param[in] channel DMA channel number
 * @return Terminal count is reached
 */
__inline__ int32_t upt_dma_is_complete(metal_dma_Type *dma, enum_dma_channel_Type channel) {
	return dma->vtable->tc_complete(dma, channel);
}


__inline__ enum_dma_retcode_Type upt_dma_reload(metal_dma_Type *dma, uint32_t channel, uint32_t src_addr, uint32_t dst_addr, uint32_t size) {
	dma->vtable->reload(dma, channel, src_addr, dst_addr, size);
	return E_DMA_SUCCESS;
}

__inline__ enum_dma_retcode_Type upt_dma_resume(metal_dma_Type *dma, uint32_t channel) {
	return dma->vtable->resume(dma, channel);
}

__inline__ enum_dma_retcode_Type upt_dma_suspend(metal_dma_Type *dma, uint32_t channel) {
	return dma->vtable->suspend(dma, channel);
}

#endif
