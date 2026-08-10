#ifndef KLIB_INTRINSICS_SIMD_H
#define KLIB_INTRINSICS_SIMD_H

#include "base.h"

#if KLIB_ENV_X64
    #include <immintrin.h>
#elif KLIB_ENV_ARM64
    #include <arm_neon.h>
#endif

namespace klib::Intrinsics
{
    class Simd final {
        public:

        KLIB_STATIC_CLASS(Simd);


    };
    
}

#endif //!KLIB_INTRINSICS_SIMD_H