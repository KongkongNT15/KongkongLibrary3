#ifndef KLIB_KONGKONG_THRAEDING_ASYNC_TAWAITERPROMISE_H
#define KLIB_KONGKONG_THRAEDING_ASYNC_TAWAITERPROMISE_H

#include "base.h"
#include "Kongkong.Threading.Async.AwaiterBase.h"

#include <coroutine>

namespace klib::Kongkong::Threading::Async
{
    struct AwaiterBasePromise {
        constexpr AwaiterBasePromise() noexcept;

        constexpr ::std::suspend_never initial_suspend() noexcept;
        constexpr ::std::suspend_never final_suspend() noexcept;
        constexpr void unhandled_exception() noexcept;

        AwaiterBase* m_action;
    };
}

namespace klib::Kongkong::Threading::Async
{
    constexpr AwaiterBasePromise::AwaiterBasePromise() noexcept
        : m_action(nullptr)
    {
    }

    constexpr ::std::suspend_never
    AwaiterBasePromise::final_suspend() noexcept
    {
        if (m_action != nullptr) {
            m_action->m_status = TaskStatus::Completed;

            if (m_action->m_hOther != nullptr) m_action->m_hOther.resume();
        }

        return {};
    }

    constexpr ::std::suspend_never
    AwaiterBasePromise::initial_suspend() noexcept
    {
        return {};
    }

    constexpr void
    AwaiterBasePromise::unhandled_exception() noexcept
    {
        if (m_action != nullptr) m_action->m_status = TaskStatus::Faulted;
    }
}

#endif //!KLIB_KONGKONG_THRAEDING_ASYNC_TAWAITERPROMISE_H