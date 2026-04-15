#ifndef KLIB_KONGKONG_IO_OUTPUTSTREAMBUFFER_H
#define KLIB_KONGKONG_IO_OUTPUTSTREAMBUFFER_H

#include "base.h"
#include "Kongkong.Memory.MemoryPage.h"
#include "Kongkong.IO.Stream.h"

namespace klib::Kongkong::IO
{
    class OutputStreamBuffer {
        private:

        Memory::MemoryPage m_page;
        uint32_t m_length;

        public:

        OutputStreamBuffer();

        ~OutputStreamBuffer();

        [[nodiscard]]
        uint32_t Capacity() const noexcept;

        void Flush(
            Stream& stream
        );

        void Write(
            Stream& stream,
            byte value
        );

        void Write(
            Stream& stream,
            uint32_t length,
            const void* source
        );
    };
}

namespace klib::Kongkong::IO
{
    inline OutputStreamBuffer::OutputStreamBuffer()
        : m_page()
        , m_length(0)
    {
        m_page.AllocUnsafe();
    }

    inline OutputStreamBuffer::~OutputStreamBuffer()
    {
        m_page.Dispose();
    }

    inline uint32_t OutputStreamBuffer::Capacity() const noexcept
    {
        return static_cast<uint32_t>(
            Memory::MemoryPageHelper::PageSize()
        );
    }

    void OutputStreamBuffer::Flush(
        Stream& stream
    )
    {
        if (m_length != 0) [[likely]] {
            stream.Write(
                m_length,
                m_page.Data()
            );

            m_length = 0;
        }
    }

    inline void OutputStreamBuffer::Write(
        Stream& stream,
        byte value
    )
    {
        if (m_length == Capacity()) {
            // ここでm_length = 0になるお
            Flush(stream);
        }

        static_cast<byte*>(m_page.Data())[m_length] = value;

        ++m_length;
    }

    inline void OutputStreamBuffer::Write(
        Stream& stream,
        uint32_t length,
        const void* source
    )
    {
        const byte* target = static_cast<const byte*>(source);
        uint32_t nokori = length;

        if (nokori + m_length > Capacity()) {
            nokori = length - m_length;
            target += m_length;
            Flush(stream);

            if (nokori > Capacity()) {
                stream.Write(
                    nokori,
                    target
                );

                return;
            }
              
        }

        // ここでnokori <= Capacity()
        //      nokori + m_length <= Capacity()

        ::memcpy(
            static_cast<byte*>(m_page.Data()) + m_length,
            target,
            nokori
        );

        m_length += nokori;
    }
}

#endif //!KLIB_KONGKONG_IO_OUTPUTSTREAMBUFFER_H