#ifndef KLIB_APPLEDEVICE_NSOBJECT_H
#define KLIB_APPLEDEVICE_NSOBJECT_H

#include "base.h"
#include "AppleDevice.ObjCHandle.h"
#include "Foundation.PointerType.h"

namespace klib::AppleDevice
{
    class NSObject : public PointerType {
        protected:

        ObjCHandle m_handle;

        public:

        [[nodiscard]]
        unsigned ClassCode() const noexcept;

        [[nodiscard]]
        Foundation::NSString ClassName() const noexcept;
    };
}

#endif //!KLIB_APPLEDEVICE_NSOBJECT_H