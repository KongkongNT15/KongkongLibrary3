#ifndef KLIB_SIGNALS_DELEGATE_H
#define KLIB_SIGNALS_DELEGATE_H

#include "base.h"
#include "Containers.ArrayView.h"
#include "Signals.Event.h"

namespace klib::Signals
{
    template <class TResult, class... TArgs>
    class Delegate<TResult(TArgs...)> final : public Event<TResult, TArgs...> {
        public:

        using Base = typename Event<TResult, TArgs...>;
        using FunctionType = typename Base::FunctionType;

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
        constexpr Base& Event() noexcept;

        [[nodiscard]]
        constexpr Base const& Event() const noexcept;

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
    Delegate<TResult(TArgs...)>&
    Delegate<TResult(TArgs...)>::operator+=(
        FunctionType const& f
    )
    {
        Base::operator+=(f);
        return *this;
    }

    template <class TResult, class... TArgs>
    Delegate<TResult(TArgs...)>&
    Delegate<TResult(TArgs...)>::operator+=(
        FunctionType&& f
    )
    {
        Base::operator+=(::std::move(f));
        return *this;
    }

    template <class TResult, class... TArgs>
    Delegate<TResult(TArgs...)>&
    Delegate<TResult(TArgs...)>::operator-=(
        FunctionType const& f
    )
    {
        Base::operator-=(f);
        return *this;
    }

    template <class TResult, class... TArgs>
    constexpr Delegate<TResult(TArgs...)>::Base&
    Delegate<TResult(TArgs...)>::Event() noexcept
    {
        return *this;
    }

    template <class TResult, class... TArgs>
    constexpr Delegate<TResult(TArgs...)>::Base const&
    Delegate<TResult(TArgs...)>::Event() const noexcept
    {
        return *this;
    }

    template <class TResult, class... TArgs>
    constexpr Containers::ArrayView<
        typename Delegate<TResult(TArgs...)>::FunctionType
    >
    Delegate<TResult(TArgs...)>::InvocationList() const noexcept
    {
        return { this->m_vec.size(), this->m_vec.data() };
    }

    template <class TResult, class... TArgs>
    TResult Delegate<TResult(TArgs...)>::Invoke(
        TArgs&&... args
    )
    {
        if constexpr (::std::same_as<TResult, void>) {
            for (auto&& f : this->m_vec) {
                f.operator()(::std::forward<TArgs>(args)...);
            }
        }
        else {
            TResult result{};

            for (auto&& f : this->m_vec) {
                result = f.operator()(::std::forward<TArgs>(args)...);
            }

            return result;
        }
    }
}

#endif //!KLIB_SIGNALS_DELEGATE_H