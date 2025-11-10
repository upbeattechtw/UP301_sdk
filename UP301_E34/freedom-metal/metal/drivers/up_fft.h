/**
 * ESP32 FFT
 * =========
 * This provides a vanilla radix-2 FFT implementation and a test example.
 *
 * Author
 * ------
 *
 * This code was written by [Robin Scheibler](http://www.robinscheibler.org)
 * during rainy days in October 2017.
 *
 * License
 * -------
 *
 * Copyright (c) 2017 Robin Scheibler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef METAL__DRIVERS__UPT_FFT_H
#define METAL__DRIVERS__UPT_FFT_H
#include <stdint.h>

//#define UPT_UDL1_2_FFT_BASE ((uint32_t *)0x58010000)
//#define UPT_UDL1_2_FFT_BASE  (0x58010000)

//#define UPT_FFT_REG(regAddr)                                                   \
//  (*(volatile uint32_t *)(UPT_UDL1_2_FFT_BASE + (regAddr >> 2)))

//#define UPT_FFT_REG(regAddr)                                                   \
//  (*(volatile uint32_t *)(UPT_UDL1_2_FFT_BASE + regAddr))

#define BIT(nr) ((1) << (nr))
#define GENMASK(hi, lo) (((1UL << ((hi) - (lo) + 1)) - 1) << (lo))    //Mask binary ...111111... from Hi to Lo bit

/* UPT_FFT_WO_INTR_CTRL interrupt control bit field */
#define UPT_FFT_CLR_INTR_BIT_MSK   BIT(2)
#define UPT_FFT_INTR_PIN_SELECT_MSK  GENMASK(1, 0)

/* UPT_FFT_RO_INTR_STATUS interrupt status bit field */
#define UPT_FFT_INTR_STATUS_MSK  BIT(0)

/* UPT_FFT_WO_START_CTRL start control bit field */
#define UPT_FFT_DOT_PROD_DIM_MSK     GENMASK(24, 16)
#define UPT_FFT_DOT_PROD_DIM_SHIFT   (16)
#define UPT_FFT_OVERLAP_MODE_MSK     BIT(15)
#define UPT_FFT_DISABLE_SCALING_MSK  BIT(9)
#define UPT_FFT_SIZE_CODE_MSK        GENMASK(7, 5)
#define UPT_FFT_SIZE_CODE_SHIFT      (5)
#define UPT_FFT_OP_CODE_MSK          GENMASK(4, 0)
#define UPT_FFT_OP_CODE_SHIFT        (0)

/* UPT_FFT_RO_STATUS status bit field */
#define UPT_FFT_ERR_CODE_MSK         GENMASK(19, 18)
#define UPT_FFT_ERR_CODE_SHIFT       (18)
#define UPT_FFT_ERR_BIT_MSK BIT      (17)
#define UPT_FFT_BUSY_BIT_MSK BIT     (16)
#define UPT_FFT_SCALING_FACTOR_MSK   GENMASK(8, 0)
#define UPT_FFT_SCALING_FACTOR_SHIFT (0)

#endif /* METAL__DRIVERS__UPT_FFT_H */
