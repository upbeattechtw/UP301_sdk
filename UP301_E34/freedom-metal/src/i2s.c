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
#include "metal/i2s.h"

extern __inline__ enum_i2s_retcode_Type upt_i2s_config(struct metal_i2s *i2s,
                                      enum_i2s_mode_Type mode,
									  enum_i2s_format_Type param_format,
									  enum_i2s_chan_nr_Type param_chan_nr,
									  enum_i2s_stream_Type stream);

extern __inline__ enum_i2s_retcode_Type upt_i2s_tdm_config(struct metal_i2s *i2s,
                                          enum_i2s_mode_Type mode,
										  enum_i2s_format_Type param_format,
										  enum_i2s_tdm_chan_nr_Type param_slot_nr,
										  enum_i2s_tdm_frame_offset_Type param_frame_offset,
										  enum_i2s_stream_Type stream);

extern __inline__ enum_i2s_retcode_Type upt_i2s_enable(struct metal_i2s *i2s,
									  bool enable);

extern __inline__ enum_i2s_retcode_Type upt_i2s_isr_enable(struct metal_i2s *i2s,
										  bool enable);

extern __inline__ enum_i2s_retcode_Type upt_i2s_dma_enable(struct metal_i2s *i2s,
										  bool enable);

extern __inline__ enum_i2s_retcode_Type upt_i2s_set_watermark(struct metal_i2s *i2s,
									  	  	 enum_i2s_watermark_Type watermark);

extern __inline__ uint32_t upt_i2s_get_status(struct metal_i2s *i2s);

extern __inline__ enum_i2s_retcode_Type upt_i2s_clear_status(struct metal_i2s *i2s);

extern __inline__ enum_i2s_retcode_Type upt_i2s_tx(struct metal_i2s *i2s,
								  uint32_t *l_ch,
								  int32_t l_len,
								  uint32_t *r_ch,
								  int32_t r_len);

extern __inline__ enum_i2s_retcode_Type upt_i2s_rx(struct metal_i2s *i2s,
								  uint32_t *l_ch,
								  int32_t l_len,
								  uint32_t *r_ch,
								  int32_t r_len);

extern __inline__ enum_i2s_retcode_Type upt_i2s_tdm_tx(struct metal_i2s *i2s,
									  int32_t slot_num,
									  uint32_t *data,
									  int32_t data_len);

extern __inline__ enum_i2s_retcode_Type upt_i2s_tdm_rx(struct metal_i2s *i2s,
									  int32_t slot_num,
									  uint32_t *data,
									  int32_t data_len);

struct metal_i2s *upt_i2s_get_device(uint32_t device_num) {
#if __METAL_DT_MAX_I2SS > 0
    if (device_num < __METAL_DT_MAX_I2SS) {
        return (struct metal_i2s *)__metal_i2s_table[device_num];
    }
#endif

    return NULL;
}
