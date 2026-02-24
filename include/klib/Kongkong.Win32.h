#ifndef KLIB_KONGKONG_WIN32_H
#define KLIB_KONGKONG_WIN32_H

#include "klibimpl/base.h"

#if !KLIB_ENV_WINDOWS
#warning このヘッダーはWindows環境のみに対応しています。
#else

#include "klibimpl/Kongkong.Win32.Win32Handle.h"

#endif //!KLIB_ENV_WINDOWS
#endif //!KLIB_KONGKONG_WIN32_H