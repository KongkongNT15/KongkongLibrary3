#ifndef KLIB_KONGKONG_IO_MEMORYSTREAM_H
#define KLIB_KONGKONG_IO_MEMORYSTREAM_H

#include "base.h"
#include "Kongkong.Containers.Primitives.ChainLink.h"
#include "Kongkong.IO.Stream.h"

namespace klib::Kongkong::IO
{
    class MemoryStream : public Stream {
        private:
        Containers::Primitives::ChainLink<byte>* m_pChain;
        ssize_t m_length;

        public:

        [[nodiscard]]
        constexpr bool CanRead() const noexcept override;

        [[nodiscard]]
        constexpr bool CanSeek() const noexcept override;

        [[nodiscard]]
        constexpr bool CanWrite() const noexcept override;

        constexpr bool Close() noexcept override;

        constexpr bool Flush() noexcept override;

        [[nodiscard]]
        constexpr bool IsOpen() const noexcept override;

        constexpr bool TryGetLength(
            int64_t& dest
        ) const noexcept override;

        StreamRWResult TryRead(
            uint32_t length,
            void* buffer
        ) noexcept override;

        bool TryReadByte(
            byte& result
        ) noexcept override;

        bool TrySeek(
            int64_t offset,
            SeekOrigin origin,
            int64_t& result
        ) override;

        StreamRWResult TryWrite(
            uint32_t length,
            const void* buffer
        ) noexcept override;

        bool TryWriteByte(
            byte value
        ) noexcept override;
    };
}

#endif //!KLIB_KONGKONG_IO_MEMORYSTREAM_H