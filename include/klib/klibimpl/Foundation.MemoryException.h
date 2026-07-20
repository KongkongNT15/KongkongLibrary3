#ifndef KLIB_FOUNDATION_MEMORYEXCEPTION_H
#define KLIB_FOUNDATION_MEMORYEXCEPTION_H

#include "base.h"
#include "Foundation.Exception.h"

namespace klib::Foundation
{
    struct MemoryException : public Exception {
        public:

        using Exception::Exception;
    };
}

#endif //!KLIB_FOUNDATION_MEMORYEXCEPTION_H
