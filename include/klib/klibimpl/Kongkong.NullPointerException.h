#ifndef KLIB_KONGKONG_NULLPOINTEREXCEPTION_H
#define KLIB_KONGKONG_NULLPOINTEREXCEPTION_H

#include "base.h"
#include "Kongkong.Exception.h"

namespace klib::Kongkong
{
    struct NullPointerException : public Exception {

        static void CheckNull(
            const void* p
        );

        using Exception::Exception;

        
    };
}

#endif //!KLIB_KONGKONG_NULLPOINTEREXCEPTION_H