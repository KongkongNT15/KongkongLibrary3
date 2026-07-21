#ifndef KLIB_IO_IOEXCEPTION_H
#define KLIB_IO_IOEXCEPTION_H

#include "base.h"
#include "Foundation.Exception.h"

namespace klib::IO
{
    struct IOException : public Exception {
        public:

        using Exception::Exception;

        constexpr IOException(
            String const& message
        ) noexcept;

        constexpr IOException(
            String&& message
        ) noexcept;
    };
}

namespace klib::IO
{
    constexpr IOException::IOException(
        String const& message
    ) noexcept
        : Exception(
            ErrorCode::IOError,
            message
        )
    {
    }

    constexpr IOException::IOException(
        String&& message
    ) noexcept
        : Exception(
            ErrorCode::IOError,
            ::std::move(message)
        )
    {
    }
}

#endif //!KLIB_IO_IOEXCEPTION_H