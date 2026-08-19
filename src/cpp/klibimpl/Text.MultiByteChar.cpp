namespace klib::Text
{
    void MultiByteChar::WriteTo(
        ::std::ostream& out
    ) const noexcept
    {
        out << m_mbc;
    }
}