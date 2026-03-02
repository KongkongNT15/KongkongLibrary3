namespace klib::Kongkong::Threading::Async
{
    void AwaiterBase::Wait() const noexcept
    {
        using namespace ::std::chrono;

        while (m_status == TaskStatus::Waiting || m_status == TaskStatus::Running) {
            ::std::this_thread::sleep_for(1ms);
        }
        
    }
}