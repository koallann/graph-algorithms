#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

struct _heap {
    int capacity;
    int size;
    int *data;
};

/* private functions */

int get_parent_index(int i);

int get_left_index(int i);

int get_right_index(int i);

void min_heapify(heap_t *queue, int i);

int swap(int *a, int *b);

/* implementations */

heap_t* heap_create(int capacity) {
    heap_t *heap = (heap_t*) malloc(sizeof(heap_t));
    int *data = (int*) malloc(sizeof(int) * (capacity+1)); // 1-based indexing
    
    heap->capacity = capacity;
    heap->size = 0;
    heap->data = data;

    return heap;
}

void heap_enqueue(heap_t *heap, int item) {
    if (heap->size >= heap->capacity) {
        printf("Heap overflow!");
        exit(-1);
    }

    heap->data[++heap->size] = item;

    int key_index = heap->size;
    int parent_index = get_parent_index(heap->size);

    while (parent_index >= 1 && heap->data[key_index] < heap->data[parent_index]) {
        swap(&heap->data[key_index], &heap->data[parent_index]);
        key_index = parent_index;
        parent_index = get_parent_index(key_index);
    }
}

int heap_dequeue(heap_t *heap) {
    if (heap->size <= 0) {
        printf("Heap underflow!");
        exit(-1);
    }

    int item = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    min_heapify(heap, 1);

    return item;
}

int get_parent_index(int i) {
    return i/2;
}

int get_left_index(int i) {
    return 2*i;
}

int get_right_index(int i) {
    return 2*i + 1;
}

void min_heapify(heap_t *heap, int i) {
    int smallest;
    int left_index = get_left_index(i);
    int right_index = get_right_index(i);
    
    if (left_index <= heap->size && heap->data[left_index] < heap->data[i]) {
        smallest = left_index;
    } else {
        smallest = i;
    }
    
    if (right_index <= heap->size && heap->data[right_index] < heap->data[smallest]) {
        smallest = right_index;
    }
    
    if (heap->data[i] != heap->data[smallest]) {
        swap(&heap->data[i], &heap->data[smallest]);
        min_heapify(heap, smallest);
    }
}

int swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}
