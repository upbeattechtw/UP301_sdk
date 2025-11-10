/**
 * \file sha256_alt.h
 *
 * \brief This file contains alternative SHA-256 definitions and functions.
 *
 * The Secure Hash Algorithms 256 (SHA-256) cryptographic
 * hash functions are defined in <em>FIPS 180-4: Secure Hash Standard (SHS)</em>.
 */
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

#ifndef MBEDTLS_SHA256_ALT_H
#define MBEDTLS_SHA256_ALT_H

#ifdef MBEDTLS_SHA256_ALT
#include "pufs_hmac.h"

/* 
 * Use PUFs hardware context pointer type.
 * Normally `mbedtls_sha256_context` is a struct, but PUFs API requires
 * a `pufs_hash_ctx_Type*` allocated by the driver.
 * Only safe if using `MBEDTLS_SHA256_ALT` for all hash operations.
 */
#define mbedtls_sha256_context pufs_hash_ctx_Type*

#endif /* MBEDTLS_SHA256_ALT */
#endif /* MBEDTLS_SHA256_ALT_H */
