#include "ex2.h"
#include <omp.h>

double dotp_naive(double *x, double *y, int arr_size) {
    double global_sum = 0.0;
    for (int i = 0; i < arr_size; i++)
        global_sum += x[i] * y[i];
    return global_sum;
}

// Critical Keyword
double dotp_critical(double *x, double *y, int arr_size) {
    double global_sum = 0.0;
// TODO: Implement this function
// Use the critical keyword here!
#pragma omp parallel for
    {
        for (int i = 0; i < arr_size; ++i) {
#pragma omp critical
            { global_sum += x[i] * y[i]; }
        }
    }
    return global_sum;
}

// Reduction Keyword
double dotp_reduction(double *x, double *y, int arr_size) {
    double global_sum = 0.0;
// TODO: Implement this function
// Use the reduction keyword here!
#pragma omp parallel for reduction(+ : global_sum)
    {
        for (int i = 0; i < arr_size; ++i)
            global_sum += x[i] * y[i];
    }
    return global_sum;
}

// Manual Reduction
double dotp_manual_reduction(double *x, double *y, int arr_size) {
    double global_sum = 0.0;
// TODO: Implement this function
// Do NOT use the `reduction` directive here!
#pragma omp parallel
    {
        int num_threads = omp_get_num_threads();
        int id = omp_get_thread_num();
        double local_sum = 0.0;
        for (int i = id; i < arr_size; i += num_threads) {
            local_sum += x[i] * y[i];
        }
#pragma omp critical
        { global_sum += local_sum; }
    }
    return global_sum;
}
