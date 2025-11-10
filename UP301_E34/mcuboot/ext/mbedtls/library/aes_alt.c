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

#include "mbedtls/aes.h"

#ifdef MBEDTLS_AES_ALT
#include <string.h>

void mbedtls_aes_init(mbedtls_aes_context *ctx) {
    // Initialization of the AES context is handled within `pufs_enc_ctr()`.
}

int mbedtls_aes_setkey_enc(mbedtls_aes_context *ctx, const unsigned char *key, unsigned int keybits) {
    memcpy(ctx->key, key, (keybits / 8));
    ctx->keybits = keybits;

    return 0;
}

int mbedtls_aes_crypt_ctr(mbedtls_aes_context *ctx,
                          size_t length,
                          size_t *nc_off,
                          unsigned char nonce_counter[16],
                          unsigned char stream_block[16],
                          const unsigned char *input,
                          unsigned char *output) {
    UNUSED(nc_off);
    UNUSED(stream_block);

    pufs_status_Type check;
    uint32_t outlen;

    check = pufs_enc_ctr(output, &outlen, input, length, AES, SWKEY, ctx->key, ctx->keybits, nonce_counter, 128);
    if (check != SUCCESS) {
        return -1;
    }

    return 0;
}

void mbedtls_aes_free(mbedtls_aes_context *ctx) {
    // Cleanup of the AES context is handled within `pufs_enc_ctr()`.
}
    
#endif /* MBEDTLS_AES_ALT */
