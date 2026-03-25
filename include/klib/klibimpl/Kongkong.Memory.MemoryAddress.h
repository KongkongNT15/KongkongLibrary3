#ifndef KLIB_KONGKONG_MEMORY_MEMORYADDRESS_H
#define KLIB_KONGKONG_MEMORY_MEMORYADDRESS_H

#include "base.h"

namespace klib::Kongkong::Memory
{
    class MemoryAddress final {
        public:

        KLIB_STATIC_CLASS(MemoryAddress);

        [[nodiscard]]
        static constexpr intptr_t AlignUpUnsafe(
            intptr_t address,
            ssize_t alignment
        ) noexcept;

        [[nodiscard]]
        static constexpr void* AlignUpUnsafe(
            void* address,
            ssize_t alignment
        ) noexcept;
    };
}

namespace klib::Kongkong::Memory
{
    constexpr intptr_t MemoryAddress::AlignUpUnsafe(
        intptr_t address,
        ssize_t alignment
    ) noexcept
    {
        return (address + (alignment - 1)) & ~(alignment - 1);
    }

    constexpr void* MemoryAddress::AlignUpUnsafe(
        void* address,
        ssize_t alignment
    ) noexcept
    {
        intptr_t addr = reinterpret_cast<intptr_t>(address);
        intptr_t result = AlignUpUnsafe(addr, alignment);

        return reinterpret_cast<void*>(result);
    }
}

#endif //!KLIB_KONGKONG_MEMORY_MEMORYADDRESS_H