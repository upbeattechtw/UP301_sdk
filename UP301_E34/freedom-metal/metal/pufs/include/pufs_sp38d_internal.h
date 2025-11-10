/**
 * @file      pufs_sp38d_internal.h
 * @brief     PUFsecurity SP38D internal interface
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

#ifndef PUFS_SP38D_INTERNAL_H
#define PUFS_SP38D_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_crypto_internal.h"
#include "pufs_sp38d_regs.h"

#define SP38D_VERSION 0x33384401

extern pufs_sp38d_regs_Type *sp38d_regs;

/**
 * enum type for GCM input.
 */
typedef enum sp38d_stage {
    SP38D_NONE,
    SP38D_AAD,
    SP38D_TEXT,
} sp38d_stage_Type;
/**
 * enum type for GCM context protection.
 */
typedef enum sp38d_op {
    SP38D_AVAILABLE,
    SP38D_GHASH,
    SP38D_GCM,
    SP38D_GMAC,
} sp38d_op_Type;

/**
 * structure for context of block cipher GCM mode. (128-bit block size)
 *
 * This structure keeps necessary information to trigger SP38D HW, including.
 *  1. operation (AVAILABLE, GCM): op.
 *  2. encryption or decryption: encrypt.
 *  3. block cipher algotithm: cipher.
 *  4. key information for AES: key, keybits, keyslot, keytype.
 *  5. translated initial vector J_0: j0.
 *  6. minimum byte length of the last input data: minlen.
 *  7. buffer for incomplete-block input: buff, buflen.
 *  8. intermediate ghash value: ghash.
 *  9. input bit lengths: aadbits, inbits.
 * 
 *  NOTE: Bool member(e.g. encrypt) should NOT be placed in front of `j0`,
 *        or `j0`(uint8[]) might start with non-word-aligned address, which
 *        might cause problems for the dma module.
 */
typedef struct pufs_sp38d_context {
    uint64_t aadbits;
    uint64_t inbits;
    uint8_t buff[BC_BLOCK_SIZE];
    uint32_t buflen;
    uint32_t keybits;
    uint32_t minlen;
    uint32_t keyslot;
    uint32_t incj0;
    pufs_key_type_Type keytype;
    bool encrypt;
    bool start;
    sp38d_op_Type op;
    sp38d_stage_Type stage;
    pufs_cipher_Type cipher;
    uint8_t j0[BC_BLOCK_SIZE];
    uint8_t ghash[DGST_INT_STATE_LEN];
    uint8_t key[SW_KEY_MAXLEN];
} pufs_sp38d_context_Type;

typedef pufs_sp38d_context_Type pufs_sp38d_ctx;

/**
 * @brief SP38D GDLE preparation.
 * @param[in] sp38d_ctx  SP38D context.
 * @param[in] out        The pointer to the output for register setting.
 * @param[in] inlen      The input text length in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type gdle_gcm_prepare(
		pufs_sp38d_ctx* sp38d_ctx,
		const uint8_t* out,
		uint32_t inlen);

/**
 * @brief SP38D GDLE post-processing
 * @param[in] sp38d_ctx  SP38D context.
 * @return pufs_status_Type value.
 */
pufs_status_Type gdle_gcm_postproc(pufs_sp38d_ctx* sp38d_ctx);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_SP38D_INTERNAL_H */
