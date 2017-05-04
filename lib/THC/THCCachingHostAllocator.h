#ifndef THC_CACHING_HOST_ALLOCATOR_INC
#define THC_CACHING_HOST_ALLOCATOR_INC

#include "THCGeneral.h"
#include "THCStream.h"

//
// A caching allocator for CUDA host allocations (pinned memory).
//
// This provides a drop-in replacement for THCudaHostAllocator, which re-uses
// freed pinned (page-locked) memory allocations. This avoids device
// synchronizations due to hipFreeHost calls.
//
// To ensure correct behavior, THCCachingHostAllocator_recordEvent must be
// called anytime a pointer from this allocator is used in a hipMemcpyAsync
// call between host and device. The THC library implements this for storages
// and tensors in THCTensor_(copyAsyncCPU) and THCTensor_(copyAsyncCuda).
//
// Note that this allocator does not split larger allocations into smaller
// blocks, unlike the caching device allocator.
//
THC_API THAllocator THCCachingHostAllocator;

// Records an event in the specified stream. The allocation 'ptr' will not be
// re-used until the event has occured.
THC_API hipError_t THCCachingHostAllocator_recordEvent(void *ptr, THCStream *stream);

// Releases cached pinned memory allocations via hipHostFree
THC_API void THCCachingHostAllocator_emptyCache(void);

#endif
