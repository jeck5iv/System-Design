# Memory usage

Использовался профайлер [heaptrack](https://github.com/KDE/heaptrack)

### Метрики
- Peak Memory (Пиковое использование памяти)
- Temporary Allocations (Временные аллокации)
- Memory Leaks (Утечки памяти)

### Использование памяти при тесте `benchmarks_bfs1_k.cpp`:
- Most memory allocations - `graph::BFS_1k<int>::run(int)`
	- `BM_BFS_AdjacencyListGraph(benchmark::State&)` - 11069484 allocations, 3530578 temporary
	- `BM_BFS_AdjacencyMatrixGraph(benchmark::State&)` - 7743928 allocations, 7715 temporary
- Peak contributions - `BM_BFS_AdjacencyMatrixGraph(benchmark::State&)` - 1,6GB
- Most temporary allocations - `std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > >::operator=(std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > > const&)` - 3530578 allocations
- Total system memory 16,1GB
- Total memory leaked 1,4kB - все утечки не вызваны работой библиотеки, они происходят внутри библиотеки benchmarks

### Использование памяти при тесте `benchmarks_dijkstra.cpp`:
- Most memory allocations - `void std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > >::_M_realloc_insert<graph::Edge<int> const&>(__gnu_cxx::__normal_iterator<graph::Edge<int>*, std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > > >, graph::Edge<int> const&) in benchmarks` - 7349126 allocations
- Peak contributions - `BM_Dijkstra_AdjacencyMatrixGraph(benchmark::State&)` - 400,1MB
- Most temporary allocations - `std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > >::operator=(std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > > const&)` - 3232364 allocations
- Total system memory 16,1GB
- Total memory leaked 1,4kB  - все утечки не вызваны работой библиотеки, они происходят внутри библиотеки benchmarks

### Анализ использования памяти (Memory Performance Analysis)

---

#### **1. Сравнение структур данных (Adjacency List vs. Matrix)**
| Метрика                  | BFS (AdjList) | BFS (AdjMatrix) | Dijkstra (AdjList) | Dijkstra (AdjMatrix) |
|--------------------------|---------------|------------------|--------------------|----------------------|
| **Peak Memory**          | 353 МБ        | **1.6 ГБ**       | 400 МБ             | 400 МБ               |
| **Allocations**          | 11M           | 7.7M             | 7.3M               | 7.3M                 |
| **Temporary Allocations**| 3.5M          | 7.7k             | 3.2M               | 7.3M                 |

**Выводы:**
- **Матрица смежности** требует в **4.5× больше памяти** для BFS из-за хранения всех возможных рёбер (`O(V²)`).
- **Список смежности** генерирует больше временных аллокаций из-за частого копирования векторов (например, `operator=`).

---

#### **2. Проблемные места**
**BFS:**
- **Главный потребитель памяти**: `AdjacencyMatrixGraph` (1.6 ГБ) из-за хранения `V^2` значений.
- **Частые аллокации**: `vector<Edge>::operator=` (3.5M раз) — копирование векторов соседей при обходе.

**Dijkstra:**
- **Пик памяти**: 400 МБ для матрицы — меньше, чем у BFS, так как приоритетная очередь оптимизирует хранение.
- **Realloc-проблемы**: `_M_realloc_insert` (7.3M вызовов) — перевыделение памяти при добавлении рёбер.

---