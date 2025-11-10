/**
 * @file      pufs_rt.h
 * @brief     PUFsecurity PUFrt API interface
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

#ifndef PUFS_RT_H
#define PUFS_RT_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#include "pufs_common.h"

#ifndef DOXYGEN
    // Note: use PUFRT_DEFAULT_ZERO if the default bit of PUF/OTP area is 0
    #define PUFRT_DEFAULT_ZERO 1
#endif

#if defined(PUFRT_DEFAULT_ZERO)
    #define PUFRT_VALUE4(value) (~value & 0xF)
    #define PUFRT_VALUE8(value) (~value & 0xFF)
    #define PUFRT_VALUE32(value) ((uint32_t)~value)
#else
    #define PUFRT_VALUE4(value) (value)
    #define PUFRT_VALUE8(value) (value)
    #define PUFRT_VALUE32(value) (value)
#endif

/**
 * @brief The size of whole OTP cells in bytes.
 */
#define OTP_LEN 1024
/**
 * @brief The size of a OTP key.
 */
#define OTP_KEY_BITS 256
#define OTP_KEY_LEN (OTP_KEY_BITS / 8)
/**
 * @brief Construct mask bit for pufs_post_mask().
 * @param[in] slot  One of \ref pufs_rt_slot_Type elements.
 * @return          The mask bit used in pufs_post_mask().
 */
#define MASK_BIT(slot) (1ULL<<(slot))
/**
 * @brief Check and output test result for testing functions.
 * @param[in] text  Description for test item.
 * @param[in] good  Description for succeeded test.
 */
#define CHECKOUT(text, good) \
    do { \
        fprintf(stderr, "  %s ... %s\n", text, ((check == SUCCESS) ? good : "failed")); \
        if (check != SUCCESS) \
            goto cleanup; \
    } while (0)

/**
 * @brief OTP lock states
 */
typedef enum pufs_otp_lock {
    NA,  ///< No-Access
    RO,  ///< Read-Only
    RW,  ///< Read-Write
    N_OTP_LOCK_T,
} pufs_otp_lock_Type;

/**
 * @brief PUFrt slots
 */
typedef enum pufs_rt_slot_t {
    // PUF slots
    PUFSLOT_0,                      ///< PUF slot 0, 256 bits
    DEFAULT_PUFSLOT = PUFSLOT_0,    ///< Default PUF slot
    PUFSLOT_1,                      ///< PUF slot 1, 256 bits
    PUFSLOT_2,                      ///< PUF slot 2, 256 bits
    PUFSLOT_3,                      ///< PUF slot 3, 256 bits
    // OTP key slots
    OTPKEY_0,                       ///< OTP key slot 0, 256 bits
    OTPKEY_1,                       ///< OTP key slot 1, 256 bits
    OTPKEY_2,                       ///< OTP key slot 2, 256 bits
    OTPKEY_3,                       ///< OTP key slot 3, 256 bits
    OTPKEY_4,                       ///< OTP key slot 4, 256 bits
    OTPKEY_5,                       ///< OTP key slot 5, 256 bits
    OTPKEY_6,                       ///< OTP key slot 6, 256 bits
    OTPKEY_7,                       ///< OTP key slot 7, 256 bits
    OTPKEY_8,                       ///< OTP key slot 8, 256 bits
    OTPKEY_9,                       ///< OTP key slot 9, 256 bits
    OTPKEY_10,                      ///< OTP key slot 10, 256 bits
    OTPKEY_11,                      ///< OTP key slot 11, 256 bits
    OTPKEY_12,                      ///< OTP key slot 12, 256 bits
    OTPKEY_13,                      ///< OTP key slot 13, 256 bits
    OTPKEY_14,                      ///< OTP key slot 14, 256 bits
    OTPKEY_15,                      ///< OTP key slot 15, 256 bits
    OTPKEY_16,                      ///< OTP key slot 16, 256 bits
    OTPKEY_17,                      ///< OTP key slot 17, 256 bits
    OTPKEY_18,                      ///< OTP key slot 18, 256 bits
    OTPKEY_19,                      ///< OTP key slot 19, 256 bits
    OTPKEY_20,                      ///< OTP key slot 20, 256 bits
    OTPKEY_21,                      ///< OTP key slot 21, 256 bits
    OTPKEY_22,                      ///< OTP key slot 22, 256 bits
    OTPKEY_23,                      ///< OTP key slot 23, 256 bits
    OTPKEY_24,                      ///< OTP key slot 24, 256 bits
    OTPKEY_25,                      ///< OTP key slot 25, 256 bits
    OTPKEY_26,                      ///< OTP key slot 26, 256 bits
    OTPKEY_27,                      ///< OTP key slot 27, 256 bits
    OTPKEY_28,                      ///< OTP key slot 28, 256 bits
    OTPKEY_29,                      ///< OTP key slot 29, 256 bits
    OTPKEY_30,                      ///< OTP key slot 30, 256 bits
    OTPKEY_31,                      ///< OTP key slot 31, 256 bits
} pufs_rt_slot_Type;

/**
 * @brief PUF UID length in bytes.
 */
#define UIDLEN 32

/**
 * @brief PUF UID.
 */
typedef struct pufs_uid_st {
    unsigned char uid[UIDLEN]; ///< UID container
} pufs_uid_st_Type ;

/**
 * @brief OTP addressing type.
 */
typedef unsigned short pufs_otp_addr_t;

/**
 * @brief Initialize PUFsrt module.
 * @param[in] rt_offset  PUFsrt offset of memory map.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rt_module_init(uint32_t rt_offset);

/**
 * @brief Export the unique device identity (256-bit).
 * @param[out] uid   The unique device identity.
 * @param[in]  slot  PUF slot.
 * @return pufs_status_Type value.
 * @note In PUFcc, only PUFSLOT_0 is available for read. Other 3 PUF slots are
 *        reserved for internal use in cryptographic engines.
 */
pufs_status_Type pufs_get_uid(pufs_uid_st_Type* uid, pufs_rt_slot_Type slot);

/**
 * @brief Read 32-bit random blocks from RNG.
 * @param[out] rand     Output random blocks
 * @param[in]  numblks  Number of blocks to be generated, each block 32 bits.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rand(unsigned char* rand, uint32_t numblks);

/**
 * @brief Read from OTP with boundary check.
 * @param[out] outbuf  OTP data.
 * @param[in]  len     The length of data in bytes.
 * @param[in]  addr    Sarting address of the read.
 * @return pufs_status_Type value.
 * @note \em addr must be aligned to 4 bytes boundary
 */
pufs_status_Type pufs_read_otp(unsigned char* outbuf, uint32_t len, pufs_otp_addr_t addr);

/**
 * @brief Write to OTP with boundary check.
 * @param[in] inbuf  The data to be written to OTP.
 * @param[in] len    The length of data in bytes.
 * @param[in] addr   Starting OTP address to be programmed.
 * @return pufs_status_Type value.
 * @note \em addr must be aligned to 4 bytes boundary
 */
pufs_status_Type pufs_program_otp(
		const unsigned char* inbuf,
		uint32_t len,
		pufs_otp_addr_t addr);

/**
 * @brief Set OTP lock state.
 * @param[in] addr  Starting OTP address lock state to be set.
 * @param[in] len   The length of OTP data in bytes.
 * @param[in] lock  The lock state.
 * @return pufs_status_Type value.
 * @note \em addr must be aligned to 4 bytes boundary.
 */
pufs_status_Type pufs_lock_otp(
		pufs_otp_addr_t addr,
		uint32_t len,
		pufs_otp_lock_Type lock);

/**
 * @brief Import a cleartext key into OTP with boundary check.
 * @param[in] slot     OTP key slot.
 * @param[in] key      The plaintext key to be imported.
 * @param[in] keybits  Key length in bits. (max key bit length: 2047)
 * @return pufs_status_Type value.
 * @note Each OTP key slot is 256-bit. For a key of length \f$b\f$ bits, the
 *       slot number \em n (starting with 0) MUST be a multiple of \f$2^k\f$
 *       where \f$k\f$ is the smallest integer such that \f$b \le 256 \cdot
 *       2^k\f$. For example, a 384-bit key can be programmed in OTPKEY_0,
 *       OTPKEY_2, and so forth.
 */
pufs_status_Type pufs_program_key2otp(
		pufs_rt_slot_Type slot,
		const unsigned char* key,
		uint32_t keybits);

/**
 * @brief Zeroize PUF slot.
 * @param[in] slot  PUF slot.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_zeroize(pufs_rt_slot_Type slot);

/**
 * @brief PUFrt post masking.
 * @param[in] maskslots  The bitmap of \ref pufs_rt_slot_Type slots to be masked.
 * @return pufs_status_Type value.
 * @note \em maskslots is constructed by bit-wise or of \ref MASK_BIT outputs
 *       of the PUF slots/OTP key slots. For example, if PUFSLOT_1 and OTPKEY_2
 *       is designed to be masked, the input is \n
 *        MASK_BIT(PUFSLOT_1) | MASK_BIT(OTPKEY_2)
 */
pufs_status_Type pufs_post_mask(uint64_t maskslots);

/**
 * @brief Read version and features register value.
 * @param[out] version   Version register value.
 * @param[out] features  Features register value.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_rt_version(uint32_t* version, uint32_t* features);

/**
 * @brief Get OTP rwlck value.
 * @param[in] addr  The address of the rwlck.
 * @return          The rwlck bits.
 */
pufs_otp_lock_Type pufs_get_otp_rwlck(pufs_otp_addr_t addr);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_RT_H */
