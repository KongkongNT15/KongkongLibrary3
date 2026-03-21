#ifndef KLIB_KONGKONG_THRAEDING_THREADPOOL_H
#define KLIB_KONGKONG_THRAEDING_THREADPOOL_H

#include "base.h"
#include "Kongkong.Threading.Async.AsyncAction.h"

#if KLIB_ENV_WINDOWS
    #include <malloc.h>
#elif KLIB_COMPILER_APPLE_CLANG
    #include <dispatch/dispatch.h>
    #include <alloca.h>
#elif KLIB_ENV_UNIX
    #include <alloca.h>
#endif

#include <coroutine>
#include <thread>

namespace klib::Kongkong::Threading
{
    class ThreadPool final {
        private:

#if KLIB_COMPILER_APPLE_CLANG
        static ::dispatch_queue_t s_queue;
#endif

        public:

        KLIB_STATIC_CLASS(ThreadPool);

        template <class TIterator, class TPredicate>
        static void ParallelFor(
            TIterator begin,
            TIterator end,
            TPredicate pred
        );

        template <class TIterator, class TPredicate>
        static Async::AsyncAction ParallelForAsync(
            TIterator begin,
            TIterator end,
            TPredicate pred
        );

        template <class TPredicate>
        static Async::AsyncAction RunAsync(
            TPredicate pred
        );
    };
}

namespace klib::Kongkong::Threading
{
    template <class TIterator, class TPredicate>
    void ThreadPool::ParallelFor(
        TIterator begin,
        TIterator end,
        TPredicate pred
    )
    {
        uint32_t threadCount = ::std::thread::hardware_concurrency();

        
    }

    template <class TIterator, class TPredicate>
    Async::AsyncAction ThreadPool::ParallelForAsync(
        TIterator begin,
        TIterator end,
        TPredicate pred
    )
    {
        return RunAsync(
            [=]() {
                ParallelFor(
                    begin,
                    end,
                    pred
                )
            }
        );
    }

    template <class TPredicate>
    Async::AsyncAction ThreadPool::RunAsync(
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

        co_await awaiter{ nullptr, ::std::move(pred) };
#elif KLIB_COMPILER_APPLE_CLANG
        struct awaiter {
            TPredicate pred;

            constexpr bool await_ready() noexcept { return false; } // すぐには完了しない

            void await_suspend(::std::coroutine_handle<> h)
            {
                ::dispatch_async(
                    ThreadPool::s_queue,
                    ^() {
                        pred();
                        h.resume();
                    }
                );
            }

            constexpr void await_resume() noexcept {}
        };

        co_await awaiter{ ::std::move(pred) };
#elif KLIB_ENV_UNIX

#endif
    }
}

#endif //!KLIB_KONGKONG_THRAEDING_THREADPOOL_H