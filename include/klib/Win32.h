#ifndef KLIB_WIN32_H
#define KLIB_WIN32_H

#include "klibimpl/base.h"

#if !KLIB_ENV_WINDOWS
#warning このヘッダーはWindows環境のみに対応しています。
#else

#include "klibimpl/Win32.Win32Handle.h"

#endif //!KLIB_ENV_WINDOWS
#endif //!KLIB_WIN32_H
