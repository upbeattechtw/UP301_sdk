/**
 * @file      pufs_hmac.h
 * @brief     PUFsecurity HMAC API interface
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

#ifndef PUFS_HMAC_H
#define PUFS_HMAC_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "pufs_isr.h"
#include "pufs_common.h"
#include "pufs_crypto_regs.h"
#include "pufs_dma.h"
#include "pufs_hmac_internal.h"
#include "pufs_ka.h"

#define HMAC_BLOCK_MAXLEN 128

/**
 * @brief Cryptographic hash algorithms
 */
typedef enum pufs_hash{
    SHA_224,                ///< SHA224
    SHA_256,                ///< SHA256
    HASH_DEFAULT = SHA_256, ///< Default to SHA256
    SHA_384,                ///< SHA384
    SHA_512,                ///< SHA512
    SHA_512_224,            ///< SHA512/224
    SHA_512_256,            ///< SHA512/256
    SM3,                    ///< SM3
    N_HASH_T,               // keep in the last one
} pufs_hash_Type;

/**
 * structure for hash/HMAC context (128-bit block size)
 * This structure keeps necessary information to trigger HMAC HW, including
 *  1. operation (Hash or HMAC): op
 *  2. hash algotithm: hash
 *  3. key information for HMAC: key, keybits, keyslot, keytype, swkey
 *  4. internal state: state
 *  5. whether the first block is sent to HW: start
 *  6. minimum byte length of the last input data: minlen
 *  7. buffer for incomplete-block input: buff, buflen
 *  FIXME: sgdma only read swkey up to 64 bytes, the rest is ignored
 */
typedef struct pufs_hmac_context {
    uint8_t buff[HMAC_BLOCK_MAXLEN];
    uint32_t buflen;
    uint32_t keybits;
    uint32_t minlen;
    uint32_t curlen;
    uint32_t keyslot;
    uint32_t blocklen;
    pufs_key_type_Type keytype;
    hmac_op_Type op;
    pufs_hash_Type hash;
    bool start;
    uint8_t iv[IV_MAXLEN];
    uint8_t state[DGST_INT_STATE_LEN];
    __attribute__ ((aligned(32))) uint8_t key[HMAC_BLOCK_MAXLEN];
} pufs_hmac_context_Type;

typedef pufs_hmac_context_Type pufs_hmac_ctx_Type;
typedef pufs_hmac_ctx_Type pufs_hash_ctx_Type;

typedef struct {
	pufs_hash_ctx_Type *ctx;
	pufs_dgst_st_Type* md;
	const unsigned char* msg;
	uint32_t msglen;
	pufs_hash_Type hash;
	bool swIntrptEnable;
} hash_async_args_Type;

typedef struct {
	pufs_hmac_ctx_Type *ctx;
	pufs_dgst_st_Type* md;
	const unsigned char* msg;
	uint32_t msglen;
	pufs_hash_Type hash;
	pufs_key_type_Type keytype;
	size_t keyaddr;
	uint32_t keybits;
	bool swIntrptEnable;
} hmac_async_args_Type;

typedef enum {
	HASH_HMAC_ASYNC_IDLE,
	HASH_HMAC_ASYNC_INIT,
	HASH_HMAC_ASYNC_UPDATE,
	HASH_HMAC_ASYNC_FINAL,
	HASH_HMAC_ASYNC_RESULT,
} hash_hmac_async_step_Type;

typedef enum {
	HASH_HMAC_UPDATE,
	HASH_HMAC_FINAL,
} hash_hmac_update_Type;

typedef struct {
	bool last;
	pufs_hmac_ctx_Type *ctx;
	pufs_dgst_st_Type *md;
	hash_hmac_update_Type update;
} hash_hmac_isr_args_Type;

/**
 * @brief Enable or disable the PUF HMAC/HASH interrupt.
 *
 * @param enable Set to 1 to enable the interrupt, 0 to disable.
 */
void enable_puf_hash_hmac_isr(uint8_t enable);

void puf_hash_hmac_isr_handler(uint16_t id, hash_hmac_isr_args_Type *args);

pufs_status_Type __hmac_get_cfg(pufs_hmac_ctx_Type *hmac_ctx, uint32_t *cfg);

pufs_status_Type __hmac_set_dgst_length(pufs_hmac_ctx_Type* hmac_ctx, pufs_dgst_st_Type* md);

/**
 * @brief Initialize hmac/hash module.
 * @param[in] hmac_offset  hmac offset of memory map.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hmac_module_init(uint32_t hmac_offset);

/**
 * @brief Obtain a pointer to HMAC internal context.
 * @return A pointer to HMAC internal context, or NULL if error.
 */
pufs_hmac_ctx_Type* pufs_hmac_ctx_new(void);

#define pufs_hash_ctx_new() pufs_hmac_ctx_new()

/**
 * @brief Free a pointer to HMAC internal context.
 * @param[in] hmac_ctx  A pointer to HMAC context.
 * @remarks no return value.
 */
void pufs_hmac_ctx_free(pufs_hmac_ctx_Type* hmac_ctx);

#define pufs_hash_ctx_free(hmac_ctx) pufs_hmac_ctx_free(hmac_ctx)

/**
 * @brief Initialize hash calculator.
 * @param[in] hash_ctx  HMAC context.
 * @param[in] hash      Hash algorithm.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hash_init(pufs_hash_ctx_Type* hash_ctx, pufs_hash_Type hash);

/**
 * @brief Input data into hash calculator
 * @param[in] hash_ctx  HMAC context.
 * @param[in] msg       Message.
 * @param[in] msglen    Message length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hash_update(
		pufs_hash_ctx_Type* hash_ctx,
		const unsigned char* msg,
		uint32_t msglen);
		
/**
 * @brief Input data into hash calculator with ISR mode
 * @param[in] hash_ctx  HMAC context.
 * @param[in] msg       Message.
 * @param[in] msglen    Message length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hash_update_isr(pufs_hash_ctx_Type* hash_ctx, const unsigned char* msg, uint32_t msglen);

/**
 * @brief Input SGDMA descriptors into hash calculator.
 * @param[in] hash_ctx  HMAC context.
 * @param[in] descs     SGDMA descriptors.
 * @param[in] descs_len the length of SGDMA descriptors.
 * @param[in] last      set true if there is no more incoming descriptors.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hash_sg_append(
		pufs_hash_ctx_Type* hash_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, xtract message digest from hash calculator.
 * @param[in]  hash_ctx  HMAC context.
 * @param[out] md        Message digest.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hash_sg_done(pufs_hash_ctx_Type *hash_ctx, pufs_dgst_st_Type* md);

/**
 * @brief Extract message digest from hash calculator.
 * @param[in]  hash_ctx  HMAC context.
 * @param[out] md        Message digest.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hash_final(pufs_hash_ctx_Type* hash_ctx, pufs_dgst_st_Type* md);

/**
 * @brief Extract message digest from hash calculator with ISR mode.
 * @param[in]  hash_ctx  HMAC context.
 * @param[out] md        Message digest.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hash_final_isr(pufs_hash_ctx_Type* hash_ctx, pufs_dgst_st_Type* md);

/**
 * @brief Calculate hash value of a message.
 * @param[out] md      Message digest.
 * @param[in]  msg     Message.
 * @param[in]  msglen  Message length in bytes.
 * @param[in]  hash    Hash algorithm.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hash(
		pufs_dgst_st_Type* md,
		const unsigned char* msg,
		uint32_t msglen,
		pufs_hash_Type hash);

/**
 * @brief Start HASH calculator.
 * @param[in]  hash_ctx			HASH context.
 * @param[out] md       		Message digest.
 * @param[in]  msg      		Message.
 * @param[in]  msglen   		Message length in bytes.
 * @param[in]  hash     		Hash algorithm.
 * @param[in]  swIntrptEnable	Enable software interrupt.
 */
void pufs_hash_async_start(
		pufs_hash_ctx_Type* hash_ctx,
		pufs_dgst_st_Type* md,
		const uint8_t* msg,
		uint32_t msglen,
		pufs_hash_Type hash,
		bool swIntrptEnable);

/**
 * @brief Run and check whether HASH calculator finished.
 */
pufs_module_state_Type pufs_hash_async_check(void);

/**
 * @brief Initialize HMAC calculator.
 * @param[in] hmac_ctx  HMAC context.
 * @param[in] hash      Hash algorithm.
 * @param[in] keytype   Key type.
 * @param[in] keyaddr   Key address.
 * @param[in] keybits   Key length in bits.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_hmac_init(hmac_ctx, hash, keytype, keyaddr, keybits) \
    _pufs_hmac_init(hmac_ctx, hash, keytype, (size_t)keyaddr, keybits)

/**
 * @brief HMAC calculator initializer with keyaddr type casting
 * @warning DO NOT call this function directly. Use pufs_hmac_init() instead.
 */
pufs_status_Type _pufs_hmac_init(
		pufs_hmac_ctx_Type* hmac_ctx,
		pufs_hash_Type hash,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits);

/**
 * @brief Input data into HMAC calculator
 * @param[in] hmac_ctx  HMAC context.
 * @param[in] msg     Message.
 * @param[in] msglen  Message length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hmac_update(
		pufs_hmac_ctx_Type* hmac_ctx,
		const unsigned char* msg,
		uint32_t msglen);

/**
 * @brief Input data into HMAC calculator with ISR mode.
 * @param[in] hmac_ctx  HMAC context.
 * @param[in] msg     Message.
 * @param[in] msglen  Message length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hmac_update_isr(
		pufs_hmac_ctx_Type* hmac_ctx,
		const unsigned char* msg,
		uint32_t msglen);

/**
 * @brief Input SGDMA descriptors into HMAC calculator
 * @param[in] hmac_ctx  HMAC context.
 * @param[in] descs     SGDMA descriptors
 * @param[in] descs_len the length of SGDMA descriptors
 * @param[in] last      set true if there is no more incoming descriptors.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hmac_sg_append(
		pufs_hmac_ctx_Type *hmac_ctx,
		pufs_dma_sg_desc_Type *descs,
		uint32_t descs_len,
		bool last);

/**
 * @brief In SGDMA mode, xtract message digest from hash calculator.
 * @param[in]  hmac_ctx  HMAC context.
 * @param[out] md        Message digest.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hmac_sg_done(pufs_hmac_ctx_Type *hmac_ctx, pufs_dgst_st_Type *md);

/**
 * @brief Extract message digest from HMAC calculator.
 * @param[in]  hmac_ctx  HMAC context.
 * @param[out] md        Message digest.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hmac_final(pufs_hmac_ctx_Type* hmac_ctx, pufs_dgst_st_Type* md);

/**
 * @brief Extract message digest from HMAC calculator with ISR mode.
 * @param[in]  hmac_ctx  HMAC context.
 * @param[out] md        Message digest.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_hmac_final_isr(pufs_hmac_ctx_Type* hmac_ctx, pufs_dgst_st_Type* md);

/**
 * @brief Calculate HMAC hash value of a message with a key.
 * @param[out] md       Message digest.
 * @param[in]  msg      Message.
 * @param[in]  msglen   Message length in bytes.
 * @param[in]  hash     Hash algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @return pufs_status_Type value.
 * @note \em keyaddr may be a \ref pufs_rt_slot_Type element, a \ref pufs_ka_slot_Type
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_hmac(md, msg, msglen, hash, keytype, keyaddr, keybits)\
    _pufs_hmac(md, msg, msglen, hash, keytype, (size_t)keyaddr, keybits)

/**
 * @brief HMAC calculator with keyaddr type casting
 * @warning DO NOT call this function directly. Use pufs_hmac() instead.
 */
pufs_status_Type _pufs_hmac(
		pufs_dgst_st_Type* md,
		const unsigned char* msg,
		uint32_t msglen,
		pufs_hash_Type hash,
		pufs_key_type_Type keytype,
		size_t keyaddr,
		uint32_t keybits);

/**
 * @brief Start HMAC calculator.
 * @param[in]  hmac_ctx			HMAC context.
 * @param[out] md       		Message digest.
 * @param[in]  msg      		Message.
 * @param[in]  msglen   		Message length in bytes.
 * @param[in]  hash     		Hash algorithm.
 * @param[in]  keytype  		Key type.
 * @param[in]  keyaddr  		Key address.
 * @param[in]  keybits  		Key length in bits.
 * @param[in]  swIntrptEnable	Enable software interrupt.
 */
void pufs_hmac_async_start(
	pufs_hmac_ctx_Type *hmac_ctx,
	pufs_dgst_st_Type* md,
	const unsigned char* msg,
	uint32_t msglen,
	pufs_hash_Type hash,
	pufs_key_type_Type keytype,
	size_t keyaddr,
	uint32_t keybits,
	bool swIntrptEnable
);

/**
 * @brief Check whether HMAC calculator finished.
 */
pufs_module_state_Type pufs_hmac_async_check(void);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_HMAC_H */
