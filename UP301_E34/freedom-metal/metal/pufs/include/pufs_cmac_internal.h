/**
 * @file      pufs_cmac_internal.h
 * @brief     PUFsecurity CMAC internal interface
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

#ifndef PUFS_CMAC_INTERNAL_H
#define PUFS_CMAC_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_cmac.h"
#include "pufs_cmac_regs.h"
#include "pufs_crypto_internal.h"
#include "pufs_ka.h"

#define CMAC_VERSION 0x33384200

extern pufs_cmac_regs_Type *cmac_regs;

/**
 * enum type for CMAC context protection
 */
typedef enum cmac_op {
    CMAC_AVAILABLE,
    CMAC_CMAC,
} cmac_op_Type;

/**
 * structure for CMAC context (128-bit block size).
 * This structure keeps necessary information to trigger CMAC HW, including
 *  1. operation (CMAC): op
 *  2. block cipher algotithm: cipher
 *  3. key information for CMAC: key, keybits, keyslot, keytype, swkey
 *  4. internal state: state
 *  5. whether the first block is sent to HW: start
 *  6. minimum byte length of the last input data: minlen
 *  7. buffer for incomplete-block input: buff, buflen
 */
#define CMAC_BLOCK_SIZE 16
typedef struct pufs_cmac_context {
    uint8_t buff[CMAC_BLOCK_SIZE];
    uint32_t buflen;
    uint32_t keybits;
    uint32_t minlen;
    uint32_t keyslot;
    pufs_key_type_Type keytype;
    cmac_op_Type op;
    pufs_cipher_Type cipher;
    bool start;
    uint8_t iv[IV_MAXLEN];
    uint8_t state[DGST_INT_STATE_LEN];
    uint8_t key[SW_KEY_MAXLEN];
} pufs_cmac_context_Type;

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_CMAC_INTERNAL_H */
