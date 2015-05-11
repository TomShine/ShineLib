#include <iostream>

#include <vector>
#include "ThreadPool.h"

class Request
{
public:
    void process()
    {
        printf("id = %d\n", id);
    }

    int id;
};


int main(int argc,char**argv)
{
    shine::ThreadPool<Request> threadpool(4, 100);

    Request* rquest = NULL;
    for(int i=0;i <100;i++)
    {
        rquest = new Request;
        rquest->id  = i;
        threadpool.append(rquest);
    }

    return 0;
}
