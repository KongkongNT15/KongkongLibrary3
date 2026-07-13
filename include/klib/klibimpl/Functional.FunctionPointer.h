#ifndef KLIB_FUNCTIONAL_FUNCTIONPOINTER_H
#define KLIB_FUNCTIONAL_FUNCTIONPOINTER_H

#include "base.h"
#include "Functional.FunctionBase.h"

namespace klib::Functional
{
    template <class TResult, class... TArgs>
    struct FunctionPointer : FunctionBase<TResult, TArgs...> {
        public:
        using FuncType = TResult(*)(TArgs&&...);
        private:

        FuncType m_funcPointer;

        public:

        constexpr FunctionPointer(
            FuncType func
        ) noexcept;

        TResult operator()(
            TArgs&&... args
        ) override;
    };
}

namespace klib::Functional
{
    template <class TResult, class... TArgs>
    constexpr FunctionPointer<TResult, TArgs...>::FunctionPointer(
        FuncType func
    ) noexcept
        : m_funcPointer(func)
    {
    }

    template <class TResult, class... TArgs>
    TResult FunctionPointer<TResult, TArgs...>::operator()(
        TArgs&&... args
    )
    {
        return m_funcPoitner(::std::forward<TArgs>(args)...);
    }
}

#endif //!KLIB_FUNCTIONAL_FUNCTIONPOINTER_H
