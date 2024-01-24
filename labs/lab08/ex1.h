
#ifndef EX1_H
#define EX1_H

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REPEAT 60
#define BUF_SIZE 8192

#define ARRAY_SIZE 5000000

void v_add_naive(double* x, double* y, double* z);
void v_add_optimized_adjacent(double* x, double* y, double* z);
void v_add_optimized_chunks(double* x, double* y, double* z);
#endif
