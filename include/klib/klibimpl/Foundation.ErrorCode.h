#ifndef KLIB_FOUNDATION_ERRORCODE_H
#define KLIB_FOUNDATION_ERRORCODE_H

#include "base.h"

namespace klib::Foundation
{
    enum struct ErrorCode {
        NoError = 0,
        ArgumentError,
        ArgumentNull,
        ArgumentOutOfRange,
        IOError,
        MemoryAllocation,
        MemoryError,
        NotImplemented,
        NotSupported,
        NullPointer,
        Unknown = -1,
    };
}

#endif //!KLIB_FOUNDATION_ERRORCODE_H
