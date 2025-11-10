/**
 * @file      pufs_pal.h
 * @brief     PUFsecurity platform abstraction layer interface
 * @copyright 2022 PUFsecurity
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

#ifndef PUFS_PAL_H
#define PUFS_PAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <stdint.h>

#define PRINT(...) printf(__VA_ARGS__)

// NOTE: The address translation APIs are for call APIs on user-space mode.
// Change the definitions to empty if the translation is not required.
#define PHY_ADDR(virt_addr) pufs_pal_phy_addr(virt_addr)
#define VIRT_ADDR(phy_addr) pufs_pal_virt_addr(phy_addr)

/**
 * @brief Translate a virtual address to a physical address
 * @param[in] virt_addr  A virtual address
 */
uintptr_t pufs_pal_phy_addr(uintptr_t virt_addr);

/**
 * @brief Translate a physical address to a virtual address
 * @param[in] phy_addr  A physical address
 */
uintptr_t pufs_pal_virt_addr(uintptr_t phy_addr);

/**
 * @brief Initialize platform abstraction layer.
 *        It could be an empty function if initialization is not required.
 * @param[in] config  config address
 */
void pufs_pal_init(void *config);

/**
 * @brief Release platform abstraction layer.
 */
void pufs_pal_release(void);

/**
 * @brief Create a new mapping in the virtual address space.
 * 
 * @param[out] virt_addr  A mapped virtual address
 * @param[in]  phy_addr   Base physical address for mapping
 * @param[in]  size       The mmaped memory size.
 */
int pufs_pal_mmap(uintptr_t *virt_addr, const uintptr_t phy_addr, size_t size);

/**
 * @brief Release a mapped virtual address space.
 * @param[in]  virt_addr  A mapped virtual address
 * @param[in]  size       The mmaped memory size
 */
void pufs_pal_ummap(const uintptr_t virt_addr, size_t size);

/**
 * @brief   Setup DMA configuration for DMA module of PUFcc.
 *          For example, setup internal write/read addresses for further usage.
 * @return  On success, 0 is returned. On error, a negative number is returned for error handling.
 */
int pufs_pal_config_dma(void);

/**
 * @brief      To handle some cases that the address of input data may not be the address for DMA module
 *             (e.g. there is a fixed internal buffer for DMA module, and input data will copy to the internal buffer),
 *             we use pufs_pal_dma_write_addr function to serve different implementation.
 * 
 * @param[in]  in    an input address
 * @param[in]  size  the length of input
 * @return     The write address for PUFcc DMA module.
 */
uintptr_t pufs_pal_dma_write_addr(const void *in, size_t len);

/**
 * @brief      To handle some cases that the address of output data may not be the address for DMA module
 *             we use pufs_pal_dma_read_addr function to serve different implementation.
 * @param[in]  out  an output address
 * @return     The read address for PUFcc DMA module.
 */
uintptr_t pufs_pal_dma_read_addr(const void *out);

/**
 * @brief      Read output from DMA buffer
 * @param[in]  out  an output buffer
 * @param[in]  len  the length to be read out
 */
void pufs_pal_read_from_dma(void *out, size_t len);

/**
 * @brief	Initialize interrupt handler.
 * @param[in]	handler	ISR function.
 * @param[in]	data	transmitted data.
 */
void pufs_pal_init_interrupt(void *handler, void *data);

/**
 * @brief	Initialize software interrupt handler.
 * @param[in]	sw_isr_handler	Software ISR function.
 */
void pufs_pal_init_sw_interrupt(void *sw_isr_handler);

/**
 * @brief	Clear software interrupt signal.
 * @param[in]	sw_isr_handler	Software ISR function.
 */
void pufs_pal_clear_sw_interrupt(void);

/**
 * @brief	Trigger software ISR.
 */
void pufs_pal_trigger_sw_interrupt(void);

#ifdef UP301_MEM_ACCESS_ISSUE
/**
 * @brief	Trigger software ISR.
 * @param[in]	dst	Destination address.
 * @param[in]	src	Source address.
 * @param[in]	len	Length to move.
 */
void pufs_pal_memcpy (void *dst, const void *src, size_t len);
#endif

/**
 * @brief  Copy memory in 32-bit word units for hardware that only supports
 *         one word (4 bytes) load/store at a time.
 * @param[out] dst  Destination buffer (must be 4-byte aligned).
 * @param[in]  src  Source buffer (must be 4-byte aligned).
 * @param[in]  size Number of bytes to copy (must be a multiple of 4).
 */
void pufs_pal_memcpy_word(void *dst, const void *src, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* PUFS_PAL_H */
