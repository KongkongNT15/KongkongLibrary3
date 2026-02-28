namespace klib::Kongkong::Memory
{
#if KLIB_ENV_WINDOWS
    size_t MemoryResource::s_pageSize = [] () {
        ::SYSTEM_INFO si;
        ::GetSystemInfo(&si);
        return si.dwPageSize;
    }();

    bool MemoryResource::do_free() noexcept
    {
        ::BOOL result = ::VirtualFree(
            m_p,
            0,
            MEM_RELEASE
        );

        return static_cast<bool>(result);
    }

    void* MemoryResource::do_reserve(
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

    bool MemoryResource::Commit(
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

    bool MemoryResource::Decommit(
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

    bool MemoryResource::DecommitAll(
    ) noexcept
    {
        ::BOOL result = ::VirtualFree(
            m_p,
            0,
            MEM_DECOMMIT
        );

        return static_cast<bool>(result);
    }

#elif KLIB_ENV_UNIX
    size_t MemoryResource::s_pageSize = ::sysconf(_SC_PAGESIZE);

    bool MemoryResource::do_free() noexcept
    {
        return ::munmap(m_p, m_regionSize) != EOF;
    }

    void* MemoryResource::do_reserve(
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

    bool MemoryResource::Commit(
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

    bool MemoryResource::Decommit(
        void* targetAddress,
        size_t bytes
    ) noexcept
    {
        // アクセスを禁止し（予約状態に戻す）、物理メモリのヒントも与えますｳﾋｮｯ
        int result1 = ::mprotect(targetAddress, bytes, PROT_NONE);
        int result2 = ::madvise(targetAddress, bytes, MADV_DONTNEED);

        return result1 != EOF && result2 != EOF;
    }

    bool MemoryResource::DecommitAll(
    ) noexcept
    {
        // 同じアドレスに対して PROT_NONE で上書きマッピングを行うｳﾋｮｯ
        return mmap(
            m_p,
            m_regionSize,
            PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
            -1,
            0
        ) != nullptr;
    }
#endif
}