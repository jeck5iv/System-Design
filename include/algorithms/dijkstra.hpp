#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <limits>
#include <queue>

#include "graph.hpp"

namespace graph {

// Класс Dijkstra реализует алгоритм Дейкстры для поиска кратчайших путей от одной вершины до всех
// остальных в графе.
template <typename edgeType>
class Dijkstra {
public:
    // Конструктор, принимающий граф.
    explicit Dijkstra(Graph<edgeType>& graph) : m_graph(graph) {}

    // Вложенный класс DijkstraResult для хранения результатов выполнения алгоритма.
    class DijkstraResult {
    public:
        // Конструктор, принимающий вектор расстояний.
        explicit DijkstraResult(const std::vector<std::int64_t>& distances)
            : m_distances(distances) {}

        // Метод для получения вектора расстояний.
        [[nodiscard]] const std::vector<std::int64_t>& distances() const { return m_distances; }

    private:
        std::vector<std::int64_t>
            m_distances;  // Вектор расстояний от стартовой вершины до всех остальных.
    };

    // Метод для запуска стандартной версии алгоритма Дейкстры.
    DijkstraResult runStandard(std::int32_t start);

    // Метод для запуска оптимизированной версии алгоритма Дейкстры с использованием приоритетной
    // очереди.
    DijkstraResult runOptimized(std::int32_t start);

private:
    Graph<edgeType>& m_graph;  // Ссылка на граф.
};

// Реализация стандартной версии алгоритма Дейкстры.
template <typename edgeType>
typename Dijkstra<edgeType>::DijkstraResult Dijkstra<edgeType>::runStandard(std::int32_t start) {
    // Инициализация вектора расстояний бесконечностью.
    std::vector<std::int64_t> distances(m_graph.numberVertices(),
                                        std::numeric_limits<std::int64_t>::max());
    // Вектор для отслеживания посещённых вершин.
    std::vector<bool> visited(m_graph.numberVertices(), false);

    // Расстояние до стартовой вершины равно 0.
    distances[start] = 0;

    // Основной цикл алгоритма Дейкстры.
    for (std::int32_t iteration = 0; iteration < m_graph.numberVertices(); iteration++) {
        // Поиск вершины с минимальным расстоянием среди непосещённых.
        std::int32_t currentMinimumVertex = -1;
        for (std::int32_t currentVertex = 0; currentVertex < m_graph.numberVertices();
             currentVertex++) {
            if (!visited[currentVertex] &&
                (currentMinimumVertex == -1 ||
                 distances[currentVertex] < distances[currentMinimumVertex])) {
                currentMinimumVertex = currentVertex;
            }
        }

        // Если минимальное расстояние осталось бесконечным, выходим из цикла.
        if (currentMinimumVertex == -1 ||
            distances[currentMinimumVertex] == std::numeric_limits<std::int64_t>::max()) {
            break;
        }

        // Помечаем вершину как посещённую.
        visited[currentMinimumVertex] = true;

        // Обновляем расстояния до соседей текущей вершины.
        std::vector<Edge<edgeType>> neighbours;
        m_graph.getNeighbours(currentMinimumVertex, neighbours);
        for (const auto& edge : neighbours) {
            std::int64_t newDistance = distances[currentMinimumVertex] + edge.edge();
            if (newDistance < distances[edge.to()]) {
                distances[edge.to()] = newDistance;
            }
        }
    }

    // Возвращение результата выполнения алгоритма.
    return DijkstraResult{distances};
}

// Реализация оптимизированной версии алгоритма Дейкстры с использованием приоритетной очереди.
template <typename edgeType>
typename Dijkstra<edgeType>::DijkstraResult Dijkstra<edgeType>::runOptimized(std::int32_t start) {
    // Инициализация вектора расстояний бесконечностью.
    std::vector<std::int64_t> distances(m_graph.numberVertices(),
                                        std::numeric_limits<std::int64_t>::max());
    // Вектор для отслеживания посещённых вершин.
    std::vector<bool> visited(m_graph.numberVertices(), false);

    // Структура для хранения узлов в приоритетной очереди.
    struct QueueNode {
        std::int64_t distance;  // Расстояние до вершины.
        std::int32_t vertex;    // Идентификатор вершины.

        // Оператор для сравнения узлов (нужен для приоритетной очереди).
        bool operator>(const QueueNode& other) const { return distance > other.distance; }
    };

    // Расстояние до стартовой вершины равно 0.
    distances[start] = 0;
    // Приоритетная очередь для хранения вершин, упорядоченных по расстоянию.
    std::priority_queue<QueueNode, std::vector<QueueNode>, std::greater<QueueNode>> pq;
    pq.push({0, start});

    // Основной цикл алгоритма Дейкстры.
    while (!pq.empty()) {
        // Извлечение вершины с минимальным расстоянием.
        std::int32_t currentVertex = pq.top().vertex;
        pq.pop();

        // Если вершина уже была обработана, пропускаем её.
        if (visited[currentVertex]) {
            continue;
        }
        visited[currentVertex] = true;

        // Обновление расстояний до соседей текущей вершины.
        std::vector<Edge<edgeType>> neighbours;
        m_graph.getNeighbours(currentVertex, neighbours);
        for (const auto& edge : neighbours) {
            std::int32_t to = edge.to();
            edgeType weight = edge.edge();

            // Если найден более короткий путь, обновляем расстояние и добавляем вершину в очередь.
            if (distances[currentVertex] + weight < distances[to]) {
                distances[to] = distances[currentVertex] + weight;
                pq.push({distances[to], to});
            }
        }
    }

    // Возвращение результата выполнения алгоритма.
    return DijkstraResult{distances};
}

}  // namespace graph

#endif
