#include <stdio.h>
#include <windows.h>
#include <pthread.h>
#define NUM_THREADS 5

void *Slepp(void *threadid){
    long *tid = (long)threadid;
    int s = 4000;
    Sleep(s);
    printf("%ld Sleeping %d\n",tid, s);
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[NUM_THREADS];
    int rc;
    for(int i=0;i<NUM_THREADS;i++){
        rc = pthread_create(&threads[i], NULL, Slepp, (void *)i);
        if(rc){
            printf("Error");
            exit(EXIT_FAILURE);
        }
    }
    
    for(int j=0;j<NUM_THREADS;j++){
        pthread_join(threads[j], NULL);

    }
    printf("Sleeping 2000 ");
    Sleep(2000);

    return 0;
}