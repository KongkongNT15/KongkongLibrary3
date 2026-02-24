#ifndef KLIB_KONGKONG_NUMERICS_INT_H
#define KLIB_KONGKONG_NUMERICS_INT_H

#include "base.h"
#include "Kongkong.Numerics.Number.h"

#include <limits.h>

namespace klib::Kongkong::Numerics
{
    template <>
    struct Number<int> final {
    private:
    public:

        using NumType = int;

        KLIB_STATIC_CLASS(Number);

        [[nodiscard]]
        static constexpr bool IsFloatingPoint() noexcept;

        [[nodiscard]]
        static constexpr bool IsInteger() noexcept;

        [[nodiscard]]
        static constexpr NumType MaxValue() noexcept;

        [[nodiscard]]
        static constexpr NumType MinValue() noexcept;
    };
}

namespace klib::Kongkong::Numerics
{
    constexpr bool Int::IsFloatingPoint() noexcept
    {
        return false;
    }

    constexpr bool Int::IsInteger() noexcept
    {
        return true;
    }

    constexpr Int::NumType Int::MaxValue() noexcept
    {
        return INT_MAX;
    }

    constexpr Int::NumType Int::MinValue() noexcept
    {
        return INT_MIN;
    }
}

#endif //!KLIB_KONGKONG_NUMERICS_INT_H