#ifndef KLIB_RANGES_RANGE_H
#define KLIB_RANGES_RANGE_H

#include "base.h"
#include "Ranges.RangeT.h"

namespace klib::Ranges
{
    template <class T>
    constexpr RangeT<T> Range(
        T end
    ) noexcept;

    template <class T>
    constexpr RangeT<T> Range(
        T begin,
        T end
    ) noexcept;

    template <class T>
    constexpr RangeT2<T> Range(
        T begin,
        T end,
        T interval
    ) noexcept;
}

namespace klib::Ranges
{
    template <class T>
    constexpr RangeT<T> Range(
        T end
    ) noexcept
    {
        return RangeT<T>(0, end);
    }

    template <class T>
    constexpr RangeT<T> Range(
        T begin,
        T end
    ) noexcept
    {
        return RangeT<T>(begin, end);
    }

    template <class T>
    constexpr RangeT2<T> Range(
        T begin,
        T end,
        T interval
    ) noexcept
    {
        return RangeT2<T>(begin, end, interval);
    }
}

#endif //!KLIB_RANGES_RANGE_H