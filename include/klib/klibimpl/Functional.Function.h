#ifndef KLIB_FUNCTIONAL_FUNCTION_H
#define KLIB_FUNCTIONAL_FUNCTION_H

#include "base.h"
#include "Functional.FunctionBase.h"
#include "Functional.FunctionObject.h"
#include "Functional.FunctionPointer.h"
#include "Functional.MemberFunction.h"
#include "Functional.RawFunction.h"

namespace klib::Functional
{
    template <class TResult, class... TArgs>
    class Function {
        private:

        FunctionBase<TResult, TArgs...>* m_func;

        public:

        template <class TFunc> requires ::std::is_invocable_v<TFunc, TArgs...>
        Function(
            TFunc&& f
        );

        template <class TInstance, class TMemberFunction> requires ::std::is_member_function_pointer_v<TMemberFunction>
        Function(
            TInstance&& p,
            TMemberFunction f
        );

        constexpr Function(
            Function&& other
        ) noexcept;

        ~Function();

        Function& operator=(
            Function&& other
        ) noexcept;

        TResult operator()(
            TArgs&&... args
        ) const;
    };
}

namespace klib::Functional
{
    template <class TResult, class... TArgs>
    template <class TFunc> requires ::std::is_invocable_v<TFunc, TArgs...>
    Function<TResult, TArgs...>::Function(
        TFunc&& f
    )
    {
        // 関数型
        if constexpr (::std::is_function_v<TFunc>) {
            m_func = new FunctionPointer<TResult, TArgs...>(f);
        }
        // 関数ポインタ
        else if constexpr (::std::same_as<TFunc, TResult(*)(TArgs...)>) {
            m_func = new FunctionPointer<TResult, TArgs...>(f);
        }
        // 関数オブジェクト？？？
        else {
            m_func = new FunctionObject<TFunc, TResult, TArgs...>(::std::forward<TFunc>(f));
        }
    }

    template <class TResult, class... TArgs>
    template <class TInstance, class TMemberFunction> requires ::std::is_member_function_pointer_v<TMemberFunction>
    Function<TResult, TArgs...>::Function(
        TInstance&& p,
        TMemberFunction f
    )
        : m_func(
            new MemberFunction<TInstance, TMemberFunction, TArgs...>(
                ::std::forward<TInstance>(p),
                f
            )
        )
    {
    }

    template <class TResult, class... TArgs>
    constexpr Function<TResult, TArgs...>::Function(
        Function<TResult, TArgs...>&& other
    ) noexcept
        : m_func(other.m_func)
    {
        other.m_func = nullptr;
    }

    template <class TResult, class... TArgs>
    Function<TResult, TArgs...>::~Function()
    {
        if (m_func == nullptr) return;

        delete m_func;
    }

    template <class TResult, class... TArgs>
    Function<TResult, TArgs...>& Function<TResult, TArgs...>::operator=(
        Function<TResult, TArgs...>&& other
    ) noexcept
    {
        if (&other != this) [[likely]] {
            if (m_func != nullptr) {
                delete m_func;
            }

            m_func = other.m_func;
            other.m_func = nullptr;
        }
        
        return *this;
    }

    template <class TResult, class... TArgs>
    TResult Function<TResult, TArgs...>::operator()(
        TArgs&&... args
    ) const
    {
        return m_func->operator()(::std::forward<TArgs>(args)...);
    }
}

#endif //!KLIB_FUNCTIONAL_FUNCTION_H
