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

    bool MemoryResource::ReserveUnsafe(
        size_t minBytes
    ) noexcept
    {
        void* p = ::VirtualAlloc(
            nullptr,
            minBytes,
            MEM_RESERVE,
            PAGE_READWRITE
        );

        if (!p) return false;

        m_p = p;

        if (minBytes % s_pageSize == 0) {
            m_regionSize = minBytes;
        }
        else {
            m_regionSize = (minBytes / s_pageSize + 1) * s_pageSize;
        }
    }

    

#elif KLIB_ENV_UNIX

#endif
}