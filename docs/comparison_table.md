# Comparison Table: Min Heap K-Way Merge vs. Pairwise Merge

This comparison table summarizes the experimental results obtained from executing both algorithms on the input transaction lists ($K=3, N=12$), along with theoretical complexity parameters.

---

## Performance & Complexity Metrics Comparison

| Feature / Metric | Min Heap K-Way Merge | Sequential Pairwise Merge | Notes / Observations |
| :--- | :---: | :---: | :--- |
| **Input Data** | $L_1, L_2, L_3$ ($N=12$) | $L_1, L_2, L_3$ ($N=12$) | 3 lists of 4 elements each |
| **Max Heap / Auxiliary Structure Size** | **3 Nodes** | **N/A** (Buffer: 8 elements) | Min Heap size is bounded strictly by $k=3$ |
| **Total Key Comparisons ($N=12, k=3$)** | **21** | **18** | Heap overhead for tiny $k$; pairwise is $O(N \cdot k)$ |
| **Total Element Moves / Copies** | **27** (Heap) / **57** (full) | **24** | Heap updates involve pointer/struct copies |
| **Theoretical Time Complexity** | $\mathbf{O(N \log k)}$ | $\mathbf{O(N \cdot k)}$ | Min Heap scales logarithmically with $k$ |
| **Auxiliary Space Complexity** | $\mathbf{O(k)}$ | $\mathbf{O(N)}$ | Min Heap requires $O(k)$ extra RAM; Pairwise requires $O(N)$ buffer |
| **Disk I/O Passes (External Sorting)** | **1 Pass** | **$k-1$ Passes** | Essential for financial systems reading large disk runs |
| **Streaming / Real-time Suitability** | **Excellent** | **Poor** | Heap processes dynamic transaction streams |
| **Scalability with Large $k$ ($k \ge 100$)** | **Optimal** | **Unusable** | Pairwise execution time explodes quadratically with $k$ |

---

## Breakdown of Operations for $N=12, K=3$

```
+------------------------------------+------------------+------------------+
| Operation Metric                   | Min Heap Merge   | Pairwise Merge   |
+------------------------------------+------------------+------------------+
| Pass 1 Comparisons                 | -                | 7                |
| Pass 2 Comparisons                 | -                | 11               |
| Total Key Comparisons              | 21               | 18               |
| Memory Overhead                    | O(3) = 3 nodes   | O(8) = 8 ints    |
| Time Complexity Class              | O(N log k)       | O(N * k)         |
+------------------------------------+------------------+------------------+
```
