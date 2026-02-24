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
        static constexpr int Digits() noexcept;

        [[nodiscard]]
        static constexpr NumType Epsiron() noexcept;

        [[nodiscard]]
        static constexpr bool IsFloatingPoint() noexcept;

        [[nodiscard]]
        static constexpr bool IsInteger() noexcept;

        [[nodiscard]]
        static constexpr bool IsSigned() noexcept;

        [[nodiscard]]
        static constexpr NumType MaxValue() noexcept;

        [[nodiscard]]
        static constexpr NumType MinValue() noexcept;
    };
}

namespace klib::Kongkong::Numerics
{
    constexpr int Single::Digits() noexcept
    {
        return FLT_MANT_DIG;
    }

    constexpr Single::NumType Single::Epsiron() noexcept
    {
        return FLT_EPSILON;
    }

    constexpr bool Single::IsFloatingPoint() noexcept
    {
        return true;
    }

    constexpr bool Single::IsInteger() noexcept
    {
        return false;
    }

    constexpr bool Single::IsSigned() noexcept
    {
        return true;
    }

    constexpr Single::NumType Single::MaxValue() noexcept
    {
        return FLT_MAX;
    }

    constexpr Single::NumType Single::MinValue() noexcept
    {
        return FLT_MIN;
    }
}

#endif //!KLIB_KONGKONG_NUMERICS_SINGLE_H