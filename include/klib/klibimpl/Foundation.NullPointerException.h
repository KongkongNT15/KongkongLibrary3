#ifndef KLIB_FOUNDATION_NULLPOINTEREXCEPTION_H
#define KLIB_FOUNDATION_NULLPOINTEREXCEPTION_H

#include "base.h"
#include "Foundation.Exception.h"

namespace klib::Foundation
{
    struct NullPointerException : public Exception {

        static void CheckNull(
            const void* p
        );

        using Exception::Exception;

        NullPointerException();
    };
}

namespace klib::Foundation
{
#if KLIB_DEBUG
    inline void NullPointerException::CheckNull(
        const void* p
    )
    {
        if (p == nullptr) [[unlikely]] throw NullPointerException();
    }

#else
    inline void NullPointerException::CheckNull(
        const void*
    )
    {
        // 何もしないお
    }
#endif
}

#endif //!KLIB_FOUNDATION_NULLPOINTEREXCEPTION_H
