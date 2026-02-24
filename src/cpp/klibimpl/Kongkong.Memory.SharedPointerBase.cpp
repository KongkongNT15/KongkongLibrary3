namespace klib::Kongkong::Memory
{
    SharedPointerBase::SharedPointerBase(
        void(*fDelete)(void*)
    )
        : m_pData(KLIB_NEW s_data(fDelete))
    {
        MemoryAllocationException::CheckNull(m_pData);
    }
}