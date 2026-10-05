#ifndef KLIB_FUNCTIONAL_LESS_H
#define KLIB_FUNCTIONAL_LESS_H

#include "base.h"
#include "Foundation.StatelessType.h"

#define KLIB_OPERATOR(l, r) l < r
#define KLIB_OPERATOR_NOEXCEPT(t1, t2) noexcept(KLIB_OPERATOR(::std::declval<t1>(), ::std::declval<t2>()))

namespace klib::Functional
{
    class Less final : public StatelessType {
        public:

        template <class T1, class T2>
        [[nodiscard]]
        constexpr bool operator()(
            T1&& left,
            T2&& right
        ) const noexcept(KLIB_OPERATOR_NOEXCEPT(T1&&, T2&&));
    };
}

namespace klib::Functional
{
    template <class T1, class T2>
    constexpr bool Less::operator()(
        T1&& left,
        T2&& right
    ) const noexcept(KLIB_OPERATOR_NOEXCEPT(T1&&, T2&&))
    {
        return KLIB_OPERATOR(static_cast<T1&&>(left), static_cast<T2&&>(right));
    }
}

#undef KLIB_OPERATOR
#undef KLIB_OPERATOR_NOEXCEPT

#endif //!KLIB_FUNCTIONAL_LESS_H