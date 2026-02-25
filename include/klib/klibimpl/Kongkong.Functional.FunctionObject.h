#ifndef KLIB_KONGKONG_FUNCTIONAL_FUNCTIONOBJECT_H
#define KLIB_KONGKONG_FUNCTIONAL_FUNCTIONOBJECT_H

#include "base.h"
#include "Kongkong.Functional.FunctionBase.h"

#define KLIB_CLASS_TEMPLATE_DEF template <class TFunc, class TResult, class... TArgs> requires ::std::is_invocable_v<TFunc, TArgs&&...>
#define KLIB_CLASS_TEMPLATE_PARAM TFunc, TResult, TArgs...

namespace klib::Kongkong::Functional
{
    KLIB_CLASS_TEMPLATE_DEF
    struct FunctionObject : FunctionBase<TResult, TArgs&&...> {
        private:
        TFunc m_func;

        public:

        FunctionObject(
            TFunc func
        );

        TResult operator()(
            TArgs&&... args
        ) override;
    };
}

namespace klib::Kongkong::Functional
{
    KLIB_CLASS_TEMPLATE_DEF
    FunctionObject<KLIB_CLASS_TEMPLATE_PARAM>::FunctionObject(
        TFunc func
    )
        : m_func(func)
    {
    }

    KLIB_CLASS_TEMPLATE_DEF
    TResult FunctionObject<KLIB_CLASS_TEMPLATE_PARAM>::operator()(
        TArgs&&... args
    )
    {
        return m_func(
            ::std::forward<TArgs>(args)...
        );
    }
}

#undef KLIB_TEMPLATE_DEF
#undef KLIB_TEMPLATE_PARAM

#endif //!KLIB_KONGKONG_FUNCTIONAL_FUNCTIONOBJECT_H