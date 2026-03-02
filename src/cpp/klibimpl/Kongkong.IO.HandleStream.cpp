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

    bool HandleStream::ReadByteUnsafe(
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

    bool HandleStream::ReadUnsafe(
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

    bool HandleStream::WriteUnsafe(
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

    bool HandleStream::WriteByteUnsafe(
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

#endif
}