/**
 * @file      pufs_ecp.h
 * @brief     PUFsecurity ECP internal interface
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

#ifndef PUFS_ECP_INTERNAL_H
#define PUFS_ECP_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_ecp.h"
#include "pufs_ecp_regs.h"

#if !defined(ECP_VERSION)
    #define ECP_VERSION 0xECF39303
#endif

#define MAXELEN 		72
#define ECP_MPMAC_SIZE	16
#define ECP_MPROG_SIZE	256

extern pufs_ecp_regs_Type *ecp_regs;

typedef enum pufs_ecp_field_t {
    P1024 = 0x85,
    P2048,
    P3072,
    P4096,
    N_ECP_FIELD_T,
} pufs_ecp_field_Type;

typedef struct ecdp_setting {
    pufs_ecp_mprog_curve_Type *mprog;
    pufs_ecp_mprog_cmac_Type *mpmac;
    pufs_ec_name_Type name;
    bool isset;
} ecdp_setting_Type;

extern ecdp_setting_Type ecdp_set;

/**
 * @brief Initialize RSA field and elen.
 * @param[out] field    RSA field.
 * @param[out] elen     RSA element length.
 * @param[in]  rsatype  RSA type.
 * @return pufs_status_Type value.
 */
pufs_status_Type __rsa_get_field_elen(
		pufs_ecp_field_Type* field,
		uint32_t* elen,
		pufs_rsa_type_Type rsatype);

/**
 * @brief Bignum comparison of a and b.
 * @param[in]  a    a.
 * @param[in]  b    b.
 * @param[in]  len  a, b length in bytes.
 * @return          An integral value which is greater than, equal to, or less
 *                   then 0 representing a > b, a = b, or a < b.
 */
int16_t __bn_cmp(const uint8_t* a, const uint8_t* b, uint32_t len);

/**
 * @brief Reset the target oeprand to zero.
 * @param pos The operand position of the operand to be written in SRAM.
 * @param elen The length in bytes of the operand stored in SRAM.
 * @return pufs_status_Type value.
 */
pufs_status_Type __reset_ecp_operand(uint32_t pos, uint32_t elen);

/**
 * @brief Write oeprands into SRAM.
 * @param pos The operand position of the operand to be written in SRAM.
 * @param op The operand.
 * @param elen The length in bytes of the operand stored in SRAM.
 * @return pufs_status_Type value.
 */
pufs_status_Type __write_ecp_operand_(uint32_t pos, const uint8_t* op, uint32_t elen);

/**
 * @brief Read resulting operands from SRAM
 *
 * @param pos       The result position of the operand to be read from SRAM
 * @param res       The pointer to the space for the resulting operand
 * @param elen      The length in bytes of the resulting operand stored in SRAM
 * @param oss_2e2s  Indication of 2e2s_oss read.
 * @return pufs_status_Type value.
 */
pufs_status_Type __read_ecp_operand(
		uint32_t pos,
		uint8_t* res,
		uint32_t elen,
		bool oss_2e2s);

/**
 * @brief Bignum subtraction b = n - a. (n > a).
 * @param[out] b    The result b.
 * @param[in]  n    n.
 * @param[in]  a    a.
 * @param[in]  len  n, a, b length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type __bn_sub(
		uint8_t* b,
		const uint8_t* n,
		const uint8_t* a,
		uint32_t len);

/**
 * @brief   Set SM2 curve domain parameters.
 * @return pufs_status_Type value.
 */
pufs_status_Type ecp_set_sm2_curve(void);

/**
 * @brief Compute x1,y1 / x2,y2 points for SM2 encryption.
 * @param[in]  puk   Public key.
 * @param[out] x1y1  EC point for C1.
 * @param[out] x2y2  EC point for C2 and C3.
 * @return pufs_status_Type value.
 */
pufs_status_Type ecp_sm2_enc_oss(
		pufs_ec_point_st_Type *puk,
		pufs_ec_point_st_Type *x1y1,
		pufs_ec_point_st_Type *x2y2);

/**
 * @brief Compute x1,y1 / x2,y2 points for SM2 encryption with ISR mode.
 * @param[in]  puk   Public key.
 * @param[out] x1y1  EC point for C1.
 * @param[out] x2y2  EC point for C2 and C3.
 * @return pufs_status_Type value.
 */
pufs_status_Type ecp_sm2_enc_oss_isr(
		pufs_ec_point_st_Type *puk,
		pufs_ec_point_st_Type *x1y1,
		pufs_ec_point_st_Type *x2y2);

/**
 * @brief Compute x2,y2 points for SM2 decryption.
 * @param[in]  prk   Private key slot.
 * @param[in]  x1y1  EC point for C1.
 * @param[out] x2y2  EC point for C2 and C3.
 * @return pufs_status_Type value.
 */
pufs_status_Type ecp_sm2_dec_oss(
		pufs_ka_slot_Type prk,
		pufs_ec_point_st_Type *x1y1,
		pufs_ec_point_st_Type *x2y2);

/**
 * @brief Compute x2,y2 points for SM2 decryption with ISR mode.
 * @param[in]  prk   Private key slot.
 * @param[in]  x1y1  EC point for C1.
 * @param[out] x2y2  EC point for C2 and C3.
 * @return pufs_status_Type value.
 */
pufs_status_Type ecp_sm2_dec_oss_isr(
		pufs_ka_slot_Type prk,
		pufs_ec_point_st_Type *x1y1,
		pufs_ec_point_st_Type *x2y2);

/**
 * @brief Sign digest using SM2 digital signature algorithm.
 * @param[out]    sig  Signature.
 * @param[in]      md  Message digest.
 * @param[in] prktype  Private key type.
 * @param[in] prkslot  Private key slot.
 * @return pufs_status_Type value.
 */
pufs_status_Type ecp_sm2_sign_dgst(
		pufs_ecdsa_sig_st_Type *sig,
		pufs_dgst_st_Type *md,
		pufs_key_type_Type prktype,
		pufs_ka_slot_Type prkslot);

/**
 * @brief Verify signature using SM2 digital signature algorithm.
 * @param[in]     sig  Signature.
 * @param[in]      md  Message digest.
 * @param[in]     puk  Public Key.
 * @return pufs_status_Type value.
 */
pufs_status_Type ecp_sm2_verify_dgst(
		pufs_ecdsa_sig_st_Type *sig,
		pufs_dgst_st_Type *md,
		pufs_ec_point_st_Type *puk);

pufs_status_Type ecp_sm2_kekdf(
		pufs_ec_point_st_Type *key,
		pufs_ec_point_st_Type *tpukl,
		pufs_ec_point_st_Type *tpukr,
		pufs_ec_point_st_Type *pukr,
		pufs_ka_slot_Type tprkslotl,
		pufs_ka_slot_Type prkslotl);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_ECP_INTERNAL_H */
