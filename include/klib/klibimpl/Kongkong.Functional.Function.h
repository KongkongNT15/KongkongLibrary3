#ifndef KLIB_KONGKONG_FUNCTIONAL_FUNCTION_H
#define KLIB_KONGKONG_FUNCTIONAL_FUNCTION_H

#include "base.h"
#include "Kongkong.Functional.FunctionObject.h"
#include "Kongkong.Memory.GCHandle.h"

namespace klib::Kongkong::Functional
{
    template <class TResult, class... TArgs>
    class Function {
        private:
        Memory::GCHandle<FunctionBase<TResult, TArgs...>> m_func;
        public:

        template <class TFunc> requires ::std::is_invocable_v<TFunc, TArgs&&...>
        Function(
            TFunc
        );

        TResult operator()(
            TArgs&&... args
        ) const;
    };
}

namespace klib::Kongkong::Functional
{
    template <class TResult, class... TArgs>
    TResult Function<TResult, TArgs...>::operator()(
        TArgs&&... args
    ) const
    {
        return m_func.GetRawPointerUnsafe()->operator()(
            ::std::forward<TArgs>(args)...
        );
    }
}

#endif //!KLIB_KONGKONG_FUNCTIONAL_FUNCTION_H