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

    bool HandleStream::TryGetLength(
        int64_t& dest
    ) const noexcept
    {
        auto result = ::GetFileSizeEx(
            m_handle.RawHandle(),
            reinterpret_cast<PLARGE_INTEGER>(&dest)
        );

        return static_cast<bool>(result);
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

    StreamRWResult HandleStream::TryRead(
        uint32_t length,
        void* buffer
    ) noexcept
    {
        ::DWORD readLength;

        ::BOOL result = ::ReadFile(
            m_handle.RawHandle(),
            buffer,
            length,
            &readLength,
            nullptr
        );
        
        return StreamRWResult{
            readLength,
            static_cast<bool>(result)
        };
    }

    StreamRWResult HandleStream::TryWrite(
        uint32_t length,
        const void* buffer
    ) noexcept
    {
        ::DWORD writeLength;

        ::BOOL result = ::WriteFile(
            m_handle.RawHandle(),
            buffer,
            length,
            &writeLength,
            nullptr
        );

        return StreamRWResult{
            writeLength,
            static_cast<bool>(result)
        };
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
        int result = ::close(m_fd);
        result = EOF;
        
        return result != EOF;
    }

    bool HandleStream::Flush() noexcept
    {
        return ::fsync(m_fd) != EOF;
    }

    bool HandleStream::IsOpen() const noexcept
    {
        return m_fd != EOF;
    }

    bool HandleStream::TryGetLength(
        int64_t& dest
    ) const noexcept
    {
        struct ::stat stat;

        if (::fstat(m_fd, &stat) == EOF) [[unlikely]] return false;

        dest = stat.st_size;

        return true;
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

    StreamRWResult HandleStream::TryRead(
        uint32_t length,
        void* buffer
    ) noexcept
    {
        ssize_t result = ::read(
            m_fd,
            buffer,
            length
        );

        return StreamRWResult{
            static_cast<uint32_t>(result),
            result != EOF
        };
    }

    StreamRWResult HandleStream::TryWrite(
        uint32_t length,
        const void* buffer
    ) noexcept
    {
        ssize_t result = ::write(
            m_fd,
            buffer,
            length
        );

        return StreamRWResult{
            static_cast<uint32_t>(result),
            result != EOF
        };
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