#ifndef KLIB_FOUNDATION_INVALIDOPERATIONEXCEPTION_H
#define KLIB_FOUNDATION_INVALIDOPERATIONEXCEPTION_H

#include "base.h"
#include "Foundation.Exception.h"

namespace klib::Foundation
{
    struct InvalidOperationException : public Exception {
        public:

        using Exception::Exception;

        consteval InvalidOperationException() noexcept;

        constexpr InvalidOperationException(
            String const& message
        ) noexcept;

        constexpr InvalidOperationException(
            String&& message
        ) noexcept;
    };
}

namespace klib::Foundation
{
    consteval InvalidOperationException::InvalidOperationException(
    ) noexcept
        : Exception(
            ErrorCode::InvalidOperation
        )
    {
    }

    constexpr InvalidOperationException::InvalidOperationException(
        String const& message
    ) noexcept
        : Exception(
            ErrorCode::InvalidOperation,
            message
        )
    {
    }

    constexpr InvalidOperationException::InvalidOperationException(
        String&& message
    ) noexcept
        : Exception(
            ErrorCode::InvalidOperation,
            message
        )
    {
    }
}

#endif //!KLIB_FOUNDATION_INVALIDOPERATIONEXCEPTION_H