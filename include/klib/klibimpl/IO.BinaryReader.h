#ifndef KLIB_IO_BINARYREADER_H
#define KLIB_IO_BINARYREADER_H

#include "base.h"
#include "IO.StreamRWBase.h"

namespace klib::IO
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

namespace klib::IO
{
    constexpr BinaryReader::BinaryReader(
        Stream& stream
    ) noexcept
        : StreamRWBase(&stream)
    {
    }

    inline int BinaryReader::Read() noexcept
    {
        byte result;

        if (!BaseStream().TryReadByte(result)) return -1;

        return result;
    }

    inline bool BinaryReader::ReadBool()
    {
        return ReadData<bool>();
    }

    inline byte BinaryReader::ReadByte()
    {
        return ReadData<byte>();
    }

    inline short BinaryReader::ReadShort()
    {
        return ReadData<short>();
    }

    inline int BinaryReader::ReadInt()
    {
        return ReadData<int>();
    }

    inline long BinaryReader::ReadLong()
    {
        return ReadData<long>();
    }

    inline long long BinaryReader::ReadLLong()
    {
        return ReadData<long long>();
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

#endif //!KLIB_IO_BINARYREADER_H
