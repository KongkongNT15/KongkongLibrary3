namespace klib::Kongkong::Threading
{
#if KLIB_COMPILER_APPLE_CLANG
    ::dispatch_queue_t ThreadPool::s_queue = ::dispatch_get_global_queue(
        DISPATCH_QUEUE_PRIORITY_DEFAULT,
        0
    );
#endif
}