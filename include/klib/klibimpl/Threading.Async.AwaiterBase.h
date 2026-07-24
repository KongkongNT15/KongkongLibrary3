#ifndef KLIB_THRAEDING_ASYNC_TAWAITERBASE_H
#define KLIB_THRAEDING_ASYNC_TAWAITERBASE_H

#include "base.h"
#include "Threading.Async.TaskStatus.h"
#include "Threading.Async.AwaiterBasePromise.h"

#include <coroutine>

namespace klib::Threading::Async
{
    struct AwaiterBase {
        template <class T>
        friend struct AsyncOperation;

        friend AwaiterBasePromise;
        private:

        ::std::coroutine_handle<> m_hOther;
        TaskStatus m_status;

        consteval AwaiterBase() noexcept;

        AwaiterBase(AwaiterBase const&) = default;
        AwaiterBase(AwaiterBase&&) = default;

        AwaiterBase& operator=(AwaiterBase const&) = default;
        AwaiterBase& operator=(AwaiterBase&&) = default;

        template <class TPromise>
        static constexpr void do_destruct(
            TaskStatus status,
            ::std::coroutine_handle<TPromise>& handle
        ) noexcept;

        template <class TPromise>
        static constexpr void do_move(
            TaskStatus status,
            ::std::coroutine_handle<TPromise>& hThis
        ) noexcept;

        static void do_throw(
            TaskStatus status
        );

        public:

        constexpr bool await_ready() const noexcept;

        constexpr void await_suspend(
            std::coroutine_handle<> h
        );

        void Wait() const noexcept;
    };
}

namespace klib::Threading::Async
{
    consteval AwaiterBase::AwaiterBase() noexcept
        : m_hOther(nullptr)
        , m_status(TaskStatus::Running)
    {
    }

    template <class TPromise>
    constexpr void AwaiterBase::do_destruct(
        TaskStatus status,
        ::std::coroutine_handle<TPromise>& handle
    ) noexcept
    {
        if (handle == nullptr) return;
            
        switch (status) {
            case TaskStatus::Canceled:
            case TaskStatus::Completed:
            case TaskStatus::Faulted:
                break;

            default:
                handle.promise().m_action = nullptr;
                break;
        }
    }

    template <class TPromise>
    constexpr void AwaiterBase::do_move(
        TaskStatus status,
        ::std::coroutine_handle<TPromise>& hThis
    ) noexcept
    {
        switch (status) {
            case TaskStatus::Canceled:
            case TaskStatus::Completed:
            case TaskStatus::Faulted:
                break;

            default:
                hThis.promise().m_action = this;
                break;
        }
    }

    constexpr bool
    AwaiterBase::await_ready() const noexcept
    {
        return false;
    }

    constexpr void AwaiterBase::await_suspend(
        ::std::coroutine_handle<> h
    )
    {
        switch (m_status) {
            case TaskStatus::Canceled:
            case TaskStatus::Completed:
            case TaskStatus::Faulted:
                h.resume();
                break;
            default:
                m_hOther = h;
                break;

        }
    }
}

#endif //!KLIB_THRAEDING_ASYNC_TAWAITERBASE_H
