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

#ifndef METAL__DRIVERS__UPT_FIXP_FFT_H
#define METAL__DRIVERS__UPT_FIXP_FFT_H
#include <stdbool.h>

#define ROWS 3
#define COLS 3

typedef int32_t fixed_point_Type;

fixed_point_Type float_to_fixed(float f);

float fixed_to_float(fixed_point_Type fp) ;

fixed_point_Type fixed_mul(fixed_point_Type a, fixed_point_Type b);

void compute_twiddle_factors(fixed_point_Type *twiddle_real, fixed_point_Type *twiddle_imag, int32_t N);

void compute_ifft_twiddle_factors(fixed_point_Type *twiddle_real, fixed_point_Type *twiddle_imag, int32_t N);

void fft_fixed(fixed_point_Type *real, fixed_point_Type *imag, int32_t N);

void ifft_fixed(fixed_point_Type *real, fixed_point_Type *imag, int32_t N);

void generate_random_input_array(fixed_point_Type *real, fixed_point_Type *imag, int32_t N);

uint32_t generate_random_power_of_2();

bool check_data_32bit(int64_t data1,int64_t data2);

bool check_data_16bit(int64_t data1,int64_t data2);

bool check_array_dimensions(int size1,int size2);

bool isaddoverflowsigned_32bits(int32_t a, int32_t b);

bool isaddoverflowsigned_16bits(int16_t a, int16_t b);

int32_t dot_product_32bits(int32_t *array1,int32_t *array2,int32_t dim);

int16_t dot_product_16bits(int16_t *array1,int16_t *array2,uint16_t dim);

uint32_t fixed_point_sqrt(uint32_t input);

void hadamardProduct(int matrixA[ROWS][COLS], int matrixB[ROWS][COLS], int result[ROWS][COLS]);

void printMatrix(int rows, int cols, int matrix[ROWS][COLS]);

bool areMatricesEqual(int matrixA[ROWS][COLS], int matrixB[ROWS][COLS]);

#endif  //FFT fixed points H
