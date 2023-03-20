#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void *thread_func(void *arg)
{
    printf("Thread started, sleeping for 8 seconds...\n");
    sleep(8);
    printf("Thread finished sleeping.\n");
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret;
    clock_t start_time, end_time;

    printf("Main thread started.\n");

    start_time = clock();

    ret = pthread_create(&tid, NULL, thread_func, NULL);
    if (ret != 0) {
        printf("Failed to create thread.\n");
        return 1;
    }

    sleep(4);

    ret = pthread_join(tid, NULL);
    if (ret != 0) {
        printf("Failed to join thread.\n");
        return 1;
    }

    end_time = clock();

    printf("Main thread finished in %f seconds.\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
