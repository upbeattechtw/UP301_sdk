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

#include "mbedtls/ecdh.h"

#ifdef MBEDTLS_ECDH_COMPUTE_SHARED_ALT
#include "pufs_common.h"
#include "pufs_ecp.h"

int mbedtls_ecdh_compute_shared(mbedtls_ecp_group *grp, mbedtls_mpi *z,
                                const mbedtls_ecp_point *Q, const mbedtls_mpi *d,
                                int (*f_rng)(void *, unsigned char *, size_t),
                                void *p_rng) {
    UNUSED(f_rng);
    UNUSED(p_rng);

    pufs_status_Type check = SUCCESS;
    pufs_ec_point_st_Type puk;
    uint8_t prk[32];
    uint8_t ss[32];

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

    // Export public key coordinates X and Y to 32-byte arrays for PUFs format.
    if (mbedtls_mpi_write_binary(&Q->private_X, puk.x, 32) != 0 ||
        mbedtls_mpi_write_binary(&Q->private_Y, puk.y, 32) != 0) {
        return MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL;
    }
    puk.qlen = 32;

    // Export private key scalar 'd' to a 32-byte binary array.
    if (mbedtls_mpi_write_binary(d, prk, 32) != 0) {
        return MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL;
    }
    
    // Import private key to PUFs key slot.
    check = pufs_import_plaintext_key(PRKEY, PRK_0, prk, B2b(sizeof(prk)));
    if (check != SUCCESS) {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    // Perform PUFs ECDH computation.
    check = pufs_ecp_ecccdh_2e(puk, PRK_0, ss);
    if (check != SUCCESS) {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    // Load the shared secret back into MPI structure.
    mbedtls_mpi_read_binary(z, ss, 32);

    // Clear the private key from key slot.
    pufs_clear_key(PRKEY, PRK_0, B2b(sizeof(prk)));
    
    return 0;
};
#endif /* MBEDTLS_ECDH_COMPUTE_SHARED_ALT */
