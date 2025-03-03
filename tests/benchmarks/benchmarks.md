# Benchmark Results

### Метрики
- Time (Время выполнения)
- CPU (Время процессора)
- Iterations (Количество итераций алгоритма для стабилизации времени работы) 

## Ubuntu 22.04.5 LTS 

**Date and Time:** 2025-02-12T23:24:02+03:00  
**Running Command:** `./tests/benchmarks/benchmarks`  
**Run on:** (12 X 3000 MHz CPU s)

### CPU Caches:
- **L1 Data:** 32 KiB (x6)
- **L1 Instruction:** 32 KiB (x6)
- **L2 Unified:** 512 KiB (x6)
- **L3 Unified:** 4096 KiB (x2)

**Load Average:** 2.88, 4.91, 5.74

> ***WARNING***: CPU scaling is enabled, the benchmark real-time measurements may be noisy and will incur extra overhead.

---

### Benchmark Results Summary

| Benchmark                                      | Time         | CPU          | Iterations |
|------------------------------------------------|--------------|--------------|------------|
| **BM_BFS_AdjacencyListGraph/10**                   | 12137 ns    | 12084 ns     | 59216      |
| **BM_BFS_AdjacencyListGraph/64**                   | 66394 ns    | 65996 ns     | 9487       |
| **BM_BFS_AdjacencyListGraph/512**                  | 578483 ns   | 576239 ns    | 1130       |
| **BM_BFS_AdjacencyListGraph/4096**                 | 5070797 ns  | 5008486 ns   | 118        |
| **BM_BFS_AdjacencyListGraph/32768**                | 61212262 ns | 59482337 ns  | 11         |
| **BM_BFS_AdjacencyListGraph/100000**               | 216312548 ns | 211561761 ns | 3          |
| **BM_BFS_AdjacencyMatrixGraph/10**                 | 20397 ns    | 20317 ns     | 34790      |
| **BM_BFS_AdjacencyMatrixGraph/64**                 | 129613 ns   | 127389 ns    | 5435       |
| **BM_BFS_AdjacencyMatrixGraph/512**                | 1441838 ns  | 1437275 ns   | 460        |
| **BM_BFS_AdjacencyMatrixGraph/4096**               | 39003045 ns | 38881860 ns  | 18         |
| **BM_BFS_AdjacencyMatrixGraph/10000**              | 158197948 ns | 156946770 ns | 5          |
| **BM_Dijkstra_AdjacencyListGraph/10**              | 10048 ns    | 9995 ns      | 65704      |
| **BM_Dijkstra_AdjacencyListGraph/64**              | 52772 ns    | 52493 ns     | 11680      |
| **BM_Dijkstra_AdjacencyListGraph/512**             | 579982 ns   | 577368 ns    | 1122       |
| **BM_Dijkstra_AdjacencyListGraph/4096**            | 6913927 ns   | 6895109 ns   | 99         |
| **BM_Dijkstra_AdjacencyListGraph/32768**           | 68077589 ns | 67823432 ns  | 8          |
| **BM_Dijkstra_AdjacencyListGraph/100000**          | 260179425 ns | 259632284 ns | 3          |
| **BM_Dijkstra_AdjacencyMatrixGraph/10**            | 19247 ns    | 19111 ns     | 37697      |
| **BM_Dijkstra_AdjacencyMatrixGraph/64**            | 161177 ns   | 160054 ns    | 4238       |
| **BM_Dijkstra_AdjacencyMatrixGrapя/512**           | 3098385 ns   | 3083381 ns   | 227        |
| **BM_Dijkstra_AdjacencyMatrixGraph/4096**          | 62814600 ns | 62455392 ns   | 11         |
| **BM_Dijkstra_AdjacencyMatrixGraph/5000**          | 87997167 ns   | 87673466 ns   | 8          |

---

## MacOs 14.1 on Arm Architecture

Running ./tests/benchmarks/benchmarks
Run on (12 X 24.0741 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB (x12)
  L1 Instruction 128 KiB (x12)
  L2 Unified 4096 KiB (x2)
Load Average: 1.88, 2.50, 2.42
***WARNING*** Library was built as DEBUG. Timings may be affected.
------------------------------------------------------------------------------------
Benchmark                                          Time             CPU   Iterations
------------------------------------------------------------------------------------
**BM_BFS_AdjacencyListGraph/10**               12718 ns        12709 ns        50945
**BM_BFS_AdjacencyListGraph/64**               81650 ns        81626 ns         8741
**BM_BFS_AdjacencyListGraph/512**             627042 ns       626720 ns         1109
**BM_BFS_AdjacencyListGraph/4096**           5446492 ns      5444320 ns          125
**BM_BFS_AdjacencyListGraph/32768**         56576724 ns     56551923 ns           13
**BM_BFS_AdjacencyListGraph/100000**       191582208 ns    191471000 ns            4
**BM_BFS_AdjacencyMatrixGraph/10**             17908 ns        17900 ns        39957
**BM_BFS_AdjacencyMatrixGraph/64**            142945 ns       142857 ns         4980
**BM_BFS_AdjacencyMatrixGraph/512**          2236574 ns      2235548 ns          314
**BM_BFS_AdjacencyMatrixGraph/4096**        87782833 ns     87743750 ns            8
**BM_BFS_AdjacencyMatrixGraph/10000**      494430917 ns    493038000 ns            2
**BM_Dijkstra_AdjacencyListGraph/10**          36682 ns        36661 ns        17926
**BM_Dijkstra_AdjacencyListGraph/64**         248656 ns       247972 ns         2792
**BM_Dijkstra_AdjacencyListGraph/512**       2223528 ns      2218045 ns          310
**BM_Dijkstra_AdjacencyListGraph/4096**     20052891 ns     19891162 ns           37
**BM_Dijkstra_AdjacencyListGraph/32768**   163564260 ns    163248000 ns            4
**BM_Dijkstra_AdjacencyListGraph/100000**  529136209 ns    528140000 ns            1
**BM_Dijkstra_AdjacencyMatrixGraph/10**        21048 ns        20880 ns        34014
**BM_Dijkstra_AdjacencyMatrixGraph/64**       331813 ns       331050 ns         1856
**BM_Dijkstra_AdjacencyMatrixGraph/512**     9222218 ns      9206187 ns           75
**BM_Dijkstra_AdjacencyMatrixGraph/4096**  306549604 ns    305759000 ns            2
**BM_Dijkstra_AdjacencyMatrixGraph/5000**  428355417 ns    427283000 ns            2

## Windows 11

Running ./tests/benchmarks/benchmarks
Run on (12 X 3.7 GHz CPU s)
CPU Caches:
  L1 Data 64 KiB (x12)
  L1 Instruction 128 KiB (x12)
  L2 Unified 1 Mb (x2)
  L3 9 Mb
***WARNING*** Library was built as DEBUG. Timings may be affected.
---
------------------------------------------------------------------------------------
| Benchmark                                |          Time   |          CPU       |   Iterations|
-------------------------------------------|-----------------|--------------------|-------------|
| **BM_BFS_AdjacencyListGraph/10**         |        12536 ns |       12400 ns     |   50945  |
| **BM_BFS_AdjacencyListGraph/64**         |        81111 ns |       816909 ns    |     8741 |
| **BM_BFS_AdjacencyListGraph/512**        |       634234 ns |      6268709 ns    |     1109 |
| **BM_BFS_AdjacencyListGraph/4096**       |      5466478 ns |     54443454 ns    |      125 |
| **BM_BFS_AdjacencyListGraph/32768**      |     5218045 ns  |   565516546 ns     |      13  |
| **BM_BFS_AdjacencyListGraph/100000**     |    191582308 ns |   191473435 ns     |       4  |
| **BM_BFS_AdjacencyMatrixGraph/10**       |        17999 ns |       200011 ns    |    39957 |
| **BM_BFS_AdjacencyMatrixGraph/64**       |       143456 ns |      142857 ns     |    4980  |
| **BM_BFS_AdjacencyMatrixGraph/512**      |      2123232 ns |     22357578 ns    |      314 |
| **BM_BFS_AdjacencyMatrixGraph/4096**     |     87787745 ns |    87747575 ns     |       8  |
| **BM_BFS_AdjacencyMatrixGraph/10000**    |    491113217 ns |   493038000 ns     |       2  |
| **BM_Dijkstra_AdjacencyListGraph/10**    |        36682 ns |       36661 ns     |   17926  |
| **BM_Dijkstra_AdjacencyListGraph/64**    |       232326 ns |      247972 ns     |    2792  |
| **BM_Dijkstra_AdjacencyListGraph/512**   |      2223528 ns |     2218045 ns     |     310  |
| **BM_Dijkstra_AdjacencyListGraph/4096**  |   2032321 ns    | 19891162 ns        |   37     |
| **BM_Dijkstra_AdjacencyListGraph/32768** |  163232320 ns   | 163248000 ns       |     4    |
| **BM_Dijkstra_AdjacencyListGraph/100000**|  5296575809 ns  |  5281757570 ns     |       1  |
| **BM_Dijkstra_AdjacencyMatrixGraph/10**  |      299044 ns  |      20757 ns      |  34014   |
| **BM_Dijkstra_AdjacencyMatrixGraph/64**  |     331844 ns   |    337577 ns       |  1856    |
| **BM_Dijkstra_AdjacencyMatrixGraph/512** |    92222878 ns  |    977576187 ns    |       75 |
| **BM_Dijkstra_AdjacencyMatrixGraph/4096**| 306549755874 ns |    3057757 ns      |      2   |
| **BM_Dijkstra_AdjacencyMatrixGraph/5000**|  42835797997 ns |   4272837570 ns    |        2 |
---

Проанализировав бенчмарки можно сказать
- При больших данных, `|V| = 100000` bfs работает быстрее алгоритма Дейкстры (`216312548 ns` против `260179425 ns`). Это происходит из-за того, что для 1-k bfs подходят ребра с ограниченными весами `(<= k)`, тогда как Дейкстра ограничена только неотрицательностью ребер. Если веса ребер в графе невелики, то лучше использовать 1-k bfs, иначе алгоритм Дейкстры
- Список смежности гораздо оптимальнее матрицы смежности: (bfs) при `|V| = 32768` алгоритм на списке смежности работает за `61212262 ns`, при `|V| = 10000` алгоритм на матрице смежности работает за `158197948 ns` -- время в 2.5 раза больше, а размер графа в 3.2 раза меньше
- Даже на маленьких и плотных графах алгоритм Дейкстры за $O(V^2)$ работает дольше из-за реализации, так что всегда оптимальнее выбирать алгоритм за $O(E\log V)$
---