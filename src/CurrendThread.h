#ifndef __CURREND_THREAD_H_
#define __CURREND_THREAD_H_

#include <stdint.h>

namespace shine
{
namespace CurrentThread
{
    // internal
    extern __thread int t_cachedTid;
    extern __thread char t_tidString[32];
    extern __thread int t_tidStringLength;
    extern __thread const char* t_threadName;
    void cachedTid();

    inline int tid()
    {
//        if (__builtin_expect(t_cachedTid == 0, 0))
//        {
//            cachedTid();
//        }

//        return t_cachedTid;
    }

    inline const char* tidString() // for Logging
    {
        return t_tidString;
    }

    inline int tidStringLength() // for Logging
    {
        return t_tidStringLength;
    }

    inline const char* name()
    {
        return t_threadName;
    }

    bool isMainThread();

    void sleepUsec(int64_t usec);
}
}

#endif // __CURREND_THREAD_H_

