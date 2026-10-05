#ifndef KLIB_FUNCTIONAL_LOGICALNOT_H
#define KLIB_FUNCTIONAL_LOGICALNOT_H

#include "base.h"
#include "Foundation.StatelessType.h"

#define KLIB_OPERATOR(l) !(l)
#define KLIB_OPERATOR_NOEXCEPT(t) noexcept(KLIB_OPERATOR(::std::declval<t>()))

namespace klib::Functional
{
    class LogicalNot final : public StatelessType {
        public:

        template <class T>
        [[nodiscard]]
        constexpr bool operator()(
            T&& value
        ) const noexcept(KLIB_OPERATOR_NOEXCEPT(T&&));
    };
}

namespace klib::Functional
{
    template <class T>
    constexpr bool LogicalNot::operator()(
        T&& value
    ) const noexcept(KLIB_OPERATOR_NOEXCEPT(T&&))
    {
        return KLIB_OPERATOR(static_cast<T&&>(value));
    }
}

#undef KLIB_OPERATOR
#undef KLIB_OPERATOR_NOEXCEPT

#endif //!KLIB_FUNCTIONAL_LOGICALNOT_H