#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned char *buffer;
  size_t capacity;
  size_t offset; // this is the limit.
} Arena;

void *arena_init(size_t size) {
  // allocate the size of the arena struct itself
  Arena *arena = malloc(sizeof(Arena));

  // allocate the buffer
  arena->buffer = malloc(size);
  arena->capacity = size;
  arena->offset = 0;

  return arena;
}

void *arena_malloc(Arena *arena, size_t bytes) {
  if (arena->offset + bytes > arena->capacity) {
    return NULL; // Out of Memory!
  }

  // the start of the block
  unsigned char *ptr = (unsigned char *)(arena->buffer + arena->offset);

  // move the offset
  arena->offset += bytes;

  return ptr;
}

void arena_reset(Arena *arena) { arena->offset = 0; }

void arena_free(Arena *arena) {
  free(arena->buffer);
  free(arena);
}
