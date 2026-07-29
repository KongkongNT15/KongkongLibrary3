#ifndef KLIB_FUNCTIONAL_FUNCTION_H
#define KLIB_FUNCTIONAL_FUNCTION_H

#include "base.h"
#include "Functional.FunctionBase.h"
#include "Functional.FunctionObject.h"
#include "Functional.FunctionPointer.h"
#include "Functional.MemberFunction.h"

namespace klib::Functional
{
    template <class TResult, class... TArgs>
    class Function<TResult(TArgs...)> {
        public:

        using FuncType = FunctionBase<TResult, TArgs...>;

        private:
        

        static TResult DoNone(TArgs...) noexcept;
        
        static inline FunctionPointer<TResult, TArgs...> s_none = { DoNone };

        FuncType* m_func;


        [[nodiscard]]
        constexpr bool ShouldDelete() const noexcept;

        public:

        Function() noexcept;

        Function(
            ::std::nullptr_t
        ) noexcept;

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
            Function const& other
        ) noexcept;

        constexpr Function(
            Function&& other
        ) noexcept;

        constexpr ~Function();

        Function& operator=(
            Function const& other
        ) noexcept;

        Function& operator=(
            Function&& other
        ) noexcept;

        TResult operator()(
            TArgs... args
        ) const;
    };
}

namespace klib::Functional
{
    template <class TResult, class... TArgs>
    Function<TResult(TArgs...)>::Function() noexcept
        : Function<TResult(TArgs...)>(nullptr)
    {
    }

    template <class TResult, class... TArgs>
    Function<TResult(TArgs...)>::Function(
        ::std::nullptr_t
    ) noexcept
        : m_func(&s_none)
    {
    }

    template <class TResult, class... TArgs>
    template <class TFunc> requires ::std::is_invocable_v<TFunc, TArgs...>
    Function<TResult(TArgs...)>::Function(
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
    Function<TResult(TArgs...)>::Function(
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
    constexpr Function<TResult(TArgs...)>::Function(
        Function<TResult(TArgs...)>&& other
    ) noexcept
        : m_func(other.m_func)
    {
        other.m_func = nullptr;
    }

    template <class TResult, class... TArgs>
    constexpr Function<TResult(TArgs...)>::~Function()
    {
        if (!ShouldDelete()) return;

        delete m_func;
    }

    template <class TResult, class... TArgs>
    Function<TResult(TArgs...)>& Function<TResult(TArgs...)>::operator=(
        Function<TResult(TArgs...)>&& other
    ) noexcept
    {
        if (&other != this) [[likely]] {
            if (ShouldDelete()) {
                delete m_func;
            }

            m_func = other.m_func;
            other.m_func = nullptr;
        }
        
        return *this;
    }

    template <class TResult, class... TArgs>
    TResult Function<TResult(TArgs...)>::operator()(
        TArgs... args
    ) const
    {
        return m_func->operator()(::std::forward<TArgs>(args)...);
    }

    template <class TResult, class... TArgs>
    TResult
    Function<TResult(TArgs...)>::DoNone(
        TArgs... args
    ) noexcept
    {
        if constexpr (::std::is_void_v<TResult>) {
            return;
        }
        else {
            return TResult{};
        }
    }

    template <class TResult, class... TArgs>
    constexpr bool
    Function<TResult(TArgs...)>::ShouldDelete() const noexcept
    {
        return m_func != nullptr && m_func != &s_none;
    }
}

#endif //!KLIB_FUNCTIONAL_FUNCTION_H
