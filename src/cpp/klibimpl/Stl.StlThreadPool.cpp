namespace klib::Std
{
    StlThreadPool::StlThreadPool(
        size_t initial_threads
    )
        : m_min_threads(initial_threads)// 初期スレッド数を下限値とするｳﾋｮｯ
    {
        m_active_threads.store(initial_threads, std::memory_order_relaxed);

        for (size_t i = 0; i < initial_threads; ++i) {
            m_workers.emplace_back(&StlThreadPool::worker_loop, this);
        }

        m_monitor_thread = ::std::thread(&StlThreadPool::monitor_loop, this);
    }

    StlThreadPool::~StlThreadPool()
    {
        m_stop.store(true, std::memory_order_relaxed);
        m_cv.notify_all();

        if (m_monitor_thread.joinable()) {
            m_monitor_thread.join();
        }

        reap_zombies(); // 最後に残ったゾンビも確実に回収するｳﾋｮｯ

        for (std::thread& worker : m_workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    void StlThreadPool::monitor_loop()
    {
        size_t last_completed = 0;

        while (!m_stop.load(std::memory_order_relaxed)) {
            ::std::this_thread::sleep_for(std::chrono::milliseconds(500));

            if (m_stop.load(std::memory_order_relaxed)) break;

            // 1. 定期的にゾンビ化したスレッドの回収（join）を行うｳﾋｮｯ
            reap_zombies();

            // 2. 飢餓（Starvation）のチェックｳﾋｮｯ
            size_t current_completed = m_completed_tasks.load(std::memory_order_relaxed);

            bool has_tasks;
            {
                ::std::lock_guard<std::mutex> lock(m_mutex);
                has_tasks = !m_tasks.empty();
            }

            if (has_tasks && current_completed == last_completed) {
                ::std::lock_guard<std::mutex> lock(m_mutex);
                
                m_workers.emplace_back(&StlThreadPool::worker_loop, this);
                m_active_threads.fetch_add(1, ::std::memory_order_relaxed);

            }
            last_completed = current_completed;
        }
    }

    void StlThreadPool::reap_zombies()
    {
        std::vector<std::thread> to_join;

        {
            ::std::lock_guard<std::mutex> lock(m_mutex);
            if (m_zombies.empty()) return;

            for (auto zid : m_zombies) {
                // IDが一致するスレッドを稼働リストから探し出すｳﾋｮｯ
                auto itr = ::std::find_if(
                    m_workers.begin(),
                    m_workers.end(),
                    [zid](const std::thread& t) { return t.get_id() == zid; }
                );

                if (itr != m_workers.end()) {
                    // ローカル配列にムーブして、稼働リストからは削除するｳﾋｮｯ
                    to_join.push_back(std::move(*itr));
                    m_workers.erase(itr);
                }
            }

            m_zombies.clear();
        }

        // ミューテックスを外した安全な状態でjoinする（他スレッドをブロックしないため）ｳﾋｮｯ
        for (auto& t : to_join) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    void StlThreadPool::worker_loop()
    {
       while (true) {

            ::std::function<void()> task;

            {
                ::std::unique_lock<std::mutex> lock(m_mutex);
                
                // 普通のwaitではなく、15秒のタイムアウト付きで待機するｳﾋｮｯ
                bool success = m_cv.wait_for(
                    lock,
                    ::std::chrono::seconds(15),
                    [this] {
                        return m_stop || !m_tasks.empty();
                    }
                );

                if (m_stop && m_tasks.empty()) {
                    return;
                }

                // 15秒間シグナルが来なかった（暇だった）場合の処理ｳﾋｮｯ
                if (!success) {
                    // 現在のスレッド数が最低数（min_threads）より多い場合のみ終了するｳﾋｮｯ
                    if (m_active_threads.load(::std::memory_order_relaxed) > m_min_threads) {

                        m_active_threads.fetch_sub(1, ::std::memory_order_relaxed);
                        m_zombies.push_back(::std::this_thread::get_id());
                        
                        return; // ループを抜けて自発的にスレッドを終了するｳﾋｮｯ
                    }
                    // 最低数以下の場合は、仕事がなくても死なずに待機を続けるｳﾋｮｯ
                    continue;
                }

                task = ::std::move(m_tasks.front());
                m_tasks.pop();
            }

            task();

            m_completed_tasks.fetch_add(1, std::memory_order_relaxed);
        }

    }

    void StlThreadPool::Enqueue(
        ::std::function<void()> task
    )
    {
        {
            ::std::lock_guard<::std::mutex> lock(m_mutex);
            m_tasks.push(::std::move(task));
        }

        m_cv.notify_one();
    }
}