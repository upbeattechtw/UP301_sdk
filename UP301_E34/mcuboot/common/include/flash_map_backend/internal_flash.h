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

#include "metal/upt_sysctrl.h"

void fospi_4kerase(size_t start_addr);
SRAM_ATTR void fospi_write(size_t dest_addr, const void *src, size_t size);
SRAM_ATTR void fospi_read(void * dest_addr, const size_t src, size_t size);
void speedup_flash();
int mcuboot_update_shared_data(Boot_shared_field_Type field, void *data);
