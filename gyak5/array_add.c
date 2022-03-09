#include <stdio.h>
#include <omp.h>
#include <time.h>
#define SIZE 10
int main(){
    int array[SIZE];
    int sum=0;
    int i;
    srand(time(NULL));
    for(int i=0;i<SIZE;i++){
        array[i]=rand();
        //printf("%d\n",array[i]);
    }
    #pragma omp parallel shared(sum,array) private(i)
    {
        #pragma omp for 
        {
        for(i=0;i<SIZE;i++){
            sum+=array[i];
            printf("%d\n",sum);
        }

        }   
    }
    

    return 0;
}