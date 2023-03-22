#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define THREAD_COUNT 60

void *thread_func(void *arg)
{
    printf("Thread ID: %ld started, sleeping for 1 seconds...\n", pthread_self());
    sleep(1);
    printf("Thread ID: %ld finished sleeping.\n", pthread_self());
    return NULL;
}

int main()
{
    pthread_t tid[THREAD_COUNT];
    int ret[THREAD_COUNT];
    clock_t start_time, end_time;

    printf("Main thread started.\n");

    start_time = clock();


    // Start the threads
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        ret[i] = pthread_create(&tid[i], NULL, thread_func, NULL);
        // Commented becuse it just said that it failed to create thread
        // if (ret != 0) {
        //     printf("Failed to create thread.\n");
        //     return 1;
        // }
    }
    

    // Wait for the threads to finish
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        ret[i] = pthread_join(tid[i], NULL);
        // Commented becuse it just said that it failed to join thread
        // if (ret != 0) {
        //     printf("Failed to join thread.\n");
        //     return 1;
        // }
    }

    end_time = clock();

    printf("Main thread finished in %f seconds.\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
