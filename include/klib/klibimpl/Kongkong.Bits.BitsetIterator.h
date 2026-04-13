#ifndef KLIB_KONGKONG_BITS_BITSETITERATOR_H
#define KLIB_KONGKONG_BITS_BITSETITERATOR_H

#include "base.h"
#include "Kongkong.ValueType.h"
#include "Kongkong.Bits.BitsetElement.h"
#include "Kongkong.Numerics.Int.h"

namespace klib::Kongkong::Bits
{
    class BitsetIterator {
        friend constexpr bool operator==(
            BitsetIterator,
            BitsetIterator
        ) noexcept;
        private:
        int* m_p;
        int m_indexBit;

        constexpr void do_add() noexcept;

        public:

        BitsetIterator(
            ::std::nullptr_t
        ) = delete;

        explicit constexpr BitsetIterator(
            int* p
        ) noexcept;

        explicit constexpr BitsetIterator(
            int* p,
            int indexBit
        ) noexcept;

        constexpr BitsetIterator& operator++() noexcept;

        constexpr BitsetIterator operator++(int) noexcept;

        [[nodiscard]]
        constexpr BitsetElement operator*() const noexcept;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;
    };

    [[nodiscard]]
    constexpr bool operator==(
        BitsetIterator left,
        BitsetIterator right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        BitsetIterator left,
        BitsetIterator right
    ) noexcept;
}

namespace klib::Kongkong::Bits
{
    constexpr BitsetIterator::BitsetIterator(
        int* p
    ) noexcept
        : m_p(p)
        , m_indexBit(0)
    {
    }

    constexpr BitsetIterator::BitsetIterator(
        int* p,
        int indexBit
    ) noexcept
        : m_p(p)
        , m_indexBit(indexBit)
    {
    }

    constexpr void BitsetIterator::do_add() noexcept
    {
        if (++m_indexBit == Numerics::Int::Bits()) {
            ++m_p;
            m_indexBit = 0;
        }
    }

    constexpr BitsetIterator&
    BitsetIterator::operator++() noexcept
    {
        do_add();

        return *this;
    }

    constexpr BitsetIterator
    BitsetIterator::operator++(int) noexcept
    {
        auto result = *this;
        do_add();

        return result;
    }

    constexpr BitsetElement
    BitsetIterator::operator*() const noexcept
    {
        return BitsetElement(*m_p, m_indexBit);
    }

    constexpr Hash::ResultType
    BitsetIterator::GetHashCode() const noexcept
    {
        auto h1 = reinterpret_cast<Hash::ResultType>(m_p);
        return h1 + m_indexBit;
    }

    constexpr bool operator==(
        BitsetIterator left,
        BitsetIterator right
    ) noexcept
    {
        return 
            left.m_p == right.m_p
            && left.m_indexBit == right.m_indexBit;
    }

    constexpr bool operator!=(
        BitsetIterator left,
        BitsetIterator right
    ) noexcept
    {
        return !(left == right);
    }
    
}

#endif //!KLIB_KONGKONG_BITS_BITSETITERATOR_H