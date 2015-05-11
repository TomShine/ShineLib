#ifndef CONDITION_H
#define CONDITION_H

#include "noncopyable.h"
#include "Mutex.h"

#include <errno.h>
#include <time.h>
#include <pthread.h>

namespace shine
{

class Condition : noncopyable
{
public:
    explicit Condition(MutexLock& mutex)
        : mutex_(mutex)
    {
        MCHECK(pthread_cond_init(&pcond_, NULL));
    }

    ~Condition()
    {
        MCHECK(pthread_cond_destroy(&pcond_));
    }

    void wait()
    {
        MutexLock::UnassignGuard ug(mutex_);
        MCHECK(pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
    }

    void notify()
    {
        MCHECK(pthread_cond_signal(&pcond_));
    }

    void notifyAll()
    {
        MCHECK(pthread_cond_broadcast(&pcond_));
    }

    bool waitForSeconds(int seconds)
    {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += seconds;
        MutexLock::UnassignGuard ug(mutex_);
        return ETIMEDOUT == pthread_cond_timedwait(&pcond_, mutex_.getPthreadMutex(), &abstime);
    }

private:
    MutexLock &mutex_;
    pthread_cond_t pcond_;
};

}
#endif //CONDITION_H
