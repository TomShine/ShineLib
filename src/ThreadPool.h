#ifndef TTHREADPOOL_H
#define TTHREADPOOL_H

#include <list>
#include <stdio.h>
#include <exception>

#include "Common.h"
#include "Mutex.h"
#include "Semaphore.h"

namespace shine 
{

template<typename T>
class ThreadPool
{
public:
    ThreadPool( int thread_number = 8, int max_requests = 10000 );
    ~ThreadPool();
    bool append( T* request );

private:
    static void* worker( void* arg );
    void run();

private:
    int threadNumber_;
    int maxRequests_;
    pthread_t* threads_;
    std::list< T* > workQueue_;
    MutexLock queueLocker_;
    Semaphore queueStat_;
    bool isStop_;
};

template<typename T>
shine::ThreadPool<T>::ThreadPool(int threadNumber, int maxRequests)
    : threadNumber_(threadNumber)
    , maxRequests_(maxRequests)
    , isStop_(false)
    , threads_( NULL)
{
    if( (threadNumber <= 0) || (maxRequests <= 0) )
    {
        throw std::exception();
    }

    threads_ = new pthread_t[threadNumber_];
    if(NULL == threads_)
    {
        throw std::exception();
    }

    for (int i = 0; i < threadNumber_; ++i)
    {
        printf("create the %dth thread\n", i);
        if(pthread_create(threads_ + i, NULL, worker, this) != 0 )
        {

            throw std::exception();
        }
        if( pthread_detach(threads_[i]))
        {
            SAFE_DELETE(threads_);
            throw std::exception();
        }
    }
}

template< typename T >
shine::ThreadPool<T>::~ThreadPool()
{
    SAFE_DELETE(threads_);
    isStop_ = true;
}

template< typename T >
bool shine::ThreadPool<T>::append( T* request )
{
    queueLocker_.lock();
    if (workQueue_.size() > maxRequests_)
    {
        queueLocker_.unlock();
        return false;
    }

    workQueue_.push_back( request );
    queueLocker_.unlock();
    queueStat_.post();
    return true;
}

template< typename T >
void* shine::ThreadPool<T>::worker( void* arg )
{
    ThreadPool* pool = ( ThreadPool* )arg;
    pool->run();
    return pool;
}

template<typename T>
void shine::ThreadPool<T>::run()
{
    while (!isStop_)
    {
        queueStat_.wait();
        queueLocker_.lock();
        if ( workQueue_.empty() )
        {
            queueLocker_.unlock();
            continue;
        }

        T* request = workQueue_.front();
        workQueue_.pop_front();
        queueLocker_.unlock();
        if ( ! request )
        {
            continue;
        }
        request->process();
    }
}

}

#endif // TTHREADPOOL_H
