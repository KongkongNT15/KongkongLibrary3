#ifndef KLIB_INTRINSICS_X86_H
#define KLIB_INTRINSICS_X86_H

#include "klibimpl/base.h"

#if KLIB_ENV_X86_64

#include "klibimpl/Intrinsics.X86.M128.h"
#include "klibimpl/Intrinsics.X86.SimdRoundingMode.h"

#define KLIB_CREATE_MATH_FUNC(type, name, memberFuncName) \
    [[nodiscard]] \
    inline klib::Intrinsics::X86::type name( \
        klib::Intrinsics::X86::type const& v\
    ) noexcept \
    { \
        return v.memberFuncName();\
    } \

#define KLIB_CREATE_CEIL(type) KLIB_CREATE_MATH_FUNC(type, ceil, Ceiling)
#define KLIB_CREATE_FLOOR(type) KLIB_CREATE_MATH_FUNC(type, floor, Floor)
#define KLIB_CREATE_NEARBYINT(type) KLIB_CREATE_MATH_FUNC(type, nearbyint, NearByInt)
#define KLIB_CREATE_RINT(type) KLIB_CREATE_MATH_FUNC(type, rint, RoundToInt)
#define KLIB_CREATE_SQRT(type) KLIB_CREATE_MATH_FUNC(type, sqrt, Sqrt)
#define KLIB_CREATE_TRUNC(type) KLIB_CREATE_MATH_FUNC(type, trunc, Trunc)


#define KLIB_CREATE_ALLMATH_FUNC(type)  \
    KLIB_CREATE_CEIL(type) \
    KLIB_CREATE_FLOOR(type) \
    KLIB_CREATE_NEARBYINT(type) \
    KLIB_CREATE_RINT(type) \
    KLIB_CREATE_SQRT(type) \
    KLIB_CREATE_TRUNC(type) \

KLIB_CREATE_ALLMATH_FUNC(M128)

#undef KLIB_CREATE_MATH_FUNC
#undef KLIB_CREATE_CEIL
#undef KLIB_CREATE_FLOOR
#undef KLIB_CREATE_NEARBYINT
#undef KLIB_CREATE_SQRT
#undef KLIB_CREATE_TRUNC
#undef KLIB_CREATE_ALLMATH_FUNC

#endif

#endif //!KLIB_INTRINSICS_X86_H