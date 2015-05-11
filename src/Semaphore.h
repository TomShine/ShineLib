#ifndef SEMAPHORE
#define SEMAPHORE

#include <semaphore.h>

#ifdef CHECK_PTHREAD_RETURN_VALUE

#ifdef NDEBUG
__BEGIN_DECLS
extern void __assert_perror_fail (int errnum,
                                  const char *file,
                                  unsigned int line,
                                  const char *function)
        __THROW __attribute__ ((__noreturn__));
__END_DECLS
#endif

#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                               if (__builtin_expect(errnum != 0, 0))    \
                      __assert_perror_fail (errnum, __FILE__, __LINE__, __func__);})

#else  // CHECK_PTHREAD_RETURN_VALUE

#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);  \
                     assert(errnum == 0); (void) errnum;})

#endif // CHECK_PTHREAD_RETURN_VALUE

namespace shine
{

class Semaphore
{
public:
    Semaphore()
    {
        MCHECK(sem_init(&sem_, 0, 0));
    }

    ~Semaphore()
    {
        MCHECK(sem_destroy(&sem_));
    }

    bool wait()
    {
        return sem_wait(&sem_) == 0;
    }

    bool post()
    {
        return sem_post(&sem_) == 0;
    }

private:
    sem_t sem_;
};

}

#endif // SEMAPHORE

