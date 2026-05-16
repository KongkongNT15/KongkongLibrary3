#ifndef KLIB_MEMORY_PRIMITIVES_GCHANDLEENTRY_H
#define KLIB_MEMORY_PRIMITIVES_GCHANDLEENTRY_H

#include "base.h"
#include "Memory.Primitives.GCObject.h"
#include "Memory.Primitives.GCObjectFlag.h"

#include <atomic>

#ifdef GetObject
    #undef GetObject
#endif

namespace klib::Memory::Primitives
{
    struct alignas(16) GCHandleEntry final {
        void* ObjectPtr;
        uint32_t RefCount;
        uint16_t Offset;
        GCObjectFlag Flags;

        [[nodiscard]]
        constexpr GCObjectHeader<>* GetHeader() const noexcept;

        [[nodiscard]]
        constexpr GCObject<>* GetObject() const noexcept;
    };
}

namespace klib::Memory::Primitives
{
    constexpr GCObjectHeader<>* GCHandleEntry::GetHeader() const noexcept
    {
        intptr_t addr = reinterpret_cast<intptr_t>(ObjectPtr);

        return reinterpret_cast<GCObjectHeader<>*>(addr - Offset);
    }

    constexpr GCObject<>*
    GCHandleEntry::GetObject() const noexcept
    {
        return GCObject<>::GetObject(GetHeader());
    }
}

#endif //!KLIB_MEMORY_PRIMITIVES_GCHANDLEENTRY_H
