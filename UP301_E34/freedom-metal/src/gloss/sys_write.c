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

#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include "metal/tty.h"

/* Write to a file.  */
ssize_t _write(int file, const void *ptr, size_t len) {
    if (file != STDOUT_FILENO) {
        errno = ENOSYS;
        return -1;
    }

    const char *bptr = ptr;
    for (size_t i = 0; i < len; ++i)
        metal_tty_putc(bptr[i]);
    return 0;
}

extern __typeof(_write) write
    __attribute__((__weak__, __weak__, __alias__("_write")));
