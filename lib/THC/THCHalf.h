#ifndef THC_HALF_CONVERSION_INC
#define THC_HALF_CONVERSION_INC

#include "THCGeneral.h"

/* We compile with CudaHalfTensor support if we have this: */
#if CUDA_VERSION >= 7050 || CUDA_HAS_FP16 || defined(__HIP_PLATFORM_HCC__)
    #define CUDA_HALF_TENSOR 1
#endif

#ifdef CUDA_HALF_TENSOR
    #if defined(__HIP_PLATFORM_HCC__)
	#include <cstdint>
        #include <hip/hip_fp16.h>
    #else
        #include <cuda_fp16.h>
    #endif


    THC_EXTERNC
    void THCFloat2Half(THCState *state, half *out, float *in, ptrdiff_t len);
    THC_EXTERNC
    void THCHalf2Float(THCState *state, float *out, half *in, ptrdiff_t len);
    THC_API half THC_float2half(float a);
    THC_API float THC_half2float(half a);

    /* Check for native fp16 support on the current device (CC 5.3+) */
    THC_API int THC_nativeHalfInstructions(THCState *state);

    /* Check for performant native fp16 support on the current device */
    THC_API int THC_fastHalfInstructions(THCState *state);
#endif /* CUDA_HALF_TENSOR */
#endif
