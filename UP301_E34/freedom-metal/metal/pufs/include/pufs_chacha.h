/**
 * @file      pufs_chacha.h
 * @brief     PUFsecurity ChaCha API interface
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
#ifndef UPT_PUFS_CHACHA_H
#define UPT_PUFS_CHACHA_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_common.h"
#include "pufs_ka.h"
#include "pufs_dma.h"
#include "pufs_isr.h"

/*****************************************************************************
 * Type definitions
 ****************************************************************************/
typedef struct pufs_chacha_context pufs_chacha_ctx;

typedef enum {
    CHACHA_AEAD_AAD,
    CHACHA_AEAD_PLAINTEXT,
} pufs_chacha_aead_data_t;

/**
 * @brief required parameters for chacha algorithm
 */
typedef struct chacha_params {
	pufs_key_type_Type keytype; ///< Key type
   /** @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
    *            element, or a memory address according to the \em keytype setting.
    *  @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
    */
    size_t          keyaddr;  ///< Key address
    uint32_t        keybits;  ///< Key length in bits
    const uint8_t*  iv;       ///< Initial vector
    uint32_t        ivlen;    ///< Initial vector length in bytes
    uint32_t        counter;  ///< Initial block counter
    // @note the default value of round is 20
    uint32_t        round;    ///< Initial quarter rounds
} pufs_chacha_params_st;

/**
 * @brief required parameters for chacha20-poly1305 algorithm
 */
typedef struct chacha20_poly1305_params {
	pufs_key_type_Type keytype;  ///< Key type
   /** @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
    *            element, or a memory address according to the \em keytype setting.
    *  @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
    */
    size_t          keyaddr;  ///< Key address
    uint32_t        keybits;  ///< Key length in bits
    const uint8_t*  iv;       ///< Initial vector
    uint32_t        ivlen;    ///< Initial vector length in bytes
} pufs_chacha20_poly1305_params_st;

/**
 * @brief required parameters for poly1305 algorithm
 */
typedef struct poly1305_params {
	pufs_key_type_Type keytype;  ///< Key type
   /** @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
    *            element, or a memory address according to the \em keytype setting.
    *  @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
    */
    size_t          keyaddr;  ///< Key address
    uint32_t        keybits;  ///< Key length in bits
} pufs_poly1305_params_st;

typedef struct {
	pufs_chacha_ctx *ctx;
	pufs_chacha_params_st *params;
	pufs_chacha20_poly1305_params_st *paramsPoly;
	uint8_t *out;
	uint32_t *outlen;
	uint32_t *toutlen;
	uint8_t *tag;
	const uint8_t *aad;
	uint32_t aadlen;
	const uint8_t *in;
	uint32_t inlen;
	bool swIntrptEnable;
} chacha_async_args_Type;

typedef enum {
	CHACHA_ASYNC_IDLE,
	CHACHA_ASYNC_INIT,
	CHACHA_ASYNC_UPDATE,
	CHACHA_ASYNC_AAD_UPDATE,
	CHACHA_ASYNC_TEXT_UPDATE,
	CHACHA_ASYNC_FINAL,
	CHACHA_ASYNC_TAG,
	CHACHA_ASYNC_RESULT,
} chacha_async_step_Type;

/*****************************************************************************
 * API functions
 ****************************************************************************/
/**
 * @brief Initialize ChaCha module.
 * @param[in] chacha_offset  ChaCha offset of memory map.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_module_init(uint32_t chacha_offset);

/**
 * @brief Obtain a pointer to ChaCha internal context.
 * @return A pointer to ChaCha internal context, or NULL if error.
 */
pufs_chacha_ctx* pufs_chacha_ctx_new(void);

/**
 * @brief Free a pointer to ChaCha internal context.
 * @param[in] chacha_ctx  A pointer to ChaCha context.
 * @remarks no return value.
 */
void pufs_chacha_ctx_free(pufs_chacha_ctx *chacha_ctx);

/**
 * @brief Initialize ChaCha encryptor.
 * @param[in] chacha_ctx  ChaCha context to be initialized.
 * @param[in] params      Parameters for ChaCha algorithm.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_enc_init(
		pufs_chacha_ctx *chacha_ctx,
		pufs_chacha_params_st *params);

/**
 * @brief Input data into ChaCha encryptor.
 * @param[in]  chacha_ctx  ChaCha context.
 * @param[out] out         Output data.
 * @param[out] outlen      Output data length in bytes.
 * @param[in]  in          Input data.
 * @param[in]  inlen       Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_enc_update(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		const uint8_t *in,
		uint32_t inlen);

/**
 * @brief Input data into ChaCha encryptor with ISR mode.
 * @param[in]  chacha_ctx  ChaCha context.
 * @param[out] out         Output data.
 * @param[out] outlen      Output data length in bytes.
 * @param[in]  in          Input data.
 * @param[in]  inlen       Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_enc_update_isr(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		const uint8_t *in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into ChaCha encryptor.
 * @param[in]  chacha_ctx  ChaCha context.
 * @param[in]  descs       Input arrays of SGDMA descriptors.
 * @param[in]  descs_len   The length of SGDMA descriptor array.
 * @param[in]  last        set true if there is no more incoming descriptors.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_enc_sg_append(
		pufs_chacha_ctx *chacha_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize ChaCha encryptor.
 * @param[in] chacha_ctx  ChaCha context.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_enc_sg_done(pufs_chacha_ctx *chacha_ctx);

/**
 * @brief Finalize ChaCha encryptor.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data. (set to NULL if using SGDMA descriptor)
 * @param[out] outlen     Output data length in bytes. (set to 0 if using SGDMA descriptor)
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_enc_final(pufs_chacha_ctx *chacha_ctx,
                                    uint8_t *out,
                                    uint32_t *outlen);

/**
 * @brief Finalize ChaCha encryptor with ISR mode.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data. (set to NULL if using SGDMA descriptor)
 * @param[out] outlen     Output data length in bytes. (set to 0 if using SGDMA descriptor)
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_enc_final_isr(pufs_chacha_ctx *chacha_ctx,
                                    uint8_t *out,
                                    uint32_t *outlen);

/**
 * @brief Start ChaCha encryption in asynchronous mode.
 * @param[in]  chacha_ctx         ChaCha context.
 * @param[in]  params             Encryption parameters (key, nonce, counter, etc.).
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding MAC (if applicable).
 * @param[out] toutlen            Total output length including MAC (if applicable).
 * @param[in]  in                 Input plaintext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_enc_chacha_async_start (
	pufs_chacha_ctx *chacha_ctx,
	pufs_chacha_params_st *params,
	uint8_t *out,
	uint32_t *outlen,
	uint32_t* toutlen,
	const uint8_t *in,
	uint32_t inlen,
	bool swIntrptEnable);

/**
 * @brief Check encryption progress status in asynchronous ChaCha mode.
 * @return Current status of the asynchronous ChaCha encryption operation.
 */
pufs_module_state_Type pufs_enc_chacha_async_check (void);

/**
 * @brief Encryption using ChaCha algorithm.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  params   Parameters for ChaCha algorithm.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_enc(
		uint8_t *out,
		uint32_t *outlen,
		pufs_chacha_params_st *params,
		const uint8_t *in,
		uint32_t inlen);

/**
 * @brief Initialize ChaCha decryptor.
 * @param[in] chacha_ctx  ChaCha context to be initialized.
 * @param[in] params      Parameters for ChaCha algorithm.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_dec_init(
		pufs_chacha_ctx *chacha_ctx,
		pufs_chacha_params_st *params);

/**
 * @brief Input data into ChaCha decryptor.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_dec_update(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		const uint8_t *in,
		uint32_t inlen);

/**
 * @brief Input data into ChaCha decryptor with ISR mode.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_dec_update_isr(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		const uint8_t *in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into ChaCha decryptor.
 * @param[in]  chacha_ctx  ChaCha context.
 * @param[in]  descs       Input arrays of SGDMA descriptors.
 * @param[in]  descs_len   The length of SGDMA descriptor array.
 * @param[in]  last        set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_dec_sg_append(
		pufs_chacha_ctx *chacha_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize ChaCha decryptor.
 * @param[in]  chacha_ctx  ChaCha context.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_dec_sg_done(pufs_chacha_ctx *chacha_ctx);

/**
 * @brief Finalize ChaCha decryptor.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data. (set to NULL if using SGDMA descriptor)
 * @param[out] outlen     Output data length in bytes. (set to 0 if using SGDMA descriptor)
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_dec_final(pufs_chacha_ctx *chacha_ctx,
                                    uint8_t *out,
                                    uint32_t *outlen);

/**
 * @brief Finalize ChaCha decryptor with ISR mode.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data. (set to NULL if using SGDMA descriptor)
 * @param[out] outlen     Output data length in bytes. (set to 0 if using SGDMA descriptor)
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_dec_final_isr(pufs_chacha_ctx *chacha_ctx, uint8_t *out, uint32_t *outlen);

/**
 * @brief Start ChaCha decryption in asynchronous mode.
 * @param[in]  chacha_ctx         ChaCha context.
 * @param[in]  params             Decryption parameters (key, nonce, counter, etc.).
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding MAC (if applicable).
 * @param[out] toutlen            Total output length including MAC (if applicable).
 * @param[in]  in                 Input ciphertext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_dec_chacha_async_start (
	pufs_chacha_ctx *chacha_ctx,
	pufs_chacha_params_st *params,
	uint8_t *out,
	uint32_t *outlen,
	uint32_t* toutlen,
	const uint8_t *in,
	uint32_t inlen,
	bool swIntrptEnable);

	
/**
 * @brief Check decryption progress status in asynchronous ChaCha mode.
 * @return Current status of the asynchronous ChaCha decryption operation.
 */
pufs_module_state_Type pufs_dec_chacha_async_check (void);

/**
 * @brief Decryption using ChaCha algorithm.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  params   Parameters for ChaCha algorithm.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha_dec(
		uint8_t *out,
		uint32_t *outlen,
		pufs_chacha_params_st *params,
		const uint8_t *in,
		uint32_t inlen);

/**
 * @brief Initialize ChaCha20-Poly1305 encryptor.
 * @param[in] chacha_ctx  ChaCha context to be initialized.
 * @param[in] params      Parameters for ChaCha20-Poly1305 algorithm.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_enc_init(
		pufs_chacha_ctx *chacha_ctx,
		pufs_chacha20_poly1305_params_st *params);

/**
 * @brief Input data into ChaCha20-Poly1305 encryptor.
 * @param[in]  chacha_ctx  ChaCha context.
 * @param[out] out         Output data.
 * @param[out] outlen      Output data length in bytes.
 * @param[in]  in          Input data.
 * @param[in]  inlen       Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_enc_update(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		const uint8_t *in,
		uint32_t inlen);

/**
 * @brief Input data into ChaCha20-Poly1305 encryptor with ISR mode.
 * @param[in]  chacha_ctx  ChaCha context.
 * @param[out] out         Output data.
 * @param[out] outlen      Output data length in bytes.
 * @param[in]  in          Input data.
 * @param[in]  inlen       Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_enc_update_isr(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		const uint8_t *in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into ChaCha20-Poly1305 encryptor.
 * @param[in]  chacha_ctx  ChaCha context.
 * @param[in]  data_type   The input data type of descriptors.
 * @param[in]  descs       Input arrays of SGDMA descriptors.
 * @param[in]  descs_len   The length of SGDMA descriptor array.
 * @param[in]  last        set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_enc_sg_append(
		pufs_chacha_ctx *chacha_ctx,
		pufs_chacha_aead_data_t data_type,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize ChaCha20-Poly1305 encryptor
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] tag        Output Tag.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_enc_sg_done(pufs_chacha_ctx *chacha_ctx, uint8_t *tag);

/**
 * @brief Finalize ChaCha20-Poly1305 encryptor.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data. (set to NULL if using SGDMA descriptor)
 * @param[out] outlen     Output data length in bytes. (set to 0 if using SGDMA descriptor)
 * @param[out] tag        Output Tag.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_enc_final(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		uint8_t *tag);

/**
 * @brief Finalize ChaCha20-Poly1305 encryptor with ISR mode.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data. (set to NULL if using SGDMA descriptor)
 * @param[out] outlen     Output data length in bytes. (set to 0 if using SGDMA descriptor)
 * @param[out] tag        Output Tag.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_enc_final_isr(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		uint8_t *tag);

pufs_status_Type pufs_chacha20_poly1305_enc_tag_isr(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		uint8_t *tag);

/**
 * @brief Start ChaCha20-Poly1305 encryption in asynchronous mode.
 * @param[in]  chacha_ctx         ChaCha20-Poly1305 context.
 * @param[in]  params             Encryption parameters (key, nonce, counter, etc.).
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding tag.
 * @param[out] toutlen            Total output length including tag.
 * @param[out] tag                Authentication tag output buffer (16 bytes).
 * @param[in]  in                 Input plaintext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  aad                Additional authenticated data.
 * @param[in]  aadlen             Length of AAD in bytes.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_enc_chacha20_poly1305_async_start (
	pufs_chacha_ctx *chacha_ctx,
	pufs_chacha20_poly1305_params_st *params,
	uint8_t *out,
	uint32_t *outlen,
	uint32_t *toutlen,
	uint8_t *tag,
	const uint8_t *in,
	uint32_t inlen,
	const uint8_t *aad,
	uint32_t aadlen,
	bool swIntrptEnable
);

/**
 * @brief Check encryption progress status in asynchronous ChaCha20-Poly1305 mode.
 * @return Current status of the asynchronous ChaCha20-Poly1305 encryption operation.
 */
pufs_module_state_Type pufs_enc_chacha20_poly1305_async_check (void);

/**
 * @brief Encryption using ChaCha20-Poly1305 algorithm.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[out] tag      Output Tag.
 * @param[in]  params   Parameters for ChaCha20-Poly1305 algorithm.
 * @param[in]  aad      Additional authenticated data.
 * @param[in]  aadlen   The length of additional authenticated data.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_enc(
		uint8_t *out,
		uint32_t *outlen,
		uint8_t *tag,
		pufs_chacha20_poly1305_params_st *params,
		const uint8_t *aad,
		uint32_t aadlen,
		const uint8_t *in,
		uint32_t inlen);

/**
 * @brief Initialize ChaCha20-Poly1305 decryptor.
 * @param[in] chacha_ctx  ChaCha context to be initialized.
 * @param[in] params      Parameters for ChaCha20-Poly1305 algorithm.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_dec_init(
		pufs_chacha_ctx *chacha_ctx,
		pufs_chacha20_poly1305_params_st *params);

/**
 * @brief Input data into ChaCha20-Poly1305 decryptor.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_dec_update(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		const uint8_t *in,
		uint32_t inlen);

/**
 * @brief Input data into ChaCha20-Poly1305 decryptor with ISR mode.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_dec_update_isr(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		const uint8_t *in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into ChaCha20-Poly1305 decryptor.
 * @param[in]  chacha_ctx  ChaCha context.
 * @param[in]  data_type   The input data type of descriptors.
 * @param[in]  descs       Input arrays of SGDMA descriptors.
 * @param[in]  descs_len   The length of SGDMA descriptor array.
 * @param[in]  last        set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_dec_sg_append(
		pufs_chacha_ctx *chacha_ctx,
		pufs_chacha_aead_data_t data_type,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize ChaCha20-Poly1305 decryptor.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[in]  tag        Input tag.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_dec_sg_done(pufs_chacha_ctx *chacha_ctx, const uint8_t *tag);

/**
 * @brief Finalize ChaCha20-Poly1305 decryptor.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data. (set to NULL if using SGDMA descriptor)
 * @param[out] outlen     Output data length in bytes. (set to 0 if using SGDMA descriptor)
 * @param[in]  tag        Input tag.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_dec_final(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		const uint8_t* tag);

/**
 * @brief Finalize ChaCha20-Poly1305 decryptor with ISR mode.
 * @param[in]  chacha_ctx ChaCha context.
 * @param[out] out        Output data. (set to NULL if using SGDMA descriptor)
 * @param[out] outlen     Output data length in bytes. (set to 0 if using SGDMA descriptor)
 * @param[in]  tag        Input tag.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_dec_final_isr(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		const uint8_t* tag);

pufs_status_Type pufs_chacha20_poly1305_dec_tag_isr(
		pufs_chacha_ctx *chacha_ctx,
		uint8_t *out,
		uint32_t *outlen,
		const uint8_t* tag);

/**
 * @brief Start ChaCha20-Poly1305 decryption in asynchronous mode.
 * @param[in]  chacha_ctx         ChaCha20-Poly1305 context.
 * @param[in]  paramsPoly         Decryption parameters (key, nonce, counter, etc.).
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding tag.
 * @param[out] toutlen            Total output length including tag.
 * @param[in]  tag                Authentication tag (16 bytes) to verify.
 * @param[in]  aad                Additional authenticated data.
 * @param[in]  aadlen             Length of AAD in bytes.
 * @param[in]  in                 Input ciphertext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_dec_chacha20_poly1305_async_start (
	pufs_chacha_ctx *chacha_ctx,
	pufs_chacha20_poly1305_params_st *paramsPoly,
	uint8_t *out,
	uint32_t *outlen,
	uint32_t *toutlen,
	uint8_t *tag,
	const uint8_t *aad,
	uint32_t aadlen,
	const uint8_t *in,
	uint32_t inlen,
	bool swIntrptEnable
);

/**
 * @brief Check decryption progress status in asynchronous ChaCha20-Poly1305 mode.
 * @return Current status of the asynchronous ChaCha20-Poly1305 decryption operation.
 */
pufs_module_state_Type pufs_dec_chacha20_poly1305_async_check (void);

/**
 * @brief Decryption using ChaCha20-Poly1305 algorithm.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  params   Parameters for ChaCha20-Poly1305 algorithm.
 * @param[in]  aad      Additional authenticated data.
 * @param[in]  aadlen   The length of additional authenticated data.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  tag      Input tag.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_chacha20_poly1305_dec(
		uint8_t *out,
		uint32_t *outlen,
		pufs_chacha20_poly1305_params_st *params,
		const uint8_t *aad,
		uint32_t aadlen,
		const uint8_t *in,
		uint32_t inlen,
		const uint8_t *tag);

/**
 * @brief Produce a tag for authentication using Poly1305 algorithm.
 * @param[out] tag      Output tag.
 * @param[in]  params   Parameters for Poly1305 algorithm.
 * @param[in]  in       Input message.
 *  @param[in] inlen    Input message length in bytes.
 * @return              SUCCESS on success, otherwise an error code.
 */
pufs_status_Type pufs_poly1305(
		uint8_t *tag,
		pufs_poly1305_params_st *params,
		const uint8_t *in,
		const uint32_t inlen);


#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* UPT_PUFS_CHACHA_H */
