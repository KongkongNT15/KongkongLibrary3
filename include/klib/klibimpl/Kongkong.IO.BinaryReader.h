#ifndef KLIB_KONGKONG_IO_BINARYREADER_H
#define KLIB_KONGKONG_IO_BINARYREADER_H

#include "base.h"
#include "Kongkong.IO.StreamRWBase.h"

namespace klib::Kongkong::IO
{
    class BinaryReader : public StreamRWBase {
        private:

        [[noreturn]]
        static void do_throwEndOfStream();

        public:

        constexpr BinaryReader(
            Stream& stream
        ) noexcept;

        [[nodiscard]]
        int Read() noexcept;

        template <class T> requires ::std::is_trivial_v<T>
        [[nodiscard]] T ReadData();

        [[nodiscard]]
        bool ReadBool();

        [[nodiscard]]
        byte ReadByte();

        [[nodiscard]]
        short ReadShort();

        [[nodiscard]]
        int ReadInt();

        [[nodiscard]]
        long ReadLong();

        [[nodiscard]]
        long long ReadLLong();
    };
}

namespace klib::Kongkong::IO
{
    constexpr BinaryReader::BinaryReader(
        Stream& stream
    ) noexcept
        : StreamRWBase(&stream)
    {
    }

    int BinaryReader::Read() noexcept
    {
        byte result;

        if (!BaseStream().TryReadByte(result)) return -1;

        return result;
    }

    template <class T> requires ::std::is_trivial_v<T>
    T BinaryReader::ReadData()
    {
        T result;

        auto length = BaseStream().Read(
            sizeof(T),
            &result
        );

        // ここでlengthはゼロではない
        if (length != sizeof(T)) [[unlikely]] {
            do_throwEndOfStream();
        }

        return result;
    }
}

#endif //!KLIB_KONGKONG_IO_BINARYREADER_H