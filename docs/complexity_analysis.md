# Complexity Analysis: K-Way Min Heap Merge vs. Pairwise Merge

This document presents a rigorous theoretical and empirical complexity analysis for merging $k$ sorted lists containing a total of $N$ elements (each list having size $n = N/k$).

---

## 1. Mathematical Notation & Setup
- $k$: Number of sorted input lists / files (for our assignment, $k = 3$).
- $n$: Length of each list (for our assignment, $n = 4$).
- $N$: Total number of elements across all lists ($N = \sum_{i=1}^{k} n_i = k \cdot n = 12$).

---

## 2. Min Heap K-Way Merge Analysis

### A. Algorithm Structure
1. **Heap Initialization**: Construct a Min-Heap containing the first element from each of the $k$ lists.
   - Time to insert $k$ elements / build heap: $O(k)$.
2. **Iterative Extraction and Replacement**:
   - Extract the root element (minimum among all active heads of lists) into the output array.
   - Read the next element from the same list as the extracted element.
   - Insert the next element into the root of the heap and invoke `min_heapify(0)`.
   - Each `min_heapify` call takes $O(\log k)$ time since the heap height is $\lfloor \log_2 k \rfloor$.
   - This process repeats exactly $N$ times (once per element).

### B. Time Complexity Derivation
$$\text{Total Time} = T_{\text{build\_heap}} + \sum_{i=1}^{N} T_{\text{extract\_and\_heapify}}$$

$$T_{\text{build\_heap}} = O(k)$$
$$T_{\text{extract\_and\_heapify}} = O(\log k)$$

$$\text{Total Time} = O(k) + N \cdot O(\log k) = O(N \log k)$$

### C. Auxiliary Space Complexity
- The Min Heap only maintains **one node per list** at any given moment.
- Heap Size: $k$ elements.
- Auxiliary Memory: $O(k)$ extra space (excluding the output array).

---

## 3. Sequential Pairwise Merging Analysis

### A. Algorithm Structure
1. Merge List 1 ($n$ elements) and List 2 ($n$ elements) $\to$ $M_1$ ($2n$ elements).
2. Merge $M_1$ ($2n$ elements) and List 3 ($n$ elements) $\to$ $M_2$ ($3n$ elements).
3. ...
4. Merge $M_{k-2}$ ($(k-1)n$ elements) and List $k$ ($n$ elements) $\to$ $M_{\text{final}}$ ($kn = N$ elements).

### B. Time Complexity Derivation
Merging two sorted lists of length $a$ and $b$ requires at most $(a + b - 1)$ comparisons and $(a + b)$ element movements.

- **Pass 1**: Merge $L_1$ ($n$) and $L_2$ ($n$) $\implies$ Operations $\approx 2n$.
- **Pass 2**: Merge $M_1$ ($2n$) and $L_3$ ($n$) $\implies$ Operations $\approx 3n$.
- **Pass 3**: Merge $M_2$ ($3n$) and $L_4$ ($n$) $\implies$ Operations $\approx 4n$.
- **Pass $i$**: Merge $M_{i-1}$ ($in$) and $L_{i+1}$ ($n$) $\implies$ Operations $\approx (i+1)n$.

Total operations across all $k-1$ pairwise merge passes:
$$\text{Total Operations} = \sum_{i=2}^{k} (i \cdot n) = n \left[ \frac{k(k+1)}{2} - 1 \right]$$

Substitute $n = N/k$:
$$\text{Total Operations} = \frac{N}{k} \left[ \frac{k^2 + k - 2}{2} \right] = \frac{N(k + 1 - 2/k)}{2} = \mathcal{O}(N \cdot k)$$

### C. Auxiliary Space Complexity
- Pairwise merging generates intermediate merged arrays $M_1, M_2, \dots, M_{k-2}$.
- The largest intermediate array $M_{k-2}$ has size $(k-1)n = N - n$.
- Auxiliary Memory: $\mathcal{O}(N)$ extra buffer memory.

---

## 4. Scalability Comparison as $k \to \infty$

| Aspect | Min Heap K-Way Merge | Pairwise Merge | Relative Performance Impact |
| :--- | :---: | :---: | :--- |
| **Time Complexity** | $\mathcal{O}(N \log k)$ | $\mathcal{O}(N \cdot k)$ | Heap merge is exponentially faster for large $k$. |
| **Disk/Disk I/O Passes** | **1 Pass** over data | **$k-1$ Passes** over data | Pairwise re-reads intermediate files $k$ times! |
| **Auxiliary Memory** | $\mathcal{O}(k)$ | $\mathcal{O}(N)$ | Heap requires minimal RAM regardless of dataset size $N$. |
| **Cache Efficiency** | High (streaming fit) | Low (large buffer thrashing) | Heap scales seamlessly to External Sorting. |

### Concrete Numerical Scaling Demonstration:
Assume merging $k = 1,000$ sorted files, each containing $n = 10,000$ transactions ($N = 10,000,000$ elements):

1. **Min Heap Merge**:
   - Heap Operations $\approx N \cdot \log_2(1000) = 10^7 \times 9.97 \approx 9.97 \times 10^7$ operations.
   - File I/O: 1 read pass, 1 write pass.

2. **Sequential Pairwise Merge**:
   - Operations $\approx \frac{N \cdot k}{2} = \frac{10^7 \times 1000}{2} = 5 \times 10^9$ operations (**50 times more work**).
   - File I/O: 1,000 passes over disk data!
