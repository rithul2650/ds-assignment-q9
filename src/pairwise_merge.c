/**
 * @file pairwise_merge.c
 * @brief Implementation of Pairwise Merging for sorted lists
 */

#include <stdio.h>
#include <stdlib.h>

void merge_two_sorted_arrays(const int *arr1, int size1, const int *arr2, int size2, int *result, long long *comparisons, long long *element_moves) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        (*comparisons)++;
        if (arr1[i] <= arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
        (*element_moves)++;
    }
    while (i < size1) {
        result[k++] = arr1[i++];
        (*element_moves)++;
    }
    while (j < size2) {
        result[k++] = arr2[j++];
        (*element_moves)++;
    }
}

void pairwise_merge_lists(int **lists, int k, int *sizes, int total_elements, int *output, long long *out_comp, long long *out_moves) {
    if (k <= 0) return;
    if (k == 1) {
        for (int i = 0; i < sizes[0]; i++) {
            output[i] = lists[0][i];
        }
        *out_comp = 0;
        *out_moves = sizes[0];
        return;
    }

    long long total_comp = 0;
    long long total_moves = 0;

    // Start with list 0
    int current_size = sizes[0];
    int *current_merged = (int*) malloc(sizeof(int) * current_size);
    for (int i = 0; i < current_size; i++) {
        current_merged[i] = lists[0][i];
        total_moves++;
    }

    // Iteratively merge with remaining lists
    for (int l = 1; l < k; l++) {
        int next_size = sizes[l];
        int new_size = current_size + next_size;
        int *next_merged = (int*) malloc(sizeof(int) * new_size);

        merge_two_sorted_arrays(current_merged, current_size, lists[l], next_size, next_merged, &total_comp, &total_moves);

        free(current_merged);
        current_merged = next_merged;
        current_size = new_size;
    }

    for (int i = 0; i < total_elements; i++) {
        output[i] = current_merged[i];
    }
    free(current_merged);

    *out_comp = total_comp;
    *out_moves = total_moves;
}
