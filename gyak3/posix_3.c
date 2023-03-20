#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_THREADS 30
#define RANGE 100

int counts[NUM_THREADS];

bool is_prime(int n) {
    if (n <= 1)
        return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

void* calculate_primes(void* args) {
    int start = *((int*)args);
    int end = start + RANGE - 1;
    int count = 0;

    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            // printf("%d ", i);
            count++;
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        if (counts[i] == 0) {
            counts[i] = count;
            break;
        }
    }
    printf("Start: %d, end: %d ,count : %d\n",start,end,count);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i * RANGE;
        pthread_create(&threads[i], NULL, calculate_primes, (void*)&thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // print the counts
    // for (int i = 0; i < NUM_THREADS; i++)
    // {
    //     printf("Count: %d\n", counts[i]);
    // }
    

    return 0;
}
