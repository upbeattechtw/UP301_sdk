/**
 * @file      pufs_common.h
 * @brief     PUFsecurity common API interface
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
#ifndef PUFS_COMMON_H
#define PUFS_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* for ISR mode */
#include "metal-platform.h"
#include "metal/upt_isr.h"

/* Register address */
#define	PUF_KWP_BASE			0x300
#define	PUF_CMAC_BASE			0x220
#define	PUF_HMAC_HASH_BASE		0x800
#define	PUF_SP38A_BASE			0x200
#define	PUF_SP38C_BASE			0x240
#define	PUF_SP38D_BASE			0x260
#define	PUF_SP38E_BASE			0x280
#define PUF_IETF_RFC_8439_BASE	0x400
#define PUF_KDF_SM2_BASE		0x900
#define PUF_PKC_BASE			0x1000

/* Register offset field */
#define	PUF_INTRPT_OFFSET	0x4
#define INTRPT_ST			(0x1 << 0)  // interrupt status
#define	INTRPT_EN			(0x1 << 16) // interrupt enable

/**
 * @brief Convert number of bits to number of bytes.
 * @param[in] bits  Number of bits.
 * @return          Number of bytes.
 */
#define b2B(bits) (((bits) + 7) / 8)

/**
 * @brief Convert number of bytes to number of bits.
 * @param[in] len  Number of bytes.
 * @return         Number of bits.
 */
#define B2b(len) (8 * (len))

/**
 * @brief Convert test cases parameters.
 * @param[in] type  Type of test cases.
 * @param[in] var   Test case variable.
 * @return          num, var
 */
#define TCPARAM(type, var) (sizeof(var) / sizeof(type)), (var)

/** @brief Block size in bytes of block cipher algorithms */
#define BC_BLOCK_SIZE 16


/**
 * @brief Status code
 */
typedef enum pufs_status {
    SUCCESS,     ///< Success.
    E_ALIGN,     ///< Address alignment mismatch.
    E_OVERFLOW,  ///< Space overflow.
    E_UNDERFLOW, ///< Size too small.
    E_INVALID,   ///< Invalid argument.
    E_BUSY,      ///< Resource is occupied.
    E_UNAVAIL,   ///< Resource is unavailable.
    E_FIRMWARE,  ///< Firmware error.
    E_VERFAIL,   ///< Invalid public key or digital signature.
    E_ECMPROG,   ///< Invalid ECC microprogram.
    E_DENY,      ///< Access denied.
    E_UNSUPPORT, ///< Not support.
    E_INFINITY,  ///< Point at infinity.
    E_ERROR,     ///< Unspecific error.
} pufs_status_Type;

/**
 * @brief Block cipher algorithm.
 */
typedef enum pufs_cipher {
    AES,        ///< AES
    SM4,        ///< SM4
    CHACHA,     ///< CHACHA
    N_CIPHER_T, // keep in the last one
} pufs_cipher_Type;

/** @brief Maximum message digest length in bytes. */
#ifndef DLEN_MAX
#define DLEN_MAX 64
#endif

/**
 * @brief Message digest structure.
 */
typedef struct pufs_dgst_st {
    uint32_t dlen;                ///< Current message digest length in bytes.
    uint8_t dgst[DLEN_MAX]; ///< Message digest.
} pufs_dgst_st_Type;

/**
 * @brief Initialize PUFs module.
 * @param[in] base_addr  base address of PUFs memory map.
 * @param[in] size  total size of PUFs memory map.
 * @return pufs_status_Type value.
 */
pufs_status_Type pufs_module_init(uintptr_t base_addr, size_t size);

/**
 * @brief Release PUFs module
 * @remarks no return value.
 */
void pufs_release(void);

/**
 * @brief Return status message.
 * @return Error code string.
 */
char *pufs_strstatus(pufs_status_Type status);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_COMMON_H */
