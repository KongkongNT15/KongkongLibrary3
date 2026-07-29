namespace klib::Threading
{
#if KLIB_ENV_WINDOWS

    ::DWORD __stdcall Thread::EntryPoint(
        void* args
    )
    {
        auto p = static_cast<Functional::Function<void()>*>(args);

        p->operator()();

        return 0;
    }

    Thread::Thread(
        Functional::Function<void()>&& entryPoint,
        size_t stackSize
    )
        : m_entryPoint(::std::move(entryPoint))
    {
        ::HANDLE thread = ::CreateThread(
            nullptr,
            stackSize,
            EntryPoint,
            &m_entryPoint,
            STACK_SIZE_PARAM_IS_A_RESERVATION,
            nullptr
        );

        if (thread == INVALID_HANDLE_VALUE) [[unlikely]] {
            throw MemoryAllocationException();
        }

        m_thread.AttachUnsafe(thread);
    }

    Thread::Thread(
        Functional::Function<void()>&& entryPoint
    )
        : m_entryPoint(::std::move(entryPoint))
    {
        ::HANDLE thread = ::CreateThread(
            nullptr,
            0,
            EntryPoint,
            &m_entryPoint,
            0,
            nullptr
        );

        if (thread == INVALID_HANDLE_VALUE) [[unlikely]] {
            throw MemoryAllocationException();
        }

        m_thread.AttachUnsafe(thread);
    }

    void Thread::Join(
        uint32_t milliSeconds
    )
    {
        ::DWORD result = ::WaitForSingleObject(m_thread.RawHandle(), milliSeconds);

        if (result == WAIT_FAILED) [[unlikely]] throw ThreadStateException(u"開始していないスレッドを待機しようとしました");
    }

#elif KLIB_ENV_UNIX

#endif
}