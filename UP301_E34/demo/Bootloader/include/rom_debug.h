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

#ifndef ROM_DEBUG_H_
#define ROM_DEBUG_H_

#ifdef UP_DEBUG
#define UP_LOG_LEVEL_TRACE   5
#define UP_LOG_LEVEL_INFO    4
#define UP_LOG_LEVEL_WARN    3
#define UP_LOG_LEVEL_ERROR   2
#define UP_LOG_LEVEL_NO	  1

#if UP_LOG_LEVEL >= UP_LOG_LEVEL_TRACE
#define UP_DEBUG_TRACE(format, args...) printf("DEBUG_TRACE:\t"format, ##args)
#else
#define UP_DEBUG_TRACE(args...)
#endif

#if UP_LOG_LEVEL >= UP_LOG_LEVEL_INFO
#define UP_DEBUG_INFO(format, args...) printf("DEBUG_INFO:\t"format, ##args)
#else
#define UP_DEBUG_INFO(args...)
#endif

#if UP_LOG_LEVEL >= UP_LOG_LEVEL_WARN
#define UP_DEBUG_WARN(format, args...) printf("DEBUG_WARN:\t"format, ##args)
#else
#define UP_DEBUG_WARN(args...)
#endif

#if UP_LOG_LEVEL >= UP_LOG_LEVEL_ERROR
#define UP_DEBUG_ERROR(format, args...) printf("DEBUG_ERROR:\t"format, ##args)
#else
#define UP_DEBUG_ERROR(args...)
#endif

#else
#define UP_DEBUG_TRACE(args...)
#define UP_DEBUG_INFO(args...)
#define UP_DEBUG_WARN(args...)
#define UP_DEBUG_ERROR(args...)
#endif

#define UPTB_INFO
#define UPTB_DEBUG			2
#define UPTB_LOG

#ifdef UPTB_INFO
#define uptb_Info(...)      up_Info(__VA_ARGS__)
#else
#define uptb_Info(...)
#endif

//#define up_Info(...)      metal_uart_pprintf(DEBUG_PORT, __VA_ARGS__ )
#define up_Info(...)      printf( __VA_ARGS__ )

#endif /* ROM_DEBUG_H_ */
