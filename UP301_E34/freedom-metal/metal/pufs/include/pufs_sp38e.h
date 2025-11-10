/**
 * @file      pufs_sp38e.h
 * @brief     PUFsecurity SP38E API interface
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

#ifndef PUFS_SP38E_H
#define PUFS_SP38E_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_common.h"
#include "pufs_dma.h"
#include "pufs_ka.h"
#include "pufs_sp38e_internal.h"
#include "pufs_isr.h"

typedef struct {
	pufs_sp38e_ctx *ctx;
	uint8_t* out;
	uint32_t* outlen;
	uint32_t* toutlen;
	const uint8_t* in;
	uint32_t inlen;
	pufs_cipher_Type cipher;
	pufs_key_type_Type keytype1;
	size_t keyaddr1;
	pufs_key_type_Type keytype2;
	size_t keyaddr2;
	uint32_t keybits;
	bool swIntrptEnable;
	const uint8_t* i;
	uint32_t j;
} sp38e_async_args_Type;

typedef enum {
	SP38E_ASYNC_IDLE,
	SP38E_ASYNC_INIT,
	SP38E_ASYNC_TWEAK,
	SP38E_ASYNC_UPDATE,
	SP38E_ASYNC_FINAL,
	SP38E_ASYNC_RESULT,
} sp38e_async_step_Type;

/**
 * @brief Prepare registers for SP38E operation.
 * @param[in] sp38e_ctx  SP38E context.
 * @return pufs_status_Type value.
 */
pufs_status_Type __sp38e_prepare(pufs_sp38e_ctx* sp38e_ctx);

/**
 * @brief Initialize sp38e module.
 * @param[in] sp38e_offset  sp38e offset of memory map.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_sp38e_module_init(uint32_t sp38e_offset);

/**
 * @brief Obtain a pointer to SP38E internal context.
 * @return A pointer to SP38E internal context, or NULL if error.
 */
pufs_sp38e_ctx* pufs_sp38e_ctx_new(void);

/**
 * @brief Free a pointer to SP38E internal context.
 * @param[in] sp38e_ctx  A pointer to SP38E context.
 */
void pufs_sp38e_ctx_free(pufs_sp38e_ctx* sp38e_ctx);

/**
 * @brief Initialize XTS encryptor.
 * @param[in] sp38e_ctx  SP38E context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype1   Key1 key type.
 * @param[in] keyaddr1   Key1 key address.
 * @param[in] keybits    Each key length in bits.
 * @param[in] keytype2   Key2 key type.
 * @param[in] keyaddr2   Key2 key address.
 * @param[in] i          Tweak value.
 * @param[in] j          Sequence number of the first input data.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_xts_init(sp38e_ctx, cipher, keytype1, keyaddr1, keybits, \
                          keytype2, keyaddr2, i, j) \
    _pufs_enc_xts_init(sp38e_ctx, cipher, keytype1, (size_t)keyaddr1, keybits, \
                       keytype2, (size_t)keyaddr2, i, j)

/**
 * @brief XTS encryptor initializer with keyaddr type casting.
 * @warning DO NOT call this function directly. Use pufs_enc_xts_init() instead.
 */
pufs_status_Type _pufs_enc_xts_init(
		pufs_sp38e_ctx* sp38e_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype1,
		size_t keyaddr1,
		uint32_t keybits,
		pufs_key_type_Type keytype2,
		size_t keyaddr2,
		const uint8_t* i,
		uint32_t j);

/**
 * @brief Input data into XTS encryptor.
 * @param[in]  sp38e_ctx  SP38E context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_xts_update(
		pufs_sp38e_ctx* sp38e_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into XTS encryptor with ISR mode.
 * @param[in]  sp38e_ctx  SP38E context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_xts_tweak_isr(
		pufs_sp38e_ctx* sp38e_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

pufs_status_Type pufs_enc_xts_update_isr(
		pufs_sp38e_ctx* sp38e_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into XTS encryptor.
 * @param[in] sp38e_ctx  SP38E context.
 * @param[in] descs      SGDMA descriptors.
 * @param[in] descs_len  the length of SGDMA descriptors.
 * @param[in] last       set true if there is no more incoming descriptors.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_xts_sg_append(
		pufs_sp38e_ctx *sp38e_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize XTS encryptor.
 * @param[in] sp38e_ctx  SP38E context.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_xts_sg_done(pufs_sp38e_ctx *sp38e_ctx);

/**
 * @brief Finalize XTS encryptor.
 * @param[in]  sp38e_ctx  SP38E context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_xts_final(
		pufs_sp38e_ctx* sp38e_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Finalize XTS encryptor with ISR mode.
 * @param[in]  sp38e_ctx  SP38E context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_xts_final_isr(
		pufs_sp38e_ctx* sp38e_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start XTS encryption in asynchronous mode.
 * @param[in]  pufs_sp38e_ctx     SP38E context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding tweak.
 * @param[out] toutlen            Total output length including tweak.
 * @param[in]  in                 Input plaintext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype1           Key type for data encryption.
 * @param[in]  keyaddr1           Key address for data encryption.
 * @param[in]  keytype2           Key type for tweak encryption.
 * @param[in]  keyaddr2           Key address for tweak encryption.
 * @param[in]  keybits            Key length in bits (per key).
 * @param[in]  i                  16-byte tweak value (usually sector number).
 * @param[in]  j                  32-bit tweak counter.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_enc_xts_async_start (
	pufs_sp38e_ctx *pufs_sp38e_ctx,
	uint8_t* out,
	uint32_t* outlen,
	uint32_t* toutlen,
	const uint8_t* in,
	uint32_t inlen,
	pufs_cipher_Type cipher,
	pufs_key_type_Type keytype1,
	size_t keyaddr1,
	pufs_key_type_Type keytype2,
	size_t keyaddr2,
	uint32_t keybits,
	const uint8_t* i,
	uint32_t j,
	bool swIntrptEnable
);


/**
 * @brief Check encryption progress status in asynchronous XTS mode.
 * @return Current status of the asynchronous XTS encryption operation.
 */
pufs_module_state_Type pufs_enc_xts_async_check (void);

/**
 * @brief Encryption using XTS mode.
 * @param[out] out       Output data.
 * @param[out] outlen    Output data length in bytes.
 * @param[in]  in        Input data.
 * @param[in]  inlen     Input data length in bytes.
 * @param[in]  cipher    Block cipher algorithm.
 * @param[in]  keytype1  Key1 key type.
 * @param[in]  keyaddr1  Key1 key address.
 * @param[in]  keybits   Each key length in bits.
 * @param[in]  keytype2  Key2 key type.
 * @param[in]  keyaddr2  Key2 key address.
 * @param[in]  i         Tweak value.
 * @param[in]  j         Sequence number of the first input data.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_xts(out, outlen, in, inlen, cipher, keytype1, keyaddr1, \
                     keybits, keytype2, keyaddr2, i, j) \
    _pufs_enc_xts(out, outlen, in, inlen, cipher, keytype1, (size_t)keyaddr1,\
                  keybits, keytype2, (size_t)keyaddr2, i, j)

/**
 * @brief Encryption using XTS mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_xts() instead.
 */
pufs_status_Type _pufs_enc_xts(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype1,
		size_t keyaddr1,
		uint32_t keybits,
		pufs_key_type_Type keytype2,
		size_t keyaddr2,
		const uint8_t* i,
		uint32_t j);

/**
 * @brief Initialize XTS decryptor.
 * @param[in] sp38e_ctx  SP38E context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype1   Key1 key type.
 * @param[in] keyaddr1   Key1 key address.
 * @param[in] keybits    Each key length in bits.
 * @param[in] keytype2   Key2 key type.
 * @param[in] keyaddr2   Key2 key address.
 * @param[in] i          Tweak value.
 * @param[in] j          Sequence number of the first input data.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_xts_init(sp38e_ctx, cipher, keytype1, keyaddr1, keybits, \
                          keytype2, keyaddr2, i, j) \
    _pufs_dec_xts_init(sp38e_ctx, cipher, keytype1, (size_t)keyaddr1, keybits, \
                       keytype2, (size_t)keyaddr2, i, j)

/**
 * @brief XTS decryptor initializer with keyaddr type casting
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_xts_init() instead.
 */
pufs_status_Type _pufs_dec_xts_init(
		pufs_sp38e_ctx* sp38e_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype1,
		size_t keyaddr1,
		uint32_t keybits,
		pufs_key_type_Type keytype2,
		size_t keyaddr2,
		const uint8_t* i,
		uint32_t j);

/**
 * @brief Input data into XTS decryptor.
 * @param[in]  sp38e_ctx  SP38E context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_xts_update(
		pufs_sp38e_ctx* sp38e_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into XTS decryptor with ISR mode.
 * @param[in]  sp38e_ctx  SP38E context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_xts_tweak_isr(
		pufs_sp38e_ctx* sp38e_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

pufs_status_Type pufs_dec_xts_update_isr(
		pufs_sp38e_ctx* sp38e_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into XTS decryptor.
 * @param[in] sp38e_ctx  SP38E context.
 * @param[in] descs      SGDMA descriptors.
 * @param[in] descs_len  the length of SGDMA descriptors.
 * @param[in] last       set true if there is no more incoming descriptors.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_xts_sg_append(
		pufs_sp38e_ctx *sp38e_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize XTS encryptor.
 * @param[in]  sp38e_ctx  SP38E context.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_xts_sg_done(pufs_sp38e_ctx *sp38e_ctx);

/**
 * @brief Finalize XTS decryptor.
 * @param[in]  sp38e_ctx  SP38E context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_xts_final(
		pufs_sp38e_ctx* sp38e_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Finalize XTS decryptor with ISR mode.
 * @param[in]  sp38e_ctx  SP38E context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_xts_final_isr(
		pufs_sp38e_ctx* sp38e_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start XTS decryption in asynchronous mode.
 * @param[in]  pufs_sp38e_ctx     SP38E context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding tweak.
 * @param[out] toutlen            Total output length including tweak.
 * @param[in]  in                 Input ciphertext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype1           Key type for data decryption.
 * @param[in]  keyaddr1           Key address for data decryption.
 * @param[in]  keytype2           Key type for tweak decryption.
 * @param[in]  keyaddr2           Key address for tweak decryption.
 * @param[in]  keybits            Key length in bits (per key).
 * @param[in]  i                  16-byte tweak value (typically sector number).
 * @param[in]  j                  32-bit tweak counter.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_dec_xts_async_start (
	pufs_sp38e_ctx *pufs_sp38e_ctx,
	uint8_t* out,
	uint32_t* outlen,
	uint32_t* toutlen,
	const uint8_t* in,
	uint32_t inlen,
	pufs_cipher_Type cipher,
	pufs_key_type_Type keytype1,
	size_t keyaddr1,
	pufs_key_type_Type keytype2,
	size_t keyaddr2,
	uint32_t keybits,
	const uint8_t* i,
	uint32_t j,
	bool swIntrptEnable
);

/**
 * @brief Check decryption progress status in asynchronous XTS mode.
 * @return Current status of the asynchronous XTS decryption operation.
 */
pufs_module_state_Type pufs_dec_xts_async_check (void);

/**
 * @brief Decryption using XTS mode.
 * @param[out] out       Output data.
 * @param[out] outlen    Output data length in bytes.
 * @param[in]  in        Input data.
 * @param[in]  inlen     Input data length in bytes.
 * @param[in]  cipher    Block cipher algorithm.
 * @param[in]  keytype1  Key1 key type.
 * @param[in]  keyaddr1  Key1 key address.
 * @param[in]  keybits   Each key length in bits.
 * @param[in]  keytype2  Key2 key type.
 * @param[in]  keyaddr2  Key2 key address.
 * @param[in]  i         Initial vector.
 * @param[in]  j         Ciphertext-stealing mode.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_xts(out, outlen, in, inlen, cipher, keytype1, keyaddr1, \
                     keybits, keytype2, keyaddr2, i, j) \
    _pufs_dec_xts(out, outlen, in, inlen, cipher, keytype1, (size_t)keyaddr1,\
                  keybits, keytype2, (size_t)keyaddr2, i, j)

/**
 * @brief Decryption using XTS mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_xts() instead.
 */
pufs_status_Type _pufs_dec_xts(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype1,
		size_t keyaddr1,
		uint32_t keybits,
		pufs_key_type_Type keytype2,
		size_t keyaddr2,
		const uint8_t* i,
		uint32_t j);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_SP38E_H */
