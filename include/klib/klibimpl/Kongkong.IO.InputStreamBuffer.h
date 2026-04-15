#ifndef KLIB_KONGKONG_IO_INPUTSTREAMBUFFER_H
#define KLIB_KONGKONG_IO_INPUTSTREAMBUFFER_H

#include "base.h"
#include "Kongkong.Memory.MemoryPage.h"
#include "Kongkong.IO.Stream.h"

namespace klib::Kongkong::IO
{
    class InputStreamBuffer {
        private:

        Memory::MemoryPage m_page;
        ssize_t m_current;
        ssize_t m_length;

        static uint32_t LoadFromStream(
            IO::Stream& stream,
            ssize_t pageLength,
            void* dest
        );

        public:

        InputStreamBuffer();

        ~InputStreamBuffer();

        [[nodiscard]]
        int Read(
            IO::Stream& stream
        ) noexcept;

        uint32_t Read(
            IO::Stream& stream,
            uint32_t length,
            void* data
        );

        bool TryLoadFromStream(
            IO::Stream& stream
        ) noexcept;

        void LoadFromStream(
            IO::Stream& stream
        ) noexcept;
    };
}

namespace klib::Kongkong::IO
{
    inline uint32_t InputStreamBuffer::LoadFromStream(
        IO::Stream& stream,
        ssize_t pageLength,
        void* dest
    ) noexcept
    {
        return stream.Read(
            Memory::MemoryPageHelper::PageSize() * pageLength,
            dest
        );
    }

    inline InputStreamBuffer::InputStreamBuffer()
        : m_page()
        , m_current(0)
        , m_length(0)
    {
        m_page.AllocUnsafe();
    }

    inline InputStreamBuffer::~InputStreamBuffer()
    {
        m_page.Dispose();
    }

    inline int InputStreamBuffer::Read(
        IO::Stream& stream
    ) noexcept
    {
        int result;

        if (m_current == m_length) {
            if (!TryLoadFromStream(stream)) return -1;
            if (m_length == 0) return -1;
        }

        result = static_cast<byte*>(m_page.Data())[m_current];
        ++m_current;

        return result;
    }

    inline bool InputStreamBuffer::TryLoadFromStream(
        IO::Stream& stream
    ) noexcept
    {
        auto result = stream.TryRead(
            Memory::MemoryPageHelper::PageSize(),
            m_page.Data()
        );

        if (!result.Success) return false;
        
        m_length = result.BytesTransferred;
        m_current = 0;

        return true;
    }

    inline void InputStreamBuffer::LoadFromStream(
        IO::Stream& stream
    ) noexcept
    {
        auto result = stream.Read(
            Memory::MemoryPageHelper::PageSize(),
            m_page.Data()
        );
        
        m_length = result;
        m_current = 0;
    }
}

#endif //!KLIB_KONGKONG_IO_INPUTSTREAMBUFFER_H