/**
 * @file      pufs_ecp_mprog.h
 * @brief     PUFsecurity ECP micro program
 * @copyright 2020 PUFsecurity
 */
/* THIS SOFTWARE IS SUPPLIED BY PUFSECURITY ''AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. TO THE FULLEST
 * EXTENT ALLOWED BY LAW, PUFSECURITY'S TOTAL LIABILITY ON ALL CLAIMS IN
 * ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES,
 * IF ANY, THAT YOU HAVE PAID DIRECTLY TO PUFSECURITY FOR THIS SOFTWARE.
 */

#ifndef PUFS_ECP_MPROG_H
#define PUFS_ECP_MPROG_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>
#include <stdint.h>

#include "pufs_ecc.h"

/**
 * @brief CMAC of RSA micro programs
 */
typedef struct pufs_rsa_mprog_cmac {
    const void *prk;
    const void *puk;
} pufs_rsa_mprog_cmac_Type;

/**
 * @brief Functions of RSA micro programs
 */
typedef struct pufs_rsa_mprog_func {
    const void *prk;
    const void *puk;
} pufs_rsa_mprog_func_Type;

/**
 * @brief RSA micro programs
 */
 typedef struct pufs_rsa_mprog {
	 pufs_rsa_mprog_cmac_Type *cmac;
	 pufs_rsa_mprog_func_Type *func;
} pufs_rsa_mprog_Type;

/**
 * @brief CMAC of SM2 micro programs
 */
typedef struct pufs_sm2_mprog_cmac {
    const void *enc_oss;
    const void *dec_oss;
    const void *puk_gen;
    const void *prks_gen;
    const void *sign;
    const void *verify;
    const void *kekdf;
} pufs_sm2_mprog_cmac_Type;

/**
 * @brief Functions of SM2 micro programs
 */
typedef struct pufs_sm2_mprog_func {
    const void *enc_oss;
    const void *dec_oss;
    const void *puk_gen;
    const void *prks_gen;
    const void *sign;
    const void *verify;
    const void *kekdf;
} pufs_sm2_mprog_func_Type;

/**
 * @brief RSA micro programs
 */
 typedef struct pufs_sm2_mprog {
	 pufs_sm2_mprog_cmac_Type *cmac;
	 pufs_sm2_mprog_func_Type *func;
} pufs_sm2_mprog_Type;

/**
 * @brief CMAC of ECP micro programs
 */
typedef struct pufs_ecp_mprog_cmac {
    uint32_t mp_version;
    const void* eccdh_2e;
    const void* eccdh_2e_oss;
    const void* eccdh_2s2e;
    const void* eccdh_2s2e_oss;
    const void* ecdsa_s;
    const void* ecdsa_s_ik;
    const void* ecdsa_v;
    const void* ecdsa_v_otpk;
    const void* prke_gen;
    const void* prki_gen;
    const void* prks_gen;
    const void* puk_gen;
    const void* pukv_f;
    const void* pukv_p;
} pufs_ecp_mprog_cmac_Type;

/**
 * @brief ECP micro programs of a curve
 */
typedef struct pufs_ecp_mprog_curve {
	pufs_ec_name_Type name;
    const void* eccdh_2e;
    const void* eccdh_2e_oss;
    const void* eccdh_2s2e;
    const void* eccdh_2s2e_oss;
    const void* ecdsa_s;
    const void* ecdsa_s_ik;
    const void* ecdsa_v;
    const void* ecdsa_v_otpk;
    const void* prke_gen;
    const void* prki_gen;
    const void* prks_gen;
    const void* puk_gen;
    const void* pukv_f;
    const void* pukv_p;
    pufs_ecp_mprog_cmac_Type *mprog_sum;
} pufs_ecp_mprog_curve_Type;

extern pufs_ecp_mprog_curve_Type *ecp_mprog[];
extern pufs_rsa_mprog_Type rsa_mprog[];
extern pufs_sm2_mprog_Type sm2_mprog;

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_ECP_MPROG_H */
