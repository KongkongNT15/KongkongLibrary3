#ifndef KLIB_FUNCTIONAL_IDENTITY_H
#define KLIB_FUNCTIONAL_IDENTITY_H

#include "base.h"
#include "Foundation.StatelessType.h"

#define KLIB_OPERATOR(v) (v)
#define KLIB_OPERATOR_NOEXCEPT(t) noexcept(KLIB_OPERATOR(::std::declval<t>()))
#define KLIB_RESULTTYPE(t) t

namespace klib::Functional
{
    class Identity final : public StatelessType {
        public:

        template <class T>
        [[nodiscard]]
        constexpr KLIB_RESULTTYPE(T&&) operator()(
            T&& value
        ) const noexcept(KLIB_OPERATOR_NOEXCEPT(T&&));
    };
}

namespace klib::Functional
{
    template <class T>
    constexpr KLIB_RESULTTYPE(T&&)
    Identity::operator()(
        T&& value
    ) const noexcept(KLIB_OPERATOR_NOEXCEPT(T&&))
    {
        return KLIB_OPERATOR(static_cast<T&&>(value));
    }
}

#undef KLIB_OPERATOR
#undef KLIB_OPERATOR_NOEXCEPT
#undef KLIB_RESULTTYPE

#endif //!KLIB_FUNCTIONAL_IDENTITY_H