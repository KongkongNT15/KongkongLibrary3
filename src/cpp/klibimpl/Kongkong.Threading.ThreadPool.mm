namespace klib::Kongkong::Threading
{
    ::dispatch_queue_t ThreadPool::s_queue = ::dispatch_get_global_queue(
        DISPATCH_QUEUE_PRIORITY_DEFAULT,
        0
    );
}