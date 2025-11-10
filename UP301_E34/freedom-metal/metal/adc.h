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
 * @file  adc.h
 * @brief API for Analog-to-Digital converter
 */
#ifndef METAL_ADC_H
#define METAL_ADC_H
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Device number of ADC engine
 * @ingroup UP301_Controller_ADC
 */
typedef enum enum_adc_device {
	AON_ADC	= 0,
} enum_adc_device_Type;

/**
 * @brief ADC number
 * @ingroup UP301_Controller_ADC
 */
typedef enum enum_adc_num {
	adc0 = 0,
	adc1
} enum_adc_num_Type;

/**
 * @brief ADC channels
 * @ingroup UP301_Controller_ADC
 */
typedef enum enum_adc_mode {
	adc_ch0 = 0,
	adc_ch1,
	adc_ch2,
	adc_ch3,
	adc_core,
	adc_battery,
	adc_0to3loop = 8
} enum_adc_mode_Type;

/**
 * @brief ADC interrupt mode
 * @ingroup UP301_Controller_ADC
 */
typedef enum enum_adc_intmode {
	adc_intmode_more_than_1 	= 0x1,
	adc_intmode_above_watermark = 0x2,
	adc_intmode_fifo_full		= 0x4,
	adc_intmode_fifo_overflow	= 0x8
} enum_adc_intmode_Type;

/**
 * @brief ADC interrupt sources
 * @ingroup UP301_Controller_ADC
 */
typedef enum enum_adc_intdes {
	adc_int_none = 0,
	adc_int_e34,
	adc_int_e21,
	adc_int_both
} enum_adc_intdes_Type;

/**
 * @brief ADC FIFO watermark level
 * @ingroup UP301_Controller_ADC
 */
typedef enum enum_adc_watermark {
	adc_watermark_8 = 0,
	adc_watermark_16,
	adc_watermark_24
} enum_adc_watermark_Type;

/**
 * @brief ADC return error code.
 * @ingroup UP301_Controller_ADC
 */
typedef enum enum_adc_retcode {
    E_ADC_SUCCESS,     // Success.
	E_ADC_INVINIT,	 	// Initial fail or resource is unavailable.
	E_ADC_INVPARA,	 	// Invalid function parameter/argument.
    E_ADC_ERROR,     	// Unspecific error.
} enum_adc_retcode_Type;

/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH0_INTST_MORE_THAN_1 			(0x1U << 0)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH0_INTST_ABOVE_WATERMARK		(0x1U << 1)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH0_INTST_FIFO_FULL				(0x1U << 2)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH0_INTST_FIFO_OVERFLOW			(0x1U << 3)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH1_INTST_MORE_THAN_1 			(0x1U << 4)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH1_INTST_ABOVE_WATERMARK 		(0x1U << 5)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH1_INTST_FIFO_FULL				(0x1U << 6)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH1_INTST_FIFO_OVERFLOW			(0x1U << 7)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH2_INTST_MORE_THAN_1 			(0x1U << 8)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH2_INTST_ABOVE_WATERMARK 		(0x1U << 9)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH2_INTST_FIFO_FULL				(0x1U << 10)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH2_INTST_FIFO_OVERFLOW			(0x1U << 11)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH3_INTST_MORE_THAN_1 			(0x1U << 12)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH3_INTST_ABOVE_WATERMARK 		(0x1U << 13)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH3_INTST_FIFO_FULL				(0x1U << 14)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CH3_INTST_FIFO_OVERFLOW			(0x1U << 15)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CORE_INTST_MORE_THAN_1 			(0x1U << 16)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CORE_INTST_ABOVE_WATERMARK 		(0x1U << 17)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CORE_INTST_FIFO_FULL			(0x1U << 18)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_CORE_INTST_FIFO_OVERFLOW		(0x1U << 19)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_BATTERY_INTST_MORE_THAN_1 		(0x1U << 20)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_BATTERY_INTST_ABOVE_WATERMARK 	(0x1U << 21)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_BATTERY_INTST_FIFO_FULL			(0x1U << 22)
/** @brief Interrupt status: return value of upt_adc_get_status() */
#define ADC_BATTERY_INTST_FIFO_OVERFLOW		(0x1U << 23)

#define ADC_VREF_MV 1200
#define ADC_BAT_VREF_MV 4800
#define ADC_VOLTAGE_BIT_MASK 0x0FFF
#define ADC_RESOLUTION_MAX 4096

/**
 * @brief Handle for a ADC engine
 */
typedef struct metal_adc {
    const struct metal_adc_vtable *vtable;
} metal_adc_Type;

struct metal_adc_vtable {
	enum_adc_retcode_Type (*init)(
    		metal_adc_Type *adc,
			uint32_t *actual_sample_rate,
			enum_adc_num_Type adc_num,
			enum_adc_mode_Type adc_ch,
			enum_adc_intmode_Type adc_intmode,
			enum_adc_watermark_Type watermark,
			uint32_t adc_clock_rate,
			uint32_t target_sample_rate);
    uint32_t (*get_raw_stat)(
    		metal_adc_Type *adc,
			 enum_adc_num_Type adc_num);
    enum_adc_intmode_Type (*get_raw_stat_channel)(
    		metal_adc_Type *adc,
			enum_adc_num_Type adc_num,
			enum_adc_mode_Type adc_ch);
    enum_adc_intmode_Type (*get_int_stat_channel)(
    		metal_adc_Type *adc,
			enum_adc_num_Type adc_num,
			enum_adc_mode_Type adc_ch);
    enum_adc_retcode_Type (*clear_int_stat_all)(
    		metal_adc_Type *adc,
			enum_adc_num_Type adc_num);
    enum_adc_retcode_Type (*clear_int_stat_channel)(
    		metal_adc_Type *adc,
			enum_adc_num_Type adc_num,
			enum_adc_mode_Type adc_ch);
    enum_adc_retcode_Type (*dma_en)(
    		metal_adc_Type *adc,
			enum_adc_num_Type adc_num,
			bool enable);
    enum_adc_retcode_Type (*dma_burst)(
			metal_adc_Type *adc,
			enum_adc_num_Type adc_num,
			bool burst);
    uint32_t (*is_active)(
    		metal_adc_Type *adc,
			enum_adc_num_Type adc_num);
    uint32_t (*read_fifo)(
    		metal_adc_Type *adc,
			enum_adc_num_Type adc_num,
			enum_adc_mode_Type adc_ch);
	uint32_t (*read_voltage)(
    		metal_adc_Type *adc,
			enum_adc_num_Type adc_num,
			enum_adc_mode_Type adc_ch);
    enum_adc_retcode_Type (*enable)(
    		metal_adc_Type *adc,
			enum_adc_num_Type adc_num,
			enum_adc_mode_Type adc_ch,
			bool enable);
    enum_adc_retcode_Type (*isr_enable)(
    		metal_adc_Type *adc,
			enum_adc_num_Type adc_num,
			enum_adc_mode_Type adc_ch,
			enum_adc_intdes_Type enable,
			uint32_t enable_evt);
    enum_adc_retcode_Type (*set_watermark)(
			metal_adc_Type *adc,
			enum_adc_num_Type adc_num,
			enum_adc_watermark_Type adc_watermark);
};

/**
 * @brief Get a handle for a ADC
 * @param[in] device_num Device_num The index of the desired ADC engine
 * @return A handle to the ADC, or NULL if the engine does not exist
 */
metal_adc_Type *upt_adc_get_device(enum_adc_device_Type device_num);

/**
 * @brief Initialize ADC Hardware.
 * @param[in] adc The ADC handle.
 * @param[out] actual_sample_rate Get the sample rate to be sampled.
 * @param[in] adc_num ADC number.
 * @param[in] adc_ch Channel to be select.
 * @param[in] target_sample_rate Set the sample rate to be sampled
 * @return enum_adc_retcode_Type value.
 */
__inline__ enum_adc_retcode_Type upt_adc_init(
		metal_adc_Type *adc,
		uint32_t *actual_sample_rate,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_ch,
		uint32_t target_sample_rate) {
    return adc->vtable->init(
			adc,
			actual_sample_rate,
			adc_num,
			adc_ch,
			(enum_adc_intmode_Type)(adc_intmode_more_than_1 |adc_intmode_above_watermark | adc_intmode_fifo_full | adc_intmode_fifo_overflow),
			adc_watermark_8,
			11059200,
			target_sample_rate);
}

/**
 * @brief Enable/Disable ADC.
 * @param[in] adc The ADC handle.
 * @param[in] adc_num ADC number.
 * @param[in] adc_ch Channel to be select.
 * @param[in] enable Enable/disable ADC.
 * @return enum_adc_retcode_Type value.
 */
__inline__ enum_adc_retcode_Type upt_adc_enable(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_ch,
		bool enable) {
	return adc->vtable->enable(
			adc,
			adc_num,
			adc_ch,
			enable);
}

/**
 * @brief Enable/Disable ADC interrupt.
 * @param[in] adc The ADC handle.
 * @param[in] adc_num ADC number.
 * @param[in] adc_ch Channel to be select.
 * @param[in] enable Enable/disable ADC ISR.
 * @param[in] enable_evt isr event trigger of ADC
 * @return enum_adc_retcode_Type value.
 */
__inline__ enum_adc_retcode_Type upt_adc_isr_enable(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_ch,
		enum_adc_intdes_Type enable,
		uint32_t enable_evt) {

	int shift_bit = 8;
	//TODO: To Enable E34 ADC interrupt, use SCU function call instead
	*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) &= ~(0x3FF << shift_bit);
	(adc_num == adc0)? (shift_bit = 8) : (shift_bit = 14);
	if (enable & adc_int_e34) {
		if (adc_ch == adc_0to3loop) {
			enable_evt = (enable_evt | (enable_evt << 4) | (enable_evt << 8) | (enable_evt << 12));
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) |=~(0xF << shift_bit);
		}
		else {
			*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) |= (0x1 << (shift_bit + adc_ch));
			enable_evt = (enable_evt << (adc_ch*4));
		}
	}
	return adc->vtable->isr_enable(
			adc,
			adc_num,
			adc_ch,
			enable,
			enable_evt);
}

/**
 * @brief Enable/Disable ADC DMA control.
 * @param[in] adc The ADC handle.
 * @param[in] adc_num ADC number.
 * @param[in] enable Enable/Disable ADC DMA control.
 * @return enum_adc_retcode_Type value.
 */
__inline__ enum_adc_retcode_Type upt_adc_dma_en(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		bool enable) {
	enum_adc_retcode_Type ret = E_ADC_SUCCESS;

	ret = adc->vtable->dma_en(
			adc,
			adc_num,
			enable);
	if (ret != E_ADC_SUCCESS) return ret;

	return adc->vtable->dma_burst(
			adc,
			adc_num,
			1);
}

/**
 * @brief Set DMA watermark of ADC.
 * @param[in] adc The ADC handle.
 * @param[in] adc_num ADC number.
 * @param[in] watermark Threshold of DMA request.
 * @return enum_adc_retcode_Type value.
 */
__inline__ enum_adc_retcode_Type upt_adc_set_watermark(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_watermark_Type watermark) {
	return adc->vtable->set_watermark(
			adc,
			adc_num,
			watermark);
}

/**
 * @brief Get all status of ADC.
 * @param[in] adc The ADC handle.
 * @param[in] adc_num ADC number.
 * @return Status of ADC.
 */
__inline__ uint32_t upt_adc_get_status(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num) {
	return adc->vtable->get_raw_stat(
			adc,
			adc_num);
}

/**
 * @brief Clear all status of ADC.
 * @param[in] adc The ADC handle.
 * @param[in] adc_num ADC number.
 * @return enum_adc_retcode_Type value.
 */
__inline__ enum_adc_retcode_Type upt_adc_clear_status(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num) {
	return adc->vtable->clear_int_stat_all(
			adc,
			adc_num);
}

/**
 * @brief Get channel status of ADC.
 * @param[in] adc The ADC handle.
 * @param[in] adc_num ADC number.
 * @param[in] adc_ch Channel to be select.
 * @return Channel status of ADC.
 */
__inline__ enum_adc_intmode_Type upt_adc_get_status_channel(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_ch) {
	return adc->vtable->get_raw_stat_channel(
			adc,
			adc_num,
			adc_ch);
}

/**
 * @brief Clear channel status of ADC.
 * @param[in] adc The ADC handle.
 * @param[in] adc_num ADC number.
 * @param[in] adc_ch Channel to be select.
 * @return enum_adc_retcode_Type value.
 */
__inline__ enum_adc_retcode_Type upt_adc_clear_int_status_channel(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_ch) {
	return adc->vtable->clear_int_stat_channel(
			adc,
			adc_num,
			adc_ch);
}

/**
 * @brief Read data from ADC.
 * @param[in] adc The ADC handle.
 * @param[in] adc_num ADC number.
 * @param[in] adc_ch ADC Channel to be read.
 * @param[out] read_buf Read buffer.
 * @param[in] read_buf_len Read buffer length.
 * @return enum_adc_retcode_Type value.
 */
__inline__ enum_adc_retcode_Type upt_adc_read_data(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_ch,
		uint16_t *read_buf,
		uint32_t read_buf_len) {
	uint32_t read_data;
	for (uint32_t i = 0; i < ( (read_buf_len >> 1) + (read_buf_len % 2) ); i ++) {
		read_data = adc->vtable->read_fifo(adc, adc_num, adc_ch);
		read_buf[(i << 1)] = read_data & 0xFFFF;

		if ( ((i << 1) + 1) < read_buf_len )
			read_buf[(i << 2) + 1] = (read_data & 0xFFFF0000) >> 16;
	}
	return E_ADC_SUCCESS;
}
/**
 * @brief change adc data to voltage mv.
 * @param[in] adc_ch ADC Channel to be read.
 * @param[in] adc_data adc data.
 * @return voltage value.
 */
__inline__ uint32_t upt_adc_data_to_voltage_mv(
		enum_adc_mode_Type adc_ch,
		uint16_t adc_data) {
	uint32_t voltage = 0;
	if(adc_ch == adc_battery)
		voltage = (adc_data & ADC_VOLTAGE_BIT_MASK) * ADC_BAT_VREF_MV / ADC_RESOLUTION_MAX;
	else
		voltage = (adc_data & ADC_VOLTAGE_BIT_MASK) * ADC_VREF_MV / ADC_RESOLUTION_MAX;
	return voltage;
}

#endif /* METAL_ADC_H */
