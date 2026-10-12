#ifndef KLIB_INTRINSICS_X86_SIMDROUNDINGMODE_H
#define KLIB_INTRINSICS_X86_SIMDROUNDINGMODE_H

#include "base.h"
#include "dep/klibintrinsics.h"

namespace klib::Intrinsics::X86
{
    enum struct SimdRoundingMode : int {
        ToNearestInt       = _MM_FROUND_TO_NEAREST_INT,
        ToNegativeInfinity = _MM_FROUND_TO_NEG_INF,
        ToPositiveInfinity = _MM_FROUND_TO_POS_INF,
        ToZero             = _MM_FROUND_TO_ZERO,
        CurrentDirection   = _MM_FROUND_CUR_DIRECTION,
        RaiseException     = _MM_FROUND_RAISE_EXC,
        NoException        = _MM_FROUND_NO_EXC,
        NInt               = _MM_FROUND_NINT,
        Floor              = _MM_FROUND_FLOOR,
        Ceiling            = _MM_FROUND_CEIL,
        Trunc              = _MM_FROUND_TRUNC,
        RInt               = _MM_FROUND_RINT,
        NearByInt          = _MM_FROUND_NEARBYINT,
    };
}

#endif //!KLIB_INTRINSICS_X86_SIMDROUNDINGMODE_H