#ifndef KLIB_KONGKONG_RANGES_INDEXFROMEND_H
#define KLIB_KONGKONG_RANGES_INDEXFROMEND_H

#include "base.h"

namespace klib::Kongkong::Ranges
{
    struct IndexFromEnd final {
        public:
        ssize_t Value;

        constexpr IndexFromEnd(
            ssize_t value
        ) noexcept;
    };

    
}

namespace klib::Kongkong::Ranges
{
    constexpr IndexFromEnd::IndexFromEnd(
        ssize_t value
    ) noexcept
        : Value(value)
    {
    }
}

namespace klib::Literals
{
    consteval Kongkong::Ranges::IndexFromEnd
    operator""_end(
        unsigned long long n
    )
    {
        ssize_t v = static_cast<ssize_t>(n);

        // 
        if (v <= 0) throw 1;

        return v;
    }
    
}

#endif //!KLIB_KONGKONG_RANGES_INDEXFROMEND_H