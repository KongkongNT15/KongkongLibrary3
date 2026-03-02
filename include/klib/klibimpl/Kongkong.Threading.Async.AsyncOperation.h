#ifndef KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCOPERATION_H
#define KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCOPERATION_H

#include "base.h"
#include "Kongkong.Threading.Async.AwaiterBase.h"
#include "Kongkong.Threading.Async.AwaiterBasePromise.h"
#include "Kongkong.LazyObject.h"

namespace klib::Kongkong::Threading::Async
{
    template <class T>
    struct AsyncOperation final : public AwaiterBase {
        public:
        using ResultType = typename ::std::remove_cvref_t<T>;

        struct promise_type final : public AwaiterBasePromise {

            AsyncOperation get_return_object();

            void return_value(
                ResultType value
            ) noexcept;
        };

        private:

        using CHType = ::std::coroutine_handle<promise_type>;

        CHType m_handle;
        LazyObject<T> m_obj;

        explicit AsyncOperation(
            promise_type& promise
        );

        public:

        AsyncOperation(
            AsyncOperation const&
        ) = delete;

        AsyncOperation(
            AsyncOperation&& other
        ) noexcept;

        ~AsyncOperation();

        AsyncOperation& operator=(
            AsyncOperation const&
        ) = delete;

        AsyncOperation& operator=(
            AsyncOperation&& other
        ) noexcept;

        ResultType await_resume();
    };
}

namespace klib::Kongkong::Threading::Async
{
    template <class T>
    AsyncOperation<T>
    AsyncOperation<T>::promise_type::get_return_object()
    {
        return AsyncOperation{ *this };
    }

    template <class T>
    void
    AsyncOperation<T>::promise_type::return_value(
        ResultType value
    )
    {
        if (this->m_action != nullptr) {
            static_cast<AsyncOperation*>(
                this->m_action
            )->m_obj.SetValue(::std::move(value));
        }
    }

    template <class T>
    AsyncOperation<T>::AsyncOperation(
        AsyncOperation<T>&& other
    ) noexcept
        : AwaiterBase(
            static_cast<AwaiterBase&&>(other)
        )
        , m_handle(::std::exchange(other.m_handle, nullptr))
        , m_obj(::std::move(other.m_obj))
    {
        this->do_move(
            this->m_status,
            m_handle
        );
    }

    template <class T>
    AsyncOperation<T>::AsyncOperation(
        promise_type& promise
    )
        : m_handle(CHType::from_promise(promise))
    {
        promise.m_action = this;
    }

    template <class T>
    AsyncOperation<T>::~AsyncOperation()
    {
        AwaiterBase::do_destruct(
            this->m_status,
            m_handle
        );
    }

    template <class T>
    AsyncOperation<T>& AsyncOperation<T>::operator=(
        AsyncOperation<T>&& other
    ) noexcept
    {
        do_destruct(
            this->m_status,
            m_handle
        );

        AwaiterBase::operator=(
            static_cast<AwaiterBase&&>(other)
        );

        m_handle = ::std::exchange(other.m_handle, nullptr);

        this->do_move(
            this->m_status,
            m_handle
        );

        return *this;
    }

    template <class T>
    typename AsyncOperation<T>::ResultType
    AsyncOperation<T>::await_resume()
    {
        this->do_throw(this->m_status);
        return ::std::move(m_obj.GetValueUnsafe());
    }
}

#endif //!KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCOPERATION_H