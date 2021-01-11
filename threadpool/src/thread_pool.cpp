# include "thread_pool.h"
#include <iostream>

void ThreadPool::ThreadWorker::operator()() {
    std::function<void()> func;
    bool dequeued;
    while (!pool->mDeinit) {
        std::unique_lock<std::mutex> lock (pool->m_cond_mutex);

        if (pool->work_q.empty () ) {
            pool->m_cond_lock.wait (lock);
        }
        dequeued = pool->work_q.dequeue (func);

        if (dequeued) {
            func ();
        }
    }
}

void ThreadPool::init () {
    for (int i = 0; i < m_threads.size (); ++i) {
        m_threads[i] = std::thread (ThreadWorker (this, i) );
    }
}

void ThreadPool::deinit () {
    mDeinit = true;
    m_cond_lock.notify_all ();

#if 1  /* range based for loop */
    for (auto &it : m_threads ) {
        if (it.joinable () ) {
            it.join ();
        }
    }
#else
    for (int i = 0; i < m_threads.size (); ++i) {
        if (m_threads[i].joinable ()) {
            m_threads[i].join ();
        }
    }
#endif

}

