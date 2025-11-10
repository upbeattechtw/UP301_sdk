/**
 * @file      pufs_dma_internal.h
 * @brief     PUFsecurity DMA internal interface
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

#ifndef PUFS_DMA_INTERNAL_H
#define PUFS_DMA_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#include "pufs_dma.h"
#include "pufs_dma_regs.h"
#include "pufs_ka.h"

#define DMA_VERSION 0x505000A1

#define DEFAULT_DESC_MEM_SIZE 2048
#define SGDMA_DESCRIPTOR_SIZE   32

#undef DMADIRECT
#ifdef NO_ALLOCATE_MEM
#ifndef DMABUFFER
#define DMADIRECT
#endif /*DMABUFFER */
#endif /* NO_ALLOCATE_MEM */

typedef struct dma_sg_mem {
    uintptr_t base_addr;
    uintptr_t virt_base_addr;
    uint32_t desc_bitmap;
} dma_sg_mem_Type ;

typedef struct dma_desc_cfg {
    uintptr_t base_addr;
    uintptr_t virt_addr;
    size_t    size;
    pufs_dma_dsc_attr_Type attr;
} dma_desc_cfg_Type;

typedef struct pufs_dma {
	pufs_dma_regs_Type *regs;
    uintptr_t             read_addr;
    uintptr_t             read_virt_addr;
    uintptr_t             write_addr;
    uintptr_t             write_virt_addr;
    size_t                buff_size;
} pufs_dma_Type;

typedef struct pufs_dma_sg_internal_desc {
    uint32_t write_addr;
    uint32_t read_addr;
    uint32_t length;
    uint32_t next;
    uint32_t cfg;
    uint32_t key_cfg;
    uint32_t cypt_cfg[2];
} pufs_dma_sg_internal_desc_Type;

typedef struct dma_sg_desc_opts
{
    bool    head;
    bool    tail;
    bool    done_interrupt;
    bool    done_pause;
    bool    no_crypto;
    unsigned char offset;
} pufs_dma_sg_desc_opts_st;

extern pufs_dma_Type pufs_dma;

#ifndef DMADIRECT
pufs_status_Type clear_dma_read(uint32_t len);
pufs_status_Type dma_read_output(unsigned char* addr, uint32_t len);
#else
#define clear_dma_read(...)
#define dma_read_output(...)
#endif /* DMADIRECT */

pufs_status_Type dma_write_rwcfg(const unsigned char *out, const unsigned char *in, uint32_t len);
pufs_status_Type dma_write_key_config_0(pufs_key_type_Type keytype, pufs_algo_type_Type algo, uint32_t size, uint32_t slot_index);
pufs_status_Type dma_write_cl_config_0(uint32_t value);
pufs_status_Type dma_write_config_0(bool rng_enable, bool sgdma_enable, bool no_cypt);
pufs_status_Type dma_write_data_block_config(bool head, bool tail, bool dn_intrpt, bool dn_pause, uint32_t offset);
pufs_status_Type dma_write_data_dsc_config(pufs_dma_sg_desc_opts_st *opts, pufs_dma_dsc_attr_Type *attr, bool no_crypto);
void dma_write_start(void);
bool dma_check_busy_status(uint32_t *status);

pufs_dma_sg_internal_desc_Type *dma_sg_new_read_ctx_descriptor(uintptr_t crypto_ctx);
pufs_dma_sg_internal_desc_Type *dma_sg_new_data_descriptor(void);
pufs_dma_sg_internal_desc_Type *dma_sg_new_write_ctx_descriptor(uintptr_t crypto_ctx);
void dma_sg_free_descriptor(pufs_dma_sg_internal_desc_Type *desc);
void dma_sg_free_all_descriptor(void);
pufs_status_Type dma_sg_desc_append_to_list(pufs_dma_sg_internal_desc_Type *desc);

pufs_status_Type dma_sg_desc_write_addr(pufs_dma_sg_internal_desc_Type *desc,
                            uintptr_t write_addr,
                            uintptr_t read_addr,
                            uint32_t length);
pufs_status_Type dma_sg_desc_write_dsc_config(pufs_dma_sg_internal_desc_Type *desc,
		pufs_dma_dsc_attr_Type *attr,
                                  pufs_dma_sg_desc_opts_st *opts);
pufs_status_Type dma_sg_desc_write_key_config(pufs_dma_sg_internal_desc_Type *desc,
		pufs_key_type_Type keytype, pufs_algo_type_Type algo,
                                  uint32_t size, uint32_t slot_index);
pufs_status_Type dma_sg_desc_write_crypto_config(pufs_dma_sg_internal_desc_Type *desc, uint32_t cfg0, uint32_t cfg1);

#if 0
// Internal IP test functions
void dma_test(void);
void dump_rand_dma_test(bool entropy);
#endif

#ifdef __cplusplus
} // Closing brace for extern "C".
#endif

#endif /* PUFS_DMA_INTERNAL_H */
