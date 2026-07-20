#ifndef KLIB_FOUNDATION_NULLPOINTEREXCEPTION_H
#define KLIB_FOUNDATION_NULLPOINTEREXCEPTION_H

#include "base.h"
#include "Foundation.Exception.h"

namespace klib::Foundation
{
    struct NullPointerException : public Exception {
        private:

        static constexpr char16_t s_defaultMessage[] = u"";

        public:

        static void CheckNull(
            const void* p
        );

        using Exception::Exception;

        constexpr NullPointerException() noexcept;
    };
}

namespace klib::Foundation
{
    inline void NullPointerException::CheckNull(
        const void* p
    )
    {
        if (p == nullptr) [[unlikely]] throw NullPointerException();
    }

    constexpr NullPointerException::NullPointerException()
        : Exception(
            ErrorCode::NullPointer,
            s_defaultMessage
        )
    {
    }
}

#endif //!KLIB_FOUNDATION_NULLPOINTEREXCEPTION_H
