/**
 * @file      pufs_sp38a.h
 * @brief     PUFsecurity SP38A API interface
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
#ifndef PUFS_SP38A_H
#define PUFS_SP38A_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_common.h"
#include "pufs_dma.h"
#include "pufs_ka.h"
#include "pufs_sp38a_internal.h"
#include "pufs_isr.h"

typedef struct {
	pufs_sp38a_ctx *ctx;
	uint8_t* out;
	uint32_t* outlen;
	uint32_t* toutlen;
	uint8_t* in;
	uint32_t inlen;
	pufs_cipher_Type cipher;
	pufs_key_type_Type keytype;
	size_t keyaddr;
	uint32_t keybits;
	bool swIntrptEnable;
	const uint8_t* iv;
	int csmode;
} sp38a_async_args_Type;

typedef enum {
	SP38A_ASYNC_IDLE,
	SP38A_ASYNC_INIT,
	SP38A_ASYNC_UPDATE,
	SP38A_ASYNC_FINAL,
	SP38A_ASYNC_RESULT,
} sp38a_async_step_Type;

typedef enum {
	SP38A_UPDATE,
	SP38A_FINAL,
} sp38a_update_Type;

typedef struct {
	bool last;
	pufs_sp38a_ctx *ctx;
	uint8_t *outbuf;
	uint32_t *outlen;
	uint32_t *outlenTemp;
	uint32_t inlen;
	sp38a_update_Type update;
} sp38a_isr_args_Type;

/**
 * @brief Enable or disable the PUF SP38A interrupt.
 *
 * @param enable Set to 1 to enable the interrupt, 0 to disable.
 */
void enable_puf_sp38a_isr(uint8_t enable);

void puf_sp38a_isr_handler(uint16_t id, sp38a_isr_args_Type *data);

/**
 * @brief Prepare registers for SP38A operation
 * @param[in] sp38a_ctx  SP38A context.
 * @return pufs_status_Type value.
 */
pufs_status_Type __sp38a_prepare(pufs_sp38a_ctx* sp38a_ctx);

pufs_status_Type sp38a_postproc(pufs_sp38a_ctx* sp38a_ctx);

/**
 * @brief Check whether two op's are the same type
 * @param[in] opf    sp38a_op_Type of function parameter
 * @param[in] opctx  sp38a_op_Type in sp38a_ctx
 * @return           true if the same type; false otherwise.
 */
bool __check_sp38a_op(sp38a_op_Type opf, sp38a_op_Type opctx);

/**
 * @brief Initialize sp38a module.
 * @param[in] sp38a_offset  Offset of memory map.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_sp38a_module_init(uint32_t sp38a_offset);

/**
 * @brief Obtain a pointer to SP38A internal context.
 * @return A pointer to SP38A internal context, or NULL if error.
 * @return A pointer to ChaCha internal context, or NULL if error.
 */
pufs_sp38a_ctx* pufs_sp38a_ctx_new(void);

/**
 * @brief Free a pointer to SP38A internal context.
 * @param[in] sp38a_ctx  A pointer to SP38A context.
 * @remarks no return value.
 */
void pufs_sp38a_ctx_free(pufs_sp38a_ctx* sp38a_ctx);

/**
 * @brief Initialize ECB encryptor.
 * @param[in] sp38a_ctx  SP38A context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_ecb_init(sp38a_ctx, cipher, keytype, keyaddr, keybits)\
    _pufs_enc_ecb_init(sp38a_ctx, cipher, keytype, (size_t)keyaddr, keybits)

/**
 * @brief ECB encryptor initializer with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_ecb_init() instead.
 */
pufs_status_Type _pufs_enc_ecb_init(
		pufs_sp38a_ctx* sp38a_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits);

/**
 * @brief Input data into ECB encryptor
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @@return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ecb_update(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into ECB encryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @@return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ecb_update_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into ECB encryptor
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ecb_sg_append(
		pufs_sp38a_ctx *sp38a_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize ECB encryptor
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ecb_sg_done(pufs_sp38a_ctx *sp38a_ctx);

/**
 * @brief Finalize ECB encryptor
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return                SUCCESS on success, otherwise an error code.
 */
pufs_status_Type pufs_enc_ecb_final(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Finalize ECB encryptor
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return                SUCCESS on success, otherwise an error code.
 */
pufs_status_Type pufs_enc_ecb_final_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start ECB encryption in asynchronous mode.
 * @param[in]  pufs_sp38a_ctx     ECB context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding padding (if any).
 * @param[out] toutlen            Total output length including padding (if any).
 * @param[in]  in                 Input plaintext.
 * @param[in]  inlen              Input length in bytes (must be multiple of block size).
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address in secure memory.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_enc_ecb_async_start (
	pufs_sp38a_ctx *pufs_sp38a_ctx,
	uint8_t* out,
	uint32_t* outlen,
	uint32_t* toutlen,
	const uint8_t* in,
	uint32_t inlen,
	pufs_cipher_Type cipher,
	pufs_key_type_Type keytype,
	size_t keyaddr,
	uint32_t keybits,
	bool swIntrptEnable
);


/**
 * @brief Check encryption progress status in asynchronous ECB mode.
 * @return Current status of the asynchronous ECB encryption operation.
 */
pufs_module_state_Type pufs_enc_ecb_async_check (void);

/**
 * @brief Encryption using ECB mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_ecb(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits)\
    _pufs_enc_ecb(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits)

/**
 * @brief Encryption using ECB mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_ecb() instead.
 */
pufs_status_Type _pufs_enc_ecb(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits);

/**
 * @brief Initialize ECB decryptor
 * @param[in] sp38a_ctx  SP38A context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_ecb_init(sp38a_ctx, cipher, keytype, keyaddr, keybits)\
    _pufs_dec_ecb_init(sp38a_ctx, cipher, keytype, (size_t)keyaddr, keybits)

/**
 * @brief ECB decryptor initializer with keyaddr type casting
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_ecb_init() instead.
 */
pufs_status_Type _pufs_dec_ecb_init(
		pufs_sp38a_ctx* sp38a_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits);

/**
 * @brief Input data into ECB decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ecb_update(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into ECB decryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ecb_update_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into ECB decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ecb_sg_append(
		pufs_sp38a_ctx *sp38a_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize ECB decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @@return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ecb_sg_done(pufs_sp38a_ctx *sp38a_ctx);

/**
 * 
 * @brief Finalize ECB decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ecb_final(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 *
 * @brief Finalize ECB decryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ecb_final_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start ECB decryption in asynchronous mode.
 * @param[in]  pufs_sp38a_ctx     ECB context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding padding (if any).
 * @param[out] toutlen            Total output length including padding (if any).
 * @param[in]  in                 Input ciphertext.
 * @param[in]  inlen              Input length in bytes (must be multiple of block size).
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address in secure memory.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_dec_ecb_async_start (
	pufs_sp38a_ctx *pufs_sp38a_ctx,
	uint8_t* out,
	uint32_t* outlen,
	uint32_t* toutlen,
	const uint8_t* in,
	uint32_t inlen,
	pufs_cipher_Type cipher,
	pufs_key_type_Type keytype,
	size_t keyaddr,
	uint32_t keybits,
	bool swIntrptEnable
);

/**
 * @brief Check decryption progress status in asynchronous ECB mode.
 * @return Current status of the asynchronous ECB decryption operation.
 */
pufs_module_state_Type pufs_dec_ecb_async_check (void);

/**
 * @brief Decryption using ECB mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_ecb(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits)\
    _pufs_dec_ecb(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits)

/**
 * @brief Decryption using ECB mode with keyaddr type casting.
 * @warning DO NOT call this function directly. Use pufs_dec_ecb() instead.
 */
pufs_status_Type _pufs_dec_ecb(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits);

/**
 * @brief Initialize CFB encryptor.
 * @param[in] sp38a_ctx  SP38A context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] iv         Initial vector.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_cfb_init(sp38a_ctx, cipher, keytype, keyaddr, keybits, iv)\
    _pufs_enc_cfb_init(sp38a_ctx, cipher, keytype, (size_t)keyaddr, keybits, iv)

/**
 * @brief CFB encryptor initializer with keyaddr type casting.
 * @warning DO NOT call this function directly. Use pufs_enc_cfb_init() instead.
 */
pufs_status_Type _pufs_enc_cfb_init(
		pufs_sp38a_ctx* sp38a_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv);

/**
 * @brief Input data into CFB encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cfb_update(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into CFB encryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cfb_update_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into CFB encryptor
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cfb_sg_append(
		pufs_sp38a_ctx *sp38a_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize CFB calculator
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cfb_sg_done(pufs_sp38a_ctx *sp38a_ctx);

/**
 * @brief Finalize CFB encryptor
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cfb_final(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Finalize CFB encryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cfb_final_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start CFB encryption in asynchronous mode.
 * @param[in]  pufs_sp38a_ctx     CFB context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding padding (if any).
 * @param[out] toutlen            Total output length including padding (if any).
 * @param[in]  in                 Input plaintext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address in secure memory.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  iv                 Initialization vector.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_enc_cfb_async_start (
	pufs_sp38a_ctx *pufs_sp38a_ctx,
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
	bool swIntrptEnable
);

/**
 * @brief Check encryption progress status in asynchronous CFB mode.
 * @return Current status of the asynchronous CFB encryption operation.
 */
pufs_module_state_Type pufs_enc_cfb_async_check (void);

/**
 * @brief Encryption using CFB mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @param[in]  iv       Initial vector.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_cfb(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     iv)\
    _pufs_enc_cfb(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, iv)

/**
 * @brief Encryption using CFB mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_cfb() instead.
 */
pufs_status_Type _pufs_enc_cfb(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv);

/**
 * @brief Initialize CFB decryptor.
 * @param[in] sp38a_ctx  SP38A context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] iv         Initial vector.
 * @return pufs_status_Type value.
 *
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_cfb_init(sp38a_ctx, cipher, keytype, keyaddr, keybits, iv)\
    _pufs_dec_cfb_init(sp38a_ctx, cipher, keytype, (size_t)keyaddr, keybits, iv)

/**
 * @brief CFB decryptor initializer with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_cfb_init() instead.
 */
pufs_status_Type _pufs_dec_cfb_init(
		pufs_sp38a_ctx* sp38a_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv);

/**
 * @brief Input data into CFB decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_cfb_update(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into CFB decryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_cfb_update_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into CFB decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_cfb_sg_append(
		pufs_sp38a_ctx *sp38a_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize CFB decryptor
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_cfb_sg_done(pufs_sp38a_ctx *sp38a_ctx);

/**
 * @brief Finalize CFB decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_cfb_final(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Finalize CFB decryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_cfb_final_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start CFB decryption in asynchronous mode.
 * @param[in]  pufs_sp38a_ctx     CFB context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding padding (if any).
 * @param[out] toutlen            Total output length including padding (if any).
 * @param[in]  in                 Input ciphertext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address in secure memory.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  iv                 Initialization vector.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_dec_cfb_async_start (
	pufs_sp38a_ctx *pufs_sp38a_ctx,
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
	bool swIntrptEnable
);


/**
 * @brief Check decryption progress status in asynchronous CFB mode.
 * @return Current status of the asynchronous CFB decryption operation.
 */
pufs_module_state_Type pufs_dec_cfb_async_check (void);

/**
 * @brief Decryption using CFB mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @param[in]  iv       Initial vector.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_cfb(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     iv)\
    _pufs_dec_cfb(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, iv)

/**
 * @brief Decryption using CFB mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_cfb() instead.
 */
pufs_status_Type _pufs_dec_cfb(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv);

/**
 * @brief Initialize OFB encryptor.
 * @param[in] sp38a_ctx  SP38A context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] iv         Initial vector.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_ofb_init(sp38a_ctx, cipher, keytype, keyaddr, keybits, iv)\
    _pufs_enc_ofb_init(sp38a_ctx, cipher, keytype, (size_t)keyaddr, keybits, iv)

/**
 * @brief OFB encryptor initializer with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_ofb_init() instead.
 */
pufs_status_Type _pufs_enc_ofb_init(
		pufs_sp38a_ctx* sp38a_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv);

/**
 * @brief Input data into OFB encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ofb_update(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into OFB encryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ofb_update_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into OFB encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ofb_sg_append(
		pufs_sp38a_ctx *sp38a_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);
/**
 * @brief In SGDMA mode, finalize OFB encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ofb_sg_done(pufs_sp38a_ctx *sp38a_ctx);

/**
 * @brief Finalize OFB encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ofb_final(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Finalize OFB encryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ofb_final_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start OFB encryption in asynchronous mode.
 * @param[in]  pufs_sp38a_ctx     OFB context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding padding (if any).
 * @param[out] toutlen            Total output length including padding (if any).
 * @param[in]  in                 Input plaintext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address in secure memory.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  iv                 Initialization vector.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_enc_ofb_async_start (
	pufs_sp38a_ctx *pufs_sp38a_ctx,
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
	bool swIntrptEnable
);


/**
 * @brief Check encryption progress status in asynchronous OFB mode.
 * @return Current status of the asynchronous OFB encryption operation.
 */
pufs_module_state_Type pufs_enc_ofb_async_check (void);

/**
 * @brief Encryption using OFB mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @param[in]  iv       Initial vector.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_ofb(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     iv)\
    _pufs_enc_ofb(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, iv)

/**
 * @brief Encryption using OFB mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_ofb() instead.
 */
pufs_status_Type _pufs_enc_ofb(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv);

/**
 * @brief Initialize OFB decryptor.
 * @param[in] sp38a_ctx  SP38A context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] iv         Initial vector.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_ofb_init(sp38a_ctx, cipher, keytype, keyaddr, keybits, iv)\
    _pufs_dec_ofb_init(sp38a_ctx, cipher, keytype, (size_t)keyaddr, keybits, iv)

/**
 * @brief OFB decryptor initializer with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_ofb_init() instead.
 */
pufs_status_Type _pufs_dec_ofb_init(
		pufs_sp38a_ctx* sp38a_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv);

/**
 * @brief Input data into OFB decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ofb_update(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into OFB decryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ofb_update_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into OFB decryptor
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ofb_sg_append(
		pufs_sp38a_ctx *sp38a_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize OFB decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ofb_sg_done(pufs_sp38a_ctx *sp38a_ctx);

/**
 * @brief Finalize OFB decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ofb_final(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Finalize OFB decryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ofb_final_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start OFB decryption in asynchronous mode.
 * @param[in]  pufs_sp38a_ctx     OFB context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding padding (if any).
 * @param[out] toutlen            Total output length including padding (if any).
 * @param[in]  in                 Input ciphertext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address in secure memory.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  iv                 Initialization vector.
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_dec_ofb_async_start (
	pufs_sp38a_ctx *pufs_sp38a_ctx,
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
	bool swIntrptEnable
);


/**
 * @brief Check decryption progress status in asynchronous OFB mode.
 * @return Current status of the asynchronous OFB decryption operation.
 */
pufs_module_state_Type pufs_dec_ofb_async_check (void);

/**
 * @brief Decryption using OFB mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @param[in]  iv       Initial vector.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_ofb(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     iv)\
    _pufs_dec_ofb(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, iv)

/**
 * @brief Decryption using OFB mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_ofb() instead.
 */
pufs_status_Type _pufs_dec_ofb(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv);

/**
 * @brief Initialize CBC encryptor.
 * @param[in] sp38a_ctx  SP38A context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] iv         Initial vector.
 * @param[in] csmode     Ciphertext-stealing mode.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_cbc_init(sp38a_ctx, cipher, keytype, keyaddr, keybits, iv, csmode)\
    _pufs_enc_cbc_init(sp38a_ctx, cipher, keytype, (size_t)keyaddr, keybits, iv, csmode)

/**
 * @brief CBC encryptor initializer with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_cbc_init() instead.
 */
pufs_status_Type _pufs_enc_cbc_init(
		pufs_sp38a_ctx* sp38a_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		int csmode);

/**
 * @brief Input data into CBC encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cbc_update(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into CBC encryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cbc_update_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into CBC encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cbc_sg_append(
		pufs_sp38a_ctx *sp38a_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize CBC encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cbc_sg_done(pufs_sp38a_ctx *sp38a_ctx);

/**
 * @brief Finalize CBC encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cbc_final(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Finalize CBC encryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_cbc_final_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start CBC encryption in asynchronous mode.
 * @param[in]  pufs_sp38a_ctx     CBC context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding padding (if any).
 * @param[out] toutlen            Total output length including padding (if any).
 * @param[in]  in                 Input plaintext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address in secure memory.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  iv                 Initialization vector.
 * @param[in]  csmode             Cipher service mode (e.g., encryption-only, encryption-with-padding).
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_enc_cbc_async_start (
	pufs_sp38a_ctx *pufs_sp38a_ctx,
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
	int csmode,
	bool swIntrptEnable
);

/**
 * @brief Check encryption progress status in asynchronous CBC mode.
 * @return Current status of the asynchronous CBC encryption operation.
 */
pufs_module_state_Type pufs_enc_cbc_async_check (void);

/**
 * @brief Encryption using CBC mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @param[in]  iv       Initial vector.
 * @param[in]  csmode   Ciphertext-stealing mode.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_cbc(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     iv, csmode)\
    _pufs_enc_cbc(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, iv, csmode)

/**
 * @brief Encryption using CBC mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_cbc() instead.
 */
pufs_status_Type _pufs_enc_cbc(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		int csmode);

/**
 * @brief Initialize CBC decryptor.
 * @param[in] sp38a_ctx  SP38A context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] iv         Initial vector.
 * @param[in] csmode     Ciphertext-stealing mode.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_cbc_init(sp38a_ctx, cipher, keytype, keyaddr, keybits, iv, csmode)\
    _pufs_dec_cbc_init(sp38a_ctx, cipher, keytype, (size_t)keyaddr, keybits, iv, csmode)

/**
 * @brief CBC decryptor initializer with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_cbc_init() instead.
 */
pufs_status_Type _pufs_dec_cbc_init(
		pufs_sp38a_ctx* sp38a_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		int csmode);

/**
 * @brief Input data into CBC decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_cbc_update(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into CBC decryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_cbc_update_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into CBC decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors
 * @return                SUCCESS on success, otherwise an error code.
 */
pufs_status_Type pufs_dec_cbc_sg_append(
		pufs_sp38a_ctx *sp38a_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize CBC decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_cbc_sg_done(pufs_sp38a_ctx *sp38a_ctx);

/**
 * @brief Finalize CBC decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_cbc_final(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Finalize CBC decryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_cbc_final_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start CBC decryption in asynchronous mode.
 * @param[in]  pufs_sp38a_ctx     CBC context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding padding (if any).
 * @param[out] toutlen            Total output length including padding (if any).
 * @param[in]  in                 Input ciphertext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address in secure memory.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  iv                 Initialization vector.
 * @param[in]  csmode             Cipher service mode (e.g., decryption-only, decryption-with-padding).
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_dec_cbc_async_start (
	pufs_sp38a_ctx *pufs_sp38a_ctx,
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
	int csmode,
	bool swIntrptEnable
);


/**
 * @brief Check decryption progress status in asynchronous CBC mode.
 * @return Current status of the asynchronous CBC decryption operation.
 */
pufs_module_state_Type pufs_dec_cbc_async_check (void);

/**
 * @brief Decryption using CBC mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @param[in]  iv       Initial vector.
 * @param[in]  csmode   Ciphertext-stealing mode.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_cbc(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     iv, csmode)\
    _pufs_dec_cbc(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, iv, csmode)

/**
 * @brief Decryption using CBC mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_cbc() instead.
 */
pufs_status_Type _pufs_dec_cbc(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* iv,
		int csmode);

/**
 * @brief Initialize CTR encryptor.
 * @param[in] sp38a_ctx  SP38A context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] t1         Initial counter.
 * @param[in] ctrlen     Incremental counter length in bits.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_ctr_init(sp38a_ctx, cipher, keytype, keyaddr, keybits, t1, ctrlen)\
    _pufs_enc_ctr_init(sp38a_ctx, cipher, keytype, (size_t)keyaddr, keybits, t1, ctrlen)

/**
 * @brief CTR encryptor initializer with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_ctr_init() instead.
 */
pufs_status_Type _pufs_enc_ctr_init(
		pufs_sp38a_ctx* sp38a_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* t1,
		int ctrlen);

/**
 * @brief Input data into CTR encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ctr_update(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into CTR encryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ctr_update_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into CTR encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ctr_sg_append(
		pufs_sp38a_ctx* sp38a_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize CTR encryptor
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ctr_sg_done(pufs_sp38a_ctx *sp38a_ctx);

/**
 * @brief Finalize CTR encryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ctr_final(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Finalize CTR encryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_enc_ctr_final_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start CTR encryption in asynchronous mode.
 * @param[in]  pufs_sp38a_ctx     CTR context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding padding (if any).
 * @param[out] toutlen            Total output length including padding (if any).
 * @param[in]  in                 Input plaintext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address in secure memory.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  iv                 Initialization vector (used as initial counter block).
 * @param[in]  csmode             Cipher service mode (e.g., raw CTR, with offset, etc.).
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_enc_ctr_async_start (
	pufs_sp38a_ctx *pufs_sp38a_ctx,
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
	int csmode,
	bool swIntrptEnable
);

/**
 * @brief Check encryption progress status in asynchronous CTR mode.
 * @return Current status of the asynchronous CTR encryption operation.
 */
pufs_module_state_Type pufs_enc_ctr_async_check (void);

/**
 * @brief Encryption using CTR mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @param[in]  t1       Initial counter.
 * @param[in]  ctrlen   Incremental counter length in bits.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_ctr(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     t1, ctrlen)\
    _pufs_enc_ctr(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, t1, ctrlen)

/**
 * @brief Encryption using CTR mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_enc_ctr() instead.
 */
pufs_status_Type _pufs_enc_ctr(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* t1,
		int ctrlen);

/**
 * @brief Initialize CTR decryptor.
 * @param[in] sp38a_ctx  SP38A context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] t1         Initial counter.
 * @param[in] ctrlen     Incremental counter length in bits.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_ctr_init(sp38a_ctx, cipher, keytype, keyaddr, keybits, t1, ctrlen)\
    _pufs_dec_ctr_init(sp38a_ctx, cipher, keytype, (size_t)keyaddr, keybits, t1, ctrlen)

/**
 * @brief CTR decryptor initializer with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_ctr_init() instead.
 */
pufs_status_Type _pufs_dec_ctr_init(
		pufs_sp38a_ctx* sp38a_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* t1,
		int ctrlen);

/**
 * @brief Input data into CTR decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ctr_update(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input data into CTR decryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ctr_update_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen);

/**
 * @brief Input SGDMA descriptors into CTR decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ctr_sg_append(
		pufs_sp38a_ctx *sp38a_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, finalize CTR decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ctr_sg_done(pufs_sp38a_ctx *sp38a_ctx);

/**
 * @brief Finalize CTR decryptor.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ctr_final(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Finalize CTR decryptor with ISR mode.
 * @param[in]  sp38a_ctx  SP38A context to be initialized.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_dec_ctr_final_isr(
		pufs_sp38a_ctx* sp38a_ctx,
		uint8_t* out,
		uint32_t* outlen);

/**
 * @brief Start CTR decryption in asynchronous mode.
 * @param[in]  pufs_sp38a_ctx     CTR context.
 * @param[out] out                Output buffer.
 * @param[out] outlen             Output length excluding padding (if any).
 * @param[out] toutlen            Total output length including padding (if any).
 * @param[in]  in                 Input ciphertext.
 * @param[in]  inlen              Input length in bytes.
 * @param[in]  cipher             Cipher algorithm.
 * @param[in]  keytype            Key type.
 * @param[in]  keyaddr            Key address in secure memory.
 * @param[in]  keybits            Key length in bits.
 * @param[in]  iv                 Initialization vector (used as initial counter block).
 * @param[in]  csmode             Cipher service mode (e.g., raw CTR, with offset, etc.).
 * @param[in]  swIntrptEnable     Enable software interrupt.
 */
void pufs_dec_ctr_async_start (
	pufs_sp38a_ctx *pufs_sp38a_ctx,
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
	int csmode,
	bool swIntrptEnable
);

/**
 * @brief Check decryption progress status in asynchronous CTR mode.
 * @return Current status of the asynchronous CTR decryption operation.
 */
pufs_module_state_Type pufs_dec_ctr_async_check (void);

/**
 * @brief Decryption using CTR mode.
 * @param[out] out      Output data.
 * @param[out] outlen   Output data length in bytes.
 * @param[in]  in       Input data.
 * @param[in]  inlen    Input data length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @param[in]  t1       Initial counter.
 * @param[in]  ctrlen   Incremental counter length in bits.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_ctr(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     t1, ctrlen)\
    _pufs_dec_ctr(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, t1, ctrlen)

/**
 * @brief Decryption using CTR mode with keyaddr type casting.
 * @return pufs_status_Type value.
 * @warning DO NOT call this function directly. Use pufs_dec_ctr() instead.
 */
pufs_status_Type _pufs_dec_ctr(
		uint8_t* out,
		uint32_t* outlen,
		const uint8_t* in,
		uint32_t inlen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits,
		const uint8_t* t1,
		int ctrlen);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_SP38A_H */
