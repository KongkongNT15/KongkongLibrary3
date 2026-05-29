#ifndef KLIB_ALL_H
#define KLIB_ALL_H

#include <klib/klibimpl/base.h>

#if KLIB_ENV_UNIX
    #include <sys/mman.h>
    #include <sys/stat.h>
#endif

#include <klib/Foundation.h>
#include <klib/Bits.h>
#include <klib/Containers.h>
#include <klib/CStd.h>
#include <klib/Functional.h>
#include <klib/IO.h>
#include <klib/Memory.h>
#include <klib/Memory.Primitives.h>
#include <klib/Net.h>
#include <klib/Numerics.h>
#include <klib/Ranges.h>
#include <klib/Std.h>
#include <klib/Text.h>
#include <klib/Text.Unicode.h>
#include <klib/Threading.h>
#include <klib/Threading.Async.h>


#if KLIB_ENV_WINDOWS
#include <klib/Win32.h>
#endif
#if KLIB_OBJECTIVE_C_ENABLED
#include <klib/AppleDevice.h>
#endif

#if KLIB_ENV_UNIX

#endif


// 標準ライブラリ
#include <chrono>
#include <thread>

#endif //!KLIB_ALL_H