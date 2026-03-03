#ifndef KLIB_KONGKONG_IO_FILECREATEMODE_H
#define KLIB_KONGKONG_IO_FILECREATEMODE_H

#include "base.h"

namespace klib::Kongkong::IO
{
    enum struct FileCreateMode {
#if KLIB_ENV_WINDOWS
        CreateAlways     = CREATE_ALWAYS,
        CreateNew        = CREATE_NEW,
        OpenAlways       = OPEN_ALWAYS,
        OpenExisting     = OPEN_EXISTING,
        TruncateExisting = TRUNCATE_EXISTING,
#elif KLIB_ENV_UNIX

#endif

    };
}

#endif //!KLIB_KONGKONG_IO_FILECREATEMODE_H