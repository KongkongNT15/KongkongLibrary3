#ifndef KLIB_KONGKONG_NONTYPE_H
#define KLIB_KONGKONG_NONTYPE_H

#include "base.h"

namespace klib::Kongkong
{
    struct NonType final {
        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode(
        ) const noexcept;
    };
}

namespace klib::Kongkong
{
    constexpr Hash::ResultType NonType::GetHashCode(
    ) const noexcept
    {
        return 0;
    }
}

#endif //!KLIB_KONGKONG_NONTYPE_H