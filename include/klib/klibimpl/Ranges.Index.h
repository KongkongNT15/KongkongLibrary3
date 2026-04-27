#ifndef KLIB_RANGES_INDEX_H
#define KLIB_RANGES_INDEX_H

#include "base.h"

namespace klib::Ranges
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

#endif //!KLIB_RANGES_INDEX_H
