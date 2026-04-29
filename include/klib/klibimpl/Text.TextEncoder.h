#ifndef KLIB_TEXT_TEXTENCODER_H
#define KLIB_TEXT_TEXTENCODER_H

#include "base.h"
#include "Text.TextEncodingArgs.h"
#include "Text.Unicode.SurrogatePair.h"
#include "Text.Unicode.UnicodeTraits.h"

namespace klib::Text
{
    class TextEncoder final {
        public:

        KLIB_STATIC_CLASS(TextEncoder);

        [[nodiscard]]
        static ssize_t GetUtf16CharCountUnsafe(
            ssize_t length,
            const char32_t* str
        ) noexcept;

        template <class TPredicate>
        static constexpr void ToUtf16Unsafe(
            ssize_t length,
            const char32_t* str,
            TPredicate&& pred
        ) noexcept;

        template <class TPredicate>
        static constexpr void ToUtf32Unsafe(
            ssize_t length,
            const char8_t* str,
            TPredicate&& pred
        ) noexcept;

        template <class TPredicate>
        static constexpr void ToUtf32Unsafe(
            ssize_t length,
            const char16_t* str,
            TPredicate&& pred
        ) noexcept;
    };
}

namespace klib::Text
{
    constexpr ssize_t TextEncoder::GetUtf16CharCountUnsafe(
        ssize_t length,
        const char32_t* str
    ) noexcept
    {
        ssize_t result = 0;

        ToUtf16Unsafe(
            length,
            str,
            [&]() { ++result; }
        );

        return result;
    }

    template <class TPredicate>
    static constexpr void TextEncoder::ToUtf16Unsafe(
        ssize_t length,
        const char32_t* str,
        TPredicate&& pred
    ) noexcept
    {
        constexpr bool isInvocaleAllArgs = ::std::invocable<TPredicate, TextEncodingArgs<char32_t, char16_t>>;
        constexpr bool isInvocableCharBool = ::std::invocable<TPredicate, char16_t, bool>;

        const char32_t* itr = str;
        const char32_t* end = itr + length;

        char32_t c;

        while (itr != end) {
            c = *itr;

            if (Unicode::UnicodeTraits::IsSurrogatePairRequired(c)) {
                Unicode::SurrogatePair pair = Unicode::SurrogatePair::CreateUnsafe(c);

                if constexpr (isInvocaleAllArgs) {
                    pred({ itr, 1, pair.HighSurrogate(), true });
                    pred({ itr, 1, pair.LowSurrogate(), true });
                }
                else if constexpr (isInvocableCharBool) {
                    pred(pair.HighSurrogate(), true);
                    pred(pair.LowSurrogate(), true);
                }
                else {
                    pred();
                    pred();
                }

                
            }
            else if (Unicode::UnicodeTraits::IsValidCodePoint(c)) [[likely]] {
                char16_t result = static_cast<char16_t>(c);
                if constexpr (isInvocaleAllArgs) {
                    pred({ itr, 1, result, true });
                }
                else if constexpr (isInvocableCharBool) {
                    pred(result, true);
                }
                else {
                    pred();
                }
            }
            else [[unlikely]] {
                if constexpr (isInvocaleAllArgs) {
                    pred({ itr, 1, u'?', false });
                }
                else if constexpr (isInvocableCharBool) {
                    pred(u'?', false);
                }
                else {
                    pred();
                }
            }

            ++itr;
        }
    }

    template <class TPredicate>
    static constexpr void TextEncoder::ToUtf32Unsafe(
        ssize_t length,
        const char8_t* str,
        TPredicate&& pred
    ) noexcept
    {
        constexpr bool isInvocaleAllArgs = ::std::invocable<TPredicate, TextEncodingArgs<char8_t, char32_t>>;
        constexpr bool isInvocableCharBool = ::std::invocable<TPredicate, char32_t, bool>;

        const char8_t* itr = str;
        const char8_t* end = itr + length;

        
    }

    template <class TPredicate>
    static constexpr void TextEncoder::ToUtf32Unsafe(
        ssize_t length,
        const char16_t* str,
        TPredicate&& pred
    ) noexcept
    {
        constexpr bool isInvocaleAllArgs = ::std::invocable<TPredicate, TextEncodingArgs<char16_t, char32_t>>;
        constexpr bool isInvocableCharBool = ::std::invocable<TPredicate, char32_t, bool>;

        const char16_t* itr = str;
        const char16_t* end = itr + length;

        char16_t c;

        while (itr != end) {
            c = *itr;

            if (Unicode::UnicodeTraits::IsHighSurrogate(c)) {
                ++itr;
                char16_t c2 = *itr;

                if (Unicode::UnicodeTraits::IsLowSurrogate(c2)) [[likely]] {
                    char32_t result = Unicode::SurrogatePair::ToUnicodeUnsafe(c, c2);
                    if constexpr (isInvocaleAllArgs) {
                        pred({ itr - 1, 2, result, true });
                    }
                    else if constexpr (isInvocableCharBool) {
                        pred(result, true);
                    }
                    else {
                        pred();
                    }
                    
                }
                else {
                    char32_t result = Unicode::SurrogatePair::ToUnicodeUnsafe(c, c2);
                    if constexpr (isInvocaleAllArgs) {
                        pred({ itr - 1, 2, U'?', false });
                    }
                    else if constexpr (isInvocableCharBool) {
                        pred(U'?', false);
                    }
                    else {
                        pred();
                    }
                }
            }
            else if (Unicode::UnicodeTraits::IsLowSurrogate(c)) [[unlikely]] {
                if constexpr (isInvocaleAllArgs) {
                    pred({ itr, 1, U'?', false });
                }
                else if constexpr (isInvocableCharBool) {
                    pred(U'?', false);
                }
                else {
                    pred();
                }
            }
            else {
                char32_t result = static_cast<char32_t>(c);
                if constexpr (isInvocaleAllArgs) {
                    pred({ itr, 2, result, true });
                }
                else if constexpr (isInvocableCharBool) {
                    pred(result, true);
                }
                else {
                    pred();
                }
            }

            ++itr;
        }
    }
}

#endif //!KLIB_TEXT_TEXTENCODER_H