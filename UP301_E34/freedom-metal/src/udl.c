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
#include "metal/udl.h"


extern __inline__ uint16_t metal_udl_conv_2d_16x16(metal_udl_Type *udl, upt_udl_config_Type *conv_2d_config);
extern __inline__ void metal_udl_reset(metal_udl_Type *udl);
extern __inline__ void metal_udl_interrupt_enable(metal_udl_Type *udl, bool enable);
extern __inline__ uint16_t metal_udl_read_pending(metal_udl_Type *udl);
extern __inline__ uint32_t metal_udl_read_stats(metal_udl_Type *udl);
extern __inline__ enum_udl_retcode_Type metal_udl_conv_2d_16x16_arm_api(const cmsis_nn_context *ctx,
                                                      const cmsis_nn_conv_params *conv_params,
                                                      const cmsis_nn_per_channel_quant_params *quant_params,
                                                      const cmsis_nn_dims *input_dims,
                                                      const int16_t *input_data,
                                                      const cmsis_nn_dims *filter_dims,
                                                      const int8_t *filter_data,
                                                      const cmsis_nn_dims *bias_dims,
                                                      const cmsis_nn_bias_data *bias_data,
                                                      const cmsis_nn_dims *output_dims,
                                                      int16_t *output_data
                                                      );
extern __inline__ enum_udl_retcode_Type metal_udl_fully_connect_arm_api (const cmsis_nn_context *ctx,
                                                      const cmsis_nn_fc_params *fc_params,
                                                      const cmsis_nn_per_tensor_quant_params *quant_params,
                                                      const cmsis_nn_dims *input_dims,
                                                      const int16_t *input_data,
                                                      const cmsis_nn_dims *filter_dims,
                                                      const int8_t *filter_data,
                                                      const cmsis_nn_dims *bias_dims,
                                                      const int64_t *bias_data,
                                                      const cmsis_nn_dims *output_dims,
                                                      int16_t *output_data 
                                                      );	
extern __inline__ enum_udl_retcode_Type metal_udl_conv_2d_16x16_upt_api(metal_udl_Type *udl,
                                                      const upt_nn_conv_params_Type *conv_params,
                                                      const upt_nn_dims_Type *input_dims,
                                                      const uint32_t *input_data,
                                                      const upt_nn_dims_Type *weight_dims,
                                                      const uint32_t *weight_data,
                                                      const uint32_t *bias_data,
                                                      const upt_nn_dims_Type *output_dims,
                                                      uint32_t *output_data
                                                      );
extern __inline__ enum_udl_retcode_Type metal_udl_fully_connect_upt_api(metal_udl_Type *udl,
                                                      const upt_nn_conv_params_Type *conv_params,
                                                      const uint32_t input_feature_nums,
                                                      const uint32_t *input_data,
                                                      const uint32_t *weight_data,
                                                      const uint32_t *bias_data,
                                                      const uint32_t output_feature_nums,
                                                      uint32_t *output_data
                                                      );
extern __inline__ enum_udl_retcode_Type metal_udl_max_pooling(metal_udl_Type *udl,
													  const upt_nn_dims_Type *input_dims,
													  const uint32_t *input_data,
													  const upt_nn_dims_Type *output_dims,
													  uint32_t *output_data,
													  const upt_nn_maxPool_params_Type *maxPool_params
													  );
extern __inline__ void metal_udl_rearrange(metal_udl_Type *udl, uint32_t *output_data, const uint16_t output_size);

metal_udl_Type *upt_udl_get_device(enum_udl_device_Type device_num) {
#if __METAL_DT_MAX_UDLS > 0
    if (device_num < __METAL_DT_MAX_UDLS) {
        return (metal_udl_Type *)__metal_udl_table[device_num];
    }
#endif

    return NULL;
}
