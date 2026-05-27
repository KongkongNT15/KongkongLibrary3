#ifndef KLIB_RANGES_RANGE_H
#define KLIB_RANGES_RANGE_H

#include "base.h"
#include "Ranges.RangeIterator.h"

namespace klib::Ranges
{
    template <class TElement>
    struct Range {
        public:

        using ElementType = typename ::std::remove_cvref_t<TElement>;

        private:

        ElementType m_start;
        ElementType m_end;

        public:

        constexpr Range(
            ElementType start,
            ElementType end
        ) noexcept;

        [[nodiscard]]
        constexpr RangeIterator<TElement> begin() const noexcept;

        [[nodiscard]]
        constexpr RangeIterator<TElement> end() const noexcept;

        [[nodiscard]]
        constexpr ElementType End() const noexcept;
        
        [[nodiscard]]
        constexpr ElementType Start() const noexcept;
    };
}

namespace klib::Ranges
{
    template <class TElement>
    constexpr Range<TElement>::Range(
        ElementType start,
        ElementType end
    ) noexcept
        : m_start(start)
        , m_end(end)
    {
    }

    template <class TElement>
    constexpr RangeIterator<TElement>
    Range<TElement>::begin() const noexcept
    {
        return Range<TElement>(m_start);
    }

    template <class TElement>
    constexpr RangeIterator<TElement>
    Range<TElement>::end() const noexcept
    {
        return Range<TElement>(m_end);
    }

    template <class TElement>
    constexpr typename Range<TElement>::ElementType
    Range<TElement>::End() const noexcept
    {
        return m_end;
    }

    template <class TElement>
    constexpr typename Range<TElement>::ElementType
    Range<TElement>::Start() const noexcept
    {
        return m_start;
    }
}

#endif //!KLIB_RANGES_RANGE_H
