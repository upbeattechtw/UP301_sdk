/**
 * @file      pufs_sm2.h
 * @brief     PUFsecurity SM2 API interface
 * @copyright 2021 PUFsecurity
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
#ifndef PUFS_SM2_H
#define PUFS_SM2_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_common.h"
#include "pufs_ecc.h"
#include "pufs_ka.h"

/**
 * @brief The format of SM2 encryption/decryption
 */
typedef enum pufs_sm2_format {
    N_SM2_T = -1,
    SM2_C1C2C3,
    SM2_C1C3C2
} pufs_sm2_format_Type;

typedef struct {
    pufs_hash_ctx_Type *ctx;
    pufs_dgst_st_Type *md;
	uint8_t* out;
	uint32_t* outlen;
	const uint8_t* in;
	uint32_t inlen;
	int32_t *msglen;
	pufs_ka_slot_Type prk;
	pufs_ec_point_st_Type puk;
	pufs_sm2_format_Type format;
	const uint8_t* k;
	pufs_ec_point_st_Type *x2y2;
	bool swIntrptEnable;
} sm2_async_args_Type;

typedef enum {
	SM2_ASYNC_IDLE,
	SM2_ASYNC_RESULT,
	SM2_ASYNC_OSS,
	SM2_ASYNC_HASH_INIT,
	SM2_ASYNC_HASH_UPDATE_0,
	SM2_ASYNC_HASH_UPDATE_1,
	SM2_ASYNC_HASH_UPDATE_2,
	SM2_ASYNC_HASH_FINAL,
	SM2_ASYNC_KDF,
	SM2_ASYNC_VERIFY_C3
} sm2_async_step_Type;

/**
 * @brief SM2 encryption.
 * @param[out] out     SM2 ciphertext.
 * @param[out] outlen  SM2 ciphertext length in bytes.
 * @param[in]  in      Plaintext.
 * @param[in]  inlen   Plaintext length in bytes.
 * @param[in]  puk     SM2 public key.
 * @param[in]  format  Format for SM2 encryption.
 * @param[in]  k       SM2 encryption ephemeral key. k can be NULL.
 * @return pufs_status_Type value.
 * @note Currently input \em k is not supported.
 */
pufs_status_Type pufs_sm2_enc(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_ec_point_st_Type puk,
		pufs_sm2_format_Type format,
		const uint8_t* k);

pufs_status_Type pufs_sm2_enc_isr(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_ec_point_st_Type puk,
		pufs_sm2_format_Type format,
		const uint8_t* k,
		pufs_dgst_st_Type *md);

/**
 * @brief SM2 encryption one-step signature with ISR mode.
 * @param[in]  puk     SM2 public key.
 * @param[in]  x2y2    EC point for C2 and C3.
 * @note Currently input \em k is not supported.
 */
pufs_status_Type pufs_sm2_enc_oss_isr(
		pufs_ec_point_st_Type puk,
		pufs_ec_point_st_Type **x2y2);

/**
 * @brief SM2 encryption KDF with ISR mode.
 * @param[out] out     SM2 ciphertext.
 * @param[in]  in      Plaintext.
 * @param[in]  inlen   Plaintext length in bytes.
 * @param[in]  format  Format for SM2 encryption.
 * @return pufs_status_Type value.
 * @note Currently input \em k is not supported.
 */
pufs_status_Type pufs_sm2_enc_kdf_isr(
		uint8_t* out,
		const uint8_t* in,
		uint32_t inlen,
		pufs_sm2_format_Type format);

/**
 * @brief SM2 encryption C3 Verification with ISR mode.
 * @param[out] out     SM2 ciphertext.
 * @param[out] outlen  SM2 ciphertext length in bytes.
 * @param[in]  inlen   Plaintext length in bytes.
 * @param[in]  format  Format for SM2 encryption.
 * @param[in]  md	   Message digest.
 * @return pufs_status_Type value.
 * @note Currently input \em k is not supported.
 */
pufs_status_Type pufs_sm2_enc_verify_c3(
		uint8_t* out,
		uint32_t* outlen,
		uint32_t inlen,
		pufs_sm2_format_Type format,
		pufs_dgst_st_Type *md);

/**
 * @brief Start SM2 public key encryption in asynchronous mode.
 * @param[in]  hash_ctx           Hash context.
 * @param[out] md                 Message digest structure.
 * @param[out] out                Output buffer for SM2 ciphertext.
 * @param[out] outlen             Output ciphertext length.
 * @param[in]  in                 Input plaintext.
 * @param[in]  inlen              Input plaintext length in bytes.
 * @param[in]  puk                Recipient's SM2 public key.
 * @param[in]  format             SM2 output format (e.g., C1C2C3 or C1C3C2).
 * @param[in]  k                  Random value k used in encryption (should be securely generated).
 * @param[out] x2y2               Optional output: ephemeral shared point (X2, Y2).
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_sm2_enc_async_start (
	pufs_hash_ctx_Type *hash_ctx,
	pufs_dgst_st_Type *md,
	uint8_t* out,
	uint32_t* outlen,
	const uint8_t* in,
	uint32_t inlen,
	pufs_ec_point_st_Type puk,
	pufs_sm2_format_Type format,
	const uint8_t* k,
	pufs_ec_point_st_Type *x2y2,
	bool swIntrptEnable
);


/**
 * @brief Check encryption progress status in asynchronous SM2 mode.
 * @return Current status of the asynchronous SM2 encryption operation.
 */
pufs_module_state_Type pufs_sm2_enc_async_check (void);

/**
 * @brief SM2 decryption
 * @param[out] out      Plaintext.
 * @param[out] outlen   Plaintext length in bytes.
 * @param[in]  in       SM2 ciphertext.
 * @param[in]  inlen    SM2 ciphertext length in bytes.
 * @param[in]  prk  Private key slot.
 * @param[in]  format  Format for SM2 encryption.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_sm2_dec(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_ka_slot_Type prk,
		pufs_sm2_format_Type format);

/**
 * @brief SM2 decryption OSS with ISR mode.
 * @param[in]  in       SM2 ciphertext.
 * @param[in]  inlen    SM2 ciphertext length in bytes.
 * @param[in]  prk      Private key slot.
 * @param[in]  msgLen   Message length.
 * @param[in]  x2y2     EC point for C2 and C3.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_sm2_dec_oss_isr(
		const uint8_t* in,
		uint32_t inlen,
		pufs_ka_slot_Type prk,
		int32_t **msgLen,
		pufs_ec_point_st_Type **x2y2);

/**
 * @brief SM2 decryption KDF with ISR mode.
 * @param[out] out      Plaintext.
 * @param[in]  format  Format for SM2 encryption.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_sm2_dec_kdf_isr(uint8_t* out, pufs_sm2_format_Type format);

/**
 * @brief SM2 decryption C3 verification with ISR mode.
 * @param[in]  format  Format for SM2 encryption.
 * @param[in]  md	   Message digest.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_sm2_dec_verify_c3(pufs_sm2_format_Type format, pufs_dgst_st_Type *md);

/**
 * @brief Start SM2 private key decryption in asynchronous mode.
 * @param[in]  hash_ctx           Hash context.
 * @param[out] md                 Message digest structure.
 * @param[out] out                Output buffer for decrypted plaintext.
 * @param[out] outlen             Actual decrypted length.
 * @param[in]  in                 Input SM2 ciphertext.
 * @param[in]  inlen              Input ciphertext length in bytes.
 * @param[out] msglen             Optional output: original message length (can be NULL if unused).
 * @param[in]  prk                SM2 private key (key agreement slot or handle).
 * @param[in]  format             SM2 input format (e.g., C1C2C3 or C1C3C2).
 * @param[out] x2y2               Optional output: ephemeral shared point (X2, Y2).
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_sm2_dec_async_start (
	pufs_hash_ctx_Type *hash_ctx,
	pufs_dgst_st_Type *md,
	uint8_t* out,
	uint32_t* outlen,
	const uint8_t* in,
	uint32_t inlen,
	int32_t *msglen,
	pufs_ka_slot_Type prk,
	pufs_sm2_format_Type format,
	pufs_ec_point_st_Type *x2y2,
	bool swIntrptEnable
);

/**
 * @brief Check decryption progress status in asynchronous SM2 mode.
 * @return Current status of the asynchronous SM2 decryption operation.
 */
pufs_module_state_Type pufs_sm2_dec_async_check (void);

/**
 * @brief SM2 key exchange protocol
 * @param[out] s2         Shared secret hash starting with 0x02. (\f$S_B\f$)
 * @param[out] s3         Shared secret hash starting with 0x03. (\f$S_A\f$)
 * @param[out] key        The shared key.
 * @param[in]  keybits    The shared key length in bits.
 * @param[in]  idl        Local party identity.
 * @param[in]  idllen     Local party identity length in bytes.
 * @param[in]  idr        Remote party identity.
 * @param[in]  idrlen     Remote party identity length in bytes.
 * @param[in]  prkslotl   Local party private key slot.
 * @param[in]  tprkslotl  Local party ephemeral private key slot.
 * @param[in]  pukr       Remote party public key.
 * @param[in]  tpukr      Remote party ephemeral public key.
 * @param[in]  init       True if the key exchange protocol is initiated by local.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_sm2_kex(
		pufs_dgst_st_Type* s2,
		pufs_dgst_st_Type* s3,
		uint8_t* key,
		uint32_t keybits,
		const uint8_t* idl,
		uint32_t idllen,
		const uint8_t* idr,
		uint32_t idrlen,
		pufs_ka_slot_Type prkslotl,
		pufs_ka_slot_Type tprkslotl,
		pufs_ec_point_st_Type pukr,
		pufs_ec_point_st_Type tpukr,
		bool init);
/**
 * @brief SM2 signature verification
 * @param[in]  sig     SM2 signature.
 * @param[in]  msg     Message.
 * @param[in]  msglen  Message length in bytes.
 * @param[in]  id      Identity.
 * @param[in]  idlen   Identity length in bytes.
 * @param[in]  puk     Public key.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_sm2_verify(
		pufs_ecdsa_sig_st_Type sig,
		const uint8_t* msg,
		uint32_t msglen,
		const uint8_t* id,
		uint32_t idlen,
		pufs_ec_point_st_Type puk);

/**
 * @brief SM2 signature signing
 * @param[in]  sig      SM2 signature.
 * @param[in]  msg      Message.
 * @param[in]  msglen   Message length in bytes.
 * @param[in]  id       Identity.
 * @param[in]  idlen    Identity length in bytes.
 * @param[in]  prk  Private key slot.
 * @param[in]  k        Ephemeral private key. k can be NULL.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_sm2_sign(
		pufs_ecdsa_sig_st_Type* sig,
		const uint8_t* msg,
		uint32_t msglen,
		const uint8_t* id,
		uint32_t idlen,
		pufs_ka_slot_Type prk,
		const uint8_t* k);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_SM2_H */
