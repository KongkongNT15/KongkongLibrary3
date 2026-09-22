#ifndef KLIB_RANGES_RANGET2_H
#define KLIB_RANGES_RANGET2_H

#include "base.h"
#include "Ranges.RangeIterator2.h"

namespace klib::Ranges
{
    template <class TElement>
    struct RangeT2 {
        public:

        using ElementType = typename ::std::remove_cvref_t<TElement>;

        private:

        ElementType m_start;
        ElementType m_end;
        ElementType m_interval;

        public:

        constexpr RangeT2(
            ElementType start,
            ElementType end,
            ElementType interval
        ) noexcept;

        [[nodiscard]]
        constexpr RangeIterator2<TElement> begin() const noexcept;

        [[nodiscard]]
        constexpr RangeIterator2<TElement> end() const noexcept;

        [[nodiscard]]
        constexpr ElementType End() const noexcept;
        
        [[nodiscard]]
        constexpr ElementType Start() const noexcept;
    };
}

namespace klib::Ranges
{
    template <class TElement>
    constexpr RangeT2<TElement>::RangeT2(
        ElementType start,
        ElementType end,
        ElementType interval
    ) noexcept
        : m_start(start)
        , m_end(end)
        , m_interval(interval)
    {
    }

    template <class TElement>
    constexpr RangeIterator2<TElement>
    RangeT2<TElement>::begin() const noexcept
    {
        return { m_start, m_interval };
    }

    template <class TElement>
    constexpr RangeIterator2<TElement>
    RangeT2<TElement>::end() const noexcept
    {
        return { m_end, m_interval };
    }

    template <class TElement>
    constexpr typename RangeT2<TElement>::ElementType
    RangeT2<TElement>::End() const noexcept
    {
        return m_end;
    }

    template <class TElement>
    constexpr typename RangeT2<TElement>::ElementType
    RangeT2<TElement>::Start() const noexcept
    {
        return m_start;
    }
}

#endif //!KLIB_RANGES_RANGET2_H