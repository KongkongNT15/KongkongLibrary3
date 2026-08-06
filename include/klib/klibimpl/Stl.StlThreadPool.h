#ifndef KLIB_STD_STLTHREADPOOL_H
#define KLIB_STD_STLTHREADPOOL_H

#include "base.h"

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace klib::Std
{
    class StlThreadPool final {
    private:
        ::std::vector<::std::thread> m_workers;
        ::std::vector<::std::thread::id> m_zombies; // 終了したスレッドのIDを格納するゴミ箱ｳﾋｮｯ

        ::std::queue<std::function<void()>> m_tasks;

        ::std::mutex m_mutex;
        ::std::condition_variable m_cv;

        ::std::atomic<size_t> m_completed_tasks{0};
        ::std::atomic<size_t> m_active_threads{0}; // 現在稼働中のワーカー数ｳﾋｮｯ
        size_t m_min_threads;                    // これ以上は減らさない最低限の数ｳﾋｮｯ

        ::std::thread m_monitor_thread;
        ::std::atomic<bool> m_stop{false};

        // 終了したスレッドを回収してOSにリソースを返す関数ｳﾋｮｯ
        void reap_zombies();

        void worker_loop();

        void monitor_loop();

    public:
        explicit StlThreadPool(
            size_t initial_threads
        );

        ~StlThreadPool();

        void Enqueue(
            ::std::function<void()> task
        );

    };
}

#endif //!KLIB_STD_STLTHREADPOOL_H