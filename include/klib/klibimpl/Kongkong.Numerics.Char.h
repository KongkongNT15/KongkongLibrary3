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

namespace klib::Kongkong::Numerics
{
    consteval int Char::Digits() noexcept
    {
        return sizeof(::int_least16_t) * CHAR_BIT;
    }

    consteval bool Char::IsFloatingPoint() noexcept
    {
        return false;
    }

    consteval bool Char::IsInteger() noexcept
    {
        return true;
    }

    consteval bool Char::IsSigned() noexcept
    {
        return false;
    }

    consteval Char::NumType Char::MaxValue() noexcept
    {
        return u'\uFFFF';
    }

    consteval Char::NumType Char::MinValue() noexcept
    {
        return u'\0';
    }
}

#endif //!KLIB_KONGKONG_NUMERICS_CHAR_H