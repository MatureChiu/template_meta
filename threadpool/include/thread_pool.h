#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>
#include <iostream>

#include "safe_queue.h"

class ThreadPool
{
    private :
        bool mDeinit;
        std::vector<std::thread> m_threads;
        SafeQueue<std::function<void()>> work_q;
        std::mutex m_cond_mutex;
        std::condition_variable m_cond_lock;

    private :
        class ThreadWorker {
            private :
                int m_id;
                ThreadPool *pool;

            public :
                ThreadWorker () = default;
                ~ThreadWorker () = default;

                ThreadWorker (ThreadPool *p, const int id)
                    : pool(p), m_id(id) {};

                void operator ()();

        }; // ThreadWorker

    public :
            ThreadPool () = default;
            ~ThreadPool () = default;
            ThreadPool (const int n_threads)
                : m_threads (std::vector<std::thread> (n_threads) ), mDeinit (false) {};

            ThreadPool& operator= (ThreadPool&) = delete;

            void init ();
            void deinit ();

            template <typename F, typename...Args>
            auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
                
                std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
                auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func); 

                std::function<void()> wrapper_func = [task_ptr]() {
                    (*task_ptr)(); 
                };

                work_q.enqueue (wrapper_func);

                m_cond_lock.notify_one();

                return task_ptr->get_future();
            };
};

#endif
