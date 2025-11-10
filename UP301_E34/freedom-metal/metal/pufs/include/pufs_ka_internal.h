/**
 * @file      pufs_ka_internal.h
 * @brief     PUFsecurity KA internal interface
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
#ifndef PUFS_KA_INTERNAL_H
#define PUFS_KA_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pufs_ka.h"
#include "pufs_ka_regs.h"
#include "pufs_kwp_regs.h"

#define KA_VERSION  0x505001A0
#define KWP_VERSION 0x33384600

extern pufs_ka_regs_Type  *ka_regs;
extern pufs_kwp_regs_Type *kwp_regs;

/**
 * @brief Enable or disable the PUF KWP interrupt.
 *
 * @param enable Set to 1 to enable the interrupt, 0 to disable.
 */
void enable_puf_kwp_isr(uint8_t enable);

/**
 * @brief check if key slot settings is available.
 * @param[in] valid    Check the KA register to ensure the key is valid if true.
 * @param[in] keytype  The type of source which the key is from.
 * @param[in] slot     The slot of the source which the key is stored in.
 * @param[in] keybits  The key length in bits. keybits can be 0.
 * @return pufs_status_Type value.
 * FIXME: Add explanation on when keybits should be 0.
 */
pufs_status_Type keyslot_check(
		bool valid,
		pufs_key_type_Type keytype,
		uint32_t slot,
		uint32_t keybits);

/**
 * @brief get the key slot index to be set in register interface.
 * @param keytype The type of source which the key is from.
 * @param slot The slot of the source which the key is stored in.
 * @param keybits The key length in bits.
 * @return SUCCESS on success, otherwise an error code.
 */
int get_key_slot_idx(pufs_key_type_Type keytype, uint32_t keyslot);

/**
 * @brief get the key bit length in the shared secret slot
 * @param[out] keybits  The key length in bits.
 * @param[in]  keyslot  The shared secret keyslot.
 * @return pufs_status_Type value.
 */
pufs_status_Type get_ss_keybits(uint32_t* keybits, pufs_ka_slot_Type keyslot);

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_KA_INTERNAL_H */
