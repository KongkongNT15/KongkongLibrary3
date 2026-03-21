namespace klib::Kongkong::IO
{
    void Stream::CheckIsOpen() const
    {
        if (!IsOpen()) [[unlikely]] throw NotSupportedException(u"ストリームが閉じられています。");
    }

    void Stream::CheckCanRead() const
    {
        CheckIsOpen();
        if (!CanRead()) [[unlikely]] throw NotSupportedException(u"このストリームは読み込みをサポートしていません。");
    }

    void Stream::CheckCanWrite() const
    {
        CheckIsOpen();
        if (!CanWrite()) [[unlikely]] throw NotSupportedException(u"このストリームは書き込みをサポートしていません。");
    }

    void Stream::Read(
        uint32_t length,
        void* buffer
    )
    {
        if (!TryRead(length, buffer)) [[unliekly]] {
            CheckCanRead();
            ThrowReadError();
        }
    }

    bool Stream::TryRead(
        uint32_t length,
        void* buffer
    ) noexcept
    {
        byte* itr = static_cast<byte*>(buffer);
        byte* end = itr + length;

        while (itr != end) {
            if (!TryReadByte(*itr)) [[unlikely]] return false;
            ++itr;
        }

        return true;
    }

    byte Stream::ReadByte()
    {
        byte result;

        if (!TryReadByte(result)) [[unlikely]] {
            CheckCanRead();
            ThrowReadError();
        }

        return result;
    }

    void Stream::ThrowReadError()
    {
        throw IOException(u"データの読み込みに失敗しました。");
    }

    void Stream::ThrowWriteError()
    {
        throw IOException(u"データの書き込みに失敗しました。");
    }

    void Stream::WriteByte(
        byte value
    )
    {
        if (!TryWriteByte(value)) [[unlikely]] {
            CheckCanWrite();
            ThrowWriteError();
        }
    }

    void Stream::Write(
        uint32_t length,
        const void* buffer
    )
    {
        if (!TryWrite(length, buffer)) [[unlikely]] {
            CheckCanWrite();
            ThrowWriteError();
        }
    }

    bool Stream::TryWrite(
        uint32_t length,
        const void* buffer
    ) noexcept
    {
        auto itr = static_cast<const byte*>(buffer);
        auto end = itr + length;

        while (itr != end) {
            if (!TryWriteByte(*itr)) [[unlikely]] return false;
            ++itr;
        }
        
        return true;
    }
}