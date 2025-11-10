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

#include "mbedtls/sha256.h"

#ifdef MBEDTLS_SHA256_ALT
#include "mbedtls/error.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static pufs_status_Type __check;

void mbedtls_sha256_init(mbedtls_sha256_context *ctx) {
    __check = SUCCESS;
    *ctx = pufs_hash_ctx_new();
}

int mbedtls_sha256_starts(mbedtls_sha256_context *ctx, int is224) {
    if (is224) {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    __check = pufs_hash_init(*ctx, SHA_256);
    if (__check != SUCCESS) {
        return -1;
    }

    return 0;
}

int mbedtls_sha256_update(mbedtls_sha256_context *ctx,
                          const unsigned char *input,
                          size_t ilen) {
    // The PUFs hardware engine supports a maximum temporary buffer size of 128 bytes.
    for (uint32_t off = 0; off < ilen; off += HMAC_BLOCK_MAXLEN) {
        uint32_t chunk = MIN(HMAC_BLOCK_MAXLEN, (ilen - off));
        __check = pufs_hash_update(*ctx, (input + off), chunk);

        if (__check != SUCCESS) {
            return -1;
        }
    }

    return 0;
}

int mbedtls_sha256_finish(mbedtls_sha256_context *ctx,
                          unsigned char *output) {
    pufs_dgst_st_Type md;

    __check = pufs_hash_final(*ctx, &md);
    if (__check != SUCCESS) {
        return -1;
    }
    
    memcpy(output, md.dgst, md.dlen);

    return 0;
}

void mbedtls_sha256_free(mbedtls_sha256_context *ctx) {
    pufs_hash_ctx_free(*ctx);
}

#endif /* MBEDTLS_SHA256_ALT */
