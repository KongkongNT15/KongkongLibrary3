#ifndef KLIB_WINRT_HSTRING_H
#define KLIB_WINRT_HSTRING_H

#include "base.h"
#include <winstring.h>

namespace klib::WinRT
{
    class HString {
        public:
        using ElementType = char16_t;
        private:

        ::HSTRING m_ref;

        public:

        [[nodiscard]]
        ElementType c_str() const noexcept;

        [[nodiscard]]
        bool IsEmpty() const noexcept;

        [[nodiscard]]
        HString SubString(
            uint32_t startIndex
        ) const;
    };
}

#endif //!KLIB_WINRT_HSTRING_H