/* Copyright 2024 Upbeat, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <metal.h>
#include <metal/pdm.h>

extern __inline__ enum_pdm_retcode_Type upt_pdm_config(struct metal_pdm *pdm, struct metal_pdm_config *pdm_config);

extern __inline__ enum_pdm_retcode_Type upt_pdm_enable(struct metal_pdm *pdm, bool enable);

extern __inline__ enum_pdm_retcode_Type upt_pdm_isr_enable(struct metal_pdm *pdm, bool enable);

extern __inline__ enum_pdm_retcode_Type upt_pdm_dma_enable(struct metal_pdm *pdm, bool enable);

extern __inline__ void upt_pdm_set_watermark(struct metal_pdm *pdm, enum_pdm_watermark_Type watermark);

extern __inline__ uint32_t upt_pdm_get_status(struct metal_pdm *pdm);

extern __inline__ enum_pdm_retcode_Type upt_pdm_clear_status(struct metal_pdm *pdm);

extern __inline__ uint32_t upt_pdm_check_status(struct metal_pdm *pdm, enum_pdm_int_flags_Type check);

extern __inline__ enum_pdm_retcode_Type upt_pdm_clear_check_status(struct metal_pdm *pdm, enum_pdm_int_flags_Type check);

extern __inline__ void upt_pdm_read_data(struct metal_pdm *pdm, uint32_t *read_buf, int32_t read_buf_len);

extern __inline__ enum_pdm_retcode_Type upt_pdm_set_dma_adr(struct metal_pdm *pdm, uint32_t dma_number, uint32_t adr);

struct metal_pdm *upt_pdm_get_device(uint32_t device_num) {
#if __METAL_DT_MAX_PDMS > 0
    if (device_num < __METAL_DT_MAX_PDMS) {
        return (struct metal_pdm *)__metal_pdm_table[device_num];
    }
#endif

    return NULL;
}
