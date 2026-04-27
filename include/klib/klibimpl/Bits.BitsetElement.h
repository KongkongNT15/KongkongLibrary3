#ifndef KLIB_BITS_BITSETELEMENT_H
#define KLIB_BITS_BITSETELEMENT_H

#include "base.h"
#include "Bits.BitsetHelper.h"

namespace klib::Bits
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

namespace klib::Bits
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

#endif //!KLIB_BITS_BITSETELEMENT_H
