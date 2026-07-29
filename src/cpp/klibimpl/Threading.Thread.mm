#define KLIB_OBJC_RAPOINTER (static_cast<::NSThread*>(m_thread.GetRawPointer()))

namespace klib::Threading
{
    Thread Thread::Current() noexcept
    {
        ::NSThread* thread = [::NSThread currentThread];

        return Thread(
            AppleDevice::ObjCHandle(thread)
        );
    }

    Thread::Thread(
        void(^f)()
    )
        : m_thread([[::NSThread alloc] initWithBlock:f])
    {
        [KLIB_OBJC_RAPOINTER start];
    }

    Thread::Thread(
        void(^f)(),
        size_t stackSize
    )
        : m_thread([[::NSThread alloc] initWithBlock:f])
    {
        KLIB_OBJC_RAPOINTER.stackSize = stackSize;
        [KLIB_OBJC_RAPOINTER start];
    }
    
}

#undef KLIB_OBJC_RAPOINTER 