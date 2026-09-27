# Financial System Sorted Transaction Merging (Data Structures Assignment - Question 9)

[![Language: C](https://img.shields.io/badge/Language-C11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![Compiler: GCC](https://img.shields.io/badge/Compiler-GCC%2010.3-green.svg)](https://gcc.gnu.org/)
[![Status: Complete](https://img.shields.io/badge/Assignment%20Status-Completed-success.svg)](#)

A comprehensive implementation, execution trace, and complexity analysis comparing **Min Heap K-Way Merge** against **Pairwise Merging** for already sorted transaction lists in a financial system.

---

## 📌 Problem Description (Question 9)

A financial system receives three already sorted transaction lists:
- **List 1 ($L_1$)**: `10, 30, 50, 70`
- **List 2 ($L_2$)**: `20, 40, 60, 80`
- **List 3 ($L_3$)**: `15, 35, 55, 75`

### Tasks Addressed:
1. **Part (a)**: Represent lists using suitable data structures and implement a $k$-way merge using a **Min Heap**. Record and show all heap states during execution.
2. **Part (b)**: Implement a **Pairwise Merging** approach for the same lists. Execute both approaches and record the number of major operations.
3. **Part (c)**: Analyse and compare:
   - Heap size
   - Number of comparisons
   - Time complexity
   - Space requirements
   - Determine which approach is more suitable when the number of sorted files increases.

---

## 📁 Repository Structure

```
k_way_merge/
├── data/
│   ├── input_data.txt          # Input transaction lists
│   ├── output_heap.txt         # Merged output using Min Heap K-Way merge
│   └── output_pairwise.txt     # Merged output using Pairwise merge
├── docs/
│   ├── trace_table.md          # Step-by-step trace tables for both algorithms
│   ├── complexity_analysis.md  # Theoretical & mathematical complexity derivations
│   ├── comparison_table.md     # Side-by-side performance comparison
│   └── final_conclusion.md     # Final justification for scaling k sorted files
├── src/
│   ├── k_way_merge.c           # Min-Heap k-Way merge implementation
│   ├── pairwise_merge.c        # Pairwise merge implementation
│   ├── main.c                  # Main driver program
│   └── k_way_vs_pairwise.c     # Standalone trace runner
├── build.bat                   # Windows batch script to compile and run
├── Makefile                    # Makefile for GCC/Linux/MinGW
└── README.md                   # Comprehensive project documentation
```

---

## 📊 Summary of Trace Results & Operations

### Inputs:
- $L_1 = [10, 30, 50, 70]$ ($n_1 = 4$)
- $L_2 = [20, 40, 60, 80]$ ($n_2 = 4$)
- $L_3 = [15, 35, 55, 75]$ ($n_3 = 4$)
- Total elements $N = 12$, Number of lists $k = 3$.

### Merged Output (Both Methods):
$$\text{Output} = [10, 15, 20, 30, 35, 40, 50, 55, 60, 70, 75, 80]$$

### Execution Operations Comparison ($N=12, k=3$):

| Parameter / Feature | Min Heap K-Way Merge | Pairwise Merging |
| :--- | :---: | :---: |
| **Max Heap / Auxiliary Size** | **3 Nodes** | **8 elements** (Buffer $M_1$) |
| **Number of Key Comparisons** | **21** | **18** |
| **Element Moves / Writes** | **57** | **24** |
| **Time Complexity (General)** | $\mathbf{O(N \log k)}$ | $\mathbf{O(N \cdot k)}$ |
| **Auxiliary Space Complexity** | $\mathbf{O(k)}$ | $\mathbf{O(N)}$ |

---

## 🔍 Detailed Traces

For full step-by-step state trace tables of both algorithms, see [`docs/trace_table.md`](docs/trace_table.md).

### Min-Heap States Summary:
- **Initial Heap**: `[(10, L1[0]), (20, L2[0]), (15, L3[0])]`
- **Extract 10**: Replace with $L_1[1]=30$ $\to$ Heapified: `[(15, L3[0]), (20, L2[0]), (30, L1[1])]`
- **Extract 15**: Replace with $L_3[1]=35$ $\to$ Heapified: `[(20, L2[0]), (35, L3[1]), (30, L1[1])]`
- **Extract 20**: Replace with $L_2[1]=40$ $\to$ Heapified: `[(30, L1[1]), (35, L3[1]), (40, L2[1])]`
- ...
- **Extract 80**: Heap size becomes 0. Merge complete.

---

## 📈 Scalability & Final Conclusion

As the number of sorted files ($k$) increases (e.g., $k=100$ or $k=1,000$ files):

1. **Time Complexity**:
   - Min Heap K-Way merge processes data in $\mathcal{O}(N \log k)$ time.
   - Sequential Pairwise merge processes data in $\mathcal{O}(N \cdot k)$ time.
   - As $k \to \infty$, $\mathcal{O}(N \log k)$ scales logarithmically, whereas $\mathcal{O}(N \cdot k)$ grows linearly with $k$, causing a severe bottleneck.

2. **Disk I/O & Memory Footprint**:
   - Min Heap merge requires **a single pass** over disk files and only $\mathcal{O}(k)$ memory.
   - Pairwise merge requires **$k-1$ disk passes** and $\mathcal{O}(N)$ temporary buffer memory.

**Conclusion**: **Min Heap K-Way Merge is the most suitable approach when the number of sorted files increases.**

---

## 🛠️ Build and Execution Instructions

### Prerequisites
- GCC compiler (`tdm64-gcc`, `mingw-w64`, or standard GCC on Linux/macOS)

### Compile and Run using Makefile:
```bash
make
./k_way_merge_app
```

### Compile and Run on Windows (PowerShell / Command Prompt):
```powershell
gcc src/main.c src/k_way_merge.c src/pairwise_merge.c -o main.exe
.\main.exe
```
Or simply run:
```cmd
.\build.bat
```
