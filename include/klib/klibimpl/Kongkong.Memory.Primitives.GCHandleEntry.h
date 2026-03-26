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
        uint16_t Offset;
        GCObjectFlag Flags;

        [[nodiscard]]
        constexpr GCObjectHeader<>* GetHeader() const noexcept;
    };
}

namespace klib::Kongkong::Memory::Primitives
{
    constexpr GCObjectHeader<>* GCHandleEntry::GetHeader() const noexcept
    {
        intptr_t addr = reinterpret_cast<intptr_t>(ObjectPtr);

        return reinterpret_cast<GCObjectHeader<>*>(addr - Offset);
    }
}

#endif //!KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLEENTRY_H