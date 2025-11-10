/**
 * @file      pufs_sp90a.h
 * @brief     PUFsecurity SP90A API interface
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

#ifndef PUFS_SP90A_H
#define PUFS_SP90A_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_common.h"

/**
 * @brief DRBG underlying cryptographic primitives
 */
typedef enum pufs_drbg_t{
    AES_CTR_DRBG,  ///< DRBG mechanisms based on AES-CTR mode.
    HASH_DRBG,     ///< DRBG mechanisms based on Hash functions.
    HMAC_DRBG,     ///< DRBG mechanisms based on HMAC functions.
} pufs_drbg_Type;

/**
 * @brief Initialize DRBG module.
 * @param[in] drbg_offset  DRBG offset of memory map.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_drbg_module_init(uint32_t drbg_offset);

/**
 * @brief Instantiate DRBG.
 * @param[in] mode      DRBG underlying cryptographic primitive
 * @param[in] security  Required security strength in bits.
 * @param[in] df        Use derivation functi on or not.
 * @param[in] nonce     Nonce.
 * @param[in] noncelen  Length of nonce in bytes.
 * @param[in] pstr      Personalization string.
 * @param[in] pstrlen   Length of personalization string in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_drbg_instantiate(
		pufs_drbg_Type mode,
		uint32_t security,
		bool df,
		const uint8_t* nonce,
		uint32_t noncelen,
		const uint8_t* pstr,
		uint32_t pstrlen);

/**
 * @brief Reseed DRBG.
 * @param[in] df       Use derivation function or not.
 * @param[in] adin     Additional input.
 * @param[in] adinlen  Length of additional input in bytes.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_drbg_reseed(bool df, const uint8_t* adin, uint32_t adinlen);

/**
 * @brief Generate random bits from DRBG.
 * @param[out] out       Random bits.
 * @param[in]  outbits   Length of output in bits.
 * @param[in]  pr        Prediction resistance request.
 * @param[in]  df        Use derivation function or not.
 * @param[in]  adin      Additional input.
 * @param[in]  adinlen   Length of additional input in bytes.
 * @param[in]  testmode  In test mode or not.
 * @return pufs_status_Type value.
 * @note error reported if \em testmode is false but DRBG test mode is enabled.
 */
pufs_status_Type pufs_drbg_generate(
		uint8_t* out,
		uint32_t outbits,
		bool pr,
		bool df,
		const uint8_t* adin,
		uint32_t adinlen,
		uint32_t testmode);

/**
 * @brief Uninstantiate DRBG.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_drbg_uninstantiate(void);

/**
 * @brief Check if SP90A hardware is in test mode.
 * @return  True if SP90A is in test mode; false otherwise.
 */
bool pufs_drbg_is_testmode(void);

/**
 * @brief Enable DRBG test mode.
 *  @remarks no return value.
 */
void pufs_drbg_enable_testmode(void);

/**
 * @brief Set entropy for test mode.
 * @param[in] entropy  Entropy.
 * @param[in] entlen   Entropy length in bytes.
 * @remarks no return value.
 */
void pufs_drbg_testmode_entropy(const uint8_t* entropy, uint32_t entlen);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_SP90A_H */
