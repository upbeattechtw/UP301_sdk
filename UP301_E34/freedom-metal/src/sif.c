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
#include "metal/sif.h"

extern __inline__ enum_sif_retcode_Type upt_sif_write_command_queue(metal_sif_Type *sif,
																	uint32_t seq,
																	sif_ic_function_Type function,
																	sif_ic_cmd_type_Type cmd,
																	uint32_t data,
																	bool last);

extern __inline__ enum_sif_retcode_Type upt_sif_trigger(metal_sif_Type *sif, sif_ic_trigger_Type trig);

metal_sif_Type *upt_sif_get_device(enum_sif_device_Type device_num) {
#if __METAL_DT_MAX_SIFS > 0
	if (device_num > __METAL_DT_MAX_GPIOS) {
		return NULL;
	}
#endif
	return (metal_sif_Type *)__metal_sif_table[device_num];
}
