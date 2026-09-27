#include <stdio.h>
#include <stdlib.h>

#define K 3
#define N1 4
#define N2 4
#define N3 4
#define TOTAL_N (N1 + N2 + N3)

typedef struct {
    int value;
    int list_index;
    int element_index;
} HeapNode;

typedef struct {
    HeapNode nodes[K];
    int size;
    long long comparisons;
    long long swaps;
    long long element_moves;
} MinHeap;

void swap_heap_nodes(HeapNode *a, HeapNode *b) {
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
        heap->swaps++;
        swap_heap_nodes(&heap->nodes[idx], &heap->nodes[smallest]);
        min_heapify(heap, smallest);
    }
}

void print_heap_state(MinHeap *heap, int step) {
    printf("Step %2d | Heap Size: %d | Nodes: [", step, heap->size);
    for (int i = 0; i < heap->size; i++) {
        printf("(Val: %2d, L%d[%d])%s", 
               heap->nodes[i].value, 
               heap->nodes[i].list_index + 1, 
               heap->nodes[i].element_index,
               (i == heap->size - 1) ? "" : ", ");
    }
    printf("]\n");
}

void k_way_merge_heap(int lists[K][4], int list_sizes[K], int output[TOTAL_N], MinHeap *heap_stats) {
    MinHeap heap;
    heap.size = 0;
    heap.comparisons = 0;
    heap.swaps = 0;
    heap.element_moves = 0;

    printf("======================================================================\n");
    printf("PART A: K-WAY MERGE USING MIN HEAP TRACE\n");
    printf("======================================================================\n");

    // Initialize Heap with 1st element of each non-empty list
    for (int i = 0; i < K; i++) {
        if (list_sizes[i] > 0) {
            heap.nodes[heap.size].value = lists[i][0];
            heap.nodes[heap.size].list_index = i;
            heap.nodes[heap.size].element_index = 0;
            heap.size++;
            heap.element_moves++;
        }
    }

    // Build min heap bottom-up
    for (int i = (heap.size - 2) / 2; i >= 0; i--) {
        min_heapify(&heap, i);
    }

    printf("Initial Min-Heap State:\n");
    print_heap_state(&heap, 0);
    printf("----------------------------------------------------------------------\n");

    int out_idx = 0;
    int step = 1;

    while (heap.size > 0) {
        // Extract root (minimum)
        HeapNode root = heap.nodes[0];
        output[out_idx++] = root.value;
        heap.element_moves++;

        int l_idx = root.list_index;
        int next_elem_idx = root.element_index + 1;

        if (next_elem_idx < list_sizes[l_idx]) {
            // Replace root with next element from same list
            heap.nodes[0].value = lists[l_idx][next_elem_idx];
            heap.nodes[0].list_index = l_idx;
            heap.nodes[0].element_index = next_elem_idx;
            heap.element_moves++;
            min_heapify(&heap, 0);
        } else {
            // List exhausted: replace root with last heap node and decrease size
            heap.nodes[0] = heap.nodes[heap.size - 1];
            heap.size--;
            heap.element_moves++;
            if (heap.size > 0) {
                min_heapify(&heap, 0);
            }
        }

        printf("Extracted: %2d (from L%d[%d]) -> Merged Array: [", root.value, l_idx + 1, root.element_index);
        for (int i = 0; i < out_idx; i++) {
            printf("%d%s", output[i], (i == out_idx - 1) ? "" : ", ");
        }
        printf("]\n");
        print_heap_state(&heap, step++);
        printf("----------------------------------------------------------------------\n");
    }

    *heap_stats = heap;
}

typedef struct {
    long long comparisons;
    long long element_moves;
} PairwiseStats;

void merge_two_lists(int *arr1, int size1, int *arr2, int size2, int *result, PairwiseStats *stats) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        stats->comparisons++;
        if (arr1[i] <= arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
        stats->element_moves++;
    }
    while (i < size1) {
        result[k++] = arr1[i++];
        stats->element_moves++;
    }
    while (j < size2) {
        result[k++] = arr2[j++];
        stats->element_moves++;
    }
}

void pairwise_merge(int lists[K][4], int list_sizes[K], int output[TOTAL_N], PairwiseStats *stats) {
    stats->comparisons = 0;
    stats->element_moves = 0;

    printf("\n======================================================================\n");
    printf("PART B: PAIRWISE MERGING APPROACH TRACE\n");
    printf("======================================================================\n");

    // Pass 1: Merge L1 and L2 into temp buffer M1
    int M1[N1 + N2];
    printf("Pass 1: Merging List 1 (L1) and List 2 (L2)...\n");
    printf("L1: [10, 30, 50, 70]\nL2: [20, 40, 60, 80]\n");
    
    PairwiseStats pass1_stats = {0, 0};
    merge_two_lists(lists[0], list_sizes[0], lists[1], list_sizes[1], M1, &pass1_stats);
    
    printf("Result M1 (L1 + L2): [");
    for (int i = 0; i < N1 + N2; i++) {
        printf("%d%s", M1[i], (i == N1 + N2 - 1) ? "" : ", ");
    }
    printf("]\n");
    printf("Pass 1 Comparisons: %lld | Pass 1 Element Moves: %lld\n", pass1_stats.comparisons, pass1_stats.element_moves);
    printf("----------------------------------------------------------------------\n");

    // Pass 2: Merge M1 and L3 into final output
    printf("Pass 2: Merging Intermediate Result (M1) and List 3 (L3)...\n");
    printf("M1: [10, 20, 30, 40, 50, 60, 70, 80]\nL3: [15, 35, 55, 75]\n");
    
    PairwiseStats pass2_stats = {0, 0};
    merge_two_lists(M1, N1 + N2, lists[2], list_sizes[2], output, &pass2_stats);

    printf("Final Merged Result: [");
    for (int i = 0; i < TOTAL_N; i++) {
        printf("%d%s", output[i], (i == TOTAL_N - 1) ? "" : ", ");
    }
    printf("]\n");
    printf("Pass 2 Comparisons: %lld | Pass 2 Element Moves: %lld\n", pass2_stats.comparisons, pass2_stats.element_moves);
    printf("----------------------------------------------------------------------\n");

    stats->comparisons = pass1_stats.comparisons + pass2_stats.comparisons;
    stats->element_moves = pass1_stats.element_moves + pass2_stats.element_moves;
}

int main() {
    int lists[K][4] = {
        {10, 30, 50, 70},
        {20, 40, 60, 80},
        {15, 35, 55, 75}
    };
    int list_sizes[K] = {4, 4, 4};

    int heap_output[TOTAL_N];
    MinHeap heap_stats;

    k_way_merge_heap(lists, list_sizes, heap_output, &heap_stats);

    int pairwise_output[TOTAL_N];
    PairwiseStats pairwise_stats;

    pairwise_merge(lists, list_sizes, pairwise_output, &pairwise_stats);

    printf("\n======================================================================\n");
    printf("PART C: PERFORMANCE AND COMPLEXITY SUMMARY\n");
    printf("======================================================================\n");
    printf("%-30s | %-15s | %-15s\n", "Metric / Feature", "Min Heap Merge", "Pairwise Merge");
    printf("----------------------------------------------------------------------\n");
    printf("%-30s | %-15d | %-15s\n", "Max Heap / Auxiliary Size", K, "N/A (Buffer: 8)");
    printf("%-30s | %-15lld | %-15lld\n", "Number of Comparisons", heap_stats.comparisons, pairwise_stats.comparisons);
    printf("%-30s | %-15lld | %-15lld\n", "Number of Element Moves", heap_stats.element_moves, pairwise_stats.element_moves);
    printf("%-30s | %-15s | %-15s\n", "Time Complexity (General)", "O(N log k)", "O(N * k)");
    printf("%-30s | %-15s | %-15s\n", "Space Complexity (General)", "O(k)", "O(N)");
    printf("======================================================================\n");

    // Save inputs & outputs to files
    FILE *f_in = fopen("C:/Users/rijul/.gemini/antigravity/scratch/k_way_merge/input_data.txt", "w");
    if (f_in) {
        fprintf(f_in, "List 1 (L1): 10, 30, 50, 70\n");
        fprintf(f_in, "List 2 (L2): 20, 40, 60, 80\n");
        fprintf(f_in, "List 3 (L3): 15, 35, 55, 75\n");
        fclose(f_in);
    }

    FILE *f_out_h = fopen("C:/Users/rijul/.gemini/antigravity/scratch/k_way_merge/output_heap.txt", "w");
    if (f_out_h) {
        fprintf(f_out_h, "Min Heap Merged Output:\n");
        for (int i = 0; i < TOTAL_N; i++) {
            fprintf(f_out_h, "%d%s", heap_output[i], (i == TOTAL_N - 1) ? "\n" : ", ");
        }
        fclose(f_out_h);
    }

    FILE *f_out_p = fopen("C:/Users/rijul/.gemini/antigravity/scratch/k_way_merge/output_pairwise.txt", "w");
    if (f_out_p) {
        fprintf(f_out_p, "Pairwise Merged Output:\n");
        for (int i = 0; i < TOTAL_N; i++) {
            fprintf(f_out_p, "%d%s", pairwise_output[i], (i == TOTAL_N - 1) ? "\n" : ", ");
        }
        fclose(f_out_p);
    }

    return 0;
}
