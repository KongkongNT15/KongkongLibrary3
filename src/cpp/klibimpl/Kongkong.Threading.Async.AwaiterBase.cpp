namespace klib::Kongkong::Threading::Async
{
    void AwaiterBase::do_throw(
        TaskStatus status
    )
    {
        switch (status) {
            case TaskStatus::Faulted: [[unlikely]]
                throw InvalidOperationException(u"コルーチンが失敗しました");

            default: [[likely]] break;
        }
    }

    void AwaiterBase::Wait() const noexcept
    {
        using namespace ::std::chrono;

        while (m_status == TaskStatus::Waiting || m_status == TaskStatus::Running) {
            ::std::this_thread::sleep_for(1ms);
        }
        
    }
}