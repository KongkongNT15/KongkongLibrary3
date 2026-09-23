#ifndef KLIB_STD_STLMEMORYALLOCATOR_H
#define KLIB_STD_STLMEMORYALLOCATOR_H

#include "base.h"

#if KLIB_COMPILER_MSVC
    #include <malloc.h>
#else
    #include <stdlib.h>
#endif


namespace klib::Std
{
    class StlMemoryAllocator final {
        public:

        KLIB_STATIC_CLASS(StlMemoryAllocator);

        [[nodiscard]]
        static void* AlignedAlloc(
            size_t alignment,
            size_t size
        ) noexcept;

        static void AlignedFree(
            void* address
        ) noexcept;

        template <class T>
        [[nodiscard]]
        static T* Alloc() noexcept;

        [[nodiscard]]
        static void* Alloc(
            size_t size
        ) noexcept;

        
    };
}

namespace klib::Std
{
    inline void* StlMemoryAllocator::AlignedAlloc(
        size_t alignment,
        size_t size
    ) noexcept
    {
#if KLIB_COMPILER_MSVC
        return ::_aligned_malloc(size, alignment);
#else
        return ::aligned_alloc(alignment, size);
#endif
    }

    void StlMemoryAllocator::AlignedFree(
        void* address
    ) noexcept
    {
#if KLIB_COMPILER_MSVC
        ::_aligned_free(address);
#else
        ::free(address);
#endif
    }

    template <class T>
    T* StlMemoryAllocator::Alloc() noexcept
    {
        return AlignedAlloc(alignof(T), sizeof(T));
    }

    void* StlMemoryAllocator::Alloc(
        size_t size
    ) noexcept
    {
        return ::malloc(size);
    }
}

#endif //!KLIB_STD_STLMEMORYALLOCATOR_H