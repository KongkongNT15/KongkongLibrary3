#ifndef KLIB_FOUNDATION_ARGUMENTEXCEPTION_H
#define KLIB_FOUNDATION_ARGUMENTEXCEPTION_H

#include "base.h"
#include "Foundation.Exception.h"

namespace klib::Foundation
{
    struct ArgumentException : public Exception {
        public:

        using Exception::Exception;

        constexpr ArgumentException() noexcept;

        constexpr ArgumentException(
            String const& message
        ) noexcept;

        constexpr ArgumentException(
            String&& message
        ) noexcept;
    };
}

namespace klib::Foundation
{
    constexpr ArgumentException::ArgumentException(
    ) noexcept
        : Exception(ErrorCode::ArgumentError)
    {
    }

    constexpr ArgumentException::ArgumentException(
        String const& message
    ) noexcept
        : Exception(
            ErrorCode::ArgumentError,
            message
        )
    {
    }

    constexpr ArgumentException::ArgumentException(
        String&& message
    ) noexcept
        : Exception(
            ErrorCode::ArgumentError,
            ::std::move(message)
        )
    {
    }
}

#endif //!KLIB_FOUNDATION_ARGUMENTEXCEPTION_H