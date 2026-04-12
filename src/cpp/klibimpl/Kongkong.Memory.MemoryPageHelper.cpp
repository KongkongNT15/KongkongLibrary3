namespace klib::Kongkong::Memory
{
#if KLIB_ENV_WINDOWS
    size_t MemoryPageHelper::s_pageSize = [] () {
        ::SYSTEM_INFO si;
        ::GetSystemInfo(&si);
        return si.dwPageSize;
    }();
#elif KLIB_ENV_UNIX
    size_t MemoryPageHelper::s_pageSize = ::sysconf(_SC_PAGESIZE);
#endif
}