#ifndef KLIB_RANGES_RANGEITERATOR2_H
#define KLIB_RANGES_RANGEITERATOR2_H

#include "base.h"

namespace klib::Ranges
{
    template <class TElement>
    struct RangeIterator2 {
        public:
        using ElementType = typename ::std::remove_cvref_t<TElement>;
        private:

        ElementType m_value;
        ElementType m_interval;

        public:

        constexpr RangeIterator2(
            ElementType value,
            ElementType interval
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType operator*() const noexcept;

        [[nodiscard]]
        constexpr RangeIterator2& operator++() noexcept;

        [[nodiscard]]
        constexpr RangeIterator2 operator++(int) noexcept;
    };

    template <class TElement>
    [[nodiscard]]
    constexpr bool operator==(
        RangeIterator2<TElement> const& left,
        RangeIterator2<TElement> const& right
    ) noexcept;

    template <class TElement>
    [[nodiscard]]
    constexpr bool operator!=(
        RangeIterator2<TElement> const& left,
        RangeIterator2<TElement> const& right
    ) noexcept;
}

namespace klib::Ranges
{
    template <class TElement>
    constexpr RangeIterator2<TElement>::RangeIterator2(
        ElementType value,
        ElementType interval
    ) noexcept
        : m_value(value)
        , m_interval(interval)
    {
    }

    template <class TElement>
    constexpr typename RangeIterator2<TElement>::ElementType
    RangeIterator2<TElement>::operator*() const noexcept
    {
        return m_value;
    }

    template <class TElement>
    constexpr RangeIterator2<TElement>&
    RangeIterator2<TElement>::operator++() noexcept
    {
        m_value += m_interval;

        return *this;
    }

    template <class TElement>
    constexpr RangeIterator2<TElement>
    RangeIterator2<TElement>::operator++(int) noexcept
    {
        auto result = *this;

        this->operator++();

        return result;
    }

    template <class TElement>
    constexpr bool operator==(
        RangeIterator2<TElement> const& left,
        RangeIterator2<TElement> const& right
    ) noexcept
    {
        return *left == *right;
    }

    template <class TElement>
    constexpr bool operator!=(
        RangeIterator2<TElement> const& left,
        RangeIterator2<TElement> const& right
    ) noexcept
    {
        if constexpr (::std::is_floating_point_v<TElement>) {
            return *left < *right;
        }
        else {
            return *left != *right;
        }
        
    }
}

#endif //!KLIB_RANGES_RANGEITERATOR2_H