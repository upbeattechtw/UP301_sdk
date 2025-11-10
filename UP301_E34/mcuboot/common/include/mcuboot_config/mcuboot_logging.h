/*
 * Copyright (c) 2018 Open Source Foundries Limited
 * Copyright (c) 2019 Arm Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __LOGGING_H__
#define __LOGGING_H__

#pragma once

#include <stdio.h>

#define MCUBOOT_LOG_MODULE_DECLARE(...)

#ifdef BOOTLOADER
  #define MCUBOOT_LOG_ERR(_fmt, ...) \
    printf("[ERR] " _fmt "\n", ##__VA_ARGS__);
  #define MCUBOOT_LOG_WRN(_fmt, ...) \
    printf("[WRN] " _fmt "\n", ##__VA_ARGS__);
  #define MCUBOOT_LOG_INF(_fmt, ...) \
    printf("[INF] " _fmt "\n", ##__VA_ARGS__);
  #define MCUBOOT_LOG_DBG(_fmt, ...) \
    printf("[DBG] " _fmt "\n", ##__VA_ARGS__);
#else // Don't print if it's not a Bootloader code.
    #define MCUBOOT_LOG_ERR(_fmt, ...)
    #define MCUBOOT_LOG_WRN(_fmt, ...)
    #define MCUBOOT_LOG_INF(_fmt, ...)
    #define MCUBOOT_LOG_DBG(_fmt, ...)
#endif

#endif /* __LOGGING_H__ */
