/**
 * @file      pufs_cmac.h
 * @brief     PUFsecurity CMAC API interface
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
#ifndef PUFS_CMAC_H
#define PUFS_CMAC_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#include "pufs_cmac_internal.h"
#include "pufs_crypto_internal.h"
#include "pufs_hmac.h"
#include "pufs_common.h"
#include "pufs_dma.h"

typedef pufs_cmac_context_Type pufs_cmac_ctx_Type;

typedef struct {
	pufs_cmac_ctx_Type *ctx;
	pufs_dgst_st_Type* md;
	const unsigned char* msg;
	uint32_t msglen;
	pufs_hash_Type hash;
	pufs_key_type_Type keytype;
	size_t keyaddr;
	uint32_t keybits;
	bool swIntrptEnable;
} cmac_async_args_Type;

typedef enum {
	CMAC_ASYNC_IDLE,
	CMAC_ASYNC_INIT,
	CMAC_ASYNC_UPDATE,
	CMAC_ASYNC_FINAL,
	CMAC_ASYNC_RESULT,
} cmac_async_step_Type;

typedef enum {
	CMAC_UPDATE,
	CMAC_FINAL,
} cmac_update_Type;

typedef struct{
	bool last;
	pufs_cmac_ctx_Type *ctx;
	pufs_dgst_st_Type *md;
	cmac_update_Type update;
} cmac_isr_args_Type;

void puf_cmac_isr_handler(uint16_t id, cmac_isr_args_Type *data);

/**
 * @brief Enable or disable the PUF CMAC interrupt.
 *
 * @param enable Set to 1 to enable the interrupt, 0 to disable.
 */
void enable_puf_cmac_isr(uint8_t enable);

pufs_status_Type __cmac_get_cfg(pufs_cmac_ctx_Type *cmac_ctx, uint32_t *cfg);

/**
 * @brief Initialize cmac module.
 * @param[in] cmac_offset  cmac offset of memory map.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_cmac_module_init(uint32_t cmac_offset);

/**
 * @brief Obtain a pointer to CMAC internal context.
 * @return A pointer to CMAC internal context, or NULL if error.
 */
pufs_cmac_ctx_Type* pufs_cmac_ctx_new(void);

/**
 * @brief Free a pointer to CMAC internal context
 * @param[in] cmac_ctx  A pointer to CMAC context.
 * @remarks no return value.
 */
void pufs_cmac_ctx_free(pufs_cmac_ctx_Type* cmac_ctx);

/**
 * @brief Initialize CMAC calculator.
 * @param[in] cmac_ctx  CMAC context to be initialized.
 * @param[in] cipher    Block cipher algorithm.
 * @param[in] keytype   Key type.
 * @param[in] keyaddr   Key address.
 * @param[in] keybits   Key length in bits.
 * @return              SUCCESS on success, otherwise an error code.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_cmac_init(cmac_ctx, cipher, keytype, keyaddr, keybits) \
    _pufs_cmac_init(cmac_ctx, cipher, keytype, (size_t)keyaddr, keybits)

/**
 * @brief CMAC calculator initializer with keyaddr type casting.
 * @warning DO NOT call this function directly. Use pufs_cmac_init() instead.
 * @return pufs_status_Type value.
 */
pufs_status_Type _pufs_cmac_init(
		pufs_cmac_ctx_Type* cmac_ctx,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits);

/**
 * @brief Input data into CMAC calculator.
 * @param[in] cmac_ctx  CMAC context.
 * @param[in] msg       Message.
 * @param[in] msglen    Message length in bytes.
 * @@return pufs_status_Type value.
 */
pufs_status_Type pufs_cmac_update(
		pufs_cmac_ctx_Type* cmac_ctx,
		const uint8_t* msg,
		uint32_t msglen);

/**
 * @brief Input data into CMAC calculator with ISR mode.
 * @param[in] cmac_ctx  CMAC context.
 * @param[in] msg       Message.
 * @param[in] msglen    Message length in bytes.
 * @@return pufs_status_Type value.
 */
pufs_status_Type pufs_cmac_update_isr(
		pufs_cmac_ctx_Type* cmac_ctx,
		const uint8_t* msg,
		uint32_t msglen);

/**
 * @brief Input SGDMA descriptors into CMAC calculator.
 * @param[in] cmac_ctx  CMAC context.
 * @param[in] descs     SGDMA descriptors.
 * @param[in] descs_len the length of SGDMA descriptors.
 * @param[in] last      set true if there is no more incoming descriptors.
 * @@return pufs_status_Type value.
 */
pufs_status_Type pufs_cmac_sg_append(
		pufs_cmac_ctx_Type *cmac_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, extract message digest from CMAC calculator.
 * @param[in] cmac_ctx  CMAC context.
 * @param[out] md       Message digest.
 * @@return pufs_status_Type value.
 */
pufs_status_Type pufs_cmac_sg_done(pufs_cmac_ctx_Type *cmac_ctx, pufs_dgst_st_Type *md);

/**
 * @brief Extract message digest from CMAC calculator.
 * @param[in] cmac_ctx  CMAC context.
 * @param[out] md       Message digest.
 * @@return pufs_status_Type value.
 */
pufs_status_Type pufs_cmac_final(pufs_cmac_ctx_Type *cmac_ctx, pufs_dgst_st_Type *md);

/**
 * @brief Extract message digest from CMAC calculator with ISR mode.
 * @param[in] cmac_ctx  CMAC context.
 * @param[out] md       Message digest.
 * @@return pufs_status_Type value.
 */
pufs_status_Type pufs_cmac_final_isr(pufs_cmac_ctx_Type *cmac_ctx, pufs_dgst_st_Type *md);

/**
 * @brief Calculate CMAC hash value of a message with a key.
 * @param[out] md       Message digest.
 * @param[in]  msg      Message.
 * @param[in]  msglen   Message length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @return              SUCCESS on success, otherwise an error code.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_cmac(md, msg, msglen, cipher, keytype, keyaddr, keybits) \
    _pufs_cmac(md, msg, msglen, cipher, keytype, (size_t)keyaddr, keybits)

/**
 * @brief CMAC calculator with keyaddr type casting.
 * @warning DO NOT call this function directly. Use pufs_cmac() instead.
 * @return pufs_status_Type value.
 */
pufs_status_Type _pufs_cmac(
		pufs_dgst_st_Type* md,
		const uint8_t* msg,
		uint32_t msglen,
		pufs_cipher_Type cipher,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits);

/**
 * @brief Start CMAC calculator.
 * @param[in]  cmac_ctx			CMAC context.
 * @param[out] md       		Message digest.
 * @param[in]  msg      		Message.
 * @param[in]  msglen   		Message length in bytes.
 * @param[in]  cipher     		Block cipher algorithm.
 * @param[in]  keytype  		Key type.
 * @param[in]  keyaddr  		Key address.
 * @param[in]  keybits  		Key length in bits.
 * @param[in]  swIntrptEnable	Enable software interrupt.
 */
void pufs_cmac_async_start (
	pufs_cmac_ctx_Type *cmac_ctx,
	pufs_dgst_st_Type* md,
	const uint8_t* msg,
	uint32_t msglen,
	pufs_cipher_Type cipher,
	pufs_key_type_Type keytype,
	size_t keyaddr,
	uint32_t keybits,
	bool swIntrptEnable);

/**
 * @brief Check whether CMAC calculator finished.
 */
pufs_module_state_Type pufs_cmac_async_check (void);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_CMAC_H */
