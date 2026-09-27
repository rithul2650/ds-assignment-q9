/**
 * @file k_way_merge.c
 * @brief Implementation of K-Way Merge using Min Heap Data Structure
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int list_index;
    int element_index;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    int size;
    int capacity;
    long long comparisons;
    long long element_moves;
} MinHeap;

MinHeap* create_min_heap(int capacity) {
    MinHeap *heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->nodes = (HeapNode*) malloc(sizeof(HeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    heap->comparisons = 0;
    heap->element_moves = 0;
    return heap;
}

void free_min_heap(MinHeap *heap) {
    if (heap) {
        if (heap->nodes) free(heap->nodes);
        free(heap);
    }
}

void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size) {
        heap->comparisons++;
        if (heap->nodes[left].value < heap->nodes[smallest].value) {
            smallest = left;
        }
    }

    if (right < heap->size) {
        heap->comparisons++;
        if (heap->nodes[right].value < heap->nodes[smallest].value) {
            smallest = right;
        }
    }

    if (smallest != idx) {
        swap_nodes(&heap->nodes[idx], &heap->nodes[smallest]);
        heap->element_moves += 3; // 3 moves for swap
        min_heapify(heap, smallest);
    }
}

void k_way_merge_min_heap(int **lists, int k, int *sizes, int total_elements, int *output, long long *out_comp, long long *out_moves) {
    MinHeap *heap = create_min_heap(k);

    // Initialize Heap with 1st element of each non-empty list
    for (int i = 0; i < k; i++) {
        if (sizes[i] > 0) {
            heap->nodes[heap->size].value = lists[i][0];
            heap->nodes[heap->size].list_index = i;
            heap->nodes[heap->size].element_index = 0;
            heap->size++;
            heap->element_moves++;
        }
    }

    // Build min heap
    for (int i = (heap->size - 2) / 2; i >= 0; i--) {
        min_heapify(heap, i);
    }

    int out_idx = 0;

    while (heap->size > 0) {
        HeapNode root = heap->nodes[0];
        output[out_idx++] = root.value;
        heap->element_moves++;

        int l_idx = root.list_index;
        int next_idx = root.element_index + 1;

        if (next_idx < sizes[l_idx]) {
            heap->nodes[0].value = lists[l_idx][next_idx];
            heap->nodes[0].list_index = l_idx;
            heap->nodes[0].element_index = next_idx;
            heap->element_moves++;
            min_heapify(heap, 0);
        } else {
            heap->nodes[0] = heap->nodes[heap->size - 1];
            heap->size--;
            heap->element_moves++;
            if (heap->size > 0) {
                min_heapify(heap, 0);
            }
        }
    }

    *out_comp = heap->comparisons;
    *out_moves = heap->element_moves;

    free_min_heap(heap);
}
