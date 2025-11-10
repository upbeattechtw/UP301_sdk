/* Copyright 2024 Upbeat, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include "metal.h"
#include "metal/dma.h"

extern __inline__ enum_dma_retcode_Type upt_dma_config(metal_dma_Type *dma, enum_dma_channel_Type channel, DMA_LLI_Type *lli_ptr, int32_t lli_len, DMA_CONFIG_INFO_Type *dma_config);

extern __inline__ enum_dma_retcode_Type upt_dma_enable(metal_dma_Type *dma, bool enable);

extern __inline__ enum_dma_retcode_Type upt_dma_enable_channel(metal_dma_Type *dma, enum_dma_channel_Type channel, bool enable);

extern __inline__ enum_dma_retcode_Type upt_dma_isr_enable(metal_dma_Type *dma, enum_dma_channel_Type channel, bool enable);

extern __inline__ uint32_t upt_dma_get_status(metal_dma_Type *dma, enum_dma_channel_Type channel, enum_dma_stauts_Type status_category);

extern __inline__ enum_dma_retcode_Type upt_dma_clear_status(metal_dma_Type *dma, enum_dma_channel_Type channel, enum_dma_stauts_Type status_category);

extern __inline__ int32_t upt_dma_is_complete(metal_dma_Type *dma, enum_dma_channel_Type channel);

extern __inline__ enum_dma_retcode_Type upt_dma_reload(metal_dma_Type *dma, uint32_t channel, uint32_t src_addr, uint32_t dst_addr, uint32_t size);

extern __inline__ enum_dma_retcode_Type upt_dma_suspend(metal_dma_Type *dma, uint32_t channel);

extern __inline__ enum_dma_retcode_Type upt_dma_resume(metal_dma_Type *dma, uint32_t channel);

metal_dma_Type *upt_dma_get_device(uint32_t device_num) {
#if __METAL_DT_MAX_DMAS > 0
    if (device_num < __METAL_DT_MAX_DMAS) {
        return (metal_dma_Type *)__metal_dma_table[device_num];
    }
#endif

    return NULL;
}
