#ifndef KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCACTION_H
#define KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCACTION_H

#include "base.h"
#include "Kongkong.Threading.Async.AwaiterBase.h"
#include "Kongkong.Threading.Async.AwaiterBasePromise.h"

namespace klib::Kongkong::Threading::Async
{
    template <>
    struct AsyncOperation<void> : public AwaiterBase {
        public:

        using ResultType = void;

        struct promise_type : AwaiterBasePromise {
            AsyncOperation get_return_object();
            constexpr void return_void() noexcept;
        };

        private:

        using CHType = ::std::coroutine_handle<promise_type>;

        CHType m_handle;

        explicit AsyncOperation(
            promise_type& promise
        );

        public:

        constexpr AsyncOperation() noexcept;

        AsyncOperation(
            AsyncOperation const&
        ) = delete;

        AsyncOperation(
            AsyncOperation&& other
        ) noexcept;

        [[nodiscard]]
        static AsyncOperation DelayAsync(
            uint32_t milliSeconds
        ) noexcept;

        ~AsyncOperation();

        void await_resume() const;
    };
}

namespace klib::Kongkong::Threading::Async
{
    inline AsyncAction
    AsyncAction::promise_type::get_return_object()
    {
        return AsyncAction{ *this };
    }

    constexpr void
    AsyncAction::promise_type::return_void() noexcept
    {
    }

    inline AsyncAction::AsyncOperation(
        promise_type& promise
    )
        : m_handle(CHType::from_promise(promise))
    {
        promise.m_action = this;
    }

    constexpr AsyncAction::AsyncOperation() noexcept
        : m_handle(nullptr)
    {
    }

    inline AsyncAction::AsyncOperation(
        AsyncAction&& other
    ) noexcept
        : AwaiterBase(static_cast<AwaiterBase&&>(other))
        , m_handle(::std::exchange(other.m_handle, nullptr))
    {
        do_move(
            m_status,
            m_handle
        );
    }

    inline AsyncAction::~AsyncOperation()
    {
        do_destruct(
            m_status,
            m_handle
        );
    }

    inline void AsyncAction::await_resume() const
    {
        do_throw(m_status);
    }
}

#endif //!KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCACTION_H