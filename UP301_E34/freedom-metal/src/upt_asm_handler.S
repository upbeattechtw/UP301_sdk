/*
 * Copyright (C) 2025 UpbeatTech Inc. All Rights Reserved
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX short identifier: Apache-2.0
 */

#ifndef UPT_HANDLER_S
#define UPT_HANDLER_S

#define BACKUP_MTIMER       0x0200BFF8UL
#define BACKUP_MTIMERCMP    0x02004000UL
#define OTP_CTRL_BASE_ADDR  0x200B3200UL
#define XIP_CTRL_BASE_ADDR  0x200A0000UL
#define PLIC_CTRL_BASE_ADDR 0x0C000000UL
#define PLIC_CTRL_EN_ADDR   0x0C002000UL
#define BOOT_ADDR           0x40000000UL
#define BACKUP_CSRS         0x50177000UL
#define REGBYTES            4

  .section .FwHandler.warm,"ax",@progbits
  //.section .text
  .align 4
  .global _upt_warmboot
  .type _upt_warmboot, @function
  .global _upt_enter_sleep
  .type _upt_enter_sleep, @function

_upt_warmboot:
    // If pseudo warmboot
    li      a0, 0x2
    li      t1, 0x20000000
    lw      t0, 0x164(t1)
    and     t0, t0, a0
    bne     t0, x0, _restore_param

    /**
    * - Restore I/O pads
    *   - Clear @ref SCU_XIP_IO_RET_EN and @ref SCU_NAON_IO_RET_EN bit
    */
    li      t1, 0x20020000
    lw      t0, 0x01C(t1)
    li      t2, 0xFFFFFFF9
    and     t0, t0, t2
    sw      t0, 0x01C(t1)

_restore_param:
    // Restore cpu context
    li      a1, BACKUP_CSRS      //pointer to L2 0x50177000

    /* Restore OTP configurations */
    li      t2, OTP_CTRL_BASE_ADDR
    lw      t0, 90*REGBYTES(a1) //4*90
    sw      t0, 0xB4(t2)
    lw      t0, 91*REGBYTES(a1) //4*91
    sw      t0, 0xB8(t2)
    lw      t0, 92*REGBYTES(a1) //4*92
    sw      t0, 0xBC(t2)

    // Restore the E31 CSRs
    lw      a0, 2*REGBYTES(a1)  //4*2
    csrw    misa, a0
    lw      a0, 3*REGBYTES(a1)  //4*3
    csrw    mscratch, a0
    lw      a0, 4*REGBYTES(a1)  //4*4
    csrw    mtvec, a0
    lw      a0, 5*REGBYTES(a1)  //4*5
    li      t0, 0xFFFFFFF7    // (keep mstatus.MIE = 0)
    and     a0, t0, a0
    csrw    mstatus, a0
    lw      a0, 6*REGBYTES(a1)  //4*6
    csrw    mepc, a0
    lw      a0, 7*REGBYTES(a1)  //4*7
    csrw    mie, a0
    lw      a0, 8*REGBYTES(a1)  //4*8
    csrw    mcause, a0
    lw      a0, 9*REGBYTES(a1)  //4*9
    csrw    mtval, a0
    lw      a0, 10*REGBYTES(a1)  //4*10
    csrw    minstret, a0
    lw      a0, 11*REGBYTES(a1) //4*11
    csrw    minstreth, a0
    lw      a0, 12*REGBYTES(a1) //4*12
    csrw    mcycle, a0
    lw      a0, 13*REGBYTES(a1) //4*13
    csrw    mcycleh, a0
    lw      a0, 14*REGBYTES(a1) //4*14
    csrw    mhpmcounter3, a0
    lw      a0, 15*REGBYTES(a1) //4*15
    csrw    mhpmcounter3h, a0
    lw      a0, 16*REGBYTES(a1) //4*16
    csrw    mhpmcounter4, a0
    lw      a0, 17*REGBYTES(a1) //4*17
    csrw    mhpmcounter4h, a0
    lw      a0, 18*REGBYTES(a1) //4*18
    csrw    mhpmevent3, a0
    lw      a0, 19*REGBYTES(a1) //4*19
    csrw    mhpmevent4, a0
    lw      a0, 20*REGBYTES(a1) //4*20
    csrw    pmpcfg0, a0
    lw      a0, 21*REGBYTES(a1) //4*21
    csrw    pmpcfg1, a0
    lw      a0, 22*REGBYTES(a1) //4*22
    csrw    pmpaddr0, a0
    lw      a0, 23*REGBYTES(a1) //4*23
    csrw    pmpaddr1, a0
    lw      a0, 24*REGBYTES(a1) //4*24
    csrw    mcounteren, a0
    li      t0, BACKUP_MTIMER
    lw      a0, 26*REGBYTES(a1) //4*26
    sw      a0, 4(t0)
    lw      a0, 25*REGBYTES(a1) //4*25
    sw      a0, 0(t0)
    li      t0, BACKUP_MTIMERCMP
    lw      a0, 29*REGBYTES(a1) //4*29
    sw      a0, 4(t0)
    lw      a0, 27*REGBYTES(a1) //4*27
    sw      a0, 0(t0)

    /* Restore XIP configurations */
    li      t2, XIP_CTRL_BASE_ADDR
    /* Stop internal clock  */
    lw      t0, 0x010(t2)
    li      a0, 0xFFFEFFFE
    and     t0, t0, a0
    sw      t0, 0x010(t2)
    /* Wait iclk stop status is ready */
_wait_xip_iclk_stop:
    lw      t0, 0x0E0(t2)
    andi    t0, t0, 0x10
    beqz    t0, _wait_xip_iclk_stop
    /* Register Write Eanble bit = 1 */
    li      t0, 0x1
    sw      t0, 0x0FC(t2)
    /* Wait Register Write Eanble status is ready */
_wait_xip_reg_rdy:
    lw      t0, 0x0E0(t2)
    andi    t0, t0, 0x80
    beqz    t0, _wait_xip_reg_rdy

    lw      a0, 30*REGBYTES(a1) //4*30
    sw      a0, 0x004(t2)
//    lw      t0, 31*REGBYTES(a1) //4*31
//    sw      t0, 0x010(t2)
    lw      t0, 32*REGBYTES(a1) //4*32
    sw      t0, 0x014(t2)
    lw      t0, 33*REGBYTES(a1) //4*33
    sw      t0, 0x018(t2)
    lw      t0, 34*REGBYTES(a1) //4*34
    sw      t0, 0x024(t2)
    lw      t0, 35*REGBYTES(a1) //4*35
    sw      t0, 0x028(t2)
    lw      t0, 36*REGBYTES(a1) //4*36
    sw      t0, 0x034(t2)
    lw      t0, 37*REGBYTES(a1) //4*37
    sw      t0, 0x044(t2)
    lw      t0, 38*REGBYTES(a1) //4*38
    sw      t0, 0x048(t2)
    lw      t0, 39*REGBYTES(a1) //4*39
    sw      t0, 0x064(t2)
    lw      t0, 40*REGBYTES(a1) //4*40
    sw      t0, 0x068(t2)
    lw      t0, 41*REGBYTES(a1) //4*41
    sw      t0, 0x074(t2)
    lw      t0, 42*REGBYTES(a1) //4*42
    sw      t0, 0x078(t2)
    lw      t0, 43*REGBYTES(a1) //4*43
    sw      t0, 0x094(t2)
    lw      t0, 44*REGBYTES(a1) //4*44
    sw      t0, 0x098(t2)
    lw      t0, 45*REGBYTES(a1) //4*45
    sw      t0, 0x0A4(t2)
    lw      t0, 46*REGBYTES(a1) //4*46
    sw      t0, 0x0B0(t2)
    lw      t0, 47*REGBYTES(a1) //4*47
    sw      t0, 0x0C4(t2)
    lw      t0, 48*REGBYTES(a1) //4*48
    sw      t0, 0x0C8(t2)
    /* Register Write Eanble bit = 0 */
    sw      x0, 0x0FC(t2)
    /* Restore clock control register (iclk = 1) */
    lw      t0, 31*REGBYTES(a1) //4*31
    sw      t0, 0x010(t2)
_wait_xip_iclk_start:
    lw      t0, 0x0E0(t2)
    andi    t0, t0, 0x10
    bne     t0, x0, _wait_xip_iclk_start

    /* Restore sp and ra */
    lw      sp, 0(a1)           //4*0
    lw      ra, 1*REGBYTES(a1)  //4*1

    lw      gp, 50*REGBYTES(a1)  //4*50
    lw      tp, 51*REGBYTES(a1)  //4*51
    lw      x5, 52*REGBYTES(a1)  //4*52
    lw      x6, 53*REGBYTES(a1)  //4*53
    lw      x7, 54*REGBYTES(a1)  //4*54
    lw      x8, 55*REGBYTES(a1)  //4*55
    lw      x9, 56*REGBYTES(a1)  //4*56
    lw      x10, 57*REGBYTES(a1)  //4*57
    //lw      x11, 58*REGBYTES(a1)  //4*58
    lw      x12, 59*REGBYTES(a1)  //4*59
    lw      x13, 60*REGBYTES(a1)  //4*60
    lw      x14, 61*REGBYTES(a1)  //4*61
    lw      x15, 62*REGBYTES(a1)  //4*62
    lw      x16, 63*REGBYTES(a1)  //4*63
    lw      x17, 64*REGBYTES(a1)  //4*64
    lw      x18, 65*REGBYTES(a1)  //4*65
    lw      x19, 66*REGBYTES(a1)  //4*66
    lw      x20, 67*REGBYTES(a1)  //4*67
    lw      x21, 68*REGBYTES(a1)  //4*68
    lw      x22, 69*REGBYTES(a1)  //4*69
    lw      x23, 70*REGBYTES(a1)  //4*70
    lw      x24, 71*REGBYTES(a1)  //4*71
    lw      x25, 72*REGBYTES(a1)  //4*72
    lw      x26, 73*REGBYTES(a1)  //4*73
    lw      x27, 74*REGBYTES(a1)  //4*74
    lw      x28, 75*REGBYTES(a1)  //4*75
    lw      x29, 76*REGBYTES(a1)  //4*76
    lw      x30, 77*REGBYTES(a1)  //4*77
    lw      x31, 78*REGBYTES(a1)  //4*78

    /* Restore PLIC configurations */
    li      t2, PLIC_CTRL_BASE_ADDR
    lw      t0, 80*REGBYTES(a1) //4*80
    sw      t0, 0x0(t2)
    lw      t0, 81*REGBYTES(a1) //4*81
    sw      t0, 0x4(t2)
    lw      t0, 82*REGBYTES(a1) //4*82
    sw      t0, 0x8(t2)
    lw      t0, 83*REGBYTES(a1) //4*83
    sw      t0, 0xC(t2)
    lw      t0, 84*REGBYTES(a1) //4*84
    li      t2, PLIC_CTRL_EN_ADDR
    sw      t0, 0x0(t2)
    lw      t0, 85*REGBYTES(a1) //4*85
    sw      t0, 0x4(t2)
    lw      t0, 86*REGBYTES(a1) //4*86
    sw      t0, 0x8(t2)
    lw      t0, 87*REGBYTES(a1) //4*87
    sw      t0, 0xC(t2)

    ret

_upt_enter_sleep:
    /* Save cpu context */
    li      a1, BACKUP_CSRS      //pointer to L2 0x50177000
    /* Save the sp and ra first */
    sw      sp, 0(a1)           //4*0
    sw      ra, 1*REGBYTES(a1)  //4*1

    sw      gp, 50*REGBYTES(a1)  //4*50
    sw      tp, 51*REGBYTES(a1)  //4*51
    sw      x5, 52*REGBYTES(a1)  //4*52
    sw      x6, 53*REGBYTES(a1)  //4*53
    sw      x7, 54*REGBYTES(a1)  //4*54
    sw      x8, 55*REGBYTES(a1)  //4*55
    sw      x9, 56*REGBYTES(a1)  //4*56
    sw      x10, 57*REGBYTES(a1)  //4*57
    //sw      x11, 58*REGBYTES(a1)  //4*58
    sw      x12, 59*REGBYTES(a1)  //4*59
    sw      x13, 60*REGBYTES(a1)  //4*60
    sw      x14, 61*REGBYTES(a1)  //4*61
    sw      x15, 62*REGBYTES(a1)  //4*62
    sw      x16, 63*REGBYTES(a1)  //4*63
    sw      x17, 64*REGBYTES(a1)  //4*64
    sw      x18, 65*REGBYTES(a1)  //4*65
    sw      x19, 66*REGBYTES(a1)  //4*66
    sw      x20, 67*REGBYTES(a1)  //4*67
    sw      x21, 68*REGBYTES(a1)  //4*68
    sw      x22, 69*REGBYTES(a1)  //4*69
    sw      x23, 70*REGBYTES(a1)  //4*70
    sw      x24, 71*REGBYTES(a1)  //4*71
    sw      x25, 72*REGBYTES(a1)  //4*72
    sw      x26, 73*REGBYTES(a1)  //4*73
    sw      x27, 74*REGBYTES(a1)  //4*74
    sw      x28, 75*REGBYTES(a1)  //4*75
    sw      x29, 76*REGBYTES(a1)  //4*76
    sw      x30, 77*REGBYTES(a1)  //4*77
    sw      x31, 78*REGBYTES(a1)  //4*78

    /* save the E31 CSRs */
    csrr    t0, misa
    sw      t0, 2*REGBYTES(a1)  //4*2
    csrr    t0, mscratch
    sw      t0, 3*REGBYTES(a1)  //4*3
    csrr    t0, mtvec
    sw      t0, 4*REGBYTES(a1)  //4*4
    csrr    t0, mstatus
    sw      t0, 5*REGBYTES(a1)  //4*5
    csrr    t0, mepc
    sw      t0, 6*REGBYTES(a1)  //4*6
    csrr    t0, mie
    sw      t0, 7*REGBYTES(a1)  //4*7
    csrr    t0, mcause
    sw      t0, 8*REGBYTES(a1)  //4*8
    csrr    t0, mtval
    sw      t0, 9*REGBYTES(a1)  //4*9
    csrr    t0, minstret
    sw      t0, 10*REGBYTES(a1)  //4*10
    csrr    t0, minstreth
    sw      t0, 11*REGBYTES(a1) //4*11
    csrr    t0, mcycle
    sw      t0, 12*REGBYTES(a1) //4*12
    csrr    t0, mcycleh
    sw      t0, 13*REGBYTES(a1) //4*13
    csrr    t0, mhpmcounter3
    sw      t0, 14*REGBYTES(a1) //4*14
    csrr    t0, mhpmcounter3h
    sw      t0, 15*REGBYTES(a1) //4*15
    csrr    t0, mhpmcounter4
    sw      t0, 16*REGBYTES(a1) //4*16
    csrr    t0, mhpmcounter4h
    sw      t0, 17*REGBYTES(a1) //4*17
    csrr    t0, mhpmevent3
    sw      t0, 18*REGBYTES(a1) //4*18
    csrr    t0, mhpmevent4
    sw      t0, 19*REGBYTES(a1) //4*19
    csrr    t0, pmpcfg0
    sw      t0, 20*REGBYTES(a1) //4*20
    csrr    t0, pmpcfg1
    sw      t0, 21*REGBYTES(a1) //4*21
    csrr    t0, pmpaddr0
    sw      t0, 22*REGBYTES(a1) //4*22
    csrr    t0, pmpaddr1
    sw      t0, 23*REGBYTES(a1) //4*23
    csrr    t0, mcounteren
    sw      t0, 24*REGBYTES(a1) //4*24
    li      a0, BACKUP_MTIMER
    lw      t0, 4(a0) //4*26
    sw      t0, 26*REGBYTES(a1)
    lw      t0, 0(a0)//4*25
    sw      t0, 25*REGBYTES(a1)
    li      a0, BACKUP_MTIMERCMP
    lw      t0, 4(a0) //4*28
    sw      t0, 28*REGBYTES(a1)
    lw      t0, 0(a0)//4*27
    sw      t0, 27*REGBYTES(a1)

    /* Save XIP configurations */
    li      t2, XIP_CTRL_BASE_ADDR
    lw      t0, 0x004(t2)
    sw      t0, 30*REGBYTES(a1) //4*30
    lw      t0, 0x010(t2)
    sw      t0, 31*REGBYTES(a1) //4*31
    lw      t0, 0x014(t2)
    sw      t0, 32*REGBYTES(a1) //4*32
    lw      t0, 0x018(t2)
    sw      t0, 33*REGBYTES(a1) //4*33
    lw      t0, 0x024(t2)
    sw      t0, 34*REGBYTES(a1) //4*34
    lw      t0, 0x028(t2)
    sw      t0, 35*REGBYTES(a1) //4*35
    lw      t0, 0x034(t2)
    sw      t0, 36*REGBYTES(a1) //4*36
    lw      t0, 0x044(t2)
    sw      t0, 37*REGBYTES(a1) //4*37
    lw      t0, 0x048(t2)
    sw      t0, 38*REGBYTES(a1) //4*38
    lw      t0, 0x064(t2)
    sw      t0, 39*REGBYTES(a1) //4*39
    lw      t0, 0x068(t2)
    sw      t0, 40*REGBYTES(a1) //4*40
    lw      t0, 0x074(t2)
    sw      t0, 41*REGBYTES(a1) //4*41
    lw      t0, 0x078(t2)
    sw      t0, 42*REGBYTES(a1) //4*42
    lw      t0, 0x094(t2)
    sw      t0, 43*REGBYTES(a1) //4*43
    lw      t0, 0x098(t2)
    sw      t0, 44*REGBYTES(a1) //4*44
    lw      t0, 0x0A4(t2)
    sw      t0, 45*REGBYTES(a1) //4*45
    lw      t0, 0x0B0(t2)
    sw      t0, 46*REGBYTES(a1) //4*46
    lw      t0, 0x0C4(t2)
    sw      t0, 47*REGBYTES(a1) //4*47
    lw      t0, 0x0C8(t2)
    sw      t0, 48*REGBYTES(a1) //4*48

    /* Save PLIC configurations */
    li      t2, PLIC_CTRL_BASE_ADDR
    lw      t0, 0x0(t2)
    sw      t0, 80*REGBYTES(a1) //4*80
    lw      t0, 0x4(t2)
    sw      t0, 81*REGBYTES(a1) //4*81
    lw      t0, 0x8(t2)
    sw      t0, 82*REGBYTES(a1) //4*82
    lw      t0, 0xC(t2)
    sw      t0, 83*REGBYTES(a1) //4*83
    li      t2, PLIC_CTRL_EN_ADDR
    lw      t0, 0x0(t2)
    sw      t0, 84*REGBYTES(a1) //4*84
    lw      t0, 0x4(t2)
    sw      t0, 85*REGBYTES(a1) //4*85
    lw      t0, 0x8(t2)
    sw      t0, 86*REGBYTES(a1) //4*86
    lw      t0, 0xC(t2)
    sw      t0, 87*REGBYTES(a1) //4*87

    /* Save OTP configurations */
    li      t2, OTP_CTRL_BASE_ADDR
    lw      t0, 0xB4(t2)
    sw      t0, 90*REGBYTES(a1) //4*90
    lw      t0, 0xB8(t2)
    sw      t0, 91*REGBYTES(a1) //4*91
    lw      t0, 0xBC(t2)
    sw      t0, 92*REGBYTES(a1) //4*92

  /**
   * - Start AxtoSx sequence (pseudo slepp or real sleep)
   *   - Set @ref ENTER_SLEEP bit
   */
    li      t1, 0x20000000
    lw      t0, 0x160(t1)
    srli    t0, t0, 5
    andi    t0, t0, 1
    li      a0, 0x1
    beq     t0, a0, _lite_softoff

   /**
   * - Retention I/O pads
   *   - Set @ref SCU_XIP_IO_RET_EN and @ref SCU_NAON_IO_RET_EN bit
   */
    li      t1, 0x20020000
    lw      t0, 0x01C(t1)
    li      t2, 0x00000006
    or      t0, t0, t2
    sw      t0, 0x01C(t1)

    li      t1, 0x20000000
    li      a0, 0x4
    sw      a0, 0x20C(t1)
    wfi
loop:
    call loop

_lite_softoff:
    /* Wait until E21 wakeup */
    li      a0, 0x1
    lw      t0, 0x164(t1)
    and     t0, t0, a0
    beqz    t0, _lite_softoff

    /* Reset IPs */
    sw      x0, 0x284(t1)
    li      t0, 0xFF9FEFFF
    sw      t0, 0x284(t1)
    li      t0, 0xFE00
    sw      t0, 0x288(t1)
    li      t0, 0xFFFF
    sw      t0, 0x288(t1)

    call    BOOT_ADDR       // Boot address

#endif  /* UPT_HANDLER_S */

