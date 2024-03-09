#include "ex1.h"
#include <omp.h>

void v_add_naive(double *x, double *y, double *z) {
#pragma omp parallel
    {
        for (int i = 0; i < ARRAY_SIZE; i++)
            z[i] = x[i] + y[i];
    }
}

// Adjacent Method
void v_add_optimized_adjacent(double *x, double *y, double *z) {
// TODO: Implement this function
// Do NOT use the `for` directive here!
#pragma omp parallel
    {
        int num = omp_get_num_threads();
        int id = omp_get_thread_num();
        for (int i = id; i < ARRAY_SIZE; i += num)
            z[i] = x[i] + y[i];
    }
}

// Chunks Method
void v_add_optimized_chunks(double *x, double *y, double *z) {
// TODO: Implement this function
// Do NOT use the `for` directive here!
#pragma omp parallel
    {
        int num = omp_get_num_threads();
        int chunk_size = (ARRAY_SIZE + num - 1) / num;
        int id = omp_get_thread_num();
        for (int i = id * chunk_size;
             i < (id + 1) * chunk_size && i < ARRAY_SIZE; ++i)
            z[i] = x[i] + y[i];
    }
}
