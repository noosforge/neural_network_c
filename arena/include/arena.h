#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct {
  unsigned char *buffer;
  size_t capacity;
  size_t offset; // this is the limit.
} Arena;

void *arena_init(size_t size);
void *arena_malloc(Arena *arena, size_t bytes);
void arena_reset(Arena *arena);
void arena_free(Arena *arena);

#endif // !ARENA_H
