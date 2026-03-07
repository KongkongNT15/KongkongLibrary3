#ifndef KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLEENTRY_H
#define KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLEENTRY_H

#include "base.h"
#include "Kongkong.Memory.Primitives.GCObjectFlag.h"

#include <atomic>

namespace klib::Kongkong::Memory::Primitives
{
    struct alignas(16) GCHandleEntry final {
        void* ObjectPtr;
        uint32_t RefCount;
        GCObjectFlag Flags;
    };
}

#endif //!KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLEENTRY_H