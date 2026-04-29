#ifndef KLIB_TEXT_UNICODE_UTH8CHAR_H
#define KLIB_TEXT_UNICODE_UTH8CHAR_H

#include "base.h"
#include "Foundation.NonType.h"
#include "Foundation.ValueType.h"

namespace klib::Text::Unicode
{
    struct Utf8Char : public ValueType {
        private:
        static constexpr int s_maxLength = 4;

        static constexpr byte do_encode(
            char32_t source,
            Utf8Char& dest
        ) noexcept;

        [[noreturn]]
        static void do_throw();

        char8_t m_char[s_maxLength];
        byte m_length;

        constexpr Utf8Char(
            char32_t c,
            NonType
        ) noexcept;
        public:

        [[nodiscard]]
        static constexpr Utf8Char CreateUnsafe(
            char32_t c
        ) noexcept;

        constexpr Utf8Char(
            char32_t c
        );
    };
}

namespace klib::Text::Unicode
{
    constexpr byte Utf8Char::do_encode(
        char32_t source,
        Utf8Char& dest
    ) noexcept
    {
        if (source < 0x80) {
            dest.m_char[0] = static_cast<char8_t>(source);
            return 1;
        }
        if (source < 0x800) {
            dest.m_char[0] = static_cast<char8_t>(0xC0 | ((source >> 6) & 0x1F));
            dest.m_char[1] = static_cast<char8_t>(0x80 | (source & 0x3F));
            
            return 2;
        }
        if (source < 0x10000) {
            dest.m_char[0] = static_cast<char8_t>(0xE0 | ((source >> 12) & 0x0F));
            dest.m_char[1] = static_cast<char8_t>(0x80 | ((source >> 6) & 0x3F));
            dest.m_char[2] = static_cast<char8_t>(0x80 | (source & 0x3F));
            
            return 3;
        }
        if (source < 0x110000) {
            dest.m_char[0] = static_cast<char8_t>(0xF0 | ((source >> 18) & 0x07));
            dest.m_char[1] = static_cast<char8_t>(0x80 | ((source >> 12) & 0x3F));
            dest.m_char[2] = static_cast<char8_t>(0x80 | ((source >> 6) & 0x3F));
            dest.m_char[3] = static_cast<char8_t>(0x80 | (source & 0x3F));
            
            return 4;
        }

        return -1;
    }

    constexpr Utf8Char Utf8Char::CreateUnsafe(
        char32_t c
    ) noexcept
    {
        return Utf8Char(c, NonType{});
    }

    constexpr Utf8Char::Utf8Char(
        char32_t c,
        NonType
    ) noexcept
        : m_char{}
        , m_length(do_encode(c, *this))
    {
    }

    constexpr Utf8Char::Utf8Char(
        char32_t c
    )
        : Utf8Char(c, NonType{})
    {
        if (m_length == static_cast<byte>(-1)) [[unlikely]] {
            do_throw();
        }
    }
}

#endif //!KLIB_TEXT_UNICODE_UTH8CHAR_H