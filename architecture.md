## Архитектура

### Структура графов
![Структура графов](./images/arc.png?raw=true)

- `class Edge <edgeType>`
    - Поля
      - `std::int32_t m_from` - начало ребра
      - `std::int32_t m_to` - конец ребра
      - `edgeType m_edge` - структура ребра
    - Методы:
      - `Edge(std::int32_t from, std::int32_t to, edgeType edge)` - конструктор
      - `std::int32_t from()` - геттер начала ребра
      - `std::int32_t to()` - геттер конца ребра
      - `edgeType edge()` - геттер структуры ребра
- `class Graph <edgeType>`
  - Поля
    - `std::int32_t m_numberVertices` - количество вершин
    - `std::int32_t m_numberEdges` - количество ребер
    - `bool m_isDirected` - ориентирован ли граф
  - Виртуальные методы
    - `void addEdge(std::int32_t from, std::int32_t to, edgeType edge)` - добавление ребра
    - `void printEdges(std::ostream& ostream)` - выводит ребра
    - `void getNeighbours(std::int32_t vertex,
      std::vector<Edge<edgeType>>& neighbours)` - записывает в `neighbours` список соседей вершины `vertex`
    - `virtual bool isVertexesConnected(std::int32_t from, std::int32_t to)` - связаны ли вершины
  - Методы
    - `Graph(std::int32_t numberVertices, bool isDirected)` - конструктор
    - `bool isVertexValid(std::int32_t vertex)` - корректна ли вершина
    - `std::int32_t numberVertices()` - геттер количества вершин
    - `std::int32_t numberEdges()` - геттер количества ребер
    - `bool isDirected()` - геттер ориентированности графа
- `class AdjacencyListGraph <edgeType> : Graph <edgeType>`
  - Поля
    - `std::vector<std::vector<Edge<edgeType>>> m_adjList` - список смежности
- `class AdjacencyMatrixGraph <edgeType> : Graph <edgeType>`
  - Поля:
    - `std::vector<std::vector<std::optional<Edge<edgeType>>>> m_adjMatrix` - матрица смежности

### Алгоритмы

#### 1-k BFS
`class BFS_1k <edgeType>`
- Поля
  - `Graph<edgeType>& m_graph` - граф
  - `std::int32_t m_maxWeight` - значение k в терминах 1-k BFS
- Методы
  - `BFS_1k(Graph<edgeType>& graph, std::int32_t maxWeight)` - конструктор
  - `BFSResult run(std::int32_t startVertex)` - запуск алгоритма от вершины `startVertex`
  - `class BFSResult`
    - `std::vector<std::int32_t> m_distances` - вектор дистанций
    - `std::vector<std::int32_t> m_accessibility` - вектор достижимости
    - `const std::vector<std::int32_t>& distances()` - геттер вектора дистанций
    - `const std::vector<std::int32_t>& accessibility()` - геттер вектора достижимости

#### Алгоритм Дейкстры
`class Dijkstra <edgeType>`
- Поля
  - `Graph<edgeType>& m_graph` - граф
- Методы
  - `Dijkstra(Graph<edgeType>& graph)` - конструктор 
  - `DijkstraResult runStandard(std::int32_t start)` - алгоритм за $O(n^2)$
  - `DijkstraResult runOptimized(std::int32_t start)` - алгоритм за $O(E\log⁡V)$
  - `class DijkstraResult`
    - `std::vector<std::int64_t> m_distances` - вектор дистанций
    - `const std::vector<std::int64_t>& distances()` - геттер вектора дистанций

#### Алгоритм Флойда-Уоршелла
`class FloydWarshall <edgeType>`
- Поля
  - `Graph<edgeType>& m_graph`
- Методы
  - `FloydWarshall(Graph<edgeType>& graph)` - конструктор
  - `FloydWarshallResult run()` - запуск алгоритма
  - `class FloydWarshallResult`
    - `std::vector<std::vector<std::int64_t>> m_distances`- массив попарных расстояний
    - `bool m_has_negative_cycles` - есть ли в графе цикл отрицательного веса
    - `const std::vector<std::vector<std::int64_t>>& distances()` - геттер вектора дистанций
    - `const bool has_negative_cycles()` - геттер индикатора наличия отрицательного цикла

#### Алгоритм Куна
`class KuhnMatching <edgeType>`
- Поля
  - `Graph<edgeType>& m_graph` - граф
- Методы
  - `KuhnMatching(Graph<edgeType>& graph)` - конструктор
  - `MatchingResult run()` - запуск алгоритма
  - `class MatchingResult`
    - `std::vector<std::int32_t> m_matching` - вектор паросочетаний. Если паросочетания с вершиной `v` не существует, то `matching[v]=−1`
    - `const std::vector<std::int32_t>& matching()` - гетер вектора паросочетаний.
  
#### Алгоритм Беллмана-Форда
`class BellmanFord <edgeType>`
- Поля
  - `Graph<edgeType>& m_graph` - граф
- Методы
  - `BellmanFord(Graph<edgeType>& graph)` - конструктор
  - `BellmanFord run(std::int32_t start_vertex)` - запуск алгоритма
  - `class BellmanFordResult`
    - `std::vector<std::int64_t> m_distances` - вектор дистанций
    - `bool m_has_negative_cycles` - есть ли в графе цикл отрицательного веса
    - `const std::vector<std::int64_t>& distances()` - гетер вектора дистанций
    - `const bool has_negative_cycles()` - геттер индикатора наличия отрицательного цикла

### Алгоритм A* (A Star)
`class AStar <edgeType>`
- Поля:
  - `Graph<edgeType>& m_graph` - граф, в котором будет происходить поиск пути
  - `std::function<double(int, int)> m_heuristic` - функция эвристики, оценивающая расстояние от текущей вершины до цели
- Методы:
  - `AStar(Graph<edgeType>& graph, std::function<double(int, int)> heuristic)` - конструктор, инициализирует граф и эвристическую функцию
  - `class AStarResult`
    - `std::vector<int> m_path` - найденный путь
    - Методы: 
      - `const std::vector<int>& getPath()` - геттер для пути
  - `AStarResult run(int start, int goal)` - запускает алгоритм поиска пути от `start` до `goal`, используя алгоритм A* для поиска кратчайшего пути с учётом эвристики

Этот алгоритм предназначен для поиска кратчайшего пути в графе с использованием алгоритма A* (A Star). В отличие от обычного поиска по ширине или глубине, A* использует эвристическую функцию для оценки "стоимости" пути, что позволяет значительно ускорить поиск в большинстве случаев.

### Алгоритм Диница (Dinic)
`class Dinic<T>`
- Поля:
  - `int n` - количество вершин в графе
  - `std::vector<std::vector<Edge>> graph` - список смежности для хранения рёбер графа
  - `std::vector<int> level` - вектор для хранения уровней вершин в процессе поиска по уровням
  - `std::vector<size_t> ptr` - указатели на текущие рёбра для каждой вершины во время поиска по графу
- Методы:
  - `Dinic(int n)` - конструктор, инициализирует алгоритм с заданным числом вершин
  - `void addEdge(int u, int v, T cap)` - добавляет ориентированное ребро с пропускной способностью `cap` между вершинами `u` и `v`
  - `T maxFlow(int source, int sink)` - находит максимальный поток между вершинами `source` и `sink` с использованием алгоритма Диница

Дополнительно:
  - Структура `Edge`:
    - `int v` - вершина, к которой ведет ребро
    - `T cap` - пропускная способность ребра
    - `size_t rev` - индекс обратного рёбра в списке смежности
  - Вспомогательные методы:
    - `bool bfs(int source, int sink)` - выполняет поиск в ширину для построения уровня графа
    - `T dfs(int u, int sink, T flow)` - выполняет поиск в глубину для прокачки потока по графу

Алгоритм Диница используется для вычисления максимального потока в поточных сетях. Он работает быстрее, чем классический алгоритм Форда-Фалкерсона за счёт использования поиска в ширину для построения уровней вершин и поиска в глубину для увеличения потока.


### Алгоритм Минимального Стоимости Потока с k Путями (Min-Cost K-Flow)
`class MinCostKFlow<edgeType>`
- Поля:
  - `Graph<edgeType>& m_graph` - граф, в котором ищется минимальный поток с ограничением по количеству путей
  - `int m_k` - максимальное количество потоков (путей), которое алгоритм может прокачать
  - `int m_flowCost` - текущая стоимость потока
  - `int m_totalFlow` - общий поток, прокачанный за все итерации

- Методы:
  - `MinCostKFlow(Graph<edgeType>& graph, int k)` - конструктор, инициализирует алгоритм с заданным графом и максимальным количеством путей `k`
  - `MinCostKFlowResult run(int source, int sink)` - находит минимальный поток с учетом стоимости для `k` путей между вершинами `source` и `sink`. Возвращает объект `MinCostKFlowResult` с потоком и стоимостью
  - `bool bellmanFord(int source, int sink, std::vector<int>& parent)` - выполняет алгоритм Беллмана-Форда для поиска кратчайшего пути с учётом стоимости и пропускной способности рёбер. Возвращает `true`, если путь найден, и `false`, если нет.

Дополнительно:
  - Структура `MinCostKFlowResult`:
    - `int m_flow` - общий поток, найденный алгоритмом
    - `int m_cost` - стоимость прокачанного потока
  - Алгоритм использует метод Беллмана-Форда для поиска путей с минимальной стоимостью и ограничением на пропускную способность рёбер.

Алгоритм решает задачу нахождения минимального потока с заданным числом путей, используя динамическую оптимизацию стоимости потока. Он может быть использован в различных задачах, где важно учитывать как количество потоков, так и их стоимость.

### Алгоритм Тарьяна для нахождения сильно связных компонент (TarjanSCC)

`class TarjanSCC<edgeType>`

- **Поля**:
  - `Graph<edgeType>& m_graph` - граф, для которого выполняется поиск сильно связных компонент.

- **Методы**:
  - `TarjanSCC(Graph<edgeType>& graph)` - конструктор, инициализирует алгоритм с заданным графом.
  - `SCCResult run()` - запускает алгоритм Тарьяна для нахождения всех сильно связных компонент в графе. Возвращает объект `SCCResult`, содержащий список компонент.
  - `void dfs(std::int32_t v, std::vector<std::int32_t>& lowLink, std::vector<std::int32_t>& preOrder, std::vector<bool>& onStack, std::stack<std::int32_t>& stack, std::vector<std::vector<std::int32_t>>& result)` - выполняет обход графа в глубину, обновляя ссылки на низшие индексы (`lowLink`) и порядок обхода (`preOrder`), чтобы находить сильно связные компоненты.

- **Структура `SCCResult`**:
  - `std::vector<std::vector<std::int32_t>> m_scc` - список сильно связных компонент. Каждая компонента представлена как вектор индексов вершин.
  - Метод `getSCC()` возвращает список всех сильно связных компонент.

- **Описание работы алгоритма**:
  - Алгоритм использует модификацию обхода в глубину для вычисления сильно связных компонент с использованием `lowLink` и `preOrder`. Если при обходе вершин обнаруживается компонентный цикл, то эти вершины собираются в отдельную компоненту.
  - Алгоритм Тарьяна работает за время O(V + E), где V — количество вершин, а E — количество рёбер в графе.
