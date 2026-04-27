#ifndef KLIB_IO_SEEKORIGIN_H
#define KLIB_IO_SEEKORIGIN_H

#include "base.h"

namespace klib::IO
{
    enum struct SeekOrigin {
        Begin,
        Current,
        End
    };
}

#endif //!KLIB_IO_SEEKORIGIN_H
