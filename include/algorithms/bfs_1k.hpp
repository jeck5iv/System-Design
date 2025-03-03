#ifndef BFS_1K_HPP
#define BFS_1K_HPP

#include <concepts>
#include <limits>
#include <queue>

#include "graph.hpp"

namespace graph {

// Класс BFS_1k реализует алгоритм 1-k BFS для графа с ограниченными весами рёбер.
template <typename edgeType>
concept OutputStreamable = requires(std::ostream& os, const edgeType& obj) {
    os << obj;  // Проверяем, что результат можно передать в std::ostream
};

template <typename edgeType>
concept Addable = requires(const edgeType& a, const edgeType& b) {
    { a + b } -> std::convertible_to<edgeType>;  // Проверяем, что результат можно преобразовать к T
};

template <typename edgeType>
concept IntAddable = requires(std::int32_t value, const edgeType& obj) {
    {
        value + obj
        } -> std::convertible_to<std::int32_t>;  // Проверяем, что результат можно преобразовать к
                                                 // int32_t
};

// Класс BFS_1k реализует алгоритм 1-k BFS для графа с ограниченными весами рёбер.
template <typename edgeType>
requires OutputStreamable<edgeType> && Addable<edgeType> && IntAddable<edgeType>
class BFS_1k {
public:
    // Конструктор, принимающий граф и максимальный вес ребра.
    BFS_1k(Graph<edgeType>& graph, std::int32_t maxWeight)
        : m_graph(graph), m_maxWeight(maxWeight) {}

    // Вложенный класс BFSResult для хранения результатов выполнения алгоритма.
    class BFSResult {
    public:
        // Конструктор, принимающий векторы расстояний и достижимости.
        BFSResult(const std::vector<std::int32_t>& distances,
                  const std::vector<std::int32_t>& accessibility)
            : m_distances(distances), m_accessibility(accessibility) {}

        // Метод для получения вектора расстояний.
        [[nodiscard]] const std::vector<std::int32_t>& distances() const { return m_distances; }

        // Метод для получения вектора достижимости.
        [[nodiscard]] const std::vector<std::int32_t>& accessibility() const {
            return m_accessibility;
        }

    private:
        std::vector<std::int32_t> m_distances;  // Вектор расстояний от стартовой вершины.
        std::vector<std::int32_t> m_accessibility;  // Вектор достижимости вершин.
    };

    // Метод для запуска алгоритма 1-k BFS.
    BFSResult run(std::int32_t startVertex);

private:
    Graph<edgeType>& m_graph;  // Ссылка на граф.
    std::int32_t m_maxWeight;  // Максимальный вес ребра.
};

// Дедукция шаблона для упрощения создания объекта BFS_1k.
template <typename edgeType>
requires OutputStreamable<edgeType> && Addable<edgeType> && IntAddable<edgeType> BFS_1k(
    Graph<Edge<edgeType>>&, int, int)
->BFS_1k<edgeType>;

// Реализация метода run, который выполняет алгоритм 1-k BFS.
template <typename edgeType>
requires OutputStreamable<edgeType> && Addable<edgeType> && IntAddable<edgeType>
typename BFS_1k<edgeType>::BFSResult BFS_1k<edgeType>::run(std::int32_t startVertex) {
    // Инициализация вектора расстояний бесконечностью.
    std::vector<std::int32_t> distances(m_graph.numberVertices(),
                                        std::numeric_limits<std::int32_t>::max());
    // Инициализация вектора достижимости нулями.
    std::vector<std::int32_t> reachability(m_graph.numberVertices());
    // Расстояние до стартовой вершины равно 0.
    distances[startVertex] = 0;

    // Очереди для хранения вершин на каждом уровне расстояния.
    std::queue<std::int32_t> queues[m_maxWeight + 1];
    queues[0].push(startVertex);

    // Количество вершин в очередях и текущее расстояние.
    std::int32_t numberOfVerticesInQueues = 1, currentDistance = 0;
    while (numberOfVerticesInQueues) {
        // Пропуск пустых очередей.
        while (queues[currentDistance % (m_maxWeight + 1)].empty()) {
            currentDistance++;
        }

        // Извлечение текущей вершины из очереди.
        std::int32_t currentVertex = queues[currentDistance % (m_maxWeight + 1)].front();
        queues[currentDistance % (m_maxWeight + 1)].pop();
        --numberOfVerticesInQueues;

        // Если вершина уже была обработана, пропуск.
        if (reachability[currentVertex]) {
            continue;
        }
        reachability[currentVertex] = true;

        // Получение соседей текущей вершины.
        std::vector<Edge<edgeType>> neighbours;
        m_graph.getNeighbours(currentVertex, neighbours);
        for (const auto& edge : neighbours) {
            // Вычисление нового расстояния.
            std::int32_t newDistance = currentDistance + edge.edge();
            // Если новое расстояние меньше текущего, обновление.
            if (newDistance < distances[edge.to()]) {
                distances[edge.to()] = newDistance;
                queues[newDistance % (m_maxWeight + 1)].push(edge.to());
                ++numberOfVerticesInQueues;
            }
        }
    }

    // Возвращение результата выполнения алгоритма.
    return BFSResult{distances, reachability};
}

};  // namespace graph

#endif  // BFS_1K_HPP
