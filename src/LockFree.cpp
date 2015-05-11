//#include <stdio.h>
//#include <unistd.h>
//#include <pthread.h>

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//bool isSuspend = false;

//void pthread_suspend() {
//    if (!isSuspend) {
//        pthread_mutex_lock(&mutex);
//        isSuspend = true;
//        printf("------pthread suspend------/n");
//        pthread_cond_signal(&cond);
//        pthread_mutex_unlock(&mutex);
//    } else {
//        printf("------!!!!pthread is suspended!!!------/n");
//    }
//}

//void pthread_resume() {
//    if (isSuspend) {
//        pthread_mutex_lock(&mutex);
//        isSuspend = false;
//        pthread_cond_signal(&cond);
//        printf("------pthread resume------/n");
//        pthread_mutex_unlock(&mutex);
//    }else{
//        printf("------!!!!pthread is resumed------/n");
//    }
//}

//void pthread_pause_location(void) {
//    pthread_mutex_lock(&mutex);

//    while (!isSuspend) {
//        pthread_cond_wait(&cond, &mutex);
//    }

//    call_back(NULL);
//    pthread_mutex_unlock(&mutex);
//}

//void* call_back(void* args) //工作线程函数
//{
//    if (!isSuspend) {
//        printf("working...\n");
//    } else {
//        printf("suspend...\n");
//    }

//    sleep(1);

//    return ((void*) 0);
//}

//void start_thread()
//{
//    pthread_t threadId;
//    pthread_create(&threadId, NULL, call_back, NULL);
//}

//int main()
//{
//    start_thread();

//    while (true) {
//        int c = getchar();
//        if (c == 's')
//            pthread_suspend();
//        if (c == 'r')
//            pthread_resume();
//        if (c =='c')
//            pthread_pause_location();
//    }

//    return 0;
//}
