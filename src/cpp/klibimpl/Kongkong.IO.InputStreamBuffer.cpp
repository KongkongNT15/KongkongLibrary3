namespace klib::Kongkong::IO
{
    uint32_t InputStreamBuffer::Read(
        IO::Stream& stream,
        uint32_t length,
        void* data
    )
    {
        ssize_t nokori = length;
        ssize_t pageSize = static_cast<ssize_t>(Memory::MemoryPageHelper::PageSize());
        byte* target = static_cast<byte*>(data);

        if (m_current != m_length) {
            ssize_t bufferedLength = m_length - m_current;

            // バッファで足りるときぃ
            if (bufferedLength >= nokori) {
                ::memcpy(
                    target,
                    static_cast<byte*>(m_page.Data()) + m_current,
                    nokori
                );

                m_current += nokori;

                return length;
            }
            //足りないときぃ
            else {
                ::memcpy(
                    target,
                    static_cast<byte*>(m_page.Data()) + m_current,
                    bufferedLength
                );

                m_length = 0;
                nokori -= bufferedLength;
                target += bufferedLength;
            }
        }

        ssize_t nokoriPages = nokori / Memory::MemoryPageHelper::PageSize();
        ssize_t amari = nokori % Memory::MemoryPageHelper::PageSize();

        if (nokoriPages != 0) {
            ssize_t written = LoadFromStream(
                stream,
                nokoriPages,
                target
            );

            target += written;

            // ストリームの末尾まで達したお
            if (written != nokoriPages * Memory::MemoryPageHelper::PageSize()) {
                return static_cast<uint32_t>(
                    target - static_cast<byte*>(data)
                );
            }
        }

        LoadFromStream(stream);

        if (m_length >= amari) {

            ::memcpy(
                target,
                m_page.Data(),
                amari
            );

            m_current = amari;

            return length;
        }
        else {
            ::memcpy(
                target,
                m_page.Data(),
                m_length
            );

            m_current = m_length;

            return static_cast<uint32_t>(
                target - static_cast<byte*>(data) + m_length
            );
        }
        
    }
}