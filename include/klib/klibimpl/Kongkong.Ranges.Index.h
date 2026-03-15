#ifndef KLIB_KONGKONG_RANGES_INDEX_H
#define KLIB_KONGKONG_RANGES_INDEX_H

#include "base.h"

namespace klib::Kongkong::Ranges
{
    struct Index {
        public:
        ssize_t Value;

        [[nodiscard]]
        static constexpr Index Begin() noexcept;

        [[nodiscard]]
        static constexpr Index End() noexcept;

        [[nodiscard]]
        static constexpr Index FromEnd(
            ssize_t index
        ) noexcept;

        constexpr Index(
            ssize_t value
        ) noexcept;
    };
}

#endif //!KLIB_KONGKONG_RANGES_INDEX_H