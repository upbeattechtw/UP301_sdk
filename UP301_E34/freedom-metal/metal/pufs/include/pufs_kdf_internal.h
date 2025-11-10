/**
 * @file      pufs_kdf_internal.h
 * @brief     PUFsecurity KDF internal interface
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

#ifndef PUFS_KDF_INTERNAL_H
#define PUFS_KDF_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_kdf.h"
#include "pufs_kdf_regs.h"

#define KDF_VERSION 0x484B4400

extern pufs_kdf_regs_Type *kdf_regs;

typedef struct pufs_kdf_cfg_params {
    pufs_key_type_Type   keytype;
    pufs_ka_slot_Type    keyslot;
    uint32_t          outbits;
    pufs_prf_family_Type prf;
    pufs_kdf_md_Type     method;
    pufs_hash_Type       hash;
    uint32_t          zbits;
    bool              feedback;
    const uint8_t*    iv;
} pufs_kdf_cfg_params_Type;

typedef struct pufs_kdf_cnt_params {
    bool                feedback;
    uint8_t             length;
    pufs_kdf_cnt_pos_Type  position;
    uint32_t            order;
} pufs_kdf_cnt_params_Type;

/**
 * @brief Check and build KDF configuration.
 * @return pufs_status_Type value.
 */
pufs_status_Type __pufs_kdf_gen_cfg(pufs_kdf_cfg_params_Type *params, uint32_t *cfg, uint32_t *ivlen);

/**
 * @brief Check and build KDF counter configuration
 * @return pufs_status_Type value.
 */
pufs_status_Type __pufs_kdf_gen_cnt(pufs_kdf_cnt_params_Type *params, uint32_t *cnt);

pufs_status_Type sm2kdf(
    pufs_key_type_Type keytype,
    pufs_ka_slot_Type keyslot,
    uint32_t outbits,
    pufs_key_type_Type ztype,
    size_t zaddr,
    uint32_t zbits,
    const uint8_t* info,
    uint32_t infolen,
    uint8_t *out);

pufs_status_Type sm2kdf_isr(
    pufs_key_type_Type keytype,
    pufs_ka_slot_Type keyslot,
    uint32_t outbits,
    pufs_key_type_Type ztype,
    size_t zaddr,
    uint32_t zbits,
    const uint8_t* info,
    uint32_t infolen,
    uint8_t *out);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_KDF_INTERNAL_H */
