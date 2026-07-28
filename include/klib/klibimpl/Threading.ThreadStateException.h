#ifndef KLIB_THREADING_THREADSTATEEXCEPTION_H
#define KLIB_THREADING_THREADSTATEEXCEPTION_H

#include "base.h"
#include "Foundation.Exception.h"

namespace klib::Threading
{
    struct ThreadStateException : public Exception {
        public:

        using Exception::Exception;

        consteval ThreadStateException() noexcept;

        constexpr ThreadStateException(
            String const& message
        ) noexcept;

        constexpr ThreadStateException(
            String&& message
        ) noexcept;
    };
}

namespace klib::Threading
{
    consteval ThreadStateException::ThreadStateException(
    ) noexcept
        : Exception(
            ErrorCode::ThreadError
        )
    {
    }

    constexpr ThreadStateException::ThreadStateException(
        String const& message
    ) noexcept
        : Exception(
            ErrorCode::ThreadError,
            message
        )
    {
    }

    constexpr ThreadStateException::ThreadStateException(
        String&& message
    ) noexcept
        : Exception(
            ErrorCode::ThreadError,
            ::std::move(message)
        )
    {
    }

}

#endif //!KLIB_THREADING_THREADSTATEEXCEPTION_H