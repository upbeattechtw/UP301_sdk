/**
 * @file      pufs_sp38a_internal.h
 * @brief     PUFsecurity SP38A internal interface
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

#ifndef PUFS_SP38A_INTERNAL_H
#define PUFS_SP38A_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_crypto_internal.h"
#include "pufs_ka.h"
#include "pufs_sp38a_regs.h"

#define SP38A_VERSION 0x33384100

extern pufs_sp38a_regs_Type *sp38a_regs;

/**
 * enum type for modes of operation of block cipher context protection.
 */
typedef enum sp38a_op {
    SP38A_AVAILABLE,
    SP38A_ECB_CLR,
    SP38A_CFB_CLR,
    SP38A_OFB,
    SP38A_CBC_CLR,
    SP38A_CBC_CS1,
    SP38A_CBC_CS2,
    SP38A_CBC_CS3,
    SP38A_CTR_32,
    SP38A_CTR_64,
    SP38A_CTR_128,
} sp38a_op_Type;

/**
 * structure for context of block cipher modes. (128-bit block size)
 *
 * This structure keeps necessary information to trigger SP38A HW, including.
 *  1. operation (ECB, CBC, CTR, ...): op.
 *  2. encryption or decryption: encrypt.
 *  3. block cipher algotithm: cipher.
 *  4. key information for AES: key, keybits, keyslot, keytype, swkey.
 *  5. initial vector for modes of operation: iv.
 *  6. whether the first block is sent to HW: start.
 *  7. minimum byte length of the last input data: minlen.
 *  8. buffer for incomplete-block input: buff, buflen.
 * 
 *  NOTE: Bool member(e.g. encrypt) should NOT be placed in front of `iv`,
 *        or `iv`(uint8[]) might start with non-word-aligned address, which
 *        will cause problems for the dma module.
 */
typedef struct pufs_sp38a_context {
    uint8_t buff[2 * BC_BLOCK_SIZE];
    uint32_t buflen;
    uint32_t keybits;
    uint32_t minlen;
    uint32_t keyslot;
    pufs_key_type_Type keytype;
    bool encrypt;
    bool start;
    sp38a_op_Type op;
    pufs_cipher_Type cipher;
    uint8_t iv[IV_MAXLEN];
    uint8_t dgst[DGST_INT_STATE_LEN];
    uint8_t key[SW_KEY_MAXLEN];
} pufs_sp38a_context_Type;

typedef pufs_sp38a_context_Type pufs_sp38a_ctx;

/**
 * @brief SP38A GDLE preparation.
 * @param[in] sp38a_ctx  SP38A context.
 * @return pufs_status_Type value.
 */
pufs_status_Type gdle_sp38a_prepare(pufs_sp38a_ctx* sp38a_ctx);

/**
 * @brief SP38A GDLE post-processing.
 * @param[in] sp38a_ctx  SP38A context.
 * @return pufs_status_Type value.
 */
pufs_status_Type gdle_sp38a_postproc(pufs_sp38a_ctx* sp38a_ctx);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_SP38A_INTERNAL_H */
