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

    void Stream::CheckCanSeek() const
    {
        CheckIsOpen();
        if (!CanSeek()) [[unlikely]] throw NotSupportedException(u"このストリームの長さを取得することはできません。");
    }

    void Stream::CheckCanWrite() const
    {
        CheckIsOpen();
        if (!CanWrite()) [[unlikely]] throw NotSupportedException(u"このストリームは書き込みをサポートしていません。");
    }

    void Stream::ThrowIOError()
    {
        throw IOException(u"ストリームの操作に失敗しました。");
    }

    void Stream::ThrowReadError()
    {
        throw IOException(u"データの読み込みに失敗しました。");
    }

    void Stream::ThrowWriteError()
    {
        throw IOException(u"データの書き込みに失敗しました。");
    }
    
}