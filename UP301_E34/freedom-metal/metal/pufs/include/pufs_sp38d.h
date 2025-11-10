/**
 * @file      pufs_sp38d.h
 * @brief     PUFsecurity SP38D API interface
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
#ifndef PUFS_SP38D_H
#define PUFS_SP38D_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_common.h"
#include "pufs_dma.h"
#include "pufs_ka.h"
#include "pufs_sp38d_internal.h"
#include "pufs_isr.h"

typedef enum pufs_gcm_input_data {
    GCM_AAD,
    GCM_PLAINTEXT,
} pufs_gcm_input_data_Type;

typedef struct {
	pufs_sp38d_ctx *ctx;
	uint8_t* out;
	uint32_t* outlen;
	uint32_t* toutlen;
	const uint8_t* in;
	uint32_t inlen;
	pufs_cipher_Type cipher;
	pufs_key_type_Type keytype;
	size_t keyaddr;
	uint32_t keybits;
	const uint8_t* iv;
	uint32_t ivlen;
	const uint8_t* aad;
	uint32_t aadlen;
	uint8_t* tag;
	uint32_t taglen;
	uint32_t *offset;
	bool swIntrptEnable;
} sp38d_async_args_Type;

typedef enum {
	SP38D_ASYNC_IDLE,
	SP38D_ASYNC_BUILD_0,
	SP38D_ASYNC_BUILD_1,
	SP38D_ASYNC_BUILD_2,
	SP38D_ASYNC_BUILD_3,
	SP38D_ASYNC_BUILD_4,
	SP38D_ASYNC_INIT,
	SP38D_ASYNC_AAD_STAGE,
	SP38D_ASYNC_AAD_UPDATE,
	SP38D_ASYNC_TEXT_STAGE,
	SP38D_ASYNC_TEXT_UPDATE,
	SP38D_ASYNC_FINAL,
	SP38D_ASYNC_TAG_0,
	SP38D_ASYNC_TAG_1,
	SP38D_ASYNC_RESULT,
} sp38d_async_step_Type;

pufs_status_Type __sp38d_get_config(uint32_t *cfg, pufs_sp38d_ctx *ctx, bool gctr, bool reg_in, bool reg_out);

/**
 * @brief Post-processing for SP38D operation.
 * @param[in] sp38d_ctx  SP38D context.
 * @return pufs_status_Type value.
 */
pufs_status_Type __sp38d_postproc(pufs_sp38d_ctx* sp38d_ctx);

/**
 * @brief Prepare registers for SP38D operation.
 * @param[in] sp38d_ctx  SP38D context.
 * @param[in] inlen      Input length for the preparing operation.
 * @return pufs_status_Type value.
 */
pufs_status_Type __sp38d_prepare(
		pufs_sp38d_ctx* sp38d_ctx,
		const uint8_t* out,
		uint32_t inlen);

/**
 * @brief Initialize GCM context for GHASH operation.
 * @param[in] sp38d_ctx  SP38D context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @return pufs_status_Type value.
 */
pufs_status_Type sp38d_ghash_init(
		pufs_sp38d_ctx* sp38d_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits);

/**
 * @brief Initialize the internal context for block cipher GCM mode.
 * @param[in] op         GCM operation mode.
 * @param[in] sp38d_ctx  SP38D context to be initialized.
 * @param[in] encrypt    True/false for encryption/decryption
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] j0         J_0
 * @return pufs_status_Type value.
 */
pufs_status_Type __sp38d_ctx_init(
		sp38d_op_Type op,
		pufs_sp38d_ctx* sp38d_ctx,
		bool encrypt,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* j0);

/**
 * @brief Initialize sp38d module.
 * @param[in] sp38d_offset  sp38d offset of memory map.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_sp38d_module_init(uint32_t sp38d_offset);

/**
 * @brief Obtain a pointer to SP38D internal context
 * @return A pointer to SP38D internal context, or NULL if error
 */
pufs_sp38d_ctx* pufs_sp38d_ctx_new(void);

/**
 * @brief Free a pointer to SP38D internal context.
 * @param[in] sp38d_ctx  A pointer to SP38D context.
 */
void pufs_sp38d_ctx_free(pufs_sp38d_ctx* sp38d_ctx);

/**
 * @brief Initialize GCM encryptor.
 * @param[in] sp38d_ctx  SP38D context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] iv         Initial vector.
 * @param[in] ivlen      Initial vector length in bytes.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_gcm_init(sp38d_ctx, cipher, keytype, keyaddr, keybits, iv, ivlen)\
    _pufs_enc_gcm_init(sp38d_ctx, cipher, keytype, (size_t)keyaddr, keybits, iv, ivlen)

/**
 * @brief Initialize GCM encryptor with ISR mode.
 * @param[in] sp38d_ctx  SP38D context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] iv         Initial vector.
 * @param[in] ivlen      Initial vector length in bytes.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_gcm_init_isr(sp38d_ctx, cipher, keytype, keyaddr, keybits, iv, ivlen)\
    _pufs_enc_gcm_init_isr(sp38d_ctx, cipher, keytype, (size_t)keyaddr, keybits, iv, ivlen)

#define pufs_enc_gcm_build_isr(cipher, keytype, keyaddr, keybits, iv, ivlen, stage)\
    _pufs_enc_gcm_build_isr(cipher, keytype, (size_t)keyaddr, keybits, iv, ivlen, stage)

/**
 * @brief GCM encryptor initializer with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_gcm_init() instead.
 */
pufs_status_Type _pufs_enc_gcm_init(
		pufs_sp38d_ctx* sp38d_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		uint32_t ivlen);

/**
 * @brief GCM encryptor initializer with keyaddr type casting with ISR mode.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_gcm_init() instead.
 */
pufs_status_Type _pufs_enc_gcm_init_isr(
		pufs_sp38d_ctx* sp38d_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		uint32_t ivlen);

pufs_status_Type _pufs_enc_gcm_build_isr(
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		uint32_t ivlen,
		uint8_t stage);

/**
 * @brief Input data into GCM encryptor.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 * @note Input data may be either AAD or plaintext. Set \a out to NULL when
 *       input AAD. Complete AAD data must be passed first before the plaintext.
 */
pufs_status_Type pufs_enc_gcm_update(
		pufs_sp38d_ctx* sp38d_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into GCM encryptor with ISR mode.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 * @note Input data may be either AAD or plaintext. Set \a out to NULL when
 *       input AAD. Complete AAD data must be passed first before the plaintext.
 */
pufs_status_Type pufs_enc_gcm_update_isr(
		pufs_sp38d_ctx* sp38d_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

pufs_status_Type pufs_enc_gcm_stage_isr(pufs_sp38d_ctx* sp38d_ctx, sp38d_stage_Type stage);

/**
 * @brief Input SGDMA descriptors into GCM encryptor.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[in]  data_type  The input data type of descriptors.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors.
 * @return pufs_status_Type value.
 * @note Input data may be either AAD or plaintext. 
 *       Complete AAD data must be passed first before the plaintext.
 *       The data length of each descriptor should be 16 * N bytes except the last one.
 *       For example, the length of descriptor could be 32 + 32 + 7.
 *       However, 5 + 5 + 5 is not allowed.
 */
pufs_status_Type pufs_enc_gcm_sg_append(
		pufs_sp38d_ctx *sp38d_ctx,
		pufs_gcm_input_data_Type data_type,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize GCM encryptor.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[out] tag        Output Tag.
 * @param[in]  taglen     Specified output tag length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_gcm_sg_done(pufs_sp38d_ctx *sp38d_ctx, uint8_t *tag, uint32_t taglen);

/**
 * @brief Finalize GCM encryptor.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[out] tag        Output tag.
 * @param[in]  taglen     Specified output tag length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_gcm_final(
		pufs_sp38d_ctx* sp38d_ctx,
		uint8_t* out,
		uint32_t* outlen,
		uint8_t* tag,
		uint32_t taglen);

/**
 * @brief Finalize GCM encryptor with ISR mode.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[out] tag        Output tag.
 * @param[in]  taglen     Specified output tag length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_gcm_final_isr(
		pufs_sp38d_ctx* sp38d_ctx,
		uint8_t* out,
		uint32_t* outlen,
		uint8_t* tag,
		uint32_t taglen);

pufs_status_Type pufs_enc_gcm_tag_isr(
		pufs_sp38d_ctx* sp38d_ctx,
		uint8_t* out,
		uint32_t* outlen,
		uint8_t* tag,
		uint32_t taglen,
		uint8_t stage);

/**
 * @brief Start GCM encryption in asynchronous mode.
 * @param[in]  pufs_sp38d_ctx     SP38D context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding tag.
 * @param[out] toutlen            Total output length including tag.
 * @param[in]  in                 Input plaintext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  iv                 Initialization vector (IV).
 * @param[in]  ivlen              IV length in bytes.
 * @param[in]  aad                Additional authenticated data (AAD).
 * @param[in]  aadlen             AAD length in bytes.
 * @param[out] tag                Generated authentication tag.
 * @param[in]  taglen             Tag length in bytes.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_enc_gcm_async_start (
	pufs_sp38d_ctx *pufs_sp38d_ctx,
	uint8_t* out,
	uint32_t* outlen,
	uint32_t* toutlen,
	const uint8_t* in,
	uint32_t inlen,
	pufs_cipher_Type cipher,
	pufs_key_type_Type keytype,
	size_t keyaddr,
	uint32_t keybits,
	const uint8_t* iv,
	uint32_t ivlen,
	const uint8_t* aad,
	uint32_t aadlen,
	uint8_t* tag,
	uint32_t taglen,
	bool swIntrptEnable
);

/**
 * @brief Check encryption progress status in asynchronous GCM mode.
 * @return Current status of the asynchronous GCM encryption operation.
 */
pufs_module_state_Type pufs_enc_gcm_async_check (void);

/**
 * @brief Encryption using GCM mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @param[in]  iv       Initial vector.
 * @param[in]  ivlen    Initial vector length in bytes.
 * @param[in]  aad      Additional authentication data.
 * @param[in]  aadlen   Additional authentication data length in bytes.
 * @param[out] tag      Output tag.
 * @param[in]  taglen   Specified output tag length in bytes.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_gcm(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     iv, ivlen, aad, aadlen, tag, taglen)\
    _pufs_enc_gcm(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, iv, ivlen, aad, aadlen, tag, taglen)

/**
 * @brief Encryption using GCM mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_gcm() instead.
 */
pufs_status_Type _pufs_enc_gcm(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		uint32_t ivlen,
		const uint8_t* aad,
		uint32_t aadlen,
		uint8_t* tag,
		uint32_t taglen);

/**
 * @brief Initialize GCM decryptor.
 * @param[in] sp38d_ctx  SP38D context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] iv         Initial vector.
 * @param[in] ivlen      Initial vector length in bytes.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_gcm_init(sp38d_ctx, cipher, keytype, keyaddr, keybits, iv, ivlen)\
    _pufs_dec_gcm_init(sp38d_ctx, cipher, keytype, (size_t)keyaddr, keybits, iv, ivlen)

/**
 * @brief Initialize GCM decryptor with ISR mode.
 * @param[in] sp38d_ctx  SP38D context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] iv         Initial vector.
 * @param[in] ivlen      Initial vector length in bytes.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_gcm_init_isr(sp38d_ctx, cipher, keytype, keyaddr, keybits, iv, ivlen)\
    _pufs_dec_gcm_init_isr(sp38d_ctx, cipher, keytype, (size_t)keyaddr, keybits, iv, ivlen)

#define pufs_dec_gcm_build_isr(cipher, keytype, keyaddr, keybits, iv, ivlen, stage)\
    _pufs_dec_gcm_build_isr(cipher, keytype, (size_t)keyaddr, keybits, iv, ivlen, stage)

/**
 * @brief GCM decryptor initializer with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_gcm_init() instead.
 */
pufs_status_Type _pufs_dec_gcm_init(
		pufs_sp38d_ctx* sp38d_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		uint32_t ivlen);

/**
 * @brief GCM decryptor initializer with keyaddr type casting with ISR mode.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_gcm_init() instead.
 */
pufs_status_Type _pufs_dec_gcm_init_isr(
		pufs_sp38d_ctx* sp38d_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		uint32_t ivlen);

pufs_status_Type _pufs_dec_gcm_build_isr(
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		uint32_t ivlen,
		uint8_t stage);

/**
 * @brief Input data into GCM decryptor.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 * @note Input data may be either AAD or plaintext. Set \a out to NULL when
 *       input AAD. Complete AAD data must be passed first before the plaintext.
 */
pufs_status_Type pufs_dec_gcm_update(
		pufs_sp38d_ctx* sp38d_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into GCM decryptor with ISR mode.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 * @note Input data may be either AAD or plaintext. Set \a out to NULL when
 *       input AAD. Complete AAD data must be passed first before the plaintext.
 */
pufs_status_Type pufs_dec_gcm_update_isr(
		pufs_sp38d_ctx* sp38d_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

pufs_status_Type pufs_dec_gcm_stage_isr(pufs_sp38d_ctx* sp38d_ctx, sp38d_stage_Type stage);

/**
 * @brief Input SGDMA descriptors into GCM decryptor.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[in]  data_type  The input data type of descriptors.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors.
 * @return pufs_status_Type value.
 * @note Input data may be either AAD or plaintext.
 *       Complete AAD data must be passed first before the plaintext.
 *       The data length of each descriptor should be 16 * N bytes except the last one.
 *       For example, the length of descriptor could be 32 + 32 + 7.
 *       However, 5 + 5 + 5 is not allowed.
 */
pufs_status_Type pufs_dec_gcm_sg_append(
		pufs_sp38d_ctx* sp38d_ctx,
		pufs_gcm_input_data_Type data_type,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize GCM decryptor.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[out] tag        Input tag.
 * @param[in]  taglen     Specified input tag length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_gcm_sg_done(pufs_sp38d_ctx *sp38d_ctx, const uint8_t *tag, uint32_t taglen);

/**
 * @brief Finalize GCM decryptor with tag output.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[out] tag        Output tag.
 * @param[in]  taglen     Specified input tag length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_gcm_final_tag(
		pufs_sp38d_ctx* sp38d_ctx,
		uint8_t* out,
		uint32_t* outlen,
		uint8_t* tag,
		uint32_t taglen);

/**
 * @brief Finalize GCM decryptor.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  tag        Input tag.
 * @param[in]  taglen     Specified input tag length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_gcm_final(
		pufs_sp38d_ctx* sp38d_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* tag,
		uint32_t taglen);

/**
 * @brief Finalize GCM decryptor with ISR mode.
 * @param[in]  sp38d_ctx  SP38D context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  tag        Input tag.
 * @param[in]  taglen     Specified input tag length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_gcm_final_isr(
		pufs_sp38d_ctx* sp38d_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* tag,
		uint32_t taglen);

pufs_status_Type pufs_dec_gcm_tag_isr(
		pufs_sp38d_ctx* sp38d_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* tag,
		uint32_t taglen,
		uint8_t stage);

/**
 * @brief Start GCM decryption in asynchronous mode.
 * @param[in]  pufs_sp38d_ctx     SP38D context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding tag.
 * @param[out] toutlen            Total output length including tag.
 * @param[in]  in                 Input ciphertext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  iv                 Initialization vector (IV).
 * @param[in]  ivlen              IV length in bytes.
 * @param[in]  aad                Additional authenticated data (AAD).
 * @param[in]  aadlen             AAD length in bytes.
 * @param[in]  tag                Expected authentication tag.
 * @param[in]  taglen             Tag length in bytes.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_dec_gcm_async_start (
	pufs_sp38d_ctx *pufs_sp38d_ctx,
	uint8_t* out,
	uint32_t* outlen,
	uint32_t* toutlen,
	const uint8_t* in,
	uint32_t inlen,
	pufs_cipher_Type cipher,
	pufs_key_type_Type keytype,
	size_t keyaddr,
	uint32_t keybits,
	const uint8_t* iv,
	uint32_t ivlen,
	const uint8_t* aad,
	uint32_t aadlen,
	const uint8_t* tag,
	uint32_t taglen,
	bool swIntrptEnable
);

/**
 * @brief Check decryption progress status in asynchronous GCM mode.
 * @return Current status of the asynchronous GCM decryption operation.
 */
pufs_module_state_Type pufs_dec_gcm_async_check (void);

/**
 * @brief Decryption using GCM mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @param[in]  iv       Initial vector.
 * @param[in]  ivlen    Initial vector length in bytes.
 * @param[in]  aad      Additional authentication data.
 * @param[in]  aadlen   Additional authentication data length in bytes.
 * @param[in]  tag      Input tag.
 * @param[in]  taglen   Specified input tag length in bytes.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_gcm(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     iv, ivlen, aad, aadlen, tag, taglen)\
    _pufs_dec_gcm(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, iv, ivlen, aad, aadlen, tag, taglen)

/**
 * @brief Decryption using GCM mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_gcm() instead.
 */
pufs_status_Type _pufs_dec_gcm(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		int ivlen,
		const uint8_t* aad,
		int aadlen,
		const uint8_t* tag,
		int taglen);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_SP38D_H */
