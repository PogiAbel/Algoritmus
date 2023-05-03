#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct {
    double *matrix;
    double *identity_matrix;
    int size;
    int thread_num;
    int num_threads;
} invert_args;

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

double* indentity_matrix(int n){
    // return indentity matrix with n*n size
    double* matrix = (double*)malloc(n*n*sizeof(double));
    for (int i = 0; i < n*n; i++)
    {
        if (i % (n+1) == 0)
        {
            matrix[i] = 1;
        }
        else
        {
            matrix[i] = 0;
        }
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

void *invert_worker(void *arg) {
    invert_args *args = (invert_args *)arg;
    double *matrix = args->matrix;
    double *identity_matrix = args->identity_matrix;
    int size = args->size;
    int thread_num = args->thread_num;
    int num_threads = args->num_threads;

    int i, j, k;
    for (k = 0; k < size; k++) {
        if (k % num_threads != thread_num) {
            continue;
    }
    int i, j, k;
    double pivot, temp;
    for (k = 0; k < size; k++) {
            if (k % num_threads != thread_num) {
            continue;
            }
            pivot = matrix[k*size + k];
            if (fabs(pivot) < 0.01) {
                // pivot is too small, matrix is singular
                return;
            }
            for (j = 0; j < size; j++) {
                matrix[k*size + j] /= pivot;
                identity_matrix[k*size + j] /= pivot;
            }
            for (i = 0; i < size; i++) {
                if (i == k) {
                    continue;
                }
                temp = matrix[i*size + k];
                for (j = 0; j < size; j++) {
                    matrix[i*size + j] -= temp * matrix[k*size + j];
                    identity_matrix[i*size + j] -= temp * identity_matrix[k*size + j];
                }
            }

        }

    }
    pthread_exit(NULL);
}

void matrix_inverse_parallel(double *matrix, double *identity_matrix, int size, int num_threads) {
    pthread_t *threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
    invert_args *args = (invert_args *)malloc(num_threads * sizeof(invert_args));
    int i;
    for (i = 0; i < num_threads; i++) {
        args[i].matrix = matrix;
        args[i].identity_matrix = identity_matrix;
        args[i].size = size;
        args[i].thread_num = i;
        args[i].num_threads = num_threads;
        pthread_create(&threads[i], NULL, invert_worker, &args[i]);
    }
    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    free(threads);
    free(args);
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    clock_t start, end;
    int n = argv[1] ? atoi(argv[1]) : 3;
    printf("n: %d\n", n);

    double* matrix = random_matrix(n);
    double* identity_matrix = indentity_matrix(n);

    int invertible = is_invertible(matrix, n);

    while (!invertible)
    {
        free(matrix);
        matrix = random_matrix(n);
        invertible = is_invertible(matrix, n);
    }
    printf("The matrix is invertible\n");
    
    
    start = clock();
    matrix_inverse_parallel(matrix, identity_matrix, n, 2);
    end = clock();

    printf("Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}