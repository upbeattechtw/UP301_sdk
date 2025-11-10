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

/*!
 * @file tty.h
 * @brief API for emulated serial terminals
 */
#ifndef METAL__TTY_H
#define METAL__TTY_H

/*!
 * @brief Write a character to the default output device
 *
 * Write a character to the default output device, which for most
 * targets is the UART serial port.
 *
 * @param c The character to write to the terminal
 * @return 0 on success, or -1 on failure.
 */
int metal_tty_putc(int c);

/*!
 * @brief Get a byte from the default output device
 *
 * The default output device, is typically the UART serial port.
 *
 * This call is non-blocking, if nothing is ready c==-1
 * if something is ready, then c=[0x00 to 0xff] byte value.
 *
 * @return 0 on success, or -1 on failure.
 */
int metal_tty_getc(int *c);

#endif
