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
            typename decltype(
                (::std::declval<TInstance>().*::std::declval<TFType>())(::std::declval<TArgs>())
            ),
            TArgs...
        >
    {
        public:

        using FType = TResult(TInstance::*)(TArgs...);

        using TResult = typename decltype(
            (::std::declval<TInstance>().*::std::declval<TFType>())(::std::declval<TArgs>())
        );

        private:

        TInstance* m_p;
        FType m_f;

        public:

        constexpr MemberFunction(
            TInstance* p,
            FType f
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
        TInstance* p,
        FType f
    ) noexcept
        : m_p(p)
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

#endif //!KLIB_FUNCTIONAL_MEMBERFUNCTION_H