#ifndef KLIB_NUMERICS_LONG_H
#define KLIB_NUMERICS_LONG_H

#include "base.h"
#include "Numerics.Number.h"

#include <limits.h>

namespace klib::Numerics
{
    template <>
    struct Number<long> final {
    private:
    public:

        using NumType = long;

        KLIB_STATIC_CLASS(Number);

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
    consteval int Long::Digits() noexcept
    {
        return sizeof(NumType) * CHAR_BIT - 1;
    }

    consteval bool Long::IsFloatingPoint() noexcept
    {
        return false;
    }

    consteval bool Long::IsInteger() noexcept
    {
        return true;
    }

    consteval bool Long::IsSigned() noexcept
    {
        return true;
    }

    consteval Long::NumType Long::MaxValue() noexcept
    {
        return LONG_MAX;
    }

    consteval Long::NumType Long::MinValue() noexcept
    {
        return LONG_MIN;
    }
}

#endif //!KLIB_NUMERICS_LONG_H
