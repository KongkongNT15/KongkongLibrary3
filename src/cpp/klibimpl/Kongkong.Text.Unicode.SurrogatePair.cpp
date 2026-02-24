namespace klib::Kongkong::Text::Unicode
{
    void SurrogatePair::s_checkPair(
        char16_t highSurrogate,
        char16_t lowSurrogate
    )
    {
        if (!UnicodeTraits::IsHighSurrogate(highSurrogate)) [[unlikely]] {
            throw ArgumentOutOfRangeException(u"high サロゲートが無効です（0xD800～0xDBFF の範囲外）");
        }
        if (!UnicodeTraits::IsLowSurrogate(lowSurrogate)) [[unlikely]] {
            throw ArgumentOutOfRangeException(u"low サロゲートが無効です（0xDC00～0xDFFF の範囲外）");
        }
    }
}