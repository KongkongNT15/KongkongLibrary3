#ifndef KLIB_WINRT_H
#define KLIB_WINRT_H

#include "klibimpl/base.h"

#if !KLIB_ENV_WINDOWS
#warning このヘッダーはWindows環境のみに対応しています。
#else

#include "klibimpl/WinRT.HString.h"

#endif //!KLIB_ENV_WINDOWS
#endif //!KLIB_WINRT_H