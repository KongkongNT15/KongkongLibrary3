#ifndef KLIB_INTRINSICS___FUNCS_H
#define KLIB_INTRINSICS___FUNCS_H

#include "Intrinsics.Float32x8.h"

namespace klib::Intrinsics
{
    Float32x8::operator Float64x4() const noexcept
    {
        
    }

    Float32x8::operator IntBlock256() const noexcept
    {
        
    }

    void Float32x8::Broadcast(
        const Float32x4* p
    ) noexcept
    {
        
    }
}

#include <math.h>

inline klib::Intrinsics::Float32x8 ceil(
    klib::Intrinsics::Float32x8 const& value
) noexcept
{
    return value.Ceiling();
}

inline klib::Intrinsics::Float32x8 floor(
    klib::Intrinsics::Float32x8 const& value
) noexcept
{
    return value.Floor();
}

inline klib::Intrinsics::Float32x8 sqrt(
    klib::Intrinsics::Float32x8 const& value
) noexcept
{
    return value.Sqrt();
}

#endif //!KLIB_INTRINSICS___FUNCS_H