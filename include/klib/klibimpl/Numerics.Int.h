#ifndef KLIB_NUMERICS_INT_H
#define KLIB_NUMERICS_INT_H

#include "base.h"
#include "Numerics.Number.h"

#include <limits.h>

namespace klib::Numerics
{
    template <>
    struct Number<int> final {
    private:
    public:

        using NumType = int;

        KLIB_STATIC_CLASS(Number);

        [[nodiscard]]
        static consteval int Bits() noexcept;

        [[nodiscard]]
        static consteval int Digits() noexcept;

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

namespace klib::Numerics
{
    consteval int Int::Bits() noexcept
    {
        return sizeof(int) * CHAR_BIT;
    }

    consteval int Int::Digits() noexcept
    {
        return sizeof(NumType) * CHAR_BIT - 1;
    }

    consteval bool Int::IsFloatingPoint() noexcept
    {
        return false;
    }

    consteval bool Int::IsInteger() noexcept
    {
        return true;
    }

    consteval bool Int::IsSigned() noexcept
    {
        return true;
    }

    consteval Int::NumType Int::MaxValue() noexcept
    {
        return INT_MAX;
    }

    consteval Int::NumType Int::MinValue() noexcept
    {
        return INT_MIN;
    }
}

#endif //!KLIB_NUMERICS_INT_H
