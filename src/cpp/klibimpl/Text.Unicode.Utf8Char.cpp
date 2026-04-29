namespace klib::Text::Unicode
{
    void Utf8Char::do_throw()
    {
        throw ArgumentOutOfRangeException(u"不正なコードポイントです");
    }
}