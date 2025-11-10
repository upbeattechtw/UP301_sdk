/**
 * @file      pufs_ecc_internal.h
 * @brief     PUFsecurity ECC internal interface
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

#ifndef PUFS_ECC_INTERNAL_H
#define PUFS_ECC_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

#include "pufs_common.h"
#include "pufs_ecc.h"

/**
 * @brief Reverse byte order of an array of specific length
 * @param dst The pointer to the space for reversed data store
 * @param src The pointer to the data to be reversed
 * @param len The length of the data to be reversed
 * @return pufs_status_Type value.
 */
pufs_status_Type reverse(uint8_t* dst, const uint8_t* src, size_t len);
/**
 * @brief Prepare the number retrieved from the hash value for ECDSA
 * @param name The elliptic curve name
 * @param z The number
 * @param md The hash value
 * @param mdlen The hash length
 * @return pufs_status_Type value.
 */
pufs_status_Type get_z(pufs_ec_name_Type name, uint8_t* z, const uint8_t* md, size_t mdlen);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_ECC_INTERNAL_H */
