#ifndef KLIB_INTRINSICS_SIMD_H
#define KLIB_INTRINSICS_SIMD_H

#include "base.h"

#if KLIB_ENV_WINDOWS

#elif KLIB_COMPILER_APPLE_CLANG
    #include <arm_neon.h>
#else

#endif

namespace klib::Intrinsics
{
    class Simd final {
        public:

        KLIB_STATIC_CLASS(Simd);


    };
}

#endif //!KLIB_INTRINSICS_SIMD_H