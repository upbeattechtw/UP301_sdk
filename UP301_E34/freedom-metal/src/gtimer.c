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
#include "metal/gtimer.h"

extern __inline__ enum_gtimer_retcode_Type upt_gtimer_init(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, uint32_t tmrld);

extern __inline__ enum_gtimer_retcode_Type upt_gtimer_init_ms(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, uint32_t ms);

extern __inline__ enum_gtimer_retcode_Type upt_gtimer_enable(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, bool enable);

extern __inline__ enum_gtimer_retcode_Type upt_gtimer_isr_enable(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst, enum_gtimer_intdes_Type enable);

extern __inline__ uint32_t upt_gtimer_get_status(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst);

extern __inline__ enum_gtimer_retcode_Type upt_gtimer_clear_status(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst);

extern __inline__ uint32_t upt_gtimer_receipt_status(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst);

extern __inline__ uint32_t upt_gtimer_get_count(metal_gtimer_Type *gtimer, enum_gtimer_inst_Type chInst);

metal_gtimer_Type *upt_gtimer_get_device(enum_gtimer_device_Type device_num) {
#if __METAL_DT_MAX_GTIMERS > 0
    if (device_num < __METAL_DT_MAX_GTIMERS) {
        return (metal_gtimer_Type *)__metal_gtimer_table[device_num];
    }
#endif
    return NULL;
}
