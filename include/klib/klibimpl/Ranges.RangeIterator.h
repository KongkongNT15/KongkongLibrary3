#ifndef KLIB_RANGES_RANGEITERATOR_H
#define KLIB_RANGES_RANGEITERATOR_H

#include "base.h"

namespace klib::Ranges
{
    template <class TElement>
    struct RangeIterator {
        public:
        using ElementType = typename ::std::remove_cvref_t<TElement>;
        private:

        ElementType m_value;

        public:

        constexpr RangeIterator(
            ElementType value
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType operator*() const noexcept;

        [[nodiscard]]
        constexpr RangeIterator& operator++() noexcept;

        [[nodiscard]]
        constexpr RangeIterator operator++(int) noexcept;
    };

    template <class TElement>
    [[nodiscard]]
    constexpr bool operator==(
        RangeIterator<TElement> const& left,
        RangeIterator<TElement> const& right
    ) noexcept;

    template <class TElement>
    [[nodiscard]]
    constexpr bool operator!=(
        RangeIterator<TElement> const& left,
        RangeIterator<TElement> const& right
    ) noexcept;
}

namespace klib::Ranges
{
    template <class TElement>
    constexpr RangeIterator<TElement>::RangeIterator(
        ElementType value
    ) noexcept
        : m_value(value)
    {
    }

    template <class TElement>
    constexpr typename RangeIterator<TElement>::ElementType
    RangeIterator<TElement>::operator*() const noexcept
    {
        return m_value;
    }

    template <class TElement>
    constexpr RangeIterator<TElement>&
    RangeIterator<TElement>::operator++() noexcept
    {
        ++m_value;

        return *this;
    }

    template <class TElement>
    constexpr RangeIterator<TElement>
    RangeIterator<TElement>::operator++(int) noexcept
    {
        auto result = *this;

        this->operator++();

        return result;
    }

    template <class TElement>
    constexpr bool operator==(
        RangeIterator<TElement> const& left,
        RangeIterator<TElement> const& right
    ) noexcept
    {
        return *left == *right;
    }

    template <class TElement>
    constexpr bool operator!=(
        RangeIterator<TElement> const& left,
        RangeIterator<TElement> const& right
    ) noexcept
    {
        return *left != *right;
    }
}

#endif //!KLIB_RANGES_RANGEITERATOR_H