/**
 * @file      pufs_chacha_internal.h
 * @brief     PUFsecurity ChaCha internal interface
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

#ifndef PUFS_CHACHA_INTERNAL_H
#define PUFS_CHACHA_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_chacha.h"
#include "pufs_crypto_internal.h"
#include "pufs_chacha_regs.h"

/**
 * enum type for ChaCha input
 */
typedef enum chacha_stage {
    CHACHA20_POLY1305_TAG,
    CHACHA20_POLY1305_AAD,
    CHACHA20_POLY1305_TEXT,
    CHACHA_TEXT,
    CHACHA_NONE,
} chacha_stage_Type;

#define CHACHA_VERSION        0x84390001
#define CHACHA_MAX_IV_LENGTH  16 // IV + counter.
#define POLY1305_TAG_SIZE     16
#define POLY1305_DGST_SIZE    64
#define CHACHA_BLOCK_SIZE     64 // 64 byte.

extern pufs_chacha_regs_Type *chacha_regs;

typedef struct pufs_chacha_context {
	chacha_stage_Type    stage;
    pufs_key_type_Type keytype;
    uint32_t        keybits;
    uint32_t        keyslot;
    uint32_t        ivlen;
    uint8_t         buf[CHACHA_BLOCK_SIZE];
    uint32_t        counter;
    uint32_t        round;
    uint32_t        buflen;
    uint64_t        aadlen;
    uint64_t        txtlen;
    uint8_t         offset;
    uint8_t         block_offset;
    bool            dgest_enable;
    bool            poly1305_enable;
    bool            chacha_enable;
    bool            pad_enable;
    bool            aead_encrypt;
    bool            aad_start;
    bool            txt_start;
    __attribute__ ((aligned (32))) uint8_t         iv[CHACHA_MAX_IV_LENGTH];
    uint8_t         dgst[POLY1305_DGST_SIZE];
    uint8_t         key[SW_KEY_MAXLEN];
} pufs_chacha_context_Type;

pufs_status_Type __chacha_perror(uint32_t status);

pufs_status_Type __chacha_form_iv_with_counter(pufs_chacha_ctx *chacha_ctx);

uint32_t __chacha_get_cfg(			// rfc8439_cfg.
		bool pad16_en,
		bool dgst_en,
		bool p1305_en,
		bool chch_en,
		bool aead_encrypt,
		bool poly1305_swkey);

pufs_status_Type __chacha_write_chacha_cfg(uint32_t round, uint32_t ivlen);

pufs_status_Type __chacha_write_cfg(uint32_t cfg);

uint32_t __fill_incomplete_block_chacha(uint8_t *buf, uint32_t *buflen, const uint8_t *in, uint32_t inlen);

pufs_status_Type __chacha_ctx_aad_final(pufs_chacha_ctx *chacha_ctx);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_CHACHA_INTERNAL_H */
