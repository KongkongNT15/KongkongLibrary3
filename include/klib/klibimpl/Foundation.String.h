#ifndef KLIB_FOUNDATION_STRING_H
#define KLIB_FOUNDATION_STRING_H

#include "base.h"
#include "Foundation.HandleType.h"

#if KLIB_ENV_WINDOWS

#elif KLIB_ENV_APPLE
    #include "AppleDevice.ObjCHandle.h"
#else

#endif

namespace klib::Foundation
{
    class String final : public HandleType {
        public:

        using ElementType = char16_t;

        private:
#if KLIB_ENV_WINDOWS
            ::HSTRING m_str;
#elif KLIB_ENV_APPLE
        AppleDevice::ObjCHandle m_str;
#else

#endif
        public:

        String(
            String const& other
        ) noexcept;

        constexpr String(
            String&& other
        ) noexcept;

        String& operator=(
            String const& other
        ) noexcept;

        String& operator=(
            String&& other
        ) noexcept;

        String& operator+=(
            String const& other
        );

        [[nodiscard]]
        const ElementType* begin() const noexcept;
        
        [[nodiscard]]
        const ElementType* end() const noexcept;
        
        [[nodiscard]]
        const ElementType* c_str() const noexcept;
        
        [[nodiscard]]
        bool Contains(
            ElementType c
        ) const noexcept;
        
        [[nodiscard]]
        bool IsEmpty() const noexcept;
    };

    [[nodiscard]]
    String operator+(
        String const& left,
        String const& right
    );

}

#endif //!KLIB_FOUNDATION_STRING_H