#ifndef KLIB_KONGKONG_NUMERICS_INTEGER16BYTE_H
#define KLIB_KONGKONG_NUMERICS_INTEGER16BYTE_H

#include "base.h"
#include "Kongkong.Numerics.Integer16ByteBase.h"

#include <limits.h>

namespace klib::Kongkong::Numerics
{
    struct Integer16Byte : public Integer16ByteBase {
        public:

        constexpr Integer16Byte() = default;

        constexpr Integer16Byte(
            int_least64_t value
        ) noexcept;

        constexpr Integer16Byte(
            uint_least64_t value
        ) noexcept;

        explicit constexpr Integer16Byte(
            uint_least64_t lowPart,
            uint_least64_t highPart
        ) noexcept;

        [[nodiscard]]
        constexpr Integer16Byte& operator++() noexcept;

        [[nodiscard]]
        constexpr Integer16Byte operator++(int) noexcept;

        [[nodiscard]]
        constexpr Integer16Byte& operator--() noexcept;

        [[nodiscard]]
        constexpr Integer16Byte operator--(int) noexcept;

        [[nodiscard]]
        constexpr Integer16Byte operator+() const noexcept;

        [[nodiscard]]
        constexpr Integer16Byte operator-() const noexcept;

        [[nodiscard]]
        constexpr Integer16Byte operator~() const noexcept;

        [[nodiscard]]
        constexpr bool IsNegative() const noexcept;

        [[nodiscard]]
        constexpr UnsignedInteger16Byte ToUnsigned() const noexcept;
    };

    struct UnsignedInteger16Byte : public Integer16ByteBase {
        constexpr UnsignedInteger16Byte() = default;

        constexpr UnsignedInteger16Byte(
            int_least64_t value
        ) noexcept;

        constexpr UnsignedInteger16Byte(
            uint_least64_t value
        ) noexcept;

        explicit constexpr UnsignedInteger16Byte(
            uint_least64_t lowPart,
            uint_least64_t highPart
        ) noexcept;

        [[nodiscard]]
        constexpr UnsignedInteger16Byte& operator++() noexcept;

        [[nodiscard]]
        constexpr UnsignedInteger16Byte operator++(int) noexcept;

        [[nodiscard]]
        constexpr UnsignedInteger16Byte& operator--() noexcept;

        [[nodiscard]]
        constexpr UnsignedInteger16Byte operator--(int) noexcept;

        [[nodiscard]]
        constexpr UnsignedInteger16Byte operator+() const noexcept;

        [[nodiscard]]
        constexpr UnsignedInteger16Byte operator-() const noexcept;

        [[nodiscard]]
        constexpr UnsignedInteger16Byte operator~() const noexcept;

        [[nodiscard]]
        constexpr Integer16Byte ToSigned() const noexcept;
    };

    [[nodiscard]]
    constexpr bool operator==(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        Integer16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        int_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        Integer16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        int_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        Integer16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        int_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        Integer16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        int_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        Integer16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        int_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        Integer16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        int_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        Integer16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        int_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept;
}

namespace klib::Kongkong::Numerics
{
    constexpr Integer16Byte::Integer16Byte(
        int_least64_t value
    ) noexcept
        : Integer16ByteBase(value)
    {
    }

    constexpr Integer16Byte::Integer16Byte(
        uint_least64_t value
    ) noexcept
        : Integer16ByteBase(value)
    {
    }

    constexpr Integer16Byte::Integer16Byte(
        uint_least64_t lowPart,
        uint_least64_t highPart
    ) noexcept
        : Integer16ByteBase(lowPart, highPart)
    {
    }

    constexpr Integer16Byte&
    Integer16Byte::operator++() noexcept
    {
        do_increment();
        return *this;
    }

    constexpr Integer16Byte
    Integer16Byte::operator++(int) noexcept
    {
        auto result = *this;
        do_increment();

        return result;
    }

    constexpr Integer16Byte&
    Integer16Byte::operator--() noexcept
    {
        do_decrement();
        return *this;
    }

    constexpr Integer16Byte
    Integer16Byte::operator--(int) noexcept
    {
        auto result = *this;
        do_decrement();

        return result;
    }

    constexpr Integer16Byte
    Integer16Byte::operator+() const noexcept
    {
        return *this;
    }

    constexpr Integer16Byte
    Integer16Byte::operator-() const noexcept
    {
        auto result = operator~();
        result.do_increment();

        return result;
    }

    constexpr Integer16Byte
    Integer16Byte::operator~() const noexcept
    {
        return Integer16Byte(
            ~m_lowPart,
            ~m_highPart
        );
    }

    constexpr bool
    Integer16Byte::IsNegative() const noexcept
    {
        return static_cast<int_least64_t>(m_highPart) < 0;
    }

    constexpr UnsignedInteger16Byte
    Integer16Byte::ToUnsigned() const noexcept
    {
        return UnsignedInteger16Byte(m_lowPart, m_highPart);
    }

    constexpr UnsignedInteger16Byte::UnsignedInteger16Byte(
        int_least64_t value
    ) noexcept
        : Integer16ByteBase(value)
    {
    }

    constexpr UnsignedInteger16Byte::UnsignedInteger16Byte(
        uint_least64_t value
    ) noexcept
        : Integer16ByteBase(value)
    {
    }

    constexpr UnsignedInteger16Byte::UnsignedInteger16Byte(
        uint_least64_t lowPart,
        uint_least64_t highPart
    ) noexcept
        : Integer16ByteBase(lowPart, highPart)
    {
    }

    constexpr UnsignedInteger16Byte&
    UnsignedInteger16Byte::operator++() noexcept
    {
        do_increment();
        return *this;
    }

    constexpr UnsignedInteger16Byte
    UnsignedInteger16Byte::operator++(int) noexcept
    {
        auto result = *this;
        do_increment();

        return result;
    }

    constexpr UnsignedInteger16Byte&
    UnsignedInteger16Byte::operator--() noexcept
    {
        do_decrement();
        return *this;
    }

    constexpr UnsignedInteger16Byte
    UnsignedInteger16Byte::operator--(int) noexcept
    {
        auto result = *this;
        do_decrement();

        return result;
    }

    constexpr UnsignedInteger16Byte
    UnsignedInteger16Byte::operator+() const noexcept
    {
        return *this;
    }

    constexpr UnsignedInteger16Byte
    UnsignedInteger16Byte::operator-() const noexcept
    {
        auto result = operator~();
        result.do_increment();

        return result;
    }

    constexpr UnsignedInteger16Byte
    UnsignedInteger16Byte::operator~() const noexcept
    {
        return UnsignedInteger16Byte(
            ~m_lowPart,
            ~m_highPart
        );
    }

    constexpr Integer16Byte
    UnsignedInteger16Byte::ToSigned() const noexcept
    {
        return Integer16Byte(m_lowPart, m_highPart);
    }

    constexpr bool operator==(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept
    {
        return
            left.HighPart() == right.HighPart()
            && left.LowPart() == right.LowPart();
    }

    constexpr bool operator==(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        if (left.IsNegative()) return false;
        return left.ToUnsigned() == right;
    }

    constexpr bool operator==(
        Integer16Byte left,
        int_least64_t right
    ) noexcept
    {
        if (left.IsNegative()) {
            if (right >= 0) return false;
            if (left.HighPart() != static_cast<uint_least64_t>(-1)) return false;

            return left.LowPart() == static_cast<uint_least64_t>(right);
        }
        // left >= 0
        else {
            if (right < 0) return false;

            return left.LowPart() == static_cast<uint_least64_t>(right);
        }
    }

    constexpr bool operator==(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept
    {
        if (left.HighPart() != 0) return false;

        return left.LowPart() == right;
    }

    constexpr bool operator==(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept
    {
        return right == left;
    }

    constexpr bool operator==(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return
            left.HighPart() == right.HighPart()
            && left.LowPart() == right.LowPart();
    }

    constexpr bool operator==(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept
    {
        if (right < 0) return false;

        return left == static_cast<uint_least64_t>(right);
    }

    constexpr bool operator==(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept
    {
        if (left.HighPart() != 0) return false;

        return left.LowPart() == right;
    }

    constexpr bool operator==(
        int_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        return right == left;
    }

    constexpr bool operator==(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return right == left;
    }

    constexpr bool operator==(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        return right == left;
    }

    constexpr bool operator==(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return right == left;
    }
    
    constexpr bool operator!=(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept
    {
        return !(left == right);
    }
    
    constexpr bool operator!=(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(left == right);
    }

    constexpr bool operator!=(
        Integer16Byte left,
        int_least64_t right
    ) noexcept
    {
        return !(left == right);
    }

    constexpr bool operator!=(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept
    {
        return !(left == right);
    }
    
    constexpr bool operator!=(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept
    {
        return !(left == right);
    }
    
    constexpr bool operator!=(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(left == right);
    }

    constexpr bool operator!=(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept
    {
        return !(left == right);
    }

    constexpr bool operator!=(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept
    {
        return !(left == right);
    }

    constexpr bool operator!=(
        int_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        return !(left == right);
    }

    constexpr bool operator!=(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(left == right);
    }

    constexpr bool operator!=(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        return !(left == right);
    }

    constexpr bool operator!=(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(left == right);
    }

    constexpr bool operator<(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept
    {
        if (left.IsNegative()) {
            if (right.IsNegative()) return left.ToUnsigned() < right.ToUnsigned();
            else return true;
        }
        else {
            if (right.IsNegative()) return false;
            else return left.ToUnsigned() < right.ToUnsigned();
        }
    }

    constexpr bool operator<(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        if (left.IsNegative()) return true;

        return left.ToUnsigned() < right;
    }

    constexpr bool operator<(
        Integer16Byte left,
        int_least64_t right
    ) noexcept
    {
        if (left.IsNegative()) {
            if (right < 0) return left.ToUnsigned() < static_cast<uint_least64_t>(right);
            else return true;
        }
        else {
            if (right < 0) return false;
            else return left.ToUnsigned() < static_cast<uint_least64_t>(right);
        }
    }

    constexpr bool operator<(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept
    {
        if (left.IsNegative()) return true;

        return left.ToUnsigned() < right;
    }

    constexpr bool operator<(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept
    {
        if (right.IsNegative()) return false;

        return left < right.ToUnsigned();
    }

    constexpr bool operator<(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        if (left.HighPart() < right.HighPart()) return true;
        if (left.HighPart() > right.HighPart()) return false;

        return left.LowPart() < right.LowPart();
    }

    constexpr bool operator<(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept
    {
        if (right < 0) return false;

        return left < static_cast<uint_least64_t>(right);
    }

    constexpr bool operator<(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept
    {
        if (left.HighPart() != 0) return false;

        return left.LowPart() < right;
    }

    constexpr bool operator<(
        int_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        if (left < 0) {
            if (right.IsNegative()) return static_cast<uint_least64_t>(left) < right.ToUnsigned();
            else return true;
        }
        else {
            if (right.IsNegative()) return false;
            return static_cast<uint_least64_t>(left) < right.ToUnsigned();
        }
    }

    constexpr bool operator<(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        if (left < 0) return true;

        return static_cast<uint_least64_t>(left) < right;
    }

    constexpr bool operator<(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        if (right.IsNegative()) return false;

        return left < right.ToUnsigned();
    }

    constexpr bool operator<(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        if (right.HighPart() != 0) return true;

        return left < right.LowPart();
    }

    constexpr bool operator<=(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator<=(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator<=(
        Integer16Byte left,
        int_least64_t right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator<=(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator<=(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator<=(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator<=(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator<=(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator<=(
        int_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator<=(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator<=(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator<=(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(right < left);
    }

    constexpr bool operator>(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        Integer16Byte left,
        int_least64_t right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        int_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>=(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr bool operator>=(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr bool operator>=(
        Integer16Byte left,
        int_least64_t right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr bool operator>=(
        Integer16Byte left,
        uint_least64_t right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr bool operator>=(
        UnsignedInteger16Byte left,
        Integer16Byte right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr bool operator>=(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr bool operator>=(
        UnsignedInteger16Byte left,
        int_least64_t right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr bool operator>=(
        UnsignedInteger16Byte left,
        uint_least64_t right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr bool operator>=(
        int_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr bool operator>=(
        int_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr bool operator>=(
        uint_least64_t left,
        Integer16Byte right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr bool operator>=(
        uint_least64_t left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        return !(left < right);
    }

    constexpr ::std::strong_ordering operator<=>(
        Integer16Byte left,
        Integer16Byte right
    ) noexcept
    {
        if (left.IsNegative()) {
            if (right.IsNegative()) return left.ToUnsigned() <=> right.ToUnsigned();
            else ::std::strong_ordering::less;
        }
        else {
            if (right.IsNegative()) return ::std::strong_ordering::greater;
            else return left.ToUnsigned() <=> right.ToUnsigned();
        }
    }

    constexpr ::std::strong_ordering operator<=>(
        Integer16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        if (left.IsNegative()) return ::std::strong_ordering::less;

        return left.ToUnsigned() <=> right;
    }

    constexpr ::std::strong_ordering operator<=>(
        UnsignedInteger16Byte left,
        UnsignedInteger16Byte right
    ) noexcept
    {
        auto highOrder = left.HighPart() <=> right.HighPart();

        if (highOrder == 0) return left.LowPart() <=> right.LowPart();
        
        return highOrder;
    }
}

#endif //!KLIB_KONGKONG_NUMERICS_INTEGER16BYTE_H