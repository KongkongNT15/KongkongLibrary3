#ifndef KLIB_KONGKONG_MEMORY_MEMORYPAGEHELPER_H
#define KLIB_KONGKONG_MEMORY_MEMORYPAGEHELPER_H

#include "base.h"

#if KLIB_ENV_WINDOWS

#elif KLIB_ENV_UNIX
    #include <sys/mman.h>
    #include <stdio.h>
#endif

namespace klib::Kongkong::Memory
{
    class MemoryPageHelper final {
        private:

        static size_t s_pageSize;

        public:

        KLIB_STATIC_CLASS(MemoryPageHelper);

        static bool Commit(
            void* targetAddress,
            size_t bytes
        ) noexcept;

        static bool Free(
            void* page,
            size_t regionSize
        ) noexcept;

        [[nodiscard]]
        static size_t PageSize() noexcept;

        [[nodiscard]]
        static void* Reserve(
            size_t minBytes
        ) noexcept;

        static bool Decommit(
            void* targetAddress,
            size_t bytes
        ) noexcept;

        static bool DecommitAll(
            void* page,
            size_t bytes
        ) noexcept;
    };
}

namespace klib::Kongkong::Memory
{
    inline size_t MemoryPageHelper::PageSize() noexcept
    {
        return s_pageSize;
    }
#if KLIB_ENV_WINDOWS
    

    inline bool MemoryPageHelper::Free(
        void* page,
        size_t
    ) noexcept
    {
        ::BOOL result = ::VirtualFree(
            page,
            0,
            MEM_RELEASE
        );

        return static_cast<bool>(result);
    }

    inline void* MemoryPageHelper::Reserve(
        size_t minBytes
    ) noexcept
    {
        return ::VirtualAlloc(
            nullptr,
            minBytes,
            MEM_RESERVE,
            PAGE_READWRITE
        );
    }

    inline bool MemoryPageHelper::Commit(
        void* targetAddress,
        size_t bytes
    ) noexcept
    {
        return ::VirtualAlloc(
            targetAddress,
            bytes,
            MEM_COMMIT,
            PAGE_READWRITE
        ) != nullptr;
    }

    inline bool MemoryPageHelper::Decommit(
        void* targetAddress,
        size_t bytes
    ) noexcept
    {
        ::BOOL result = ::VirtualFree(
            targetAddress,
            bytes,
            MEM_DECOMMIT
        );

        return static_cast<bool>(result);
    }

    inline bool MemoryPageHelper::DecommitAll(
        void* page,
        size_t
    ) noexcept
    {
        ::BOOL result = ::VirtualFree(
            page,
            0,
            MEM_DECOMMIT
        );

        return static_cast<bool>(result);
    }

#elif KLIB_ENV_UNIX

    inline bool MemoryPageHelper::Free(
        void* page,
        size_t regionSize
    ) noexcept
    {
        return ::munmap(page, regionSize) != EOF;
    }

    inline void* MemoryPageHelper::Reserve(
        size_t minBytes
    ) noexcept
    {
        return ::mmap(
            nullptr,
            minBytes,
            PROT_NONE,
            MAP_PRIVATE | MAP_ANONYMOUS,
            -1,
            0
        );
    }

    inline bool MemoryPageHelper::Commit(
        void* targetAddress,
        size_t bytes
    ) noexcept
    {
        return ::mprotect(
            targetAddress,
            bytes,
            PROT_READ | PROT_WRITE
        ) != EOF;
    }

    inline bool MemoryPageHelper::Decommit(
        void* targetAddress,
        size_t bytes
    ) noexcept
    {
        // アクセスを禁止し（予約状態に戻す）、物理メモリのヒントも与えますｳﾋｮｯ
        int result1 = ::mprotect(targetAddress, bytes, PROT_NONE);
        int result2 = ::madvise(targetAddress, bytes, MADV_DONTNEED);

        return result1 != EOF && result2 != EOF;
    }

    inline bool MemoryPageHelper::DecommitAll(
        void* page,
        size_t bytes
    ) noexcept
    {
        // 同じアドレスに対して PROT_NONE で上書きマッピングを行うｳﾋｮｯ
        return mmap(
            page,
            bytes,
            PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
            -1,
            0
        ) != nullptr;
    }
#endif
}

#endif //!KLIB_KONGKONG_MEMORY_MEMORYPAGEHELPER_H