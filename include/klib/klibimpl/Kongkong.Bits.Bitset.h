#ifndef KLIB_KONGKONG_BITS_BITSET_H
#define KLIB_KONGKONG_BITS_BITSET_H

#include "base.h"
#include "Kongkong.Bits.BitsetConstIterator.h"
#include "Kongkong.Bits.BitsetHelper.h"
#include "Kongkong.Bits.BitsetIterator.h"
#include "Kongkong.Numerics.Int.h"

#define KLIB_CLASS_TEMPLATE_DEF template <ssize_t N> requires (N >= 1)

namespace klib::Kongkong::Bits
{
    KLIB_CLASS_TEMPLATE_DEF
    struct Bitset {
        public:
        private:
        int m_placeHolder[((N - 1) / Numrics::Int::Bits()) + 1];
        public:

        [[nodiscard]]
        constexpr BitsetElement operator[](
            ssize_t index
        ) noexcept;

        [[nodiscard]]
        constexpr bool operator[](
            ssize_t index
        ) const noexcept;

        [[nodiscard]]
        constexpr BitsetIterator begin() noexcept;

        [[nodiscard]]
        constexpr BitsetConstIterator begin() const noexcept;

        [[nodiscard]]
        constexpr BitsetIterator end() noexcept;

        [[nodiscard]]
        constexpr BitsetConstIterator end() const noexcept;

        
    };
}

namespace klib::Kongkong::Bits
{
    KLIB_CLASS_TEMPLATE_DEF
    constexpr BitsetElement Bitset<N>::operator[](
        ssize_t index
    ) noexcept
    {
        return BitsetElement(
            m_placeHolder[index / Numrics::Int::Bits()],
            static_cast<int>(index % Numrics::Int::Bits())
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr bool Bitset<N>::operator[](
        ssize_t index
    ) const noexcept
    {
        return BitsetHelper::ReadUnsafe(
            m_placeHolder[index / Numrics::Int::Bits()],
            static_cast<int>(index % Numrics::Int::Bits())
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr BitsetIterator Bitset<N>::begin() noexcept
    {
        return BitsetIterator(m_placeHolder);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr BitsetConstIterator
    Bitset<N>::begin() const noexcept
    {
        return BitsetConstIterator(m_placeHolder);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr BitsetIterator Bitset<N>::end() noexcept
    {
        return BitsetIterator(
            m_placeHolder + N / Numrics::Int::Bits(),
            N % Numrics::Int::Bits()
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr BitsetConstIterator
    Bitset<N>::end() const noexcept
    {
        return BitsetConstIterator(
            m_placeHolder + N / Numrics::Int::Bits(),
            N % Numrics::Int::Bits()
        );
    }
}

#undef KLIB_CLASS_TEMPLATE_DEF

#endif //!KLIB_KONGKONG_BITS_BITSET_H