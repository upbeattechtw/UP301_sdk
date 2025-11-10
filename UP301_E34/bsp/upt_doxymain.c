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

/*
*   File with no code
*   Serve as the place holder for the Doxygen main page
*/

/**
 * @mainpage Introduction to UP301 Power Mode APIs
 * @tableofcontents
 * @startuml "State Transition from HW View" width=8cm
 *  state "Full Chip Active Mode" as FullChipActiveMode{
 *          state Ax {
 *          }
 *          state AxSC {
 *                  AxSC: Stop clock
 *          }
 *  }
 *
 *  state "AON mode" as AONMode {
 *          state Sx {
 *          }
 *          state L0 {
 *          }
 *  }
 *
 *  state "RTC-only mode" as RTCOnlyMode {
 *          state R0 {
 *          }
 *  }
 *
 *  [*] --> Ax: Power on or any bootup event/reset
 *  Ax --> AxSC: E34 set ENTER_STOP_CLOCK
 *  AxSC --> Ax: RESUME_CLK_INT_STAT occurs
 *  Ax --> Sx: E34 set ENTER_SLEEP\n(Power-off Non-AON domain)
 *  Sx --> Ax: E21 set LEAVE_SLEEP\n(Power-on Non-AON domain)
 *  Sx --> L0: E21 set ENTER_LURKING
 *  L0 --> Sx: E21 set LEAVE_LURKING
 *  Ax --> R0: E34 set ENTER_RTCM\n(Power-off AON, Non-AON, SRAM domain)
 *  R0 --> Ax: RTC/TICK/RTCM_GPIO/_INT_STAT occurs\n(Power-on AON, Non-AON, SRAM domain)
 * @enduml
 *
 * @section AX_TO_AXSC_TO_AX_SECTION Ax to AxSC to Ax
 *  Refer to @ref AX_TO_AXSC_TO_AX_GROUP for details
 * - Ax \f$\rightarrow\f$ AxSC: call @ref upt_power_Ax_AxSc_Ax in E34 to start Ax to AxSC transition.
 * - AxSC \f$\rightarrow\f$ Ax: AxSC to Ax transition is automatically triggered by @ref SCU_RESUME_CLK_INT_STAT events.
 *
 * @section AX_TO_SX_TO_AX_SECTION Ax to Sx to Ax
 *  Refer to @ref AX_TO_SX_TO_AX_GROUP for details
 * - Ax \f$\rightarrow\f$ Sx: call @ref upt_power_Ax_to_Sx in E34 to start Ax to Sx transition.
 * - Sx \f$\rightarrow\f$ Ax: wait for E21 set @ref SCU_LEAVE_LURKING bit to start Sx to Ax transition.
 *
 * @section AX_TO_R0_TO_AX_SECTION Ax to R0 to Ax
 *  Refer to @ref AX_TO_R0_TO_AX_GROUP for details
 * - Ax \f$\rightarrow\f$ R0: call @ref upt_power_Ax_to_R0 in E34 to start Ax to R0 transition.
 * - R0 \f$\rightarrow\f$ Ax: R0 to Ax transition is automatically triggered by @ref SCU_RTC_INT_STAT and @ref SCU_RTCM_GPIO_INT_STAT events.
 *
*/
