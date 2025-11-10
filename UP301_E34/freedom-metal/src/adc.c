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

#include "metal.h"
#include "metal/adc.h"

extern __inline__ enum_adc_retcode_Type upt_adc_init(
		metal_adc_Type *adc,
		uint32_t *actual_sample_rate,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_ch,
		uint32_t target_sample_rate);

extern __inline__ enum_adc_retcode_Type  upt_adc_enable(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_mode,
		bool enable);

extern __inline__ enum_adc_retcode_Type  upt_adc_isr_enable(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_ch,
		enum_adc_intdes_Type enable,
		uint32_t enable_evt);

extern __inline__ enum_adc_retcode_Type upt_adc_dma_en(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		bool enable);

extern __inline__ enum_adc_retcode_Type upt_adc_set_watermark(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_watermark_Type watermark);

extern __inline__ uint32_t upt_adc_get_status(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num);

extern __inline__ enum_adc_retcode_Type upt_adc_clear_status(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num);

extern __inline__ enum_adc_intmode_Type upt_adc_get_status_channel(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_ch);

extern __inline__ enum_adc_retcode_Type upt_adc_clear_int_status_channel(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_ch);

extern __inline__ enum_adc_retcode_Type upt_adc_read_data(
		metal_adc_Type *adc,
		enum_adc_num_Type adc_num,
		enum_adc_mode_Type adc_ch,
		uint16_t *read_buf,
		uint32_t read_buf_len);

extern __inline__ uint32_t upt_adc_data_to_voltage_mv(
		enum_adc_mode_Type adc_ch,
		uint16_t read_data);


metal_adc_Type *upt_adc_get_device(enum_adc_device_Type device_num) {
#if __METAL_DT_MAX_ADCS > 0
    if (device_num > __METAL_DT_MAX_ADCS) {
    	return NULL;
    }
#endif
	return (struct metal_adc *)__metal_adc_table[device_num];
}
