namespace klib::Text::Unicode
{
    void Utf8Char::do_throw()
    {
        throw ArgumentOutOfRangeException(u"不正なコードポイントです");
    }

    void Utf8Char::WriteTo(
        ::std::ostream& out
    )
    {
#if KLIB_ENV_WINDOWS
        KLIB_NOT_IMPLEMENTED;
#elif KLIB_ENV_UNIX
        out.write(
            reinterpret_cast<const char*>(m_char),
            m_length
        );
    #else
        KLIB_NOT_IMPLEMENTED;
    #endif
    }
}