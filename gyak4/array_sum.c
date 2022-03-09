#include <stdio.h>
#include <pthread.h>
#define SIZE 10
#define NUM_THREADS 3

void *sum(void *threadid, void *array){
    int *tid = threadid;
    int sum=0;
    int *arra = array;
    for(int i=tid;i<SIZE;i+=3){
        sum += arra[i];
    }
    pthread_exit(sum);
}

int main(){
    int array[SIZE];
    pthread_t threads[NUM_THREADS];
    int rc;
    int osszeg=0;
    for(int i=0;i<NUM_THREADS;i++){
        rc = pthread_create(&threads[i], NULL, sum, (void *)i);
        if(rc){
            printf("Error");
        }
    }
    int ret;
    for(int j=0;j<NUM_THREADS;j++){
        pthread_join(threads[j], &ret);
        osszeg += ret;

    }




    return 0;
}