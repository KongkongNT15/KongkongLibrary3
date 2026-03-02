#ifndef KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCOPERATION_H
#define KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCOPERATION_H

#include "base.h"
#include "Kongkong.Threading.Async.AwaiterBase.h"
#include "Kongkong.LazyObject.h"

namespace klib::Kongkong::Threading::Async
{
    template <class T>
    struct AsyncOperation final : public AwaiterBase {
        public:
        using ResultType = typename ::std::remove_cv_t<T>;

        struct promise_type final : public AwaiterBase::promise_type_base {

            AsyncOperation get_return_object();

            void return_value(
                ResultType const& value
            );

            void return_value(
                ResultType&& value
            ) noexcept;
        };

        private:

        using CHType = ::std::coroutine_handle<promise_type>;

        CHType m_handle;
        LazyObject<T> m_obj;

        AsyncOperation(
            AsyncOperation&&
        ) noexcept;

        ~AsyncOperation();
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
        ResultType const& value
    )
    {
        if (this->m_action != nullptr) {
            static_cast<AsyncOperation*>(
                this->m_action
            )->m_obj.SetValue(value);
        }
    }

    template <class T>
    void
    AsyncOperation<T>::promise_type::return_value(
        ResultType&& value
    )
    {
        if (this->m_action != nullptr) {
            static_cast<AsyncOperation*>(
                this->m_action
            )->m_obj.SetValue(::std::move(value));
        }
    }
}

#endif //!KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCOPERATION_H