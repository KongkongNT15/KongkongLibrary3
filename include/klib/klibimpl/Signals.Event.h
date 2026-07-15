#ifndef KLIB_SIGNALS_EVENT_H
#define KLIB_SIGNALS_EVENT_H

#include "base.h"
#include "Containers.ArrayView.h"
#include "Functional.Function.h"

#include <vector>

namespace klib::Signals
{
    template <class TResult, class... TArgs>
    class Event {
        public:

        using FunctionType =
            typename Functional::Function<TResult(TArgs...)>;
        private:

        ::std::vector<FunctionType> m_vec;

        protected:

        Event() = default;
        Event(Event const&) = default;
        Event(Event&&) = default;

        Event& operator=(Event const&) = default;
        Event& operator=(Event&&) = default;

        public:

        using FunctionType =
            typename Functional::Function<TResult(TArgs...)>;

        Event& operator+=(
            FunctionType const& f
        );

        Event& operator+=(
            FunctionType&& f
        );

        Event& operator-=(
            FunctionType const& f
        );

        void Add(
            FunctionType const& f
        );

        void Add(
            FunctionType&& f
        );

        void Remove(
            FunctionType const& f
        );
    };
}

namespace klib::Signals
{
    template <class TResult, class... TArgs>
    Event<TResult, TArgs...>&
    Event<TResult, TArgs...>::operator+=(
        FunctionType const& f
    )
    {
        m_vec.push_back(f);
        return *this;
    }

    template <class TResult, class... TArgs>
    Event<TResult, TArgs...>&
    Event<TResult, TArgs...>::operator+=(
        FunctionType&& f
    )
    {
        m_vec.push_back(::std::move(f));
        return *this;
    }

    template <class TResult, class... TArgs>
    Event<TResult, TArgs...>&
    Event<TResult, TArgs...>::operator-=(
        FunctionType const& f
    )
    {
        Remove(f);

        return *this;
    }

    template <class TResult, class... TArgs>
    void Event<TResult, TArgs...>::Add(
        FunctionType const& f
    )
    {
        m_vec.push_back(f);
    }

    template <class TResult, class... TArgs>
    void Event<TResult, TArgs...>::Add(
        FunctionType&& f
    )
    {
        m_vec.push_back(::std::move(f));
    }

    template <class TResult, class... TArgs>
    void Event<TResult, TArgs...>::Remove(
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
        
    }
}

#endif //!KLIB_SIGNALS_EVENT_H