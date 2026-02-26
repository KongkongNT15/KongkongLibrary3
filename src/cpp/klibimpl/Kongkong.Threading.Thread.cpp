namespace klib::Kongkong::Threading
{
#if KLIB_ENV_WINDOWS
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