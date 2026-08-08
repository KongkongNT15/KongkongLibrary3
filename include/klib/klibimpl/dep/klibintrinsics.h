#ifndef KLIBIMPL_DEP_KLIBINTRINSICS_H
#define KLIBIMPL_DEP_KLIBINTRINSICS_H

#include "../base.h"

#if KLIB_COMPILER_MSVC
    #include <intrin.h>
#elif KLIB_ENV_X64
    #include <immintrin.h>
#elif KLIB_ENV_ARM64
    #include <arm_neon.h>
#endif

#endif //!KLIBIMPL_DEP_KLIBINTRINSICS_H