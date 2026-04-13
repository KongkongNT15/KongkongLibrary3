#ifndef KLIB_KONGKONG_INITIALIZER_H
#define KLIB_KONGKONG_INITIALIZER_H

#include "base.h"

namespace klib::Kongkong
{
    class Initializer final {
        
        template <class TFunc>
        Initializer(
            TFunc&& func
        );

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode(
        ) const noexcept;
    };
}

namespace klib::Kongkong
{
    template <class TFunc>
    Initializer::Initializer(
        TFunc&& func
    )
    {
        func();
    }

    constexpr Hash::ResultType
    Initializer::GetHashCode(
    ) const noexcept
    {
        return 0;
    }
}

#endif //!KLIB_KONGKONG_INITIALIZER_H