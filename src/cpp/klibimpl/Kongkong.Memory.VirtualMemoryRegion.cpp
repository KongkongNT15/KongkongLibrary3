namespace klib::Kongkong::Memory
{
    bool VirtualMemoryRegion::do_resizeUnsafe(
        ssize_t length
    ) noexcept
    {
#if KLIB_HAS_CPP23
        [[assume(length >= 1)]];
#endif

        ssize_t pageSize = static_cast<ssize_t>(MemoryResource::PageSize());
        ssize_t newPageCount = (length - 1) / pageSize + 1;
        ssize_t currentPageCount;

        if (m_length == 0) {
            currentPageCount = 0;
        }
        else {
            currentPageCount = (m_length - 1) / pageSize + 1;
        }

        if (newPageCount == currentPageCount) {
            return true;
        }
        
        // サイズが小さくなるぅ
        if (newPageCount < currentPageCount) {
            byte* begin = static_cast<byte*>(Data());
            byte* decommiBegin = begin + newPageCount * pageSize;
            size_t decommitSize = static_cast<size_t>(
                (currentPageCount - newPageCount) * pageSize
            );

            return m_resource.Decommit(
                decommiBegin,
                decommitSize
            );
        }
        // サイズが大きすぎるぅ
        else if (length > RegionSize()) [[unlikely]] {
            return false;
        }
        // サイズが大きくなるぅ
        else {
            byte* begin = static_cast<byte*>(Data());
            byte* commiBegin = begin + currentPageCount * pageSize;
            size_t commitSize = static_cast<size_t>(
                (newPageCount - currentPageCount) * pageSize
            );

            return m_resource.Decommit(
                commiBegin,
                commitSize
            );
        }
    }
}