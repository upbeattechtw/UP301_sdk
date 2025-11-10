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

#include "mbedtls/ecdsa.h"

#ifdef MBEDTLS_ECDSA_VERIFY_ALT
#include "pufs_common.h"
#include "pufs_ecp.h"

int mbedtls_ecdsa_verify(mbedtls_ecp_group *grp,
                         const unsigned char *buf, size_t blen,
                         const mbedtls_ecp_point *Q,
                         const mbedtls_mpi *r,
                         const mbedtls_mpi *s) {
    pufs_status_Type check = SUCCESS;
    pufs_dgst_st_Type md;
    pufs_ec_point_st_Type puk;
    pufs_ecdsa_sig_st_Type sig;

    // Check for null pointers to prevent invalid memory access.
    if (grp == NULL || buf == NULL || Q == NULL || r == NULL || s == NULL) {
        return MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
    }

    // Set the elliptic curve in the PUFs API according to the group ID.
    switch (grp->id) {
        case MBEDTLS_ECP_DP_SECP256R1:
            check = pufs_ecp_set_curve_byname(NISTP256);
            break;

        default:
            return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }
    // If PUFs curve setup fails, return error.
    if (check != SUCCESS) {
        return MBEDTLS_ERR_ECP_VERIFY_FAILED;
    }
    
    // Limit the length of the message digest to 64 bytes.
    if (blen > 64) {
        blen = 64;
    }
    
    // Copy the message digest into hardware digest structure.
    md.dlen = blen;
    memcpy(md.dgst, buf, md.dlen);
    
    // Export public key coordinates X and Y to 32-byte arrays for PUFs format.
    if (mbedtls_mpi_write_binary(&Q->private_X, puk.x, 32) != 0 ||
        mbedtls_mpi_write_binary(&Q->private_Y, puk.y, 32) != 0) {
        return MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL;
    }
    puk.qlen = 32;
    
    // Export ECDSA signature components r and s to 32-byte arrays.
    if (mbedtls_mpi_write_binary(r, sig.r, 32) != 0 ||
    mbedtls_mpi_write_binary(s, sig.s, 32) != 0) {
        return MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL;
    }
    sig.qlen = 32;

    // Call the PUFs API to verify the signature.
    check = pufs_ecp_ecdsa_verify_dgst(sig, md, puk);
    if (check != SUCCESS) {
        return MBEDTLS_ERR_ECP_VERIFY_FAILED;
    }

    return 0;
}
#endif /* MBEDTLS_ECDSA_VERIFY_ALT */
