#ifndef TENSOR_H
#define TENSOR_H

#include "arena.h"

typedef struct {
  float *data;
  int *shape;
  int ndim;
  int size;
} Tensor;

Tensor *tensor_create(Arena *arena, int rows, int cols);

void tensor_fill(Tensor *tensor, float value);

void tensor_print(Tensor *tensor);

Tensor *tensor_matmul(Arena *arena, Tensor *A, Tensor *B);

#endif // !TENSOR_H
