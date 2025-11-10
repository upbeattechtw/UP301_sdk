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

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "upt_fixp_fft.h"
#include "upt_up301.h"

#define FIXED_POINT_FRACTION_BITS 16
#define FIXED_POINT_SCALE (1 << FIXED_POINT_FRACTION_BITS)

#define MAX_EXPONENT  10  // The maximum value of the exponent, so we generate up to 2^30
#define NSET_FFTPOINT  3
#define M_PI  3.141592653589793238462643383279502884197169399375105820974944

typedef int32_t fixed_point_Type;

// Convert float to fixed-point
fixed_point_Type float_to_fixed(float f) {
    return (fixed_point_Type)(f * FIXED_POINT_SCALE);
}

// Convert fixed-point to float
float fixed_to_float(fixed_point_Type fp) {
    return (float)fp / FIXED_POINT_SCALE;
}

// Multiply two fixed-point numbers
fixed_point_Type fixed_mul(fixed_point_Type a, fixed_point_Type b) {
    return (fixed_point_Type)(((int64_t)a * b) >> FIXED_POINT_FRACTION_BITS);
}

// Compute twiddle factors
void compute_twiddle_factors(fixed_point_Type *twiddle_real, fixed_point_Type *twiddle_imag, int32_t N) {
    for (int32_t k = 0; k < N/2; k++) {
        float angle = -2.0f * M_PI * k / N;
        twiddle_real[k] = float_to_fixed(cos(angle));
        twiddle_imag[k] = float_to_fixed(sin(angle));
    }
}

// Compute IFFT twiddle factors (with positive exponent)
void compute_ifft_twiddle_factors(fixed_point_Type *twiddle_real, fixed_point_Type *twiddle_imag, int32_t N) {
    for (int32_t k = 0; k < N / 2; k++) {
        float angle = 2.0f * M_PI * k / N;
        twiddle_real[k] = float_to_fixed(cos(angle));
        twiddle_imag[k] = float_to_fixed(sin(angle));
    }
}

// Perform the FFT using fixed-point arithmetic
void fft_fixed(fixed_point_Type *real, fixed_point_Type *imag, int32_t N) {
	int32_t stages = (int32_t)(log(N) / log(2));
    fixed_point_Type twiddle_real[N / 2], twiddle_imag[N / 2];

    // Compute twiddle factors
    compute_twiddle_factors(twiddle_real, twiddle_imag, N);

    // Bit reversal
    int32_t j = 0;
    for (int32_t i = 0; i < N; i++) {
        if (i < j) {
            // Swap real[i] and real[j]
        	fixed_point_Type temp_real = real[i];
            real[i] = real[j];
            real[j] = temp_real;

            // Swap imag[i] and imag[j]
            fixed_point_Type temp_imag = imag[i];
            imag[i] = imag[j];
            imag[j] = temp_imag;
        }
        int32_t m = N >> 1;
        while (j >= m && m >= 2) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }

    // FFT butterfly operations
    for (int32_t s = 1; s <= stages; s++) {
    	int32_t m = 1 << s;
        int32_t m2 = m >> 1;
        int32_t k = 0;
        for (int32_t j = 0; j < m2; j++) {
        	fixed_point_Type w_real = twiddle_real[k];
        	fixed_point_Type w_imag = twiddle_imag[k];
            for (int32_t i = j; i < N; i += m) {
            	int32_t i1 = i + m2;
                // Butterfly calculations
                fixed_point_Type t_real = fixed_mul(w_real, real[i1]) - fixed_mul(w_imag, imag[i1]);
                fixed_point_Type t_imag = fixed_mul(w_real, imag[i1]) + fixed_mul(w_imag, real[i1]);

                real[i1] = real[i] - t_real;
                imag[i1] = imag[i] - t_imag;
                real[i] = real[i] + t_real;
                imag[i] = imag[i] + t_imag;
            }
            k += (N >> s);
        }
    }
}

// Perform IFFT using fixed-point arithmetic
void ifft_fixed(fixed_point_Type *real, fixed_point_Type *imag, int32_t N) {
	int32_t stages = (int32_t)(log(N) / log(2));
    fixed_point_Type twiddle_real[N / 2], twiddle_imag[N / 2];

    // Compute IFFT twiddle factors
    compute_ifft_twiddle_factors(twiddle_real, twiddle_imag, N);

    // Bit reversal
    int32_t j = 0;
    for (int32_t i = 0; i < N; i++) {
        if (i < j) {
            // Swap real[i] and real[j]
        	fixed_point_Type temp_real = real[i];
            real[i] = real[j];
            real[j] = temp_real;

            // Swap imag[i] and imag[j]
            fixed_point_Type temp_imag = imag[i];
            imag[i] = imag[j];
            imag[j] = temp_imag;
        }
        int32_t m = N >> 1;
        while (j >= m && m >= 2) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }

    // IFFT butterfly operations
    for (int32_t s = 1; s <= stages; s++) {
    	int32_t m = 1 << s;
        int32_t m2 = m >> 1;
        int32_t k = 0;
        for (int32_t j = 0; j < m2; j++) {
        	fixed_point_Type w_real = twiddle_real[k];
        	fixed_point_Type w_imag = twiddle_imag[k];
            for (int32_t i = j; i < N; i += m) {
            	int32_t i1 = i + m2;
                // Butterfly calculations
                fixed_point_Type t_real = fixed_mul(w_real, real[i1]) - fixed_mul(w_imag, imag[i1]);
                fixed_point_Type t_imag = fixed_mul(w_real, imag[i1]) + fixed_mul(w_imag, real[i1]);

                real[i1] = real[i] - t_real;
                imag[i1] = imag[i] - t_imag;
                real[i] = real[i] + t_real;
                imag[i] = imag[i] + t_imag;
            }
            k += (N >> s);
        }
    }

    // Scale the results by 1/N
    for (int32_t i = 0; i < N; i++) {
        real[i] /= N;
        imag[i] /= N;
    }
}

// Generate a random input array (real and imaginary parts)
void generate_random_input_array(fixed_point_Type *real, fixed_point_Type *imag, int32_t N) {
    srand(time(NULL));  // Seed the random number generator

    for (int32_t i = 0; i < N; i++) {
        float random_real = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;  // Random float between -1 and 1
        float random_imag = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;  // Random float between -1 and 1

        real[i] = float_to_fixed(random_real);  // Convert to fixed-point
        imag[i] = float_to_fixed(random_imag);  // Convert to fixed-point
    }
}

// Function to generate a random power of 2
uint32_t generate_random_power_of_2() {
    // Generate a random exponent between 0 and MAX_EXPONENT
    int32_t exponent = rand() % (MAX_EXPONENT + 1);  // Random value from 0 to MAX_EXPONENT
    // Return 2^exponent
    return 1U << exponent;  // Left shift 1 by the random exponent
}

bool check_data_32bit(int64_t data1,int64_t data2){

	if(data1 > INT32_MAX || data1 < INT32_MIN){
		printf("Input data is overflow\n");
		return false;
	}

	if(data2 > INT32_MAX || data2 < INT32_MIN){
		printf("Input data is overflow\n");
		return false;
	}

	if(data1==data2){
        return true;
	}
	else{
		printf("Two compared data are different\n");
		return false;
	}
}

bool check_data_16bit(int64_t data1,int64_t data2){

	if(data1 > INT16_MAX || data1 < INT16_MIN){
		printf("Input data is overflow\n");
		return false;
	}

	if(data2 > INT16_MAX || data2 < INT16_MIN){
		printf("Input data is overflow\n");
		return false;
	}

	if(data1==data2){
        return true;
	}
	else{
		printf("Two compared data are different\n");
		return false;
	}
}

bool check_array_dimensions(int size1,int size2){
	 return size1 == size2;
}

// Function to check if addition overflows
bool isaddoverflowsigned_32bits(int32_t a, int32_t b) {
    // Check if both numbers are positive and overflow occurs
    if (a > 0 && b > 0 && (a > INT_MAX - b)) {
        return true;
    }

    // Check if both numbers are negative and overflow occurs
    if (a < 0 && b < 0 && (a < INT_MIN - b)) {
        return true;
    }

    // No overflow
    return false;
}

// Function to check if addition overflows
bool isaddoverflowsigned_16bits(int16_t a, int16_t b) {
    // Check if both numbers are positive and overflow occurs
    if (a > 0 && b > 0 && (a > INT_MAX - b)) {
        return true;
    }

    // Check if both numbers are negative and overflow occurs
    if (a < 0 && b < 0 && (a < INT_MIN - b)) {
        return true;
    }

    // No overflow
    return false;
}

int32_t dot_product_32bits(int32_t *array1,int32_t *array2,int32_t dim)
{

	int32_t temp_result=0;
	int32_t result = 0;

	if ((dim>3)||(dim<1)){
		printf("dim should be 1~3\n");
        return E_UPT_ERROR;
	}

	    for (int32_t i = 0; i < dim; i++) {
	    	   temp_result = array1[i] * array2[i];

	    	   if ((temp_result > 0 && result > INT32_MAX  - temp_result) || (temp_result < 0 && result < INT32_MIN - temp_result)) {
	    		   printf("32bits Dot product result overflow\n");
	    		   return E_UPT_ERROR; // Overflow detected
	    	   }


	           result+=temp_result;

	            if((array1[i]!=0)&&((temp_result/array1[i])!=array2[i])){
	            	printf("32 bits Dot product result overflow\n");
	            	return E_UPT_ERROR;
	            }

	    }

	    return result;

}

int16_t dot_product_16bits(int16_t *array1,int16_t *array2,uint16_t dim)
{

	int16_t temp_result=0;
	int16_t result = 0;

	if ((dim>511)||(dim<0)){
		printf("dim should be 0~511\n");
        return E_UPT_ERROR;
	}

	    for (uint16_t i = 0; i < dim; i++) {
	    	   temp_result = array1[i] * array2[i];

	    	   if ((temp_result > 0 && result > INT16_MAX  - temp_result) || (temp_result < 0 && result < INT16_MIN - temp_result)) {
	    		   printf("16bits Dot product result overflow\n");
	    		   return E_UPT_ERROR; // Overflow detected
	    	   }

	           result+=temp_result;

	            if((array1[i]!=0)&&((temp_result/array1[i])!=array2[i])){
	            	printf("16bits Dot product result overflow\n");
	            	return E_UPT_ERROR;
	            }

	    }

	    return result;

}

// Function to compute the fixed-point square root
uint32_t fixed_point_sqrt(uint32_t input) {
    if (input == 0) return 0;  // Special case: sqrt(0) = 0

    uint32_t result = 0;
    uint32_t bit = 1 << 30; // Start from 2^30 (highest bit position)

    // Adjust bit position so it doesn't exceed input
    while (bit > input) {
        bit >>= 2;
    }

    // Binary search method to find sqrt(input)
    while (bit != 0) {
        if (input >= result + bit) {
            input -= result + bit;
            result = (result >> 1) + bit;
        } else {
            result >>= 1;
        }
        bit >>= 2;
    }

    return result;
}


void hadamardProduct(int matrixA[ROWS][COLS], int matrixB[ROWS][COLS], int result[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[i][j] = matrixA[i][j] * matrixB[i][j];
        }
    }
}

void printMatrix(int rows, int cols, int matrix[ROWS][COLS]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to compare two matrices
bool areMatricesEqual(int matrixA[ROWS][COLS], int matrixB[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matrixA[i][j] != matrixB[i][j]) {
            	//printf(" HadamardProduct Result Error!\n");
                return false; // If any element is different, the matrices are not equal
            }
        }
    }
    //printf(" HadamardProduct Result Pass!\n");
    return true; // If all elements are the same, the matrices are equal
}



