#ifndef KLIB_TEXT_UNICODE_UNICODETRAITS_H
#define KLIB_TEXT_UNICODE_UNICODETRAITS_H

#include "base.h"
#include "Text.Unicode.Utf8CharAttribute.h"

namespace klib::Text::Unicode
{
    class UnicodeTraits final {
        public:

        KLIB_STATIC_CLASS(UnicodeTraits);

        [[nodiscard]]
        static constexpr Utf8CharAttribute
        CharAttribute(
            char8_t c
        ) noexcept;

        [[nodiscard]]
        static constexpr bool IsHighSurrogate(
            char16_t c
        ) noexcept;

        [[nodiscard]]
        static constexpr bool IsLowSurrogate(
            char16_t c
        ) noexcept;

        [[nodiscard]]
        static constexpr bool IsSurrogate(
            char16_t c
        ) noexcept;

        [[nodiscard]]
        static constexpr bool IsSurrogatePairRequired(
            char32_t c
        ) noexcept;

        [[nodiscard]]
        static constexpr bool IsValidCodePoint(
            char16_t c
        ) noexcept;

        [[nodiscard]]
        static constexpr bool IsValidCodePoint(
            char32_t c
        ) noexcept;
    };
}

namespace klib::Text::Unicode
{
    constexpr Utf8CharAttribute UnicodeTraits::CharAttribute(
        char8_t c
    ) noexcept
    {
        if ((c & 0x80) == 0x00) return Utf8CharAttribute::SingleByte;
        if ((c & 0xE0) == 0xC0) return Utf8CharAttribute::TwoByteLead;
        if ((c & 0xF0) == 0xE0) return Utf8CharAttribute::ThreeByteLead;
        if ((c & 0xF8) == 0xF0) return Utf8CharAttribute::FourByteLead;
        if ((c & 0xFC) == 0xF8) return Utf8CharAttribute::FiveByteLead;
        if ((c & 0xFE) == 0xFC) return Utf8CharAttribute::SixByteLead;

        return Utf8CharAttribute::ContinuationByte;
    }

    constexpr bool UnicodeTraits::IsHighSurrogate(
        char16_t c
    ) noexcept
    {
        return 0xD7FF < c && c < 0xDC00;
    }

    constexpr bool UnicodeTraits::IsLowSurrogate(
        char16_t c
    ) noexcept
    {
        return 0xDBFF < c && c < 0xE000;
    }

    constexpr bool UnicodeTraits::IsSurrogate(
        char16_t c
    ) noexcept
    {
        return 0xD7FF < c && c < 0xE000;
    }

    constexpr bool UnicodeTraits::IsSurrogatePairRequired(
        char32_t c
    ) noexcept
    {
        return U'\U00010000' <= c && c <= U'\U0010FFFF';
    }

    constexpr bool UnicodeTraits::IsValidCodePoint(
        char16_t c
    ) noexcept
    {
        switch (c) {
            case 0xFFFE: [[unlikely]]
            case 0xFFFF: [[unlikely]]
                return false;

            default: [[likely]]
            {
                if (c < 0xD800) return true;

                // ここで c >= U'\uD800'
                // サロゲートペア
                if (c < 0xE000) return false;

                // ここで c >= U'\uE000'
                if (c < 0xFDD0) return true;

                // ここで c >= U'\uFDD0'
                // 非文字
                if (c < 0xFDF0) return false;

                return true;
            }
        }

#if KLIB_HAS_CPP23
        ::std::unreachable();
#endif
    }

    constexpr bool UnicodeTraits::IsValidCodePoint(
        char32_t c
    ) noexcept
    {
        if (c < 0xD800) return true;

        // ここで c >= U'\uD800'
        // サロゲートペア
        if (c < 0xE000) return false;

        // ここで c >= U'\uE000'
        if (c < 0xFDD0) return true;

        // ここで c >= U'\uFDD0'
        // 非文字
        if (c < 0xFDF0) return false;

        if ((c & 0xFFFF) == 0xFFFF || (c & 0xFFFE) == 0xFFFE) [[unlikely]] return false;

        return c < 0x00110000;
    }
    
}

#endif //!KLIB_TEXT_UNICODE_UNICODETRAITS_H
