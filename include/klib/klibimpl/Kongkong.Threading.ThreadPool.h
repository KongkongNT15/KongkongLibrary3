#ifndef KLIB_KONGKONG_THRAEDING_THREADPOOL_H
#define KLIB_KONGKONG_THRAEDING_THREADPOOL_H

#include "base.h"
#include "Kongkong.Ranges.IteratorHelper.h"
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
            TPredicate&& pred
        );

        template <class TIterator, class TPredicate>
        static Async::AsyncAction ParallelForAsync(
            TIterator begin,
            TIterator end,
            TPredicate&& pred
        );

        template <class TPredicate>
        static Async::AsyncAction RunAsync(
            TPredicate&& pred
        );
    };
}

namespace klib::Kongkong::Threading
{
    template <class TIterator, class TPredicate>
    void ThreadPool::ParallelFor(
        TIterator begin,
        TIterator end,
        TPredicate&& pred
    )
    {
        uint32_t threadCount = ::std::thread::hardware_concurrency();


    }

    template <class TIterator, class TPredicate>
    Async::AsyncAction ThreadPool::ParallelForAsync(
        TIterator begin,
        TIterator end,
        TPredicate&& pred
    )
    {
        struct fArgs {
            TIterator begin;
            TIterator end;
            TPredicate func;
            ::PTP_WORK work;
        };

        void (*func)(
            ::PTP_CALLBACK_INSTANCE,
            ::PVOID,
            ::PTP_WORK
        ) = [](
            ::PTP_CALLBACK_INSTANCE, 
            ::PVOID args,
            ::PTP_WORK
        )
        {
            fArgs fargs = static_cast<fArgs*>(args);

            while (fargs.begin != fargs.end) {
                fargs.func(
                    *fargs.begin
                );
                ++begin;
            }
        };

        uint32_t threadCount = ::std::thread::hardware_concurrency();

        ssize_t containerLength =
            Ranges::IteratorHelper::GetLengthUnsafe(begin, end);

        ssize_t listLength;

        if (threadCount > containerLength) listLength = containerLength;
        else listLength = threadCount;

        fArgs* stackAllocArray = static_cast<fArgs*>(
            ::alloca(sizeof(fArgs) * listLength)
        );

        ssize_t c = containerLength % listLength;
        ssize_t d = containerLength / listLength;

        auto addTask = [](fArgs* target, TIterator b, TIterator e) {
            new (target) fArgs{
                b,
                e,
                pred,
                ::CreateThreadpoolWork(func, target, nullptr)
            };
        };

        ssize_t stackArrayIndex = 0;
        TIterator itr = begin;

        // 全スレッドで同じ数だけ実行
        if (c == 0) {
            
            while (itr != end) {
                TIterator next = Ranges::IteratorHelper::Add(itr, d);

                addTask(
                    stackAllocArray + stackArrayIndex,
                    itr,
                    next
                );

                ++stackArrayIndex;
                itr = std::move(next);
            }
        }
        // ふぁ！？っく
        else {
            ssize_t n = d * (listLength * (d + 1) - containerLength);

            // 最初のほうのスレッドは少なめに実行
            for (
                TIterator e1 = Ranges::IteratorHelper::Add(begin, n);
                itr != e1;
                ++stackArrayIndex
            ) {
                TIterator next = Ranges::IteratorHelper::Add(itr, d);

                addTask(
                    stackAllocArray + stackArrayIndex,
                    itr,
                    next
                );

                itr = ::std::move(next);
            }

            // これ以降は多めに実行
            d++;

            for (; itr != end; ++stackArrayIndex) {
                TIterator next = Ranges::IteratorHelper::Add(itr, d);

                addTask(
                    stackAllocArray + stackArrayIndex,
                    itr,
                    next
                );

                itr = ::std::move(next);
            }
        }

        {
            fArgs* itr1 = stackAllocArray;
            fArgs* end1 = itr1 + listLength;

            while (itr1 != end1) {
                ::WaitForThreadpoolWorkCallbacks(itr1->work, FALSE);
                ::CloseThreadpoolWork(itr1->work);

                itr1->~fArgs();
            }
        }
    }

    template <class TPredicate>
    Async::AsyncAction ThreadPool::RunAsync(
        TPredicate&& pred
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

        co_await awaiter{ nullptr, ::std::forward(pred) };
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

        co_await awaiter{ ::std::forward(pred) };
#elif KLIB_ENV_UNIX

#endif
    }
}

#endif //!KLIB_KONGKONG_THRAEDING_THREADPOOL_H