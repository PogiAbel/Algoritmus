#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int n = argc - 1;
    int *x = (int*)malloc(n * sizeof(int));
    int *y = (int*)malloc(n * sizeof(int));
    int i, j;

    // Initialize input array x
    for (i = 0; i < n; i++) {
        x[i] = atoi(argv[i+1]);
    }

    // Perform EREW prefix computation
    for (i = 0; i < n; i++) {
        y[i] = x[i];
    }

    int t = 1;
    while (t < n) {
        #pragma omp parallel for private(i) shared(y, t)
        for (i = t; i < n; i += 2*t) {
            y[i] += y[i-t];
        }
        t *= 2;
    }

    // Print output array y
    for (i = 0; i < n; i++) {
        printf("%d ", y[i]);
    }
    printf("\n");

    free(x);
    free(y);
    return 0;
}
