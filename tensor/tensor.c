#include "arena.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float *data;
  int *shape;
  int ndim;
  int size;
} Tensor;

Tensor *tensor_create(Arena *arena, int rows, int cols) {
  // allocate the tensor to the heap, it must outlive the function
  Tensor *tensor = malloc(sizeof(Tensor));

  // from row/col -> size and ndim
  tensor->ndim = 2; // Matrix
  tensor->size = rows * cols;

  // set the shape
  // This goes to pointer arithmetic, where its (start_address
  // + (0 or 1)*sizeof(int))
  tensor->shape = arena_malloc(arena, sizeof(int) * tensor->ndim);
  tensor->shape[0] = rows;
  tensor->shape[1] = cols;

  // update the data
  tensor->data = arena_malloc(arena, sizeof(float) * tensor->size);

  return tensor;
}

void tensor_fill(Tensor *tensor, float value) {
  for (int i = 0; i < tensor->size; i++) {
    tensor->data[i] = value;
  }
}

void tensor_print(Tensor *tensor) {
  for (int i = 0; i < tensor->shape[0]; i++) {
    printf("[");
    for (int j = 0; j < tensor->shape[1]; j++) {
      printf("%f", tensor->data[(i * tensor->shape[1]) + j]);
      printf(" ");
    }
    printf("]\n");
  }
}

Tensor *tensor_matmul(Arena *arena, Tensor *A, Tensor *B) {
  // get the dimentions
  int rows_A = A->shape[0];
  int rows_B = B->shape[0];
  int cols_A = A->shape[1];
  int cols_B = B->shape[1];

  // create new_tensor
  Tensor *tensor_C = tensor_create(arena, rows_A, cols_B);

  for (int i = 0; i < rows_A; i++) {

    for (int j = 0; j < cols_B; j++) {
      float sum = 0.0;

      // cols_A and rows_B are simillar, we could use either.
      for (int k = 0; k < rows_B; k++) {
        float val_a = A->data[(i * cols_A) + k];
        float val_b = B->data[(k * cols_B) + j];

        sum += (val_a * val_b);
      }

      tensor_C->data[(i * tensor_C->shape[1]) + j] = sum;
    }
  }

  return tensor_C;
}
