/**
 * @file      pufs_ecc.h
 * @brief     PUFsecurity ECC API interface
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

/**
 * @file      pufs_ecc.h
 * @brief     PUFsecurity ECC interface
 * @copyright 2020 PUFsecurity
 */
#ifndef PUFS_ECC_H
#define PUFS_ECC_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief RSA variant.
 */
typedef enum pufs_rsa_type {
    RSA1024,      ///< RSA-1024
    RSA2048,      ///< RSA-2048
    RSA3072,      ///< RSA-3072
    RSA4096,      ///< RSA-4096
    N_RSA_TYPE_T, // keep in the last one
} pufs_rsa_type_Type;

/**
 * @brief NIST standardized elliptic curves.
 */
typedef enum pufs_ec_name_t {
#ifndef ROM_CODE
    NISTB163,   ///< NIST B-163
    NISTB233,   ///< NIST B-233
    NISTB283,   ///< NIST B-283
    NISTB409,   ///< NIST B-409
    NISTB571,   ///< NIST B-571
    NISTK163,   ///< NIST K-163
    NISTK233,   ///< NIST K-233
    NISTK283,   ///< NIST K-283
    NISTK409,   ///< NIST K-409
    NISTK571,   ///< NIST K-571
    NISTP192,   ///< NIST P-192
    NISTP224,   ///< NIST P-224
#endif
    NISTP256,   ///< NIST P-256
#ifndef ROM_CODE
    NISTP384,   ///< NIST P-384
    NISTP521,   ///< NIST P-521
#endif
    SM2,        ///< SM2
    N_ECNAME_T, // keep in the last one
} pufs_ec_name_Type;

/**
 * @brief Elliptic curve (EC) domain parameters
 */
typedef struct pufs_ecc_param_st {
    const void* field; ///< Field modulus.
    const void* a;     ///< EC parameter a.
    const void* b;     ///< EC parameter b.
    const void* px;    ///< x-coordinate of base point P.
    const void* py;    ///< y-coordinate of base point P.
    const void* order; ///< Subgroup order.
    unsigned short fbits;    ///< Field element length in bits.
    unsigned short nbits;    ///< Subgroup order length in bits.
    unsigned char ftype;     ///< Field type in hardware.
    unsigned char h;         ///< Co-factor.
    unsigned char len;       ///< Field element length in bytes.
    bool pf;           ///< Prime field flag
} pufs_ecc_param_st_Type;

/**
 * @brief Maximum field element length in bytes.
 */
#ifndef QLEN_MAX
#define QLEN_MAX 72
#endif

/**
 * @brief Elliptic curve point (x,y).
 */
typedef struct pufs_ec_point_st {
    uint32_t qlen;       ///< Field element length in bytes.
    unsigned char x[QLEN_MAX]; ///< x-coordinate
    unsigned char y[QLEN_MAX]; ///< y-coordinate
} pufs_ec_point_st_Type;

/**
 * @brief Maximum field element length in bytes.
 */
#ifndef NLEN_MAX
#define NLEN_MAX 72
#endif

/**
 * @brief ECDSA signature (r,s).
 */
typedef struct pufs_ecdsa_sig_st {
    uint32_t qlen;       ///< Field element length in bytes.
    unsigned char r[NLEN_MAX]; ///< r
    unsigned char s[NLEN_MAX]; ///< s
} pufs_ecdsa_sig_st_Type;

extern pufs_ecc_param_st_Type ecc_param[];

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_ECC_H */
