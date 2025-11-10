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

/**
 * @file udl.h
 * @brief API for User Define Logic
 */
#ifndef METAL_UDL_H
#define METAL_UDL_H
#include <stdint.h>

#include "metal/cmsis_nn.h"
/**
 * @brief Enum for UDL device types.
 *
 * This enum defines different types of UDL modules, such as NAON UDL and AON UDL.
 */
typedef enum enum_udl_device {
    NAON_UDL_1_1 = 0, /**< NAON UDL module. */
    AON_UDL_2         /**< AON UDL module. */
} enum_udl_device_Type;

/**
 * @brief Enum for activation function types in UDL.
 *
 * This enum defines the supported activation functions, including linear, ReLU,
 * and LeakyReLU.
 */
typedef enum enum_udl_activation {
    udl_atype_linear = 0,  /**< Linear activation function. */
    udl_atype_relu,        /**< ReLU activation function. */
    udl_atype_leakyrelu    /**< LeakyReLU activation function. */
} enum_udl_activation_Type;

/**
 * @brief Configuration parameters for a 2D Convolution operation in UDL.
 *
 * This structure contains all the necessary parameters for performing a 2D 
 * convolution operation, including pointers to input/output data, kernel, and bias, 
 * as well as dimensions, strides, activation function, and shift values for scaling.
 *
 * @param in                Pointer to the input data buffer.
 * @param out               Pointer to the output data buffer.
 * @param w                 Pointer to the weights buffer for the convolution kernels.
 * @param b                 Pointer to the bias buffer for the operation.
 * @param inx               Width of the input tensor.
 * @param iny               Height of the input tensor.
 * @param inz               Depth of the input tensor (number of input channels).
 * @param outx              Width of the output tensor.
 * @param outy              Height of the output tensor.
 * @param kx                Width of the convolution kernel.
 * @param ky                Height of the convolution kernel.
 * @param k_number          Number of kernels (equivalent to the number of output channels).
 * @param stride_x          Stride of the kernel in the x (horizontal) direction.
 * @param stride_y          Stride of the kernel in the y (vertical) direction (fixed at 1).
 * @param acc_rshift        Right shift value applied to the accumulator for scaling results.
 * @param leaky_pos_rshift  Right shift value for positive values in leaky ReLU activation.
 * @param leaky_neg_rshift  Right shift value for negative values in leaky ReLU activation.
 * @param bias_lshift       Left shift value applied to the bias for scaling.
 * @param activation        Specifies the type of activation function applied post-convolution.
 */
typedef struct {
    uint16_t *in;                 
    uint16_t *out;                 
    uint16_t *w;                  
    uint16_t *b;                  
    uint16_t inx;                  
    uint16_t iny;                 
    uint16_t inz;                  
    uint16_t outx;                
    uint16_t outy;                
    uint16_t kx;                 
    uint16_t ky;                  
    uint16_t k_number;            
    uint8_t stride_x;              
    uint8_t stride_y;             
    uint8_t acc_rshift;          
    uint8_t leaky_pos_rshift;     
    uint8_t leaky_neg_rshift;      
    uint8_t bias_lshift;         
    enum_udl_activation_Type activation;
    uint8_t pool_mask;   // Pooling mask, specific to hardware optimization.
    uint8_t pool_stride; // Stride size for max pooling.
} upt_udl_config_Type;

/**
 * @brief Structure representing the dimensions of a tensor in UDL.
 *
 * This structure holds the dimensions for a tensor, including the following parameters:
 * 
 * @param h Height of the tensor. Represents the vertical size of the data.
 * @param w Width of the tensor. Represents the horizontal size of the data.
 * @param c Number of channels. Represents the depth or number of feature maps in the tensor.
 */
typedef struct {
    uint32_t h; 
    uint32_t w; 
    uint32_t c; 
} upt_nn_dims_Type;

/**
 * @brief Structure representing the dimensions of a tile in UPT.
 *
 * This structure defines the size of a tile, including its width and height.
 *
 * @param w Width of the tile.
 * @param h Height of the tile.
 */
typedef struct {
    uint16_t w;
    uint16_t h;
} upt_tiles_Type;

/**
 * @brief Structure representing parameters for a convolution operation in UDL.
 *
 * This structure holds configuration parameters that control the behavior of a 
 * convolution operation. It includes settings for shift values (used for scaling), 
 * stride configuration, and the activation function to apply.
 *
 * @param acc_rshift         Right shift value for accumulation, used for scaling the output.
 * @param leaky_pos_rshift   Right shift value for scaling the positive slope of the leaky ReLU.
 * @param leaky_neg_rshift   Right shift value for scaling the negative slope of the leaky ReLU.
 * @param bias_lshift        Left shift value for bias, used to scale the bias before accumulation.
 * @param stride             Stride configuration, defining the step size for the convolution kernel.
 * @param activation         The type of activation function to be applied after the convolution.
 */                          
typedef struct {   
    uint8_t acc_rshift;         
    uint8_t leaky_pos_rshift;  
    uint8_t leaky_neg_rshift;  
    uint8_t bias_lshift;        
    upt_tiles_Type stride;         
    enum_udl_activation_Type activation; 
} upt_nn_conv_params_Type;

/**
 * @brief Structure for max pooling parameters.
 *
 * This structure defines the parameters required for max pooling operations.
 *
 * @param pool_mask      Pooling mask, used for custom hardware-specific optimizations.
 * @param pool_kx        Kernel width for max pooling operation.
 * @param pool_ky        Kernel height for max pooling operation.
 * @param pool_stride_x  Horizontal stride size for the pooling operation.
 * @param pool_stride_y  Vertical stride size for the pooling operation.
 */
typedef struct {
    uint8_t pool_kx; // Kernel width for max pooling.
    uint8_t pool_ky; // Kernel height for max pooling.
    uint8_t pool_stride_x; // Stride size for max pooling.
    uint8_t pool_stride_y;
} upt_nn_maxPool_params_Type;


/**
 * @brief UDL return error code.
 * @ingroup UP301_Controller_UDL
 */
typedef enum enum_udl_retcode{
    E_UDL_SUCCESS,      // Success.
	E_UDL_INVINIT,	 	// Initial fail or resource is unavailable.
	E_UDL_INVPARA,	 	// Invalid function parameter/argument.
    E_UDL_ERROR,     	// Unspecific error.
    E_UDL_NOTSUP        // Not support function
} enum_udl_retcode_Type;


/**
 * @brief Handle for a udl engine
 */
typedef struct metal_udl {
    const struct metal_udl_vtable *vtable;
} metal_udl_Type;

struct metal_udl_vtable {
    uint16_t (*conv_2d_16x16)(metal_udl_Type *udl, upt_udl_config_Type *conv_2d_config);
    void (*reset)(metal_udl_Type *udl);
    void (*interrupt_enable)(metal_udl_Type *udl, bool enable);
    uint16_t (*read_pending)(metal_udl_Type *udl);
    uint16_t (*read_stats)(metal_udl_Type *udl);
    enum_udl_retcode_Type (*arm_convolve_s16)(metal_udl_Type *udl1, 
                            const cmsis_nn_context *ctx,
                            const cmsis_nn_conv_params *conv_params,
                            const cmsis_nn_per_channel_quant_params *quant_params,
                            const cmsis_nn_dims *input_dims,
                            const int16_t *input_data,
                            const cmsis_nn_dims *filter_dims,
                            const int8_t *filter_data,
                            const cmsis_nn_dims *bias_dims,
                            const cmsis_nn_bias_data *bias_data,
                            const cmsis_nn_dims *output_dims,
                            int16_t *output_data
                            );
    enum_udl_retcode_Type (*upt_convolve_s16)(metal_udl_Type *udl,
                            const upt_nn_conv_params_Type *conv_params,
                            const upt_nn_dims_Type *input_dims,
                            const uint32_t *input_data,
                            const upt_nn_dims_Type *weight_dims,
                            const uint32_t *weight_data,
                            const uint32_t *bias_data,
                            const upt_nn_dims_Type *output_dims,
                            uint32_t *output_data
                            );
    enum_udl_retcode_Type (*upt_max_pooling)(metal_udl_Type *udl,
							const upt_nn_dims_Type *input_dims,
							const uint32_t *input_data,
							const upt_nn_dims_Type *output_dims,
							const uint32_t *output_data,
							const upt_nn_maxPool_params_Type *maxPool_params
							);
    void (*output_rearrange)(uint32_t *output_data, const uint16_t output_size); 
};



/**
 * @brief Get a handle for a UDL.
 * @param device_num The index of the desired UDL engine.
 * @return A handle to the UDL, or NULL if the engine does not exist.
 */
__inline__ metal_udl_Type *upt_udl_get_device(enum_udl_device_Type device_num);

/**
 * @brief Do convolution 2D
 * @param udl The UDL engine handle
 * @param conv_2d_config Convolution parameters for udl
 * @return Convolution result
 */
__inline__ uint16_t metal_udl_conv_2d_16x16(metal_udl_Type *udl, upt_udl_config_Type *conv_2d_config) {
    return udl->vtable->conv_2d_16x16(udl, conv_2d_config);
}

/**
 * @brief Reset for UDL
 * @param udl The UDL engine handle
 */
__inline__ void metal_udl_reset(metal_udl_Type *udl) {
	udl->vtable->reset(udl);
}

/**
 * @brief Eaable UDL interrupt
 * @param udl The UDL engine handle
 * @param enable enable/disable interrupt bit
 */
__inline__ void metal_udl_interrupt_enable(metal_udl_Type *udl, bool enable) {
	udl->vtable->interrupt_enable(udl, enable);
}

/**
 * @brief Read and clear UDL pending bit
 * @param udl The UDL engine handle
 * @return pending bit status
 */
__inline__ uint16_t metal_udl_read_pending(metal_udl_Type *udl) {
    return udl->vtable->read_pending(udl);
}

/**
 * @brief Read and clear UDL overflow status
 * @param udl The UDL engine handle
 * @return  overflow status
 */
__inline__ uint32_t metal_udl_read_stats(metal_udl_Type *udl) {
    return udl->vtable->read_stats(udl);
}



/**
 * @brief Performs a 2D convolution operation compatible with the ARM-CMSIS NN API.
 *
 *
 * @param[in] ctx (Not used in our implementation) Function context that contains the additional buffer if required by the function.
 * @param[in] conv_params (Dilations, padding, input/output offset not used in our implementation) Convolution parameters (e.g. strides, dilations, pads,...)
 * @param[in] quant_params (Not used in our implementation)	Per-channel quantization info. It contains the multiplier and shift values to be applied to each output channel
 * @param[in] input_dims Input tensor dimensions (H, W, C_IN).
 * @param[in] input_data Input data pointer. Data type: int16_t.
 * @param[in] filter_dims Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the spatial filter dimensions
 * @param[in] filter_data filter data pointer. Data type: int8_t.
 * @param[in] bias_dims Bias tensor dimensions. Format: [C_OUT]
 * @param[in] bias_data Optional bias data pointer. Data type: int64
 * @param[in] output_dims Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out] output_data Output data pointer. Data type: int16
 * @return The status of the convolution operation.
 */
__inline__ enum_udl_retcode_Type metal_udl_conv_2d_16x16_arm_api(const cmsis_nn_context *ctx,
                                     const cmsis_nn_conv_params *conv_params,
                                     const cmsis_nn_per_channel_quant_params *quant_params,
                                     const cmsis_nn_dims *input_dims,
                                     const int16_t *input_data,
                                     const cmsis_nn_dims *filter_dims,
                                     const int8_t *filter_data,
                                     const cmsis_nn_dims *bias_dims,
                                     const cmsis_nn_bias_data *bias_data,
                                     const cmsis_nn_dims *output_dims,
                                     int16_t *output_data) {

    metal_udl_Type *udl = upt_udl_get_device(NAON_UDL_1_1);
    return udl->vtable->arm_convolve_s16(udl, 
                                        ctx,
                                        conv_params,
                                        quant_params,
                                        input_dims,
                                        input_data,
                                        filter_dims,
                                        filter_data,
                                        bias_dims,
                                        bias_data,
                                        output_dims,
                                        output_data
                                        );
}
/**
 * @brief Performs a 2D convolution operation compatible with the ARM-CMSIS NN API.
 *
 *
 * @param[in] ctx Context structure TODO:(not used in this implementation).
 * @param[in] fc_params offset of zero TODO:(not used in this implementation).
 * @param[in] quant_params Per-tensor quantization parameters TODO:(not used in this implementation).
 * @param[in] input_dims Dimensions of the input tensor. Format: [N, H, W, C_IN].
 * @param[in] input_data Pointer to the input tensor data. Data type: int16_t.
 * @param[in] filter_dims Dimensions of the filter tensor. Format: [C_OUT, C_IN].
 * @param[in] filter_data Pointer to the filter tensor data. Data type: int8_t.
 * @param[in] bias_dims Dimensions of the bias tensor. Format: [C_OUT].
 * @param[in] bias_data Pointer to the optional bias tensor data. Data type: int64_t.
 * @param[in] output_dims Dimensions of the output tensor. Format: [N, H, W, C_OUT].
 * @param[out] output_data Pointer to the output tensor data. Data type: int16_t.
 * @return The status of the convolution operation.
 */
__inline__ enum_udl_retcode_Type metal_udl_fully_connect_arm_api (const cmsis_nn_context *ctx,
                                        const cmsis_nn_fc_params *fc_params,
                                        const cmsis_nn_per_tensor_quant_params *tensor_quant_params,
                                        const cmsis_nn_dims *input_dims,
                                        const int16_t *input_data,
                                        const cmsis_nn_dims *filter_dims,
                                        const int8_t *filter_data,
                                        const cmsis_nn_dims *bias_dims,
                                        const int64_t *bias_data,
                                        const cmsis_nn_dims *output_dims,
                                        int16_t *output_data 
                                        ) {
    metal_udl_Type *udl = upt_udl_get_device(NAON_UDL_1_1);

    cmsis_nn_conv_params conv_params;  
    cmsis_nn_per_channel_quant_params quant_params;  
    conv_params.input_offset = 0;
    conv_params.output_offset = 0;
    conv_params.activation.min = 0;
    conv_params.activation.max = 0;
    conv_params.padding.w = 0;
    conv_params.padding.h = 0;
    conv_params.dilation.w = 1;
    conv_params.dilation.h = 1;
    quant_params.multiplier = NULL;
    quant_params.shift = NULL;
    
    
    cmsis_nn_dims fc_input_dims;
    fc_input_dims.n = 1; // udl not support batch calculation
    fc_input_dims.w = input_dims->h * input_dims->w * input_dims->c;
    fc_input_dims.h = 1;
    fc_input_dims.c = 1;

    cmsis_nn_dims fc_output_dims;
    fc_output_dims.n = 1;
    fc_output_dims.w = 1;
    fc_output_dims.h = 1;
    fc_output_dims.c = output_dims->c;

    cmsis_nn_dims fc_weight_dims;
    fc_weight_dims.w = input_dims->h * input_dims->w * input_dims->c;
    fc_weight_dims.h = 1;

    cmsis_nn_bias_data converted_bias = {
        .data = (const int32_t *)bias_data,
        .is_int32_bias = true // Assuming bias is in int32 format
    };

    return udl->vtable->arm_convolve_s16(udl, 
                                        ctx,
                                        &conv_params,
                                        &quant_params,
                                        &fc_input_dims,
                                        input_data,
                                        &fc_weight_dims,
                                        filter_data,
                                        bias_dims,
                                        &converted_bias,
                                        &fc_output_dims,
                                        output_data
                                        );
}
/** 
 *  @brief Perform a 2D convolution operation using 16-bit input values with the UpBeatTech UDL API.
 *
 * @param[in] udl Pointer to the metal_udl structure.
 * @param[in] conv_params Convolution parameters (e.g. strides, leaky_pos_shift, leaky_neg_shift,...)
 * @param[in] input_dims  Input tensor dimensions (H, W, C_IN).
 * @param[in] input_data Input data pointer. Data type: uint32_t.
 * @param[in] weight_dims Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the spatial filter dimensions
 * @param[in] weight_data  filter data pointer. Data type: uint32_t.
 * @param[in] bias_data Pointer to the bias data array.
 * @param[in] output_dims Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out] output_data Output data pointer. Data type: uint32_t
 * @return Status of the convolution operation.
 */
__inline__ enum_udl_retcode_Type metal_udl_conv_2d_16x16_upt_api(metal_udl_Type *udl,
                                        const upt_nn_conv_params_Type *conv_params,
                                        const upt_nn_dims_Type *input_dims,
										const uint32_t *input_data,
                                        const upt_nn_dims_Type *weight_dims,
										const uint32_t *weight_data,
										const uint32_t *bias_data,
                                        const upt_nn_dims_Type *output_dims,
										uint32_t *output_data
                                        ) {
    return udl->vtable->upt_convolve_s16(udl, 
                                        conv_params,
                                        input_dims,
                                        input_data,
                                        weight_dims,
										weight_data,
                                        bias_data,
                                        output_dims,
                                        output_data
                                        );
}
/** 
 *  @brief Perform a 2D convolution operation using 16-bit input values with the UpBeatTech UDL API.
 *
 * 
 *
 * @param[in] udl Pointer to the metal_udl structure.
 * @param[in] conv_params Convolution parameters (e.g. strides, leaky_pos_shift, leaky_neg_shift,...)
 * @param[in] input_feature_nums
 * @param[in] input_data Input data pointer. Data type: uint32_t.
 * @param[in] weight_data  filter data pointer. Data type: uint32_t.
 * @param[in] bias_data Pointer to the bias data array.
 * @param[in] output_feature_nums
 * @param[out] output_data Output data pointer. Data type: uint32_t
 * @return Status of the convolution operation.
 */
__inline__ enum_udl_retcode_Type metal_udl_fully_connect_upt_api(metal_udl_Type *udl,
                                                      const upt_nn_conv_params_Type *conv_params,
                                                      const uint32_t input_feature_nums,
                                                      const uint32_t *input_data,
                                                      const uint32_t *weight_data,
                                                      const uint32_t *bias_data,
                                                      const uint32_t output_feature_nums,
                                                      uint32_t *output_data
                                        ) {
    upt_nn_dims_Type input_dims;
    input_dims.w = input_feature_nums;
    input_dims.h = 1;
    input_dims.c = 1;

    upt_nn_dims_Type output_dims;
    output_dims.w = 1;
    output_dims.h = 1;
    output_dims.c = output_feature_nums;

    upt_nn_dims_Type weight_dims;
    weight_dims.w = input_feature_nums;
    weight_dims.h = 1;
    
    return udl->vtable->upt_convolve_s16(udl, 
                                        conv_params,
                                        &input_dims,
                                        input_data,
                                        &weight_dims,
										weight_data,
                                        bias_data,
                                        &output_dims,
                                        output_data
                                        );
};

/**
 * @brief Perform a 2D max pooling operation using 16-bit input values with the UpBeatTech UDL API.
 *
 * @param[in] udl Pointer to the metal_udl structure.
 * @param[in] conv_params Convolution parameters (e.g. strides, leaky_pos_shift, leaky_neg_shift,...)
 * @param[in] input_dims Input tensor dimensions (H, W, C_IN).
 * @param[in] input_data Input data pointer. Data type: uint32_t.
 * @param[in] weight_dims Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the spatial filter dimensions
 * @param[in] weight_data  filter data pointer. Data type: uint32_t.
 * @param[in] bias_data Pointer to the bias data array.
 * @param[in] output_dims Output tensor dimensions. Format: [N, H, W, C_OUT].
 * @param[out] output_data Output data pointer. Data type: uint32_t.
 * @param[in] maxPool_params Max pooling parameters (e.g., pool size, strides, padding).
 * @return Status of the max pooling operation.
 */
__inline__ enum_udl_retcode_Type metal_udl_max_pooling(metal_udl_Type *udl,
                                        const upt_nn_dims_Type *input_dims,
										const uint32_t *input_data,
                                        const upt_nn_dims_Type *output_dims,
										uint32_t *output_data,
										const upt_nn_maxPool_params_Type *maxPool_params
                                        ) {
    return udl->vtable->upt_max_pooling(udl,
                                        input_dims,
                                        input_data,
                                        output_dims,
                                        output_data,
										maxPool_params
                                        );
}

__inline__ void metal_udl_rearrange(metal_udl_Type *udl, uint32_t *output_data, const uint16_t output_size) {
    return udl->vtable->output_rearrange(output_data, output_size);
}

#endif
