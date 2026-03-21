namespace klib::Kongkong::IO
{
#if KLIB_ENV_WINDOWS
    bool HandleStream::Close() noexcept
    {
        return m_handle.Detach();
    }

    bool HandleStream::Flush() noexcept
    {
        return static_cast<bool>(
            ::FlushFileBuffers(m_handle.RawHandle())
        );
    }

    bool HandleStream::IsOpen() const noexcept
    {
        return m_handle != nullptr;
    }

    bool HandleStream::TryReadByte(
        byte& result
    ) noexcept
    {
        return static_cast<bool>(
            ::ReadFile(
                m_handle.RawHandle(),
                &result,
                1,
                nullptr,
                nullptr
            )
        );
    }

    bool HandleStream::TryRead(
        uint32_t length,
        void* buffer
    ) noexcept
    {
        return static_cast<bool>(
            ::ReadFile(
                m_handle.RawHandle(),
                buffer,
                length,
                nullptr,
                nullptr
            )
        );
    }

    bool HandleStream::TryWrite(
        uint32_t length,
        const void* buffer
    ) noexcept
    {
        return static_cast<bool>(
            ::WriteFile(
                m_handle.RawHandle(),
                buffer,
                length,
                nullptr,
                nullptr
            )
        );
    }

    bool HandleStream::TryWriteByte(
        byte value
    ) noexcept
    {
        return static_cast<bool>(
            ::WriteFile(
                m_handle.RawHandle(),
                &value,
                1,
                nullptr,
                nullptr
            )
        );
    }

#elif KLIB_ENV_UNIX
    bool HandleStream::Close() noexcept
    {
        return ::close(m_fd) != EOF;
    }

    bool HandleStream::Flush() noexcept
    {
        return ::fsync(m_fd) != EOF;
    }

    bool HandleStream::IsOpen() const noexcept
    {
        return m_fd != EOF;
    }

    bool HandleStream::TryReadByte(
        byte& result
    ) noexcept
    {
        return ::read(
            m_fd,
            &result,
            1
        ) != EOF;
    }

    bool HandleStream::TryRead(
        uint32_t length,
        void* buffer
    ) noexcept
    {
        return ::read(
            m_fd,
            buffer,
            length
        ) != EOF;
    }

    bool HandleStream::TryWrite(
        uint32_t length,
        const void* buffer
    ) noexcept
    {
        return ::write(
            m_fd,
            buffer,
            length
        ) != EOF;
    }

    bool HandleStream::TryWriteByte(
        byte value
    ) noexcept
    {
        return ::write(
            m_fd,
            &value,
            1
        ) != EOF;
    }
#endif
}