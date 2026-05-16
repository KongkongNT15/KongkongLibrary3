namespace klib::CStd
{
    bool CFileStream::IsOpen() const noexcept
    {
        return m_fp != nullptr;
    }

    bool CFileStream::TryReadByte(
        byte& result
    ) noexcept
    {
        int v = ::fgetc(m_fp);

        result = static_cast<byte>(v);

        return v != EOF;
    }

    bool CFileStream::TrySeek(
        int64_t offset,
        IO::SeekOrigin origin,
        int64_t& result
    )
    {
        return ::fseek(
            m_fp,
            static_cast<long>(offset),
            static_cast<int>(origin)
        ) != EOF;
    }

    IO::StreamRWResult CFileStream::TryWrite(
        uint32_t length,
        const void* buffer
    ) noexcept
    {
        size_t result = ::fwrite(buffer, 1, length, m_fp);

        return {
            static_cast<uint32_t>(result),
            result != EOF
        };
    }

    bool CFileStream::TryWriteByte(
        byte value
    ) noexcept
    {
        return ::fputc(value, m_fp) != EOF;
    }
}