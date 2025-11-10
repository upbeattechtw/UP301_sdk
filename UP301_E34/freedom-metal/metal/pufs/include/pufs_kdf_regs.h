/**
 * @file      pufs_kdf_regs.h
 * @brief     PUFsecurity KDF register definition
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
#ifndef PUFS_KDF_REGS_H
#define PUFS_KDF_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#define KDF_IV_LEN 64 ///< the byte length of KDF_IV_ADDR

typedef struct pufs_kdf_regs {
    volatile uint32_t version;
    volatile uint32_t interrupt;
    volatile uint32_t feature;
    uint32_t _pad1;
    volatile uint32_t status;
    uint32_t _pad2;
    volatile uint32_t cfg;
    volatile uint32_t cnt;
    uint32_t _pad3[4];
    volatile uint32_t klen;
    volatile uint32_t kcount;
    volatile uint32_t iv_len;
    uint32_t _pad4;
    volatile uint8_t  iv[KDF_IV_LEN];
    volatile uint32_t salt_len;
} pufs_kdf_regs_Type;

#define KDF_CFG_PRF_BITS                 4
#define KDF_CFG_VARIANT_BITS             8
#define KDF_CFG_IVEN_BITS               16
#define KDF_CFG_FBEN_BITS               17
#define KDF_CFG_KEY_TYPE_BITS           27
#define KDF_CFG_KEY_IDX_TO_BITS         28

#define KDF_CNT_LEN_BITS                 4
#define KDF_CNT_POS_BITS                 6
#define KDF_CNT_ORD_BITS                 8

#define KDF_INTRPT_INTRPT_ST_MASK       0x00000001
#define KDF_INTRPT_INTRPT_EN_MASK       0x00010000
#define KDF_FEATURE_HMAC_KDF_MASK       0x00000001
#define KDF_FEATURE_CMAC_KDF_MASK       0x00000002
#define KDF_STATUS_BUSY_MASK            0x00000001
#define KDF_STATUS_RESP_MASK            0xfffffffe
#define KDF_CFG_MD_MASK                 0x00000007
#define KDF_CFG_PRF_MASK                0x00000030
#define KDF_CFG_VARIANT_MASK            0x00000F00
#define KDF_CFG_IVEN_MASK               0x00010000
#define KDF_CFG_FBEN_MASK               0x00020000
#define KDF_CFG_KEY_TYPE_TO_MASK        0x08000000
#define KDF_CFG_KEY_IDX_TO_MASK         0xf0000000

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_KDF_REGS_H */
