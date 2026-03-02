#ifndef KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCOPERATION_H
#define KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCOPERATION_H

#include "base.h"
#include "Kongkong.Threading.Async.AwaiterBase.h"

namespace klib::Kongkong::Threading::Async
{
    template <class T>
    struct AsyncOperation final : public AwaiterBase {
        public:
        using ResultType = typename ::std::remove_cv_t<T>;

        struct promise_type final : public AwaiterBase::promise_type_base {

            AsyncOperation get_return_object();
            void return_value(ResultType const& value);
            void return_value(T&& value) noexcept { if (this->__action != nullptr) static_cast<AsyncOperation*>(this->__action)->_obj.SetValue(::std::move(value)); }
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
}

#endif //!KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCOPERATION_H