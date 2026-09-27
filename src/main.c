/**
 * @file main.c
 * @brief Main driver program for Data Structures Assignment - Question 9
 */

#include <stdio.h>
#include <stdlib.h>

extern void k_way_merge_min_heap(int **lists, int k, int *sizes, int total_elements, int *output, long long *out_comp, long long *out_moves);
extern void pairwise_merge_lists(int **lists, int k, int *sizes, int total_elements, int *output, long long *out_comp, long long *out_moves);

int main() {
    printf("======================================================================\n");
    printf("     DATA STRUCTURES ASSIGNMENT - QUESTION 9 IMPLEMENTATION          \n");
    printf("======================================================================\n\n");

    int k = 3;
    int sizes[] = {4, 4, 4};
    int total_elements = 12;

    int l1[] = {10, 30, 50, 70};
    int l2[] = {20, 40, 60, 80};
    int l3[] = {15, 35, 55, 75};

    int *lists[3];
    lists[0] = l1;
    lists[1] = l2;
    lists[2] = l3;

    printf("Input Transaction Lists:\n");
    printf("  List 1 (L1): 10, 30, 50, 70\n");
    printf("  List 2 (L2): 20, 40, 60, 80\n");
    printf("  List 3 (L3): 15, 35, 55, 75\n\n");

    int *heap_output = (int*) malloc(sizeof(int) * total_elements);
    int *pairwise_output = (int*) malloc(sizeof(int) * total_elements);

    long long heap_comp = 0, heap_moves = 0;
    long long pairwise_comp = 0, pairwise_moves = 0;

    // Execute Min Heap K-Way Merge
    k_way_merge_min_heap(lists, k, sizes, total_elements, heap_output, &heap_comp, &heap_moves);

    // Execute Pairwise Merge
    pairwise_merge_lists(lists, k, sizes, total_elements, pairwise_output, &pairwise_comp, &pairwise_moves);

    // Print Results
    printf("----------------------------------------------------------------------\n");
    printf("1. Min Heap K-Way Merge Result:\n   [ ");
    for (int i = 0; i < total_elements; i++) {
        printf("%d%s", heap_output[i], (i == total_elements - 1) ? " " : ", ");
    }
    printf("]\n");
    printf("   Comparisons: %lld | Element Moves: %lld\n", heap_comp, heap_moves);

    printf("\n2. Pairwise Merge Result:\n   [ ");
    for (int i = 0; i < total_elements; i++) {
        printf("%d%s", pairwise_output[i], (i == total_elements - 1) ? " " : ", ");
    }
    printf("]\n");
    printf("   Comparisons: %lld | Element Moves: %lld\n", pairwise_comp, pairwise_moves);
    printf("----------------------------------------------------------------------\n\n");

    // Write input data
    FILE *fin = fopen("data/input_data.txt", "w");
    if (fin) {
        fprintf(fin, "Financial System Input Transaction Lists (K=3, N=12):\n");
        fprintf(fin, "L1 = 10, 30, 50, 70\n");
        fprintf(fin, "L2 = 20, 40, 60, 80\n");
        fprintf(fin, "L3 = 15, 35, 55, 75\n");
        fclose(fin);
    }

    // Write heap output
    FILE *fout_h = fopen("data/output_heap.txt", "w");
    if (fout_h) {
        fprintf(fout_h, "Min Heap K-Way Merged Output (Sorted Transactions):\n");
        for (int i = 0; i < total_elements; i++) {
            fprintf(fout_h, "%d%s", heap_output[i], (i == total_elements - 1) ? "\n" : ", ");
        }
        fclose(fout_h);
    }

    // Write pairwise output
    FILE *fout_p = fopen("data/output_pairwise.txt", "w");
    if (fout_p) {
        fprintf(fout_p, "Pairwise Merged Output (Sorted Transactions):\n");
        for (int i = 0; i < total_elements; i++) {
            fprintf(fout_p, "%d%s", pairwise_output[i], (i == total_elements - 1) ? "\n" : ", ");
        }
        fclose(fout_p);
    }

    free(heap_output);
    free(pairwise_output);

    printf("Outputs successfully generated in data/ folder.\n");
    return 0;
}
