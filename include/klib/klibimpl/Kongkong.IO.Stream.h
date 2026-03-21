#ifndef KLIB_KONGKONG_IO_STREAM_H
#define KLIB_KONGKONG_IO_STREAM_H

#include "base.h"

namespace klib::Kongkong::IO
{
    class Stream {
        private:

        void CheckCanRead() const;
        void CheckCanWrite() const;
        void CheckIsOpen() const;

        [[noreturn]]
        static void ThrowReadError();
        
        [[noreturn]]
        static void ThrowWriteError();
        
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
        virtual bool CanWrite() const noexcept = 0;

        virtual bool Close() noexcept = 0;

        virtual bool Flush() noexcept = 0;

        [[nodiscard]]
        virtual bool IsOpen() const noexcept = 0;

        void Read(
            uint32_t length,
            void* buffer
        );

        virtual bool TryRead(
            uint32_t length,
            void* buffer
        ) noexcept;

        [[nodiscard]]
        byte ReadByte();

        virtual bool TryReadByte(
            byte& result
        ) noexcept = 0;
        
        void Write(
            uint32_t length,
            const void* buffer
        );

        virtual bool TryWrite(
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
}

#endif //!KLIB_KONGKONG_IO_STREAM_H