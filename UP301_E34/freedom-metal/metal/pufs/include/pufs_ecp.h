/**
 * @file      pufs_ecp.h
 * @brief     PUFsecurity ECP API interface
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
#ifndef PUFS_ECP_H
#define PUFS_ECP_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>

#include "pufs_ecc.h"
#include "pufs_ecp_mprog.h"
#include "pufs_hmac.h"
#include "pufs_ka.h"
#include "pufs_rt.h"

typedef struct {
	pufs_ka_slot_Type slot;
	pufs_rt_slot_Type pufslot;
	const uint8_t* salt;
	uint32_t saltlen;
	const uint8_t* info;
	uint32_t infolen;
	pufs_hash_Type hash;
    pufs_hash_ctx_Type *ctx;
    pufs_dgst_st_Type *md;
	uint8_t* sign;
	pufs_rsa_type_Type rsatype;
	const uint8_t* n;
	uint32_t puk;
	const uint8_t* prk;
	const uint8_t* msg;
	uint32_t msglen;
	const uint8_t* phi;
	bool swIntrptEnable;
} pkc_async_args_Type;

typedef enum {
	PKC_ASYNC_IDLE,
	PKC_ASYNC_KDF,
	PKC_ASYNC_SPRK,
	PKC_ASYNC_RESULT,
	PKC_ASYNC_X931_SIGN_INIT,
	PKC_ASYNC_HASH_INIT,
	PKC_ASYNC_HASH_UPDATE,
	PKC_ASYNC_HASH_FINAL,
	PKC_ASYNC_X931_SIGN_ENCODE,
	PKC_ASYNC_X931_SIGN_FINAL,
	PKC_ASYNC_X931_VERIFY_INIT,
	PKC_ASYNC_X931_VERIFY_ENCODE,
	PKC_ASYNC_X931_VERIFY_FINAL,
	PKC_ASYNC_P1V15_SIGN_INIT,
	PKC_ASYNC_P1V15_SIGN_ENCODE,
	PKC_ASYNC_P1V15_VERIFY_INIT,
	PKC_ASYNC_P1V15_VERIFY_ENCODE,
	PKC_ASYNC_P1V15_VERIFY_FINAL,
} pkc_async_step_Type;

/**
 * @brief Initialize PKC module
 * @param[in] pkc_offset  PKC offset of memory map
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_pkc_module_init(uintptr_t pkc_offset);

/**
 * @brief RSA verification.
 * @param[in] sig      RSA signature.
 * @param[in] rsatype  RSA type.
 * @param[in] n        RSA parameter n.
 * @param[in] puk      RSA public key.
 * @param[in] msg      Message.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_verify(
		const uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		const uint8_t* msg);

/**
 * @brief RSA verification with ISR mode.
 * @param[in] sig      RSA signature.
 * @param[in] rsatype  RSA type.
 * @param[in] n        RSA parameter n.
 * @param[in] puk      RSA public key.
 * @param[in] msg      Message.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_verify_isr(
		const uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		const uint8_t* msg);

/**
 * @brief RSA signing.
 * @param[out] sig      RSA signature.
 * @param[in]  rsatype  RSA type.
 * @param[in]  n        RSA parameter n.
 * @param[in]  puk      RSA public key.
 * @param[in]  prk      RSA private key.
 * @param[in]  msg      Message.
 * @param[in]  phi      The value of Euler totient function of RSA parameter n. phi can be NULL.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_sign(
		uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		const uint8_t* prk,
		const uint8_t* msg,
		const uint8_t* phi);

/**
 * @brief RSA signing with ISR mode.
 * @param[out] sig      RSA signature.
 * @param[in]  rsatype  RSA type.
 * @param[in]  n        RSA parameter n.
 * @param[in]  puk      RSA public key.
 * @param[in]  prk      RSA private key.
 * @param[in]  msg      Message.
 * @param[in]  phi      The value of Euler totient function of RSA parameter n. phi can be NULL.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_sign_isr(
		uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		const uint8_t* prk,
		const uint8_t* msg,
		const uint8_t* phi);

/**
 * @brief X9.31 RSA verification.
 * @param[in] sig      RSA signature.
 * @param[in] rsatype  RSA type.
 * @param[in] n        RSA parameter n.
 * @param[in] puk      RSA public key.
 * @param[in] msg      Message.
 * @param[in] msglen   Message length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_x931_verify(
		const uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		const uint8_t* msg,
		uint32_t msglen);

/**
 * @brief X9.31 RSA verification initialization with ISR mode.
 * @param[in] sig      RSA signature.
 * @param[in] rsatype  RSA type.
 * @param[in] n        RSA parameter n.
 * @param[in] puk      RSA public key.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_x931_verify_init_isr(
		const uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk);
/**
 * @brief X9.31 RSA verification with ISR mode.
 * @param[in] n        RSA parameter n.
 * @param[in] hash     HASH algorithm.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_x931_verify_encode(
		const uint8_t* n,
		pufs_hash_Type *hash);

/**
 * @brief X9.31 RSA verification finalization with ISR mode.
 * @param[in] md		Message digest.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_x931_verify_final(pufs_dgst_st_Type *md);

/**
 * @brief Start RSA-X9.31 digital signature verification in asynchronous mode.
 * @param[in]  hash_ctx           Hash context.
 * @param[out] md                 Message digest structure.
 * @param[in]  hash               Hash algorithm used for the signature.
 * @param[in]  sign               Input signature to verify.
 * @param[in]  rsatype            RSA key type.
 * @param[in]  n                  RSA modulus (public key component).
 * @param[in]  puk                Public exponent (e.g., 0x10001).
 * @param[in]  msg                Original message.
 * @param[in]  msglen             Message length in bytes.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_rsa_x931_verify_async_start (
	pufs_hash_ctx_Type *hash_ctx,
	pufs_dgst_st_Type *md,
	pufs_hash_Type *hash,
	uint8_t* sign,
	pufs_rsa_type_Type rsatype,
	const uint8_t* n,
	uint32_t puk,
	const uint8_t* msg,
	uint32_t msglen,
	bool swIntrptEnable
);

/**
 * @brief Check signature verification progress in asynchronous RSA-X9.31 mode.
 * @return Current status of the asynchronous RSA-X9.31 verification operation.
 */
pufs_module_state_Type pufs_rsa_x931_verify_async_check (void);

/**
 * @brief X9.31 RSA signing.
 * @param[out] sig      RSA signature.
 * @param[in]  rsatype  RSA type.
 * @param[in]  n        RSA parameter n.
 * @param[in]  puk      RSA public key.
 * @param[in]  prk      RSA private key.
 * @param[in]  hash     Hash algorithm.
 * @param[in]  msg      Message.
 * @param[in]  msglen   Message length in bytes.
 * @param[in]  phi      The value of Euler totient function of RSA parameter n. phi can be NULL.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_x931_sign(
		uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		const uint8_t* prk,
		pufs_hash_Type hash,
		const uint8_t* msg,
		uint32_t msglen,
		const uint8_t* phi);

/**
 * @brief X9.31 RSA signing initialization with ISR mode.
 * @param[in]  rsatype  RSA type.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_x931_sign_init(pufs_rsa_type_Type rsatype);

/**
 * @brief X9.31 RSA signing with ISR mode.
 * @param[out] sig      RSA signature.
 * @param[in]  rsatype  RSA type.
 * @param[in]  n        RSA parameter n.
 * @param[in]  puk      RSA public key.
 * @param[in]  prk      RSA private key.
 * @param[in]  hash     Hash algorithm.
 * @param[in]  phi      The value of Euler totient function of RSA parameter n. phi can be NULL.
 * @param[in]  md		Message digest.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_x931_sign_encode_isr(
		uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		const uint8_t* prk,
		pufs_hash_Type hash,
		const uint8_t* phi,
		pufs_dgst_st_Type *md);

/**
 * @brief X9.31 RSA signing finalization with ISR mode.
 * @param[out] sig      RSA signature.
 * @param[in]  n        RSA parameter n.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_x931_sign_final(
		uint8_t* sig,
		const uint8_t* n);

/**
 * @brief Start RSA-X9.31 digital signature generation in asynchronous mode.
 * @param[in]  hash_ctx           Hash context.
 * @param[out] md                 Message digest structure.
 * @param[out] sign               Output signature buffer.
 * @param[in]  rsatype            RSA key type.
 * @param[in]  n                  RSA modulus (public key component).
 * @param[in]  puk                Public exponent (e.g., 0x10001).
 * @param[in]  prk                Private key component (e.g., d or CRT form).
 * @param[in]  hash               Hash algorithm.
 * @param[in]  msg                Input message to be signed.
 * @param[in]  msglen             Message length in bytes.
 * @param[in]  phi                φ(n) or related parameter for CRT.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_rsa_x931_sign_async_start (
	pufs_hash_ctx_Type *hash_ctx,
	pufs_dgst_st_Type *md,
	uint8_t* sign,
	pufs_rsa_type_Type rsatype,
	const uint8_t* n,
	uint32_t puk,
	const uint8_t* prk,
	pufs_hash_Type hash,
	const uint8_t* msg,
	uint32_t msglen,
	const uint8_t* phi,
	bool swIntrptEnable
);

/**
 * @brief Check signature generation progress in asynchronous RSA-X9.31 mode.
 * @return Current status of the asynchronous RSA-X9.31 signature operation.
 */
pufs_module_state_Type pufs_rsa_x931_sign_async_check (void);

/**
 * @brief PKCS#1 v1.5 RSA verification with ISR mode.
 * @param[in] sig      RSA signature.
 * @param[in] rsatype  RSA type.
 * @param[in] n        RSA parameter n.
 * @param[in] puk      RSA public key.
 * @param[in] msg      Message.
 * @param[in] msglen   Message length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_p1v15_verify(
		const uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		const uint8_t* msg,
		uint32_t msglen);

/**
 * @brief PKCS#1 v1.5 RSA verification.
 * @param[in] hash		Hash algorithm.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_p1v15_verify_encode(pufs_hash_Type *hash);

/**
 * @brief PKCS#1 v1.5 RSA verification finalization.
 * @param[in] args     Arguments for incoming HASH operation.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_p1v15_verify_final(pufs_dgst_st_Type *md);

/**
 * @brief Start RSA PKCS#1 v1.5 signature verification in asynchronous mode.
 * @param[in]  hash_ctx           Hash context.
 * @param[out] md                 Message digest structure.
 * @param[in]  sign               Input signature to verify.
 * @param[in]  rsatype            RSA key type.
 * @param[in]  n                  RSA modulus (public key component).
 * @param[in]  puk                Public exponent (e.g., 0x10001).
 * @param[in]  hash               Hash algorithm used for the signature.
 * @param[in]  msg                Original message.
 * @param[in]  msglen             Message length in bytes.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_rsa_p1v15_verify_async_start (
	pufs_hash_ctx_Type *hash_ctx,
	pufs_dgst_st_Type *md,
	uint8_t* sign,
	pufs_rsa_type_Type rsatype,
	const uint8_t* n,
	uint32_t puk,
	pufs_hash_Type *hash,
	const uint8_t* msg,
	uint32_t msglen,
	bool swIntrptEnable
);

/**
 * @brief Check signature verification progress in asynchronous RSA PKCS#1 v1.5 mode.
 * @return Current status of the asynchronous RSA-PKCS#1 v1.5 verification operation.
 */
pufs_module_state_Type pufs_rsa_p1v15_verify_async_check (void);

/**
 * @brief PKCS#1 v1.5 RSA verification initialization with ISR mode.
 * @param[in] sig      RSA signature.
 * @param[in] rsatype  RSA type.
 * @param[in] n        RSA parameter n.
 * @param[in] puk      RSA public key.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_p1v15_verify_init_isr(
		const uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk);

/**
 * @brief PKCS#1 v1.5 RSA signing.
 * @param[out] sig      RSA signature.
 * @param[in]  rsatype  RSA type.
 * @param[in]  n        RSA parameter n.
 * @param[in]  puk      RSA public key.
 * @param[in]  prk      RSA private key.
 * @param[in]  hash     Hash algorithm.
 * @param[in]  msg      Message.
 * @param[in]  msglen   Message length in bytes.
 * @param[in]  phi      The value of Euler totient function of RSA parameter n. phi can be NULL.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_p1v15_sign(
		uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		const uint8_t* prk,
		pufs_hash_Type hash,
		const uint8_t* msg,
		uint32_t msglen,
		const uint8_t* phi);

/**
 * @brief PKCS#1 v1.5 RSA signing initialization with ISR mode.
 * @param[in]  rsatype  RSA type.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_p1v15_sign_init(pufs_rsa_type_Type rsatype);

/**
 * @brief PKCS#1 v1.5 RSA signing with ISR mode.
 * @param[out] sig      RSA signature.
 * @param[in]  rsatype  RSA type.
 * @param[in]  n        RSA parameter n.
 * @param[in]  puk      RSA public key.
 * @param[in]  prk      RSA private key.
 * @param[in]  hash     Hash algorithm.
 * @param[in]  msg      Message.
 * @param[in]  msglen   Message length in bytes.
 * @param[in]  phi      The value of Euler totient function of RSA parameter n. phi can be NULL.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_p1v15_sign_encode_isr(
		uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		const uint8_t* prk,
		pufs_hash_Type hash,
		const uint8_t* phi,
		pufs_dgst_st_Type *md);

/**
 * @brief Start RSA PKCS#1 v1.5 digital signature generation in asynchronous mode.
 * @param[in]  hash_ctx           Hash context.
 * @param[out] md                 Message digest structure.
 * @param[out] sign               Output signature buffer.
 * @param[in]  rsatype            RSA key type.
 * @param[in]  n                  RSA modulus (public key component).
 * @param[in]  puk                Public exponent (e.g., 0x10001).
 * @param[in]  prk                Private key component (e.g., d or CRT form).
 * @param[in]  hash               Hash algorithm.
 * @param[in]  msg                Input message to be signed.
 * @param[in]  msglen             Message length in bytes.
 * @param[in]  phi                φ(n) or related parameter for CRT optimization.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_rsa_p1v15_sign_async_start (
	pufs_hash_ctx_Type *hash_ctx,
	pufs_dgst_st_Type *md,
	uint8_t* sign,
	pufs_rsa_type_Type rsatype,
	const uint8_t* n,
	uint32_t puk,
	const uint8_t* prk,
	pufs_hash_Type hash,
	const uint8_t* msg,
	uint32_t msglen,
	const uint8_t* phi,
	bool swIntrptEnable
);

/**
 * @brief Check signature generation progress in asynchronous RSA PKCS#1 v1.5 mode.
 * @return Current status of the asynchronous RSA-PKCS#1 v1.5 signature operation.
 */
pufs_module_state_Type pufs_rsa_p1v15_sign_async_check (void);

/**
 * @brief RSA PSS verification.
 * @param[in] sig      RSA signature.
 * @param[in] rsatype  RSA type.
 * @param[in] n        RSA parameter n.
 * @param[in] puk      RSA public key.
 * @param[in] hash     Hash algorithm.
 * @param[in] msg      Message.
 * @param[in] msglen   Message length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_pss_verify(
		const uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		pufs_hash_Type hash,
		const uint8_t* msg,
		uint32_t msglen);

/**
 * @brief RSA PSS signing.
 * @param[out] sig      RSA signature.
 * @param[in]  rsatype  RSA type.
 * @param[in]  n        RSA parameter n.
 * @param[in]  puk      RSA public key.
 * @param[in]  prk      RSA private key.
 * @param[in]  hash     Hash algorithm.
 * @param[in]  msg      Message.
 * @param[in]  msglen   Message length in bytes.
 * @param[in]  salt     Salt.
 * @param[in]  saltlen  Salt length in bytes.
 * @param[in]  phi      The value of Euler totient function of RSA parameter n. phi can be NULL.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rsa_pss_sign(
		uint8_t* sig,
		pufs_rsa_type_Type rsatype,
		const uint8_t* n,
		uint32_t puk,
		const uint8_t* prk,
		pufs_hash_Type hash,
		const uint8_t* msg,
		uint32_t msglen,
		const uint8_t* salt,
		uint32_t saltlen,
		const uint8_t* phi);

/**
 * @brief Set elliptic curve domain parameters by name.
 * @param[in] name  Elliptic curve name.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_set_curve_byname(pufs_ec_name_Type name);

/**
 * @brief Generate static ECC private key.
 * @param[in] slot     Private key slot.
 * @param[in] pufslot  PUF slots (1-3).
 * @param[in] salt     Salt used by the KDF to derive KDK.
 * @param[in] saltlen  Salt length.
 * @param[in] info     Info used in KDF.
 * @param[in] infolen  Info length.
 * @param[in] hash     Hash algorithm. Default is SHA256.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_gen_sprk(
		pufs_ka_slot_Type slot,
		pufs_rt_slot_Type pufslot,
		const uint8_t* salt,
		uint32_t saltlen,
		const uint8_t* info,
		uint32_t infolen,
		pufs_hash_Type hash);

/**
 * @brief Generate static ECC private key with ISR mode.
 * @param[in] slot     Private key slot.
 * @param[in] pufslot  PUF slots (1-3).
 * @param[in] salt     Salt used by the KDF to derive KDK.
 * @param[in] saltlen  Salt length.
 * @param[in] info     Info used in KDF.
 * @param[in] infolen  Info length.
 * @param[in] hash     Hash algorithm. Default is SHA256.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_gen_sprk_isr(
		pufs_ka_slot_Type slot,
		pufs_rt_slot_Type pufslot,
		const uint8_t* salt,
		uint32_t saltlen,
		const uint8_t* info,
		uint32_t infolen,
		pufs_hash_Type hash);

/**
 * @brief Generate ephemeral ECC private key.
 * @param[in] slot  Private key slot.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_gen_eprk(pufs_ka_slot_Type slot);

/**
 * @brief Generate ephemeral ECC private key with ISR mode.
 * @param[in] slot  Private key slot.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_gen_eprk_isr(pufs_ka_slot_Type slot);

/**
 * @brief Generate ECC public key of the corresponding private key.
 * @param[out] puk      Public key.
 * @param[in]  prktype  Private key type.
 * @param[in]  prkslot  Private key slot.
 * @return pufs_status_Type value.
 * @note Only \ref PRKEY and \ref OTPKEY are allowed \em keytype.
 */
pufs_status_Type pufs_ecp_gen_puk(
		pufs_ec_point_st_Type* puk,
		pufs_key_type_Type prktype,
		uint32_t prkslot);

/**
 * @brief Generate ECC public key of the corresponding private key with ISR mode.
 * @param[out] puk      Public key.
 * @param[in]  prktype  Private key type.
 * @param[in]  prkslot  Private key slot.
 * @return pufs_status_Type value.
 * @note Only \ref PRKEY and \ref OTPKEY are allowed \em keytype.
 */
pufs_status_Type pufs_ecp_gen_puk_isr(
		pufs_ec_point_st_Type* puk,
		pufs_key_type_Type prktype,
		uint32_t prkslot);

/**
 * @brief Validate ECC public key.
 * @param[in] puk   ECC public key.
 * @param[in] full  A flag to enable full validation. 
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_validate_puk(pufs_ec_point_st_Type puk, bool full);

/**
 * @brief Validate ECC public key with ISR mode.
 * @param[in] puk   ECC public key.
 * @param[in] full  A flag to enable full validation.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_validate_puk_isr(pufs_ec_point_st_Type puk, bool full);

/**
 * @brief Derive shared secret from ephemeral keys by ECC CDH.
 * @param[in]  puk      Public key.
 * @param[in]  prkslot  Private key slot.
 * @param[out] ss       Shared secret. ss can be NULL.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_ecccdh_2e(
		pufs_ec_point_st_Type puk,
		pufs_ka_slot_Type prkslot,
		uint8_t* ss);

/**
 * @brief Derive shared secret from ephemeral keys by ECC CDH with ISR mode.
 * @param[in]  puk      Public key.
 * @param[in]  prkslot  Private key slot.
 * @param[out] ss       Shared secret. ss can be NULL.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_ecccdh_2e_isr(
		pufs_ec_point_st_Type puk,
		pufs_ka_slot_Type prkslot,
		uint8_t* ss);

/**
 * @brief Derive shared secret from ephemeral and static keys by ECC CDH.
 * @param[in]  puk_e      Ephemeral public key.
 * @param[in]  puk_s      Static public key.
 * @param[in]  prkslot_e  Ephemeral private key slot.
 * @param[in]  prktype_s  Static private key type.
 * @param[in]  prkslot_s  Static private key slot.
 * @param[out] ss         Shared secret. ss can be NULL.
 * @return pufs_status_Type value.
 * @note Only \ref PRKEY and \ref OTPKEY are allowed \em keytype.
 */
pufs_status_Type pufs_ecp_ecccdh_2e2s(
		pufs_ec_point_st_Type puk_e,
		pufs_ec_point_st_Type puk_s,
		pufs_ka_slot_Type prkslot_e,
		pufs_key_type_Type prktype_s,
		uint32_t prkslot_s,
		uint8_t* ss);

/**
 * @brief Derive shared secret from ephemeral and static keys by ECC CDH with ISR mode.
 * @param[in]  puk_e      Ephemeral public key.
 * @param[in]  puk_s      Static public key.
 * @param[in]  prkslot_e  Ephemeral private key slot.
 * @param[in]  prktype_s  Static private key type.
 * @param[in]  prkslot_s  Static private key slot.
 * @param[out] ss         Shared secret. ss can be NULL.
 * @return pufs_status_Type value.
 * @note Only \ref PRKEY and \ref OTPKEY are allowed \em keytype.
 */
pufs_status_Type pufs_ecp_ecccdh_2e2s_isr(
		pufs_ec_point_st_Type puk_e,
		pufs_ec_point_st_Type puk_s,
		pufs_ka_slot_Type prkslot_e,
		pufs_key_type_Type prktype_s,
		uint32_t prkslot_s,
		uint8_t* ss);

/**
 * @brief Verify the ECDSA signature of the message digest.
 * @param[in] sig  Signature.
 * @param[in] md   Message digest.
 * @param[in] puk  Public key for signature verification.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_ecdsa_verify_dgst(
		pufs_ecdsa_sig_st_Type sig,
		pufs_dgst_st_Type md,
		pufs_ec_point_st_Type puk);

/**
 * @brief Verify the ECDSA signature of the message digest with ISR mode.
 * @param[in] sig  Signature.
 * @param[in] md   Message digest.
 * @param[in] puk  Public key for signature verification.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_ecdsa_verify_dgst_isr(
		pufs_ecdsa_sig_st_Type sig,
		pufs_dgst_st_Type md,
		pufs_ec_point_st_Type puk);

/**
 * @brief Verify the ECDSA signature of the message.
 * @param[in] sig     Signature.
 * @param[in] msg     Message.
 * @param[in] msglen  Message length in bytes.
 * @param[in] hash    Hash algorithm.
 * @param[in] puk     Public key for signature verification.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_ecdsa_verify_msg(
		pufs_ecdsa_sig_st_Type sig,
		const uint8_t* msg,
		uint32_t msglen,
		pufs_hash_Type hash,
		pufs_ec_point_st_Type puk);

/**
 * @brief Verify the ECDSA signature of the message digest using OTP public key.
 * @param[in] sig  Signature.
 * @param[in] md   Digest of the signed message.
 * @param[in] puk  OTP key slot of public key for signature verification.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_ecdsa_verify_dgst_otpkey(
		pufs_ecdsa_sig_st_Type sig,
		pufs_dgst_st_Type md,
		pufs_rt_slot_Type puk);

/**
 * @brief Verify the ECDSA signature of the message using OTP public key.
 * @param[in] sig     Signature.
 * @param[in] msg     Message.
 * @param[in] msglen  Message length in bytes.
 * @param[in] hash    Hash algorithm.
 * @param[in] puk     OTP key slot of public key for signature verification.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_ecp_ecdsa_verify_msg_otpkey(
		pufs_ecdsa_sig_st_Type sig,
		const uint8_t* msg,
		uint32_t msglen,
		pufs_hash_Type hash,
		pufs_rt_slot_Type puk);

/**
 * @brief Generate an ECDSA signature from a message digest.
 * @param[in] sig      Signature.
 * @param[in] md       Message digest.
 * @param[in] prktype  Private key type.
 * @param[in] prkslot  Private key slot.
 * @param[in] k        Random k only used in CAVP. k can be NULL.
 * @return pufs_status_Type value.
 * @note Only \ref PRKEY and \ref OTPKEY are allowed \em keytype.
 */
pufs_status_Type pufs_ecp_ecdsa_sign_dgst(
		pufs_ecdsa_sig_st_Type* sig,
		pufs_dgst_st_Type md,
		pufs_key_type_Type prktype,
		uint32_t prkslot,
		const uint8_t* k);

/**
 * @brief Generate an ECDSA signature from a message digest with ISR mode.
 * @param[in] sig      Signature.
 * @param[in] md       Message digest.
 * @param[in] prktype  Private key type.
 * @param[in] prkslot  Private key slot.
 * @param[in] k        Random k only used in CAVP. k can be NULL.
 * @return pufs_status_Type value.
 * @note Only \ref PRKEY and \ref OTPKEY are allowed \em keytype.
 */
pufs_status_Type pufs_ecp_ecdsa_sign_dgst_isr(
		pufs_ecdsa_sig_st_Type* sig,
		pufs_dgst_st_Type md,
		pufs_key_type_Type prktype,
		uint32_t prkslot,
		const uint8_t* k);

/**
 * @brief Generate an ECDSA signature of a message.
 * @param[in] sig      Signature.
 * @param[in] msg      Message.
 * @param[in] msglen   Message length in bytes.
 * @param[in] hash     Hash algorithm.
 * @param[in] prktype  Private key type.
 * @param[in] prkslot  Private key slot.
 * @param[in] k        Random k only used in CAVP. k can be NULL.
 * @return pufs_status_Type value.
 * @note Only \ref PRKEY and \ref OTPKEY are allowed \em keytype.
 */
pufs_status_Type pufs_ecp_ecdsa_sign_msg(
		pufs_ecdsa_sig_st_Type* sig,
		const uint8_t* msg,
		uint32_t msglen,
		pufs_hash_Type hash,
		pufs_key_type_Type prktype,
		uint32_t prkslot,
		const uint8_t* k);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_ECP_H */
