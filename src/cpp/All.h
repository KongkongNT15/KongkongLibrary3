#ifndef KLIB_ALL_H
#define KLIB_ALL_H

#include <klib/klibimpl/base.h>

#if KLIB_ENV_UNIX
    #include <sys/mman.h>
#endif

#include <klib/Kongkong.h>
#include <klib/Kongkong.Containers.h>
#include <klib/Kongkong.Functional.h>
#include <klib/Kongkong.IO.h>
#include <klib/Kongkong.Memory.h>
#include <klib/Kongkong.Numerics.h>
#include <klib/Kongkong.Threading.h>
#include <klib/Kongkong.Threading.Async.h>
#include <klib/Kongkong.Std.h>
#include <klib/Kongkong.Text.Unicode.h>

#if KLIB_ENV_WINDOWS
#include <klib/Kongkong.Win32.h>
#endif
#if KLIB_OBJECTIVE_C_ENABLED
#include <klib/Kongkong.AppleDevice.h>
#endif

#if KLIB_ENV_UNIX

#endif


// 標準ライブラリ
#include <chrono>
#include <thread>

#endif //!KLIB_ALL_H