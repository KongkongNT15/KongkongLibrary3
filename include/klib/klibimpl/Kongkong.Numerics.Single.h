#ifndef KLIB_KONGKONG_NUMERICS_SINGLE_H
#define KLIB_KONGKONG_NUMERICS_SINGLE_H

#include "base.h"
#include "Kongkong.Numerics.Number.h"

#include <float.h>

namespace klib::Kongkong::Numerics
{
    template <>
    struct Number<float> final {
    private:
    public:

        using NumType = float;

        KLIB_STATIC_CLASS(Number);

        [[nodiscard]]
        static consteval int Digits() noexcept;

        [[nodiscard]]
        static consteval NumType Epsiron() noexcept;

        [[nodiscard]]
        static consteval bool IsFloatingPoint() noexcept;

        [[nodiscard]]
        static consteval bool IsInteger() noexcept;

        [[nodiscard]]
        static consteval bool IsSigned() noexcept;

        [[nodiscard]]
        static consteval NumType MaxValue() noexcept;

        [[nodiscard]]
        static consteval NumType MinValue() noexcept;
    };
}

namespace klib::Kongkong::Numerics
{
    consteval int Single::Digits() noexcept
    {
        return FLT_MANT_DIG;
    }

    consteval Single::NumType Single::Epsiron() noexcept
    {
        return FLT_EPSILON;
    }

    consteval bool Single::IsFloatingPoint() noexcept
    {
        return true;
    }

    consteval bool Single::IsInteger() noexcept
    {
        return false;
    }

    consteval bool Single::IsSigned() noexcept
    {
        return true;
    }

    consteval Single::NumType Single::MaxValue() noexcept
    {
        return FLT_MAX;
    }

    consteval Single::NumType Single::MinValue() noexcept
    {
        return FLT_MIN;
    }
}

#endif //!KLIB_KONGKONG_NUMERICS_SINGLE_H