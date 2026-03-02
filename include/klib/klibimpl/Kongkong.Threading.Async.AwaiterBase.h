#ifndef KLIB_KONGKONG_THRAEDING_ASYNC_TAWAITERBASE_H
#define KLIB_KONGKONG_THRAEDING_ASYNC_TAWAITERBASE_H

#include "base.h"
#include "Kongkong.Threading.Async.TaskStatus.h"
#include "Kongkong.Threading.Async.AwaiterBasePromise.h"

#include <coroutine>

namespace klib::Kongkong::Threading::Async
{
    struct AwaiterBase {
        template <class T>
        friend struct AsyncOperation;

        friend AwaiterBasePromise;
        private:

        ::std::coroutine_handle<> m_hOther;
        TaskStatus m_status;

        constexpr AwaiterBase() noexcept;

        AwaiterBase(AwaiterBase const&) = default;
        AwaiterBase(AwaiterBase&&) = default;

        AwaiterBase& operator=(AwaiterBase const&) = default;
        AwaiterBase& operator=(AwaiterBase&&) = default;

        template <class TPromise>
        static void do_destruct(
            TaskStatus status,
            ::std::coroutine_handle<TPromise>& handle
        ) noexcept;

        template <class TPromise>
        static void do_move(
            TaskStatus status,
            ::std::coroutine_handle<TPromise>& hThis,
            ::std::coroutine_handle<TPromise>& hOther
        ) noexcept;

        public:

        constexpr bool await_ready() const noexcept;

        constexpr void await_suspend(
            std::coroutine_handle<> h
        );

        void Wait() const noexcept;
    };
}

namespace klib::Kongkong::Threading::Async
{
    constexpr AwaiterBase::AwaiterBase() noexcept
        : m_hOther(nullptr)
        , m_status(TaskStatus::Running)
    {
    }

    template <class TPromise>
    void AwaiterBase::do_destruct(
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
    void AwaiterBase::do_move(
        TaskStatus status,
        ::std::coroutine_handle<TPromise>& hThis,
        ::std::coroutine_handle<TPromise>& hOther
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

        hOther = nullptr;
    }

    constexpr bool
    AwaiterBase::await_ready() const noexcept
    {
        return false;
    }

    void AwaiterBase::await_suspend(
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

#endif //!KLIB_KONGKONG_THRAEDING_ASYNC_TAWAITERBASE_H