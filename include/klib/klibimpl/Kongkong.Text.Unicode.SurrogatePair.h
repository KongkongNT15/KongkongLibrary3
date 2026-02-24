#ifndef KLIB_KONGKONG_TEXT_UNICODE_SURROGATEPAIR_H
#define KLIB_KONGKONG_TEXT_UNICODE_SURROGATEPAIR_H

#include "base.h"
#include "Kongkong.NonType.h"

namespace klib::Kongkong::Text::Unicode
{
    struct SurrogatePair {
        private:

        static void s_checkPair(
            char16_t highSurrogate,
            char16_t lowSurrogate
        );

        char16_t m_lowSurrogate;
        char16_t m_highSurrogate;

        constexpr SurrogatePair(
            char32_t c,
            NonType
        ) noexcept;

        public:

        [[nodiscard]]
        static constexpr SurrogatePair CreateUnsafe(
            char32_t c
        ) noexcept;

        [[nodiscard]]
        static char32_t ToUnicode(
            char16_t highSurrogate,
            char16_t lowSurrogate
        );

        [[nodiscard]]
        static constexpr char32_t ToUnicodeUnsafe(
            char16_t highSurrogate,
            char16_t lowSurrogate
        ) noexcept;

        SurrogatePair(
            char32_t c
        );

        SurrogatePair(
            char16_t highSurrogate,
            char16_t lowSurrogate
        );

        [[nodiscard]]
        constexpr char16_t HighSurrogate() const noexcept;

        [[nodiscard]]
        constexpr char16_t LowSurrogate() const noexcept;

        [[nodiscard]]
        constexpr char32_t ToUnicode() const noexcept;
    };

    [[nodiscard]]
    constexpr bool operator==(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        SurrogatePair const& left,
        char32_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        char32_t left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept;

     [[nodiscard]]
    constexpr bool operator!=(
        SurrogatePair const& left,
        char32_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        char32_t left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        SurrogatePair const& left,
        char32_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        char32_t left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        SurrogatePair const& left,
        char32_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        char32_t left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        SurrogatePair const& left,
        char32_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        char32_t left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        SurrogatePair const& left,
        char32_t right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        char32_t left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        SurrogatePair const& left,
        char32_t right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        char32_t left,
        SurrogatePair const& right
    ) noexcept;
}

namespace klib::Kongkong::Text::Unicode
{
    constexpr SurrogatePair SurrogatePair::CreateUnsafe(
        char32_t c
    ) noexcept
    {
        return SurrogatePair(c, NonType{});
    }

    constexpr char32_t SurrogatePair::ToUnicodeUnsafe(
        char16_t highSurrogate,
        char16_t lowSurrogate
    ) noexcept {
        return static_cast<char32_t>(
            ((highSurrogate - 0xD800) << 10)
            + lowSurrogate
            + (-0xDC00 + 0x10000)
        );
    }

    constexpr SurrogatePair::SurrogatePair(
        char32_t c,
        NonType
    ) noexcept
    {
        uint32_t cpPrime = c - 0x10000;

        m_highSurrogate = static_cast<char16_t>(
            0xD800 + (cpPrime >> 10)
        );
        m_lowSurrogate = static_cast<char16_t>(
            0xDC00 + (cpPrime & 0x3FF)
        );
    }

    inline SurrogatePair::SurrogatePair(
        char32_t c
    )
        : SurrogatePair(c, NonType{})
    {
        s_checkPair(m_highSurrogate, m_lowSurrogate);
    }

    inline SurrogatePair::SurrogatePair(
            char16_t highSurrogate,
            char16_t lowSurrogate
    )
        : m_highSurrogate(highSurrogate)
        , m_lowSurrogate(lowSurrogate)
    {
        s_checkPair(highSurrogate, lowSurrogate);
    }

    constexpr char16_t SurrogatePair::HighSurrogate() const noexcept
    {
        return m_highSurrogate;
    }

    constexpr char16_t SurrogatePair::LowSurrogate() const noexcept
    {
        return m_lowSurrogate;
    }

    constexpr char32_t SurrogatePair::ToUnicode() const noexcept
    {
        return ToUnicodeUnsafe(m_highSurrogate, m_lowSurrogate);
    }

    constexpr bool operator==(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept
    {
        if (left.HighSurrogate() != right.HighSurrogate()) return false;
        return left.LowSurrogate() == right.LowSurrogate();
    }

    constexpr bool operator==(
        SurrogatePair const& left,
        char32_t right
    ) noexcept
    {
        return left.ToUnicode() == right;
    }

    constexpr bool operator==(
        char32_t left,
        SurrogatePair const& right
    ) noexcept
    {
        return left == right.ToUnicode();
    }

    constexpr bool operator!=(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept
    {
        if (left.HighSurrogate() == right.HighSurrogate()) return false;
        return left.LowSurrogate() != right.LowSurrogate();
    }

    constexpr bool operator!=(
        SurrogatePair const& left,
        char32_t right
    ) noexcept
    {
        return left.ToUnicode() != right;
    }

    constexpr bool operator!=(
        char32_t left,
        SurrogatePair const& right
    ) noexcept
    {
        return left != right.ToUnicode();
    }

    constexpr bool operator<(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept
    {
        return left.ToUnicode() < right.ToUnicode();
    }

    constexpr bool operator<(
        SurrogatePair const& left,
        char32_t right
    ) noexcept
    {
        return left.ToUnicode() < right;
    }

    constexpr bool operator<(
        char32_t left,
        SurrogatePair const& right
    ) noexcept
    {
        return left < right.ToUnicode();
    }
    
    constexpr bool operator<=(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept
    {
        return left.ToUnicode() <= right.ToUnicode();
    }

    constexpr bool operator<=(
        SurrogatePair const& left,
        char32_t right
    ) noexcept
    {
        return left.ToUnicode() <= right;
    }

    constexpr bool operator<=(
        char32_t left,
        SurrogatePair const& right
    ) noexcept
    {
        return left <= right.ToUnicode();
    }

    constexpr bool operator>(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept
    {
        return left.ToUnicode() > right.ToUnicode();
    }

    constexpr bool operator>(
        SurrogatePair const& left,
        char32_t right
    ) noexcept
    {
        return left.ToUnicode() > right;
    }

    constexpr bool operator>(
        char32_t left,
        SurrogatePair const& right
    ) noexcept
    {
        return left > right.ToUnicode();
    }

    constexpr bool operator>=(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept
    {
        return left.ToUnicode() >= right.ToUnicode();
    }

    constexpr bool operator>=(
        SurrogatePair const& left,
        char32_t right
    ) noexcept
    {
        return left.ToUnicode() >= right;
    }

    constexpr bool operator>=(
        char32_t left,
        SurrogatePair const& right
    ) noexcept
    {
        return left >= right.ToUnicode();
    }

    constexpr ::std::strong_ordering operator<=>(
        SurrogatePair const& left,
        SurrogatePair const& right
    ) noexcept
    {
        return left.ToUnicode() <=> right.ToUnicode();
    }

    constexpr ::std::strong_ordering operator<=>(
        SurrogatePair const& left,
        char32_t right
    ) noexcept
    {
        return left.ToUnicode() <=> right;
    }

    constexpr ::std::strong_ordering operator<=>(
        char32_t left,
        SurrogatePair const& right
    ) noexcept
    {
        return left <=> right.ToUnicode();
    }
}

#endif //!KLIB_KONGKONG_TEXT_UNICODE_SURROGATEPAIR_H