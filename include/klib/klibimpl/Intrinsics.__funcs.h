#ifndef KLIB_INTRINSICS___FUNCS_H
#define KLIB_INTRINSICS___FUNCS_H

#include "Intrinsics.Float32x4.h"
#include "Intrinsics.Float32x8.h"
#include "Intrinsics.UInt32x4.h"

namespace klib::Intrinsics
{
#if KLIB_ENV_X64

    inline UInt32x4 Float32x4::Compare(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return vceqq_f32(left.m_value, right.m_value);
    }

    inline Float32x4::operator UInt32x4() const noexcept
    {
        
    }

#elif KLIB_ENV_ARM64
    inline Float32x4::operator UInt32x4() const noexcept
    {
        return vreinterpretq_u32_f32(m_value);
    }

    inline UInt32x4 Float32x4::Compare(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return vceqq_f32(left.m_value, right.m_value);
    }

    inline Float32x8::operator Float64x4() const noexcept
    {
        
    }

    inline Float32x8::operator IntBlock256() const noexcept
    {
        
    }

    void Float32x8::Broadcast(
        const Float32x4* p
    ) noexcept
    {
        
    }

#else

#endif
}

#include <math.h>

inline klib::Intrinsics::Float32x4 ceil(
    klib::Intrinsics::Float32x4 const& value
) noexcept
{
    return value.Ceiling();
}

inline klib::Intrinsics::Float32x4 floor(
    klib::Intrinsics::Float32x4 const& value
) noexcept
{
    return value.Floor();
}

inline klib::Intrinsics::Float32x4 fma(
    klib::Intrinsics::Float32x4 const& a,
    klib::Intrinsics::Float32x4 const& b,
    klib::Intrinsics::Float32x4 const& c
) noexcept
{
    return klib::Intrinsics::Float32x4::FusedMultiplyAdd(
        a, b, c
    );
}

inline klib::Intrinsics::Float32x4 round(
    klib::Intrinsics::Float32x4 const& value
) noexcept
{
    return value.Round();
}

inline klib::Intrinsics::Float32x4 sqrt(
    klib::Intrinsics::Float32x4 const& value
) noexcept
{
    return value.Sqrt();
}

#endif //!KLIB_INTRINSICS___FUNCS_H