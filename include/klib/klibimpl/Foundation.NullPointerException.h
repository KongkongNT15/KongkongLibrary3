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

        
    };
}

#endif //!KLIB_FOUNDATION_NULLPOINTEREXCEPTION_H
