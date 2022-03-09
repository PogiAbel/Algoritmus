#include <stdio.h>
#include <omp.h>

int main(){
    int n_threads, th_id;
    #pragma omp parallel private(th_id)
    {
        th_id = omp_get_thread_num();
        printf("Hello World form %d thread\n",th_id);
    }

    #pragma omp barrier
    if ( th_id == 0 ) {
      n_threads = omp_get_max_threads();
      printf("There are %d threads\n",n_threads);
    }



    return 0;
}