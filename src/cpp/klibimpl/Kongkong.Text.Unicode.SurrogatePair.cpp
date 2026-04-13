namespace klib::Kongkong::Text::Unicode
{
    void SurrogatePair::do_throwHighSurrogateError()
    {
        throw ArgumentOutOfRangeException(u"high サロゲートが無効です（0xD800～0xDBFF の範囲外）");
    }

    void SurrogatePair::do_throwLowSurrogateError()
    {
        throw ArgumentOutOfRangeException(u"low サロゲートが無効です（0xDC00～0xDFFF の範囲外）");
    }
}