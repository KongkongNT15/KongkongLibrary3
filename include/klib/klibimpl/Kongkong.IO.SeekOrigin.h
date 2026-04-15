#ifndef KLIB_KONGKONG_IO_SEEKORIGIN_H
#define KLIB_KONGKONG_IO_SEEKORIGIN_H

#include "base.h"

namespace klib::Kongkong::IO
{
    enum struct SeekOrigin {
        Begin,
        Current,
        End
    };
}

#endif //!KLIB_KONGKONG_IO_SEEKORIGIN_H