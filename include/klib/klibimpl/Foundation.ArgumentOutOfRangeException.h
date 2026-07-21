#ifndef KLIB_FOUNDATION_ARGUMENTOUTOGRANGEEXCEPTION_H
#define KLIB_FOUNDATION_ARGUMENTOUTOGRANGEEXCEPTION_H

#include "base.h"
#include "Foundation.ArgumentException.h"

namespace klib::Foundation
{
    struct ArgumentOutOfRangeException : public ArgumentException {
        public:

        using ArgumentException::ArgumentException;

        constexpr ArgumentOutOfRangeException() noexcept;

        constexpr ArgumentOutOfRangeException(
            String const& message
        ) noexcept;

        constexpr ArgumentOutOfRangeException(
            String&& message
        ) noexcept;

    };
}

namespace klib::Foundation
{
    constexpr ArgumentOutOfRangeException::ArgumentOutOfRangeException(
    ) noexcept
        : ArgumentException(
            ErrorCode::ArgumentOutOfRange
        )
    {
    }

    constexpr ArgumentOutOfRangeException::ArgumentOutOfRangeException(
        String const& message
    ) noexcept
        : ArgumentException(
            ErrorCode::ArgumentOutOfRange,
            message
        )
    {
    }

    constexpr ArgumentOutOfRangeException::ArgumentOutOfRangeException(
        String&& message
    ) noexcept
        : ArgumentException(
            ErrorCode::ArgumentOutOfRange,
            ::std::move(message)
        )
    {
    }

}

#endif //!KLIB_FOUNDATION_ARGUMENTOUTOGRANGEEXCEPTION_H