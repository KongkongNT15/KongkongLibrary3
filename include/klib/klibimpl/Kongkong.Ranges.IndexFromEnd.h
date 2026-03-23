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

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;
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

    constexpr Hash::ResultType
    IndexFromEnd::GetHashCode() const noexcept
    {
        return ~::std::hash<ssize_t>{}.operator()(Value);
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