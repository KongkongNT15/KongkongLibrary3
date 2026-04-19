#ifndef KLIB_KONGKONG_NUMERICS_NUMBER_H
#define KLIB_KONGKONG_NUMERICS_NUMBER_H

#include "base.h"
#include "Kongkong.Numerics.Integer16Byte.h"
#include "Kongkong.Numerics.UnsignedInteger16Byte.h"

#include <limits.h>

namespace klib::Kongkong::Numerics
{
    template <>
    struct Number<void> final {
    public:

    private:
    public:

        KLIB_STATIC_CLASS(Number);

        
    };

    template <>
    struct Number<int_least128_t> final {
         KLIB_STATIC_CLASS(Number);

        using NumType = int_least128_t;

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

    template <>
    struct Number<uint_least128_t> final {
         KLIB_STATIC_CLASS(Number);

        using NumType = uint_least128_t;

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

namespace klib::Kongkong::Numerics
{
    consteval int Number<int_least128_t>::Bits() noexcept
    {
        return sizeof(int_least128_t) * CHAR_BIT;
    }

    consteval int Number<int_least128_t>::Digits() noexcept
    {
        return sizeof(int_least128_t) * CHAR_BIT - 1;
    }

    consteval bool Number<int_least128_t>::IsInteger() noexcept
    {
        return true;
    }

    consteval bool Number<int_least128_t>::IsFloatingPoint() noexcept
    {
        return false;
    }

    consteval bool Number<int_least128_t>::IsSigned() noexcept
    {
        return true;
    }

    consteval Number<int_least128_t>::NumType
    Number<int_least128_t>::MaxValue() noexcept
    {
        NumType result = 0;
        result = ~result;

        return result >> 1;
    }

    consteval Number<int_least128_t>::NumType
    Number<int_least128_t>::MinValue() noexcept
    {
        NumType result = 0;
        result = ~result;
        result >>= 1;

        return ++result;
    }

    consteval int Number<uint_least128_t>::Bits() noexcept
    {
        return sizeof(uint_least128_t) * CHAR_BIT;
    }

    consteval int Number<uint_least128_t>::Digits() noexcept
    {
        return sizeof(uint_least128_t) * CHAR_BIT;
    }

    consteval bool Number<uint_least128_t>::IsInteger() noexcept
    {
        return true;
    }

    consteval bool Number<uint_least128_t>::IsFloatingPoint() noexcept
    {
        return false;
    }

    consteval bool Number<uint_least128_t>::IsSigned() noexcept
    {
        return false;
    }

    consteval Number<uint_least128_t>::NumType
    Number<uint_least128_t>::MaxValue() noexcept
    {
        NumType result = 0;

        return ~result;
    }

    consteval Number<uint_least128_t>::NumType
    Number<uint_least128_t>::MinValue() noexcept
    {
        return 0;
    }
}

#endif //!KLIB_KONGKONG_NUMERICS_NUMBER_H