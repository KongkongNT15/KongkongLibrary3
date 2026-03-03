#ifndef KLIB_KONGKONG_IO_FILESHAREMODE_H
#define KLIB_KONGKONG_IO_FILESHAREMODE_H

#include "base.h"

namespace klib::Kongkong::IO
{
    enum struct FileShareMode {
#if KLIB_ENV_WINDOWS
        Private = 0,
        Delete  = FILE_SHARE_DELETE,
        Read    = FILE_SHARE_READ,
        Write   = FILE_SHARE_WRITE,
#elif KLIB_ENV_UNIX

#endif

    };
}

#endif //!KLIB_KONGKONG_IO_FILESHAREMODE_H