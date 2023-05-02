#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

int random_number(){
    // return random intiger between 0 and 99
    return rand() % 100;
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

int inverse(double* matrix, double* identity_matrix, int size) {
    int i, j, k, max_row;
    double temp, max_val;

    // Copy the matrix to a temporary matrix
    double temp_matrix[size][2*size];
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            temp_matrix[i][j] = matrix[i*size+j];
        }
    }

    // Append the identity matrix to the right of the temporary matrix
    for (i = 0; i < size; i++) {
        for (j = size; j < 2*size; j++) {
            if (j == i+size) {
                temp_matrix[i][j] = 1.0;
            } else {
                temp_matrix[i][j] = 0.0;
            }
        }
    }

    // Perform row operations to transform the left side of the matrix into the identity matrix
    for (i = 0; i < size; i++) {
        // Partial pivoting: choose the row with the largest absolute value in the current column as the pivot row
        max_row = i;
        max_val = fabs(temp_matrix[i][i]);
        for (j = i+1; j < size; j++) {
            if (fabs(temp_matrix[j][i]) > max_val) {
                max_row = j;
                max_val = fabs(temp_matrix[j][i]);
            }
        }
        if (max_row != i) {
            for (j = i; j < 2*size; j++) {
                temp = temp_matrix[i][j];
                temp_matrix[i][j] = temp_matrix[max_row][j];
                temp_matrix[max_row][j] = temp;
            }
            for (j = 0; j < size; j++) {
                temp = identity_matrix[i*size+j];
                identity_matrix[i*size+j] = identity_matrix[max_row*size+j];
                identity_matrix[max_row*size+j] = temp;
            }
        }
        temp = temp_matrix[i][i];
        if (temp == 0.0) {
            printf("Error: Matrix is not invertible\n");
            return -1; // Matrix is not invertible
        }
        for (j = i; j < 2*size; j++) {
            temp_matrix[i][j] /= temp;
        }
        for (j = 0; j < size; j++) {
            if (i != j) {
                temp = temp_matrix[j][i];
                for (k = i; k < 2*size; k++) {
                    temp_matrix[j][k] -= temp_matrix[i][k] * temp;
                }
                for (k = 0; k < size; k++) {
                    identity_matrix[j*size+k] -= identity_matrix[i*size+k] * temp;
                }
            }
        }
    }

    // Copy the right side of the temporary matrix (the inverse matrix) to the identity matrix
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            identity_matrix[i*size+j] = temp_matrix[i][j+size];
        }
    }

    // Copy the left side of the temporary matrix (the identity matrix) to the input matrix
    // for (i = 0; i < size; i++) {
    //     for (j = 0; j < size; j++) {
    //         matrix[i*size+j] = temp_matrix[i][j];
    //     }
    // }

    return 0; // Success
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

int main()
{
    srand(time(NULL));
    int n = 3;
    double* matrix1 = random_matrix(n);
    print_matrix(matrix1, n);
    double* matrix2 = indentity_matrix(n);
    int invertible = is_invertible(matrix1, n);
    if(invertible){
        inverse(matrix1, matrix2, n);
        print_matrix(matrix1, n);
        print_matrix(matrix2, n);
    }
    else{
        printf("Matrix is not invertible\n");
    }

    return 0;
}
