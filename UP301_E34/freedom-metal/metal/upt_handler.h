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

/**
 * @file  adc.h
 * @brief API for UPT controller unit logic-1
 */
#ifndef UPT_HANDLER_H
#define UPT_HANDLER_H

/**
 * @brief Power mode Sx->Ax.
 * @ingroup AX_TO_SX_TO_AX_GROUP
 * @remarks no return value
 */
void _upt_warmboot(void);

/**
 * @brief Power mode Ax->Sx.
 * @ingroup AX_TO_SX_TO_AX_GROUP
 * @remarks no return value
 */
void _upt_enter_sleep(void);

#endif /* UPT_HANDLER_H */
