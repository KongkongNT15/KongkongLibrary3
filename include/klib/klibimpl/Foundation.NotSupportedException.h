#ifndef KLIB_FOUNDATION_NOTSUPPORTEDEXCEPTION_H
#define KLIB_FOUNDATION_NOTSUPPORTEDEXCEPTION_H

#include "base.h"
#include "Foundation.Exception.h"

namespace klib::Foundation
{
    struct NotSupportedException : public Exception {
        public:

        constexpr NotSupportedException(
            String const& message
        ) noexcept;

        constexpr NotSupportedException(
            String&& message
        ) noexcept;
    };
}

namespace klib::Foundation
{
    constexpr NotSupportedException::NotSupportedException(
        String const& message
    ) noexcept
        : Exception(
            ErrorCode::NotSupported,
            message
        )
    {
    }

    constexpr NotSupportedException::NotSupportedException(
        String&& message
    ) noexcept
        : Exception(
            ErrorCode::NotSupported,
            ::std::move(message)
        )
    {
    }
}

#endif //!KLIB_FOUNDATION_NOTSUPPORTEDEXCEPTION_H