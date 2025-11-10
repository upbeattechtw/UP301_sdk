/*
 * Copyright (C) 2024 UpbeatTech Inc. All Rights Reserved
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

#ifndef PUFS_ISR_H
#define PUFS_ISR_H

#include "pufs_dma_internal.h"
#include "pufs_internal.h"
#include "pufs_pal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration for PUFS module operating state.
 *
 * Represents whether the PUFS module is currently idle or busy.
 */
typedef enum {
    IDLE,  /**< Module is idle and ready for operation. */
    BUSY,  /**< Module is currently processing a task. */
} pufs_module_state_Type;

/**
 * @brief Structure representing the ISR post-process of the PUFS module.
 *
 * Contains both the current module state and the status check result.
 */
typedef struct {
    pufs_module_state_Type state;  /**< Current operating state of the module. */
    pufs_status_Type check;        /**< Status check ISR post-process result. */
} pufs_isr_status_Type;

extern pufs_isr_status_Type isrStatus;

/**
 * @brief Retrieve the current PUFS ISR status.
 *
 * @return The current ISR status as a pufs_isr_status_Type structure.
 */
pufs_isr_status_Type pufs_check_isr_status(void);


/**
 * @brief Reset the PUFS ISR status to its default values.
 *
 * Sets the ISR status state to IDLE and the check result to SUCCESS.
 */
void pufs_reset_isr_status(void);

#ifdef __cplusplus
}
#endif

#endif /* PUFS_ISR_H */
