# Final Conclusion & Justification: Most Suitable Approach

This document synthesizes the execution results and complexity analysis for Question 9, justifying the optimal data structure and algorithm for merging sorted transaction lists in a financial system.

---

## 1. Summary of Empirical & Theoretical Findings

1. **For Small Datasets ($K=3, N=12$)**:
   - Both **Min Heap K-Way Merge** and **Sequential Pairwise Merge** correctly merge the 3 transaction lists into the unified sorted order: `[10, 15, 20, 30, 35, 40, 50, 55, 60, 70, 75, 80]`.
   - Pairwise merging incurs slightly fewer comparisons (18 vs 21) due to the tiny value of $k=3$ ($\log_2 3 \approx 1.58$) and heap tree balance maintenance overhead.

2. **For Large Datasets & Increasing Number of Sorted Files ($k \to \infty$)**:
   - **Time Complexity**:
     - Min Heap K-Way Merge operates in $\mathcal{O}(N \log k)$ time.
     - Sequential Pairwise Merge operates in $\mathcal{O}(N \cdot k)$ time.
     - As $k$ grows (e.g., $k=100$ or $k=1,000$ transaction runs), $\mathcal{O}(N \log k)$ is orders of magnitude faster than $\mathcal{O}(N \cdot k)$.
   - **Space & Memory Overhead**:
     - Min Heap K-Way Merge requires only $\mathcal{O}(k)$ auxiliary space, maintaining a fixed-size priority queue containing exactly 1 node per active list.
     - Pairwise Merging requires $\mathcal{O}(N)$ space to hold intermediate merged buffers ($M_1, M_2, \dots$).
   - **External Memory / Disk I/O**:
     - In real-world financial systems, transaction lists are stored as sorted runs on disk/cloud storage. Min Heap merging requires **a single pass** over the input streams.
     - Pairwise merging requires **$k-1$ passes**, re-reading and re-writing intermediate data repeatedly to disk.

---

## 2. Final Justification

Based on the execution results and theoretical complexity analysis:

> **The Min Heap K-Way Merge algorithm is unequivocally the most suitable approach for merging sorted transaction lists.**

### Key Reasons:
1. **Logarithmic Scalability**: Min Heap execution time grows as $\mathcal{O}(N \log k)$, preventing system slowdowns as the number of financial transaction streams ($k$) scales.
2. **Minimal Memory Footprint**: Heap memory consumption is proportional only to the number of lists ($k$), not total transactions ($N$), allowing processing of terabyte-scale financial data in finite RAM.
3. **Single-Pass Stream Processing**: Enables real-time pipeline processing where incoming transactions are streamed from disk/network without creating intermediate temporary files.
