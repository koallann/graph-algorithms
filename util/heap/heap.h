#ifndef HEAP_H
#define HEAP_H

typedef struct _heap heap_t;

heap_t* heap_create(int capacity);

void heap_enqueue(heap_t *heap, int item);

int heap_dequeue(heap_t *heap);

#endif
