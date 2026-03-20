#ifndef KLIB_KONGKONG_BITS_BitsetConstIterator_H
#define KLIB_KONGKONG_BITS_BitsetConstIterator_H

#include "base.h"
#include "Kongkong.Numerics.Int.h"

namespace klib::Kongkong::Bits
{
    class BitsetConstIterator {
        friend constexpr bool operator==(
            BitsetConstIterator,
            BitsetConstIterator
        ) noexcept;
        private:
        const int* m_p;
        int m_indexBit;
        int m_cash;

        constexpr void do_add() noexcept;

        public:

        BitsetConstIterator(
            ::std::nullptr_t
        ) = delete;

        explicit constexpr BitsetConstIterator(
            const int* p
        ) noexcept;

        explicit constexpr BitsetConstIterator(
            const int* p,
            int indexBit
        ) noexcept;

        constexpr BitsetConstIterator& operator++() noexcept;

        constexpr BitsetConstIterator operator++(int) noexcept;

        [[nodiscard]]
        constexpr bool operator*() const noexcept;
    };

    [[nodiscard]]
    constexpr bool operator==(
        BitsetConstIterator left,
        BitsetConstIterator right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        BitsetConstIterator left,
        BitsetConstIterator right
    ) noexcept;
}

namespace klib::Kongkong::Bits
{
    constexpr BitsetConstIterator::BitsetConstIterator(
        const int* p
    ) noexcept
        : m_p(p)
        , m_indexBit(0)
        , m_cash(*p)
    {
    }

    constexpr BitsetConstIterator::BitsetConstIterator(
        const int* p,
        int indexBit
    ) noexcept
        : m_p(p)
        , m_indexBit(indexBit)
        , m_cash()
    {
    }

    constexpr void BitsetConstIterator::do_add() noexcept
    {
        if (++m_indexBit == Numerics::Int::Bits()) {
            ++m_p;
            m_indexBit = 0;
            m_cash = *m_p;
        }
        else {
            m_cash >>= 1;
        }
    }

    constexpr BitsetConstIterator&
    BitsetConstIterator::operator++() noexcept
    {
        do_add();

        return *this;
    }

    constexpr BitsetConstIterator
    BitsetConstIterator::operator++(int) noexcept
    {
        auto result = *this;
        do_add();

        return result;
    }

    constexpr bool
    BitsetConstIterator::operator*() const noexcept
    {
        return static_cast<bool>(m_cash & 1);
    }

    constexpr bool operator==(
        BitsetConstIterator left,
        BitsetConstIterator right
    ) noexcept
    {
        return
            left.m_p == right.m_p
            && left.m_indexBit == right.m_indexBit;
    }

    constexpr bool operator!=(
        BitsetConstIterator left,
        BitsetConstIterator right
    ) noexcept
    {
        return !(left == right);
    }
}

#endif //!KLIB_KONGKONG_BITS_BitsetConstIterator_H