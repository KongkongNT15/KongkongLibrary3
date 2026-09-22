#ifndef KLIB_RANGES_RANGET_H
#define KLIB_RANGES_RANGET_H

#include "base.h"
#include "Ranges.RangeIterator.h"

namespace klib::Ranges
{
    template <class TElement>
    struct RangeT {
        public:

        using ElementType = typename ::std::remove_cvref_t<TElement>;

        private:

        ElementType m_start;
        ElementType m_end;

        public:

        constexpr RangeT(
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
    constexpr RangeT<TElement>::RangeT(
        ElementType start,
        ElementType end
    ) noexcept
        : m_start(start)
        , m_end(end)
    {
    }

    template <class TElement>
    constexpr RangeIterator<TElement>
    RangeT<TElement>::begin() const noexcept
    {
        return RangeIterator<TElement>(m_start);
    }

    template <class TElement>
    constexpr RangeIterator<TElement>
    RangeT<TElement>::end() const noexcept
    {
        return RangeIterator<TElement>(m_end);
    }

    template <class TElement>
    constexpr typename RangeT<TElement>::ElementType
    RangeT<TElement>::End() const noexcept
    {
        return m_end;
    }

    template <class TElement>
    constexpr typename RangeT<TElement>::ElementType
    RangeT<TElement>::Start() const noexcept
    {
        return m_start;
    }
}

#endif //!KLIB_RANGES_RANGET_H
