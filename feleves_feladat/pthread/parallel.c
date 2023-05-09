#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct thread_data{
    double *A;
    int n;
    int start_row;
    int end_row;
    int j;
} thread_data;

int random_number(){
    // return random intiger between 0 and 99
    return rand() % 100;
}

void print_matrix(double* matrix, int size){
    // print matrix
    for (int i = 0; i < size*size; i++)
    {
        printf("%f ", matrix[i]);
        if ((i+1) % size == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}

double* random_matrix(int n){
    // return random matrix with n*n size
    double* matrix = (double*)malloc(n*n*sizeof(double));
    for (int i = 0; i < n*n; i++)
    {
        matrix[i] = (double)random_number();
    }
    return matrix;
}

int is_invertible(double *matrix, int n) {
    double det = 1;
    double *temp = (double *)malloc(n * n * sizeof(double));
    memcpy(temp, matrix, n * n * sizeof(double));  // make a copy of the matrix
    int i, j, k;
    for (k = 0; k < n; k++) {
        int i_max = k;
        double max_val = fabs(*(temp + k * n + k));
        for (i = k + 1; i < n; i++) {
            double val = fabs(*(temp + i * n + k));
            if (val > max_val) {
                i_max = i;
                max_val = val;
            }
        }
        if (i_max != k) {  // swap rows
            det *= -1;
            for (j = k; j < n; j++) {
                double temp_val = *(temp + k * n + j);
                *(temp + k * n + j) = *(temp + i_max * n + j);
                *(temp + i_max * n + j) = temp_val;
            }
        }
        double pivot = *(temp + k * n + k);
        if (pivot == 0) {
            free(temp);
            return 0;  // matrix is not invertible
        }
        det *= pivot;
        for (j = k; j < n; j++) {
            *(temp + k * n + j) /= pivot;
        }
        for (i = k + 1; i < n; i++) {
            double factor = *(temp + i * n + k);
            for (j = k; j < n; j++) {
                *(temp + i * n + j) -= factor * *(temp + k * n + j);
            }
        }
    }
    free(temp);
    return det != 0;  // matrix is invertible if determinant is non-zero
}

void *subtract_rows(void *arg) {
    struct thread_data *data = (struct thread_data *) arg;
    double *A = data->A;
    int n = data->n;
    int start_row = data->start_row;
    int end_row = data->end_row;
    int j = data->j;
    int i, k;
    double factor;
    for (i = start_row; i < end_row; i++) {
        factor = A[i*n+j] / A[j*n+j];
        for (k = j; k < n; k++) {
            A[i*n+k] -= factor * A[j*n+k];
        }
    }
    pthread_exit(NULL);
}

void inplace_inverse(double* A, int n, int num_threads){
    int i,j,k,pivot;
    double temp;
    int rows_per_thread = (n-1) / num_threads + 1;

    for (j = 0; j < n; j++) {
        // Find pivot row
        pivot = j;
        for (i = j+1; i < n; i++) {
            if (fabs(A[i*n+j]) > fabs(A[pivot*n+j])) {
                pivot = i;
            }
        }
        if (pivot != j) {
            // Swap rows
            for (k = 0; k < n; k++) {
                temp = A[j*n+k];
                A[j*n+k] = A[pivot*n+k];
                A[pivot*n+k] = temp;
            }
        }
        // Subtract scaled pivot row from other rows
        pthread_t threads[num_threads];
        struct thread_data thread_data_array[num_threads];
        int thread_index = 0;
        for (i = j+1; i < n; i += rows_per_thread) {
            struct thread_data *data = &thread_data_array[thread_index];
            data->A = A;
            data->n = n;
            data->start_row = i;
            data->end_row = i + rows_per_thread;
            if (data->end_row > n) {
                data->end_row = n;
            }
            data->j = j;
            pthread_create(&threads[thread_index], NULL, subtract_rows, (void *) data);
            thread_index++;
        }
        for (i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
        }
    }
}

float main_function(int n, FILE* fp){
    clock_t start, end;

    // create invertible matrix
    double* matrix = random_matrix(n);

    int invertible = is_invertible(matrix, n);

    while (!invertible)
    {
        free(matrix);
        matrix = random_matrix(n);
        invertible = is_invertible(matrix, n);
    }
    
    // inverse matrix
    for (int  i = 5; i <= 50; i+=5)
    {
        start = clock();
        inplace_inverse(matrix, n, i);
        end = clock();
        fprintf(fp, "%d, %d, %f\n", n, i, (float)(end - start) / CLOCKS_PER_SEC);
    }
    

    return (float)(end - start) / CLOCKS_PER_SEC;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    FILE* fp = fopen("statics/data_parallel_bigger.txt", "w");

    for (int i = 500; i <= 2000; i+=500)
    {
        main_function(i, fp);
    }

    fclose(fp);
   
    return 0;
}