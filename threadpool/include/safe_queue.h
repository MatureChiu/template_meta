#ifndef _SAFE_QUEUE_H_
#define _SAFE_QUEUE_H_

#include <iostream>
#include <queue>
#include <mutex>

template <typename T>
class SafeQueue
{
    private :
        std::queue<T> mQueue;
        std::mutex mMutex;

    public :

        bool empty () {
            std::unique_lock <std::mutex> lock (mMutex);
            return mQueue.empty ();
        };

        int size () {
            std::unique_lock <std::mutex> lock (mMutex);
            return mQueue.size ();
        };

        void enqueue (T& t) {
            std::unique_lock <std::mutex> lock (mMutex);
            mQueue.push (t);
        };

        bool dequeue (T& t) {
            std::unique_lock <std::mutex> lock (mMutex);

            if (mQueue.empty () ) {
                std::cout<<"Empty Queue"<<std::endl;
                return false;
            }
            t = std::move (mQueue.front () );
            mQueue.pop ();

            return true;
        };
}; // SafeQueue

#endif

