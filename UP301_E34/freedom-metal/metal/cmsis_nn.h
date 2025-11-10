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

#ifndef METAL_CMSISNN_H
#define METAL_CMSISNN_H
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Enum for specifying activation function types in CMSIS-NN.
 */
typedef enum
{
    ARM_SIGMOID = 0, /**< Sigmoid activation function. */
    ARM_TANH = 1     /**< Tanh activation function. */
} cmsis_nn_activation;

/**
 * @brief Structure for defining quantized ReLU activation parameters in CMSIS-NN.
 *
 * This structure holds the minimum and maximum values used to clamp the output
 * of a quantized ReLU activation function.
 */
typedef struct
{
    int32_t min; /**< Minimum clamping value. */
    int32_t max; /**< Maximum clamping value. */
} cmsis_nn_reluparam;

/**
 * @brief Structure for function context in CMSIS-NN.
 *
 * Contains a pointer to a buffer used in function optimizations and the buffer size.
 */
typedef struct
{
    void *buf;    /**< Pointer to optimization buffer. */
    int32_t size; /**< Size of the buffer in bytes. */
} cmsis_nn_context;

/**
 * @brief Structure to hold bias data for int16 variants in CMSIS-NN.
 *
 * This structure contains a pointer to bias data and an indicator of the data type,
 * allowing for either int32 or int64 biases.
 */
typedef struct
{
    const void *data;         /**< Pointer to the bias data. */
    const bool is_int32_bias; /**< Indicates bias data type: true for int32, false for int64. */
} cmsis_nn_bias_data;

/**
 * @brief Enum representing return codes for CMSIS-NN functions.
 *
 * Defines the possible return values for CMSIS-NN functions, including success,
 * argument error, no implementation, and general failure.
 */
typedef enum
{
    ARM_CMSIS_NN_SUCCESS = 0,        /**< No error. */
    ARM_CMSIS_NN_ARG_ERROR = -1,     /**< One or more arguments are incorrect. */
    ARM_CMSIS_NN_NO_IMPL_ERROR = -2, /**< No implementation available. */
    ARM_CMSIS_NN_FAILURE = -3        /**< Logical or unknown error. */
} arm_cmsis_nn_status;


/**
 * @brief Structure representing the dimensions of a tensor in CMSIS-NN.
 *
 * This structure defines the shape of a tensor with parameters for batch size,
 * height, width, and channel count.
 */
typedef struct
{
    int32_t n; /**< Dimension representing batch size or output channels. */
    int32_t h; /**< Height of the tensor. */
    int32_t w; /**< Width of the tensor. */
    int32_t c; /**< Number of input channels. */
} cmsis_nn_dims;

/**
 * @brief Structure to represent the dimensions of a tile in CMSIS-NN.
 *
 * This structure holds the width and height parameters for a tile, 
 * used in configurations such as stride, padding, or dilation.
 */
typedef struct
{
    int32_t w; /**< Width of the tile. */
    int32_t h; /**< Height of the tile. */
} cmsis_nn_tile;

/**
 * @brief Convolution layer parameters for CMSIS-NN.
 *
 * This structure defines various configuration parameters for a convolution
 * operation, including offsets, stride, padding, dilation, and activation settings.
 */
typedef struct
{
    int32_t input_offset;          /**< Offset applied to the input tensor, typically the negative zero point value. */
    int32_t output_offset;         /**< Offset applied to the output tensor, typically the negative zero point value. */
    cmsis_nn_tile stride;          /**< Stride configuration in width and height for the convolution operation. */
    cmsis_nn_tile padding;         /**< Padding configuration in width and height. */
    cmsis_nn_tile dilation;        /**< Dilation configuration in width and height. */
    cmsis_nn_reluparam activation;/**< Activation function settings, including min/max thresholds for clipping. */
} cmsis_nn_conv_params;

/**
 * @brief Structure for per-channel quantization parameters in CMSIS-NN.
 *
 * This structure holds quantization parameters that are applied per output channel,
 * including multiplier and shift values for adjusting quantization scales.
 */
typedef struct
{
    int32_t *multiplier; /**< Pointer to an array of multiplier values for each channel. */
    int32_t *shift;      /**< Pointer to an array of shift values for each channel. */
} cmsis_nn_per_channel_quant_params;

/** CMSIS-NN object for the per-tensor quantization parameters */
typedef struct
{
    int32_t multiplier; /**< Multiplier value */
    int32_t shift;      /**< Shift value */
} cmsis_nn_per_tensor_quant_params;

/** CMSIS-NN object for Fully Connected layer parameters */
typedef struct
{
    int32_t input_offset;  /**< The negative of the zero value for the input tensor */
    int32_t filter_offset; /**< The negative of the zero value for the filter tensor */
    int32_t output_offset; /**< The negative of the zero value for the output tensor */
    cmsis_nn_activation activation;
} cmsis_nn_fc_params;

#endif
