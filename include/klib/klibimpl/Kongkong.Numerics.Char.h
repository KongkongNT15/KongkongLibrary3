#ifndef KLIB_KONGKONG_NUMERICS_CHAR_H
#define KLIB_KONGKONG_NUMERICS_CHAR_H

#include "base.h"
#include "Kongkong.Numerics.Number.h"

#include <inttypes.h>

namespace klib::Kongkong::Numerics
{
    template <>
    struct Number<char16_t> final {
    private:
    public:

        using NumType = char16_t;

        KLIB_STATIC_CLASS(Number);

        [[nodiscard]]
        static constexpr int Digits() noexcept;

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
    constexpr int Char::Digits() noexcept
    {
        return sizeof(::int_least16_t) * CHAR_BIT;
    }

    constexpr bool Char::IsFloatingPoint() noexcept
    {
        return false;
    }

    constexpr bool Char::IsInteger() noexcept
    {
        return true;
    }

    constexpr bool Char::IsSigned() noexcept
    {
        return false;
    }

    constexpr Char::NumType Char::MaxValue() noexcept
    {
        return u'\uFFFF';
    }

    constexpr Char::NumType Char::MinValue() noexcept
    {
        return u'\0';
    }
}

#endif //!KLIB_KONGKONG_NUMERICS_CHAR_H