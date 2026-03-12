namespace klib::Kongkong::Memory
{
    bool MemoryBlock::ResizeUnsafe(
        ssize_t length
    ) noexcept
    {
        if (length == 0) {
            return m_resource.DecommitAll();
        }

        ssize_t pageSize = static_cast<ssize_t>(MemoryResource::PageSize());
        ssize_t currentPageCount = (m_length - 1) / pageSize + 1;
        ssize_t newPageCount = (length - 1) / pageSize + 1;

        if (newPageCount == currentPageCount) {
            m_length = length;
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