#ifndef KLIB_NULLPOINTEREXCEPTION_H
#define KLIB_NULLPOINTEREXCEPTION_H

#include "base.h"
#include "Exception.h"

namespace klib
{
    struct NullPointerException : public Exception {

        static void CheckNull(
            const void* p
        );

        using Exception::Exception;

        
    };
}

#endif //!KLIB_NULLPOINTEREXCEPTION_H
