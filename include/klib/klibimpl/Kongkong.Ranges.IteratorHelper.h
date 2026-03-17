#ifndef KLIB_KONGKONG_RANGES_ITERATORHELPER_H
#define KLIB_KONGKONG_RANGES_ITERATORHELPER_H

#include "base.h"
#include <iterator>

namespace klib::Kongkong::Ranges
{
    class IteratorHelper {
        
        template <class TIterator>
        static constexpr ssize_t GetLengthUnsafe(
            TIterator begin,
            TIterator end
        ) noexcept;
    };
}

namespace klib::Kongkong::Ranges
{
    template <class TIterator>
    constexpr ssize_t IteratorHelper::GetLengthUnsafe(
        TIterator begin,
        TIterator end
    ) noexcept
    {
        if constexpr (::std::random_access_iterator<TIterator>) {
            return end - begin;
        }
        else {
            ssize_t length = 0;

            while (begin != end) {
                ++length;
                ++begin;
            }

            return length;
        }
    }
}

#endif //!KLIB_KONGKONG_RANGES_ITERATORHELPER_H