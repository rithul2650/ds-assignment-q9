# Trace Tables for Question 9: Transaction List Merging

This document provides the complete, step-by-step trace tables for both **Min-Heap K-Way Merge** and **Pairwise Merge** operating on the input lists:
- **List 1 ($L_1$)**: `[10, 30, 50, 70]`
- **List 2 ($L_2$)**: `[20, 40, 60, 80]`
- **List 3 ($L_3$)**: `[15, 35, 55, 75]`

---

## Part (a): Min-Heap K-Way Merge Trace Table

### Heap Node Representation
Each node in the Min Heap is represented as `(Value, List_ID[Index])`.
The Heap array of capacity $K=3$ maintains the min-heap property: `heap[0] <= heap[1]` and `heap[0] <= heap[2]`.

### Execution Trace

| Step | Heap Size | Heap State Array `[0, 1, 2]` | Extracted Min Element | Source List & Index | Merged Output Array | Heap Operation / Action |
| :---: | :---: | :--- | :---: | :---: | :--- | :--- |
| **0** | 3 | `[(10, L1[0]), (20, L2[0]), (15, L3[0])]` | — | — | `[]` | Heap initialized with 1st elements of $L_1, L_2, L_3$. Heapified. Root is 10. |
| **1** | 3 | `[(15, L3[0]), (20, L2[0]), (30, L1[1])]` | **10** | $L_1[0]$ | `[10]` | Pop 10 from root; insert $L_1[1]=30$ at root; `min_heapify(0)` swaps 30 & 15. |
| **2** | 3 | `[(20, L2[0]), (35, L3[1]), (30, L1[1])]` | **15** | $L_3[0]$ | `[10, 15]` | Pop 15 from root; insert $L_3[1]=35$ at root; `min_heapify(0)` swaps 35 & 20. |
| **3** | 3 | `[(30, L1[1]), (35, L3[1]), (40, L2[1])]` | **20** | $L_2[0]$ | `[10, 15, 20]` | Pop 20 from root; insert $L_2[1]=40$ at root; `min_heapify(0)` swaps 40 & 30. |
| **4** | 3 | `[(35, L3[1]), (50, L1[2]), (40, L2[1])]` | **30** | $L_1[1]$ | `[10, 15, 20, 30]` | Pop 30 from root; insert $L_1[2]=50$ at root; `min_heapify(0)` swaps 50 & 35. |
| **5** | 3 | `[(40, L2[1]), (50, L1[2]), (55, L3[2])]` | **35** | $L_3[1]$ | `[10, 15, 20, 30, 35]` | Pop 35 from root; insert $L_3[2]=55$ at root; `min_heapify(0)` swaps 55 & 40. |
| **6** | 3 | `[(50, L1[2]), (60, L2[2]), (55, L3[2])]` | **40** | $L_2[1]$ | `[10, 15, 20, 30, 35, 40]` | Pop 40 from root; insert $L_2[2]=60$ at root; `min_heapify(0)` swaps 60 & 50. |
| **7** | 3 | `[(55, L3[2]), (60, L2[2]), (70, L1[3])]` | **50** | $L_1[2]$ | `[10, 15, 20, 30, 35, 40, 50]` | Pop 50 from root; insert $L_1[3]=70$ at root; `min_heapify(0)` swaps 70 & 55. |
| **8** | 3 | `[(60, L2[2]), (75, L3[3]), (70, L1[3])]` | **55** | $L_3[2]$ | `[10, 15, 20, 30, 35, 40, 50, 55]` | Pop 55 from root; insert $L_3[3]=75$ at root; `min_heapify(0)` swaps 75 & 60. |
| **9** | 3 | `[(70, L1[3]), (75, L3[3]), (80, L2[3])]` | **60** | $L_2[2]$ | `[10, 15, 20, 30, 35, 40, 50, 55, 60]` | Pop 60 from root; insert $L_2[3]=80$ at root; `min_heapify(0)` swaps 80 & 70. |
| **10** | 2 | `[(75, L3[3]), (80, L2[3])]` | **70** | $L_1[3]$ | `[10, 15, 20, 30, 35, 40, 50, 55, 60, 70]` | Pop 70. $L_1$ exhausted. Move last node `(80, L2[3])` to root, reduce heap size to 2. `min_heapify(0)` swaps 80 & 75. |
| **11** | 1 | `[(80, L2[3])]` | **75** | $L_3[3]$ | `[10, 15, 20, 30, 35, 40, 50, 55, 60, 70, 75]` | Pop 75. $L_3$ exhausted. Move last node `(80, L2[3])` to root, reduce heap size to 1. |
| **12** | 0 | `[]` | **80** | $L_2[3]$ | `[10, 15, 20, 30, 35, 40, 50, 55, 60, 70, 75, 80]` | Pop 80. $L_2$ exhausted. Heap size 0. Algorithm terminates. |

---

## Part (b): Pairwise Merging Trace Tables

### Pass 1: Merge $L_1 = [10, 30, 50, 70]$ and $L_2 = [20, 40, 60, 80] \to M_1$

| Comparison Step | Element from $L_1$ | Element from $L_2$ | Comparison Made | Selected Element | Intermediate Array $M_1$ |
| :---: | :---: | :---: | :---: | :---: | :--- |
| **1** | 10 | 20 | $10 \le 20$ (True) | **10** (from $L_1$) | `[10]` |
| **2** | 30 | 20 | $30 \le 20$ (False) | **20** (from $L_2$) | `[10, 20]` |
| **3** | 30 | 40 | $30 \le 40$ (True) | **30** (from $L_1$) | `[10, 20, 30]` |
| **4** | 50 | 40 | $50 \le 40$ (False) | **40** (from $L_2$) | `[10, 20, 30, 40]` |
| **5** | 50 | 60 | $50 \le 60$ (True) | **50** (from $L_1$) | `[10, 20, 30, 40, 50]` |
| **6** | 70 | 60 | $70 \le 60$ (False) | **60** (from $L_2$) | `[10, 20, 30, 40, 50, 60]` |
| **7** | 70 | 80 | $70 \le 80$ (True) | **70** (from $L_1$) | `[10, 20, 30, 40, 50, 60, 70]` |
| **End** | — | 80 | — (List 1 exhausted) | **80** (from $L_2$) | `[10, 20, 30, 40, 50, 60, 70, 80]` |

* **Pass 1 Summary**: 7 Comparisons, 8 Element Copies.

---

### Pass 2: Merge $M_1 = [10, 20, 30, 40, 50, 60, 70, 80]$ and $L_3 = [15, 35, 55, 75] \to M_{\text{final}}$

| Comparison Step | Element from $M_1$ | Element from $L_3$ | Comparison Made | Selected Element | Final Merged Array $M_{\text{final}}$ |
| :---: | :---: | :---: | :---: | :---: | :--- |
| **1** | 10 | 15 | $10 \le 15$ (True) | **10** (from $M_1$) | `[10]` |
| **2** | 20 | 15 | $20 \le 15$ (False) | **15** (from $L_3$) | `[10, 15]` |
| **3** | 20 | 35 | $20 \le 35$ (True) | **20** (from $M_1$) | `[10, 15, 20]` |
| **4** | 30 | 35 | $30 \le 35$ (True) | **30** (from $M_1$) | `[10, 15, 20, 30]` |
| **5** | 40 | 35 | $40 \le 35$ (False) | **35** (from $L_3$) | `[10, 15, 20, 30, 35]` |
| **6** | 40 | 55 | $40 \le 55$ (True) | **40** (from $M_1$) | `[10, 15, 20, 30, 35, 40]` |
| **7** | 50 | 55 | $50 \le 55$ (True) | **50** (from $M_1$) | `[10, 15, 20, 30, 35, 40, 50]` |
| **8** | 60 | 55 | $60 \le 55$ (False) | **55** (from $L_3$) | `[10, 15, 20, 30, 35, 40, 50, 55]` |
| **9** | 60 | 75 | $60 \le 75$ (True) | **60** (from $M_1$) | `[10, 15, 20, 30, 35, 40, 50, 55, 60]` |
| **10** | 70 | 75 | $70 \le 75$ (True) | **70** (from $M_1$) | `[10, 15, 20, 30, 35, 40, 50, 55, 60, 70]` |
| **11** | 80 | 75 | $80 \le 75$ (False) | **75** (from $L_3$) | `[10, 15, 20, 30, 35, 40, 50, 55, 60, 70, 75]` |
| **End** | 80 | — | — (List 3 exhausted) | **80** (from $M_1$) | `[10, 15, 20, 30, 35, 40, 50, 55, 60, 70, 75, 80]` |

* **Pass 2 Summary**: 11 Comparisons, 12 Element Copies.
* **Total Pairwise Summary**: $7 + 11 = 18$ Comparisons, $8 + 12 = 20$ Element Writes (24 including input copy).
