#ifndef KLIB_FUNCTIONAL_MEMBERFUNCTION_H
#define KLIB_FUNCTIONAL_MEMBERFUNCTION_H

#include "base.h"
#include "Functional.FunctionBase.h"

#define KLIB_CLASS_TEMPLATE_DEF template <class TInstance, class TFType, class... TArgs>
#define KLIB_CLASS_TEMPLATE_PARAM TInstance, TFType, TArgs...

namespace klib::Functional
{
    KLIB_CLASS_TEMPLATE_DEF
    struct MemberFunction :
        public FunctionBase<
            typename ::std::invoke_result_t<
                TFType,
                typename ::std::remove_reference_t<decltype(*::std::declval<TInstance>())>,
                TArgs...
            >,
            TArgs...
        >
    {
        public:

        using TResult = typename ::std::invoke_result_t<
            TFType,
            typename ::std::remove_reference_t<decltype(*::std::declval<TInstance>())>,
            TArgs...
        >;

        private:

        TInstance m_p;
        TFType m_f;

        public:

        constexpr MemberFunction(
            TInstance const& p,
            TFType f
        ) noexcept;

        constexpr MemberFunction(
            TInstance&& p,
            TFType f
        ) noexcept;

        TResult operator()(
            TArgs&&... args
        ) override;
    };
}

namespace klib::Functional
{
    KLIB_CLASS_TEMPLATE_DEF
    constexpr MemberFunction<KLIB_CLASS_TEMPLATE_PARAM>::MemberFunction(
        TInstance const& p,
        TFType f
    ) noexcept
        : m_p(p)
        , m_f(f)
    {
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr MemberFunction<KLIB_CLASS_TEMPLATE_PARAM>::MemberFunction(
        TInstance&& p,
        TFType f
    ) noexcept
        : m_p(::std::move(p))
        , m_f(f)
    {
    }

    KLIB_CLASS_TEMPLATE_DEF
    MemberFunction<KLIB_CLASS_TEMPLATE_PARAM>::TResult
    MemberFunction<KLIB_CLASS_TEMPLATE_PARAM>::operator()(
        TArgs&&... args
    )
    {
        return (m_p->*m_f)(::std::forward<TArgs>(args)...);
    }
}

#undef KLIB_CLASS_TEMPLATE_DEF
#undef KLIB_CLASS_TEMPLATE_PARAM

#endif //!KLIB_FUNCTIONAL_MEMBERFUNCTION_H