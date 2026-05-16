#ifndef KLIB_CSTD_CFILESTREAM_H
#define KLIB_CSTD_CFILESTREAM_H

#include "base.h"
#include "IO.Stream.h"

#include <stdio.h>

namespace klib::CStd
{
    class CFileStream : IO::Stream {
        private:

        ::FILE* m_fp;

        public:

        [[nodiscard]]
        constexpr bool IsOpen() const noexcept override;

        bool TryReadByte(
            byte& result
        ) noexcept override;

        bool TrySeek(
            int64_t offset,
            IO::SeekOrigin origin,
            int64_t& result
        ) override;

        IO::StreamRWResult TryWrite(
            uint32_t length,
            const void* buffer
        ) noexcept override;

        bool TryWriteByte(
            byte value
        ) noexcept override;


    };
}

#endif //!KLIB_CSTD_CFILESTREAM_H