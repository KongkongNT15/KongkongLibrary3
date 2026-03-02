#ifndef KLIB_KONGKONG_IO_HANDLESTREAM_H
#define KLIB_KONGKONG_IO_HANDLESTREAM_H

#include "base.h"
#include "Kongkong.IO.Stream.h"

#if KLIB_ENV_WINDOWS
    #include "Kongkong.Win32.Win32Handle.h"
#endif

namespace klib::Kongkong::IO
{
    class HandleStream : public Stream {
        protected:

        Win32::Win32Handle m_handle;

        public:

        bool Close() noexcept override;

        bool Flush() noexcept override;

        bool IsOpen() const noexcept override;

        bool ReadByteUnsafe(
            byte& result
        ) noexcept override;

        bool ReadUnsafe(
            uint32_t length,
            void* buffer
        ) noexcept override;
        
        bool WriteUnsafe(
            uint32_t length,
            const void* buffer
        ) noexcept override;

        bool WriteByteUnsafe(
            byte value
        ) noexcept override;
    };
}

#endif //!KLIB_KONGKONG_IO_HANDLESTREAM_H