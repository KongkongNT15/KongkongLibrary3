namespace klib::Kongkong::Threading::Async
{
    AsyncAction AsyncAction::DelayAsync(
        uint32_t milliSeconds
    ) noexcept
    {
        return ThreadPool::RunAsync(
            [=] () { Thread::Sleep(milliSeconds); }
        );
    }
    
}