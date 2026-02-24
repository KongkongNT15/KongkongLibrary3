#ifndef KLIB_KONGKONG_NUMERICS_LONG_H
#define KLIB_KONGKONG_NUMERICS_LONG_H

#include "base.h"
#include "Kongkong.Numerics.Number.h"

#include <limits.h>

namespace klib::Kongkong::Numerics
{
    template <>
    struct Number<long> final {
    private:
    public:

        using NumType = long;

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
    constexpr bool Long::IsFloatingPoint() noexcept
    {
        return false;
    }

    constexpr bool Long::IsInteger() noexcept
    {
        return true;
    }

    constexpr Long::NumType Long::MaxValue() noexcept
    {
        return LONG_MAX;
    }

    constexpr Long::NumType Long::MinValue() noexcept
    {
        return LONG_MIN;
    }
}

#endif //!KLIB_KONGKONG_NUMERICS_LONG_H