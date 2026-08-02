#ifndef KLIB_FOUNDATION_STATELESSTYPE_H
#define KLIB_FOUNDATION_STATELESSTYPE_H

#include "base.h"

namespace klib::Foundation
{
    class StatelessType : public KLibType {
        public:

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;

        constexpr void WriteTo(
            ::std::ostream&
        ) const noexcept;
    };

    [[nodiscard]]
    constexpr bool operator==(
        StatelessType const&,
        StatelessType const&
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        StatelessType const&,
        StatelessType const&
    ) noexcept;
}

namespace klib::Foundation
{
    constexpr Hash::ResultType
    StatelessType::GetHashCode() const noexcept
    {
        return 0;
    }

    constexpr void
    StatelessType::WriteTo(
        ::std::ostream&
    ) const noexcept
    {
    }

    constexpr bool operator==(
        StatelessType const&,
        StatelessType const&
    ) noexcept
    {
        return true;
    }

    constexpr bool operator!=(
        StatelessType const&,
        StatelessType const&
    ) noexcept
    {
        return false;
    }
}

#endif //!KLIB_FOUNDATION_STATELESSTYPE_H
