#ifndef KLIB_SIGNALS_DELEGATE_H
#define KLIB_SIGNALS_DELEGATE_H

#include "base.h"
#include "Containers.ArrayView.h"
#include "Functional.Function.h"

#include <vector>

namespace klib::Signals
{
    template <class TResult, class... TArgs>
    class Delegate final {
        public:

        using FunctionType =
            typename Functional::Function<TResult(TArgs...)>;

        private:

        ::std::vector<FunctionType> m_vec;

        public:

        Delegate& operator+=(
            FunctionType const& f
        );

        Delegate& operator+=(
            FunctionType&& f
        );

        Delegate& operator-=(
            FunctionType const& f
        );

        [[nodiscard]]
        constexpr Containers::ArrayView<FunctionType>
        InvocationList() const noexcept;

        TResult Invoke(
            TArgs&&... args
        );
    };
}

namespace klib::Signals
{
    template <class TResult, class... TArgs>
    Delegate<TResult, TArgs...>&
    Delegate<TResult, TArgs...>::operator+=(
        FunctionType const& f
    )
    {
        m_vec.push_back(f);
        return *this;
    }

    template <class TResult, class... TArgs>
    Delegate<TResult, TArgs...>&
    Delegate<TResult, TArgs...>::operator+=(
        FunctionType&& f
    )
    {
        m_vec.push_back(::std::move(f));
        return *this;
    }

    template <class TResult, class... TArgs>
    Delegate<TResult, TArgs...>&
    Delegate<TResult, TArgs...>::operator-=(
        FunctionType const& f
    )
    {
        auto itr = m_vec.begin();
        auto end = m_vec.end();

        while (itr != end) {
            if (*itr == f) {
                m_vec.erase(itr);
                break;
            }
            ++itr;
        }

        return *this;
    }

    template <class TResult, class... TArgs>
    constexpr Containers::ArrayView<
        typename Delegate<TResult, TArgs...>::FunctionType
    >
    Delegate<TResult, TArgs...>::InvocationList() const noexcept
    {
        return { m_vec.size(), m_vec.data() };
    }

    template <class TResult, class... TArgs>
    TResult Delegate<TResult, TArgs...>::Invoke(
        TArgs&&... args
    )
    {
        if constexpr (::std::same_as<TResult, void>) {
            for (auto&& f : m_vec) {
                f.operator()(::std::forward<TArgs>(args)...);
            }
        }
        else {
            TResult result{};

            for (auto&& f : m_vec) {
                result = f.operator()(::std::forward<TArgs>(args)...);
            }

            return result;
        }
    }
}

#endif //!KLIB_SIGNALS_DELEGATE_H