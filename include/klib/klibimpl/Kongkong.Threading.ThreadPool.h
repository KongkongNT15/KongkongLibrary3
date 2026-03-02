#ifndef KLIB_KONGKONG_THRAEDING_THREADPOOL_H
#define KLIB_KONGKONG_THRAEDING_THREADPOOL_H

#include "base.h"

#if KLIB_ENV_WINDOWS

#elif KLIB_OBJECTIVE_C_ENABLED


#elif KLIB_ENV_UNIX

#endif

#include <coroutine>

namespace klib::Kongkong::Threading
{
    class ThreadPool final {
        private:

#if KLIB_OBJECTIVE_C_ENABLED

#endif

        public:

        KLIB_STATIC_CLASS(ThreadPool);

        template <class TPredicate>
        static AsyncAction RunAsync(
            TPredicate pred
        );
    };
}

namespace klib::Kongkong::Threading
{
    template <class TPredicate>
    AsyncAction ThreadPool::RunAsync(
        TPredicate pred
    )
    {
#if KLIB_ENV_WINDOWS
        struct awaiter {

            ::std::coroutine_handle<> m_h;
            TPredicate pred;

            static void CallBack(
                ::PTP_CALLBACK_INSTANCE,
                ::PVOID context,
                ::PTP_WORK
            )
            {
                awaiter* p = static_cast<awaiter*>(context);

                p->pred();
                p->m_h.resume();
            }

            constexpr bool await_ready() noexcept { return false; } // すぐには完了しない

            void await_suspend(::std::coroutine_handle<> h)
            {
                m_h = h;

                ::PTP_WORK work = ::CreateThreadpoolWork(
                    CallBack,
                    this,
                    nullptr
                );

                ::SubmitThreadpoolWork(work);

                ::CloseThreadpoolWork(work);
            }

            constexpr void await_resume() noexcept {}
        };

        co_await awaiter{ nullptr, pred };
#elif KLIB_OBJECTIVE_C_ENABLED

#elif KLIB_ENV_UNIX

#endif
    }
}

#endif //!KLIB_KONGKONG_THRAEDING_THREADPOOL_H