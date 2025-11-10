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
#include "metal/img.h"


extern __inline__ enum_img_retcode_Type upt_img_enable(metal_img_Type *img, bool enable);

extern __inline__ enum_img_retcode_Type upt_img_init(metal_img_Type *img, upt_img_config_Type *config);
                                          
extern __inline__ uint32_t upt_img_check_status(metal_img_Type *img, enum_img_int_flags_Type check);

extern __inline__ uint32_t upt_img_get_status(metal_img_Type *img);

extern __inline__ void upt_img_clear_status(metal_img_Type *img);

extern __inline__ enum_img_retcode_Type upt_img_isr_enable(metal_img_Type *img, uint32_t enable_evt);

metal_img_Type *upt_img_get_device(enum_img_device_Type device_num) {
#if __METAL_DT_MAX_IMGS > 0
    if (device_num < __METAL_DT_MAX_IMGS) {
        return (metal_img_Type *)__metal_img_table[device_num];
    }
#endif

    return NULL;
}