#define KLIB_OBJC_RAPOINTER (static_cast<::NSThread*>(m_thread.GetRawPointer()))

namespace klib::Kongkong::Threading
{
    Thread Thread::Current() noexcept
    {
        ::NSThread* thread = [::NSThread currentThread];

        return Thread(
            AppleDevice::ObjCHandle(thread)
        );
    }

    void Thread::Start()
    {
        [KLIB_OBJC_RAPOINTER start];
    }
}

#undef KLIB_OBJC_RAPOINTER 