#ifndef KLIB_KONGKONG_APPLEDEVICE_H
#define KLIB_KONGKONG_APPLEDEVICE_H

#include "klibimpl/base.h"

#if !KLIB_ENV_APPLE
#warning このヘッダーはApple環境のみに対応しています。
#else

#include "klibimpl/Kongkong.AppleDevice.ObjCHandle.h"

#endif //!KLIB_ENV_APPLE
#endif //!KLIB_KONGKONG_APPLEDEVICE_H