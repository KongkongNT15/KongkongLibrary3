#ifndef KLIB_KONGKONG_BITS_BITSETELEMENT_H
#define KLIB_KONGKONG_BITS_BITSETELEMENT_H

#include "base.h"
#include "Kongkong.Bits.BitsetHelper.h"

namespace klib::Kongkong::Bits
{
    class BitsetElement {
        private:

        int* m_p;
        int m_indexBit;

        public:

        explicit constexpr BitsetElement(
            int& target,
            int index
        ) noexcept;

        BitsetElement& operator=(
            bool value
        ) noexcept;

        [[nodiscard]]
        constexpr operator bool() const noexcept;

        
    };
}

namespace klib::Kongkong::Bits
{
    constexpr BitsetElement::BitsetElement(
        int& target,
        int index
    ) noexcept
        : m_p(&target)
        , m_indexBit(index)
    {
    }

    BitsetElement& BitsetElement::operator=(
        bool value
    ) noexcept
    {
        BitsetHelper::WriteUnsafe(
            *m_p,
            m_indexBit,
            value
        );

        return *this;
    }

    constexpr BitsetElement::operator bool() const noexcept
    {
        return BitsetHelper::ReadUnsafe(
            *m_p,
            m_indexBit
        );
    }
}

#endif //!KLIB_KONGKONG_BITS_BITSETELEMENT_H