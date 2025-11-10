/*
 * Copyright (C) 2025 UpbeatTech Inc. All Rights Reserved
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This file contains code derived from software originally developed by SiFive, Inc.
 * Copyright 2018 SiFive, Inc
 * SPDX-License-Identifier: Apache-2.0
 *
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

#include <metal.h>
#include <metal/spi.h>

extern __inline__ enum_spi_retcode_Type  upt_spi_init(metal_spi_Type *spi, enum_spi_type_Type type, enum_spi_mode_Type mode, enum_spi_speed_Type speed_mode);

extern __inline__ enum_spi_retcode_Type  upt_spi_set_mode(metal_spi_Type *spi, enum_spi_mode_Type mode);

extern __inline__ enum_spi_retcode_Type upt_spi_transfer(metal_spi_Type *spi, uint8_t *txbuf, int16_t txlen, uint8_t *rxbuf, int16_t rxlen, int16_t slave_num);

extern __inline__ enum_spi_retcode_Type upt_spi_configure(metal_spi_Type *spi, int16_t slave_num, Tmode_Type mode);

extern __inline__ enum_spi_retcode_Type upt_spi_isr_enable(metal_spi_Type *spi, uint32_t enable_evt);

extern __inline__ enum_spi_retcode_Type upt_spi_dma_enable(metal_spi_Type *spi, enum_spi_dma_mode_Type mode);

extern __inline__ enum_spi_retcode_Type upt_spi_set_watermark(metal_spi_Type *spi, enum_spi_watermark_Type watermark);

extern __inline__ uint32_t upt_spi_get_status(metal_spi_Type *spi);

extern __inline__ uint32_t upt_spi_get_status_register(metal_spi_Type *spi);

extern __inline__ uint32_t upt_spi_clear_status(metal_spi_Type *spi);

extern __inline__ enum_spi_retcode_Type upt_spi_read_data(metal_spi_Type *spi, uint8_t *read_buf, int16_t read_buf_len);

extern __inline__ enum_spi_retcode_Type upt_spi_send_data(metal_spi_Type *spi, uint8_t *send_buf, int16_t send_buf_len);

extern __inline__ enum_spi_retcode_Type upt_spi_send_dummy(metal_spi_Type *spi, int16_t send_buf_len);

extern __inline__ enum_spi_retcode_Type upt_spi_enable(metal_spi_Type *spi, enum_spi_act_Type mode);

extern __inline__ enum_spi_retcode_Type upt_spi_set_timeout_us(metal_spi_Type *i2c, uint64_t timeout_us); 

extern __inline__ uint64_t upt_spi_get_timeout_us(metal_spi_Type *i2c); 

metal_spi_Type *upt_spi_get_device(uint16_t device_num) {
#if __METAL_DT_MAX_SPIS > 0
    if (device_num < __METAL_DT_MAX_SPIS) {
        return (metal_spi_Type *)__metal_spi_table[device_num];
    }
#endif

    return NULL;
}
