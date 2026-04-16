#ifndef KLIB_KONGKONG_IO_STREAM_H
#define KLIB_KONGKONG_IO_STREAM_H

#include "base.h"
#include "Kongkong.IO.StreamRWResult.h"

namespace klib::Kongkong::IO
{
    class Stream {
        private:

        void CheckCanRead() const;
        void CheckCanSeek() const;
        void CheckCanWrite() const;
        void CheckIsOpen() const;

        [[noreturn]]
        static void ThrowReadError();
        
        [[noreturn]]
        static void ThrowWriteError();

        [[noreturn]]
        static void ThrowIOError();
        
        protected:

        Stream() = default;

        Stream(
            Stream const&
        ) = default;

        Stream(
            Stream&&
        ) = default;

        Stream& operator=(
            Stream const&
        ) = default;

        Stream& operator=(
            Stream&&
        ) = default;

        public:

        virtual ~Stream();

        [[nodiscard]]
        virtual bool CanRead() const noexcept = 0;

        [[nodiscard]]
        virtual bool CanSeek() const noexcept = 0;

        [[nodiscard]]
        virtual bool CanWrite() const noexcept = 0;

        virtual bool Close() noexcept = 0;

        virtual bool Flush() noexcept = 0;

        [[nodiscard]]
        int64_t Length() const;

        [[nodiscard]]
        virtual bool IsOpen() const noexcept = 0;

        uint32_t Read(
            uint32_t length,
            void* buffer
        );

        virtual int64_t Seek(
            int64_t offset,
            SeekOrigin origin
        ) = 0;

        virtual bool TryGetLength(
            int64_t& dest
        ) const noexcept = 0;

        virtual StreamRWResult TryRead(
            uint32_t length,
            void* buffer
        ) noexcept;

        [[nodiscard]]
        byte ReadByte();

        virtual bool TryReadByte(
            byte& result
        ) noexcept = 0;
        
        uint32_t Write(
            uint32_t length,
            const void* buffer
        );

        virtual StreamRWResult TryWrite(
            uint32_t length,
            const void* buffer
        ) noexcept;

        void WriteByte(
            byte value
        );

        virtual bool TryWriteByte(
            byte value
        ) noexcept = 0;
    };
}

namespace klib::Kongkong::IO
{
    inline Stream::~Stream()
    {
        Close();
    }

    inline int64_t Stream::Length() const
    {
        int64_t result;

        if (!TryGetLength(result)) [[unlikely]] {
            CheckCanSeek();
            ThrowIOError();
        }

        return result;
    }

    inline uint32_t Stream::Read(
        uint32_t length,
        void* buffer
    )
    {
        auto result = TryRead(length, buffer);

        if (!result.Success) [[unlikely]] {
            CheckCanRead();
            ThrowReadError();
        }

        return result.BytesTransferred;
    }

    inline StreamRWResult Stream::TryRead(
        uint32_t length,
        void* buffer
    ) noexcept
    {
        byte* itr = static_cast<byte*>(buffer);
        byte* end = itr + length;

        while (itr != end) {
            if (!TryReadByte(*itr)) [[unlikely]] {
                uint32_t readLength = static_cast<uint32_t>(
                    itr - static_cast<byte*>(buffer)
                );
                return StreamRWResult{ readLength, readLength != 0 };
            }
            ++itr;
        }

        return StreamRWResult{ length, true };
    }

    inline byte Stream::ReadByte()
    {
        byte result;

        if (!TryReadByte(result)) [[unlikely]] {
            CheckCanRead();
            ThrowReadError();
        }

        return result;
    }

    inline void Stream::WriteByte(
        byte value
    )
    {
        if (!TryWriteByte(value)) [[unlikely]] {
            CheckCanWrite();
            ThrowWriteError();
        }
    }

    inline uint32_t Stream::Write(
        uint32_t length,
        const void* buffer
    )
    {
        auto result = TryWrite(length, buffer);

        if (!result.Success) [[unlikely]] {
            CheckCanWrite();
            ThrowWriteError();
        }

        return result.BytesTransferred;
    }

    inline StreamRWResult Stream::TryWrite(
        uint32_t length,
        const void* buffer
    ) noexcept
    {
        auto itr = static_cast<const byte*>(buffer);
        auto end = itr + length;

        while (itr != end) {
            if (!TryWriteByte(*itr)) [[unlikely]] {
                uint32_t writeLength = static_cast<uint32_t>(
                    itr - static_cast<const byte*>(buffer)
                );
                return StreamRWResult{ writeLength, writeLength != 0 };
            }
            ++itr;
        }
        
        return StreamRWResult{ length, true };
    }
}

#endif //!KLIB_KONGKONG_IO_STREAM_H