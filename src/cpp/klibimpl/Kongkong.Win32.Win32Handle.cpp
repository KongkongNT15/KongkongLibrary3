namespace klib::Kongkong::Win32
{
    ::HANDLE Win32Handle::DuplicateRawHandleUnsafe(
        ::HANDLE rawHandle
    ) noexcept
    {
        ::HANDLE handle;

        ::DuplicateHandle(
            ::GetCurrentProcess(),
            rawHandle,
            ::GetCurrentProcess(),
            &handle,
            0,
            FALSE,
            DUPLICATE_SAME_ACCESS
        );

        return handle;
    }

    Win32Handle::Win32Handle(
        Win32Handle const& other
    ) noexcept
        : m_rawHandle(
            other.m_rawHandle == INVALID_HANDLE_VALUE ?
            INVALID_HANDLE_VALUE : DuplicateRawHandleUnsafe(other.m_rawHandle)
        )
    {
    }

    Win32Handle& Win32Handle::operator=(
        Win32Handle const& other
    ) noexcept
    {
        if (&other == this) [[unlikely]] return *this;

        if (other.m_rawHandle == INVALID_HANDLE_VALUE) {
            Detach();
        }
        else {
            if (m_rawHandle != INVALID_HANDLE_VALUE) ::CloseHandle(m_rawHandle);

            m_rawHandle = DuplicateRawHandleUnsafe(other.m_rawHandle);
        }

        return *this;
    }
}