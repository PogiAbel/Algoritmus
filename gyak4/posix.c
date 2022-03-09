#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#define NUM_THREADS 5

void *Hello(void *threadid){
    int *tid;
    tid = (int *)threadid;
    printf("Hello from %d\n",tid);
    pthread_exit(NULL);
    
}


int main(){
    pthread_t threads[NUM_THREADS];
    time_t t;
    srand(time(&t));
    
    int size = 10;
    int szamok[size];
    for(int i=0;i<size;i++){
        szamok[i]=rand();
    }

    //parhuzamossag
    int rc = pthread_create (&threads[0], NULL, Hello,(void *)0);
    if(rc){
        printf("Error");
    }
    pthread_join(threads[0],NULL);
    pthread_exit(NULL);

    return 0;
}
