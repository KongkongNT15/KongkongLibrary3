#ifndef KLIB_KONGKONG_BITS_BITSETHELPER_H
#define KLIB_KONGKONG_BITS_BITSETHELPER_H

#include "base.h"
#include "Kongkong.Numerics.Int.h"

namespace klib::Kongkong::Bits
{
    class BitsetHelper {
        private:
        public:

        KLIB_STATIC_CLASS(BitsetHelper);

        static void ReadUnsafe(
            ::std::nullptr_t,
            ssize_t
        ) = delete;

        static constexpr bool ReadUnsafe(
            const int* p,
            ssize_t index
        ) noexcept;

        static constexpr bool ReadUnsafe(
            int p,
            int indexBit
        ) noexcept;

        static void WriteUnsafe(
            ::std::nullptr_t,
            ssize_t,
            bool
        ) = delete;

        static constexpr void WriteUnsafe(
            int* p,
            ssize_t index,
            bool value
        ) noexcept;

        static constexpr void WriteUnsafe(
            int& target,
            int indexBit,
            bool value
        ) noexcept;
    };
}

namespace klib::Kongkong::Bits
{
    constexpr bool BitsetHelper::ReadUnsafe(
        const int* p,
        ssize_t index
    ) noexcept
    {
        ReadUnsafe(
            p[index / Numerics::Int::Bits()],
            static_cast<int>(index % Numerics::Int::Bits())
        );
    }

    constexpr bool BitsetHelper::ReadUnsafe(
        int p,
        int indexBit
    ) noexcept
    {
        int value = p;

        return static_cast<bool>(
            value & (1 << indexBit)
        );
    }

    constexpr void BitsetHelper::WriteUnsafe(
        int* p,
        ssize_t index,
        bool value
    ) noexcept
    {
        WriteUnsafe(
            p[index / Numerics::Int::Bits()],
            static_cast<int>(index % Numerics::Int::Bits()),
            value
        );
    }

    constexpr void BitsetHelper::WriteUnsafe(
        int& target,
        int indexBit,
        bool value
    ) noexcept
    {
        int targetValue = target;
        int bitValue = 1 << indexBit;
        int result;

        if (value) {
            result = targetValue | bitValue;
        }
        else {
            result = targetValue ^ bitValue;
        }

        target = result;
    }
}

#endif //!KLIB_KONGKONG_BITS_BITSETHELPER_H