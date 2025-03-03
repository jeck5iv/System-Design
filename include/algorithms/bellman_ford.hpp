#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include <algorithm>
#include <limits>
#include <vector>

#include "graph.hpp"

namespace graph {

template <typename edgeType>
concept OutputStreamable = requires(std::ostream& os, const edgeType& obj) {
    os << obj;  // Проверяем, что результат можно передать в std::ostream
};

template <typename edgeType>
concept Addable = requires(const edgeType& a, const edgeType& b) {
    { a + b } -> std::convertible_to<edgeType>;  // Проверяем, что результат можно преобразовать к T
};

template <typename edgeType>
concept IntAddable = requires(std::int64_t value, const edgeType& obj) {
    {
        value + obj
        } -> std::convertible_to<std::int64_t>;  // Проверяем, что результат можно преобразовать к
                                                 // int64_t
};

template <typename edgeType>
requires OutputStreamable<edgeType> && Addable<edgeType> && IntAddable<edgeType>
class BellmanFord {
public:
    // Конструктор, принимающий граф и начальную вершину для выполнения алгоритма Форда-Беллмана
    BellmanFord(Graph<edgeType>& graph) : m_graph(graph) {}

    // Класс для хранения результата выполнения алгоритма Форда-Беллмана
    class BellmanFordResult {
    public:
        // Конструктор, принимающий вектор расстояний и флаг наличия отрицательных циклов
        BellmanFordResult(std::vector<std::int64_t>& distances, bool has_negative_cycles)
            : m_distances(distances), m_has_negative_cycles(has_negative_cycles) {}

        // Метод для получения вектора расстояний
        [[nodiscard]] const std::vector<std::int64_t>& distances() const { return m_distances; }

        // Метод для проверки наличия отрицательных циклов
        [[nodiscard]] const bool has_negative_cycles() const { return m_has_negative_cycles; }

    private:
        std::vector<std::int64_t> m_distances;  // Вектор расстояний
        bool m_has_negative_cycles;  // Флаг наличия отрицательных циклов
    };

    // Метод для запуска алгоритма Форда-Беллмана
    BellmanFordResult run(std::int32_t start_vertex);

private:
    Graph<edgeType>& m_graph;  // Ссылка на граф
};

// Дедукция шаблона для конструктора BellmanFord
template <typename edgeType>
requires OutputStreamable<edgeType> && Addable<edgeType> && IntAddable<edgeType> BellmanFord(
    Graph<edgeType>&, int)
->BellmanFord<edgeType>;

// Реализация метода run() для алгоритма Форда-Беллмана
template <typename edgeType>
requires OutputStreamable<edgeType> && Addable<edgeType> && IntAddable<edgeType>
typename BellmanFord<edgeType>::BellmanFordResult BellmanFord<edgeType>::run(
    std::int32_t start_vertex) {
    if (!m_graph.isVertexValid(start_vertex)) {
        std::stringstream error;
        error << "Start vertex is out of bounds: " << start_vertex << '\n';
        throw std::domain_error(error.str());
    }
    const std::int64_t INF = std::numeric_limits<std::int64_t>::max();

    // Инициализация вектора расстояний бесконечными значениями
    std::vector<std::int64_t> distances(m_graph.numberVertices(), INF);
    distances[start_vertex] = 0;  // Расстояние до начальной вершины равно 0

    // Основной цикл алгоритма Форда-Беллмана
    for (std::int32_t iteration = 0; iteration < m_graph.numberVertices() - 1; ++iteration) {
        for (std::int32_t vertex = 0; vertex < m_graph.numberVertices(); ++vertex) {
            std::vector<Edge<edgeType>> neighbours;
            m_graph.getNeighbours(vertex, neighbours);
            for (const auto& edge : neighbours) {
                if (distances[vertex] != INF &&
                    distances[vertex] + edge.edge() < distances[edge.to()]) {
                    distances[edge.to()] = distances[vertex] + edge.edge();
                }
            }
        }
    }

    // Проверка наличия отрицательных циклов
    bool has_negative_cycles = false;

    for (std::int32_t vertex = 0; vertex < m_graph.numberVertices(); ++vertex) {
        std::vector<Edge<edgeType>> neighbours;
        m_graph.getNeighbours(vertex, neighbours);
        for (const auto& edge : neighbours) {
            if (distances[vertex] != INF &&
                distances[vertex] + edge.edge() < distances[edge.to()]) {
                has_negative_cycles = true;
            }
        }
    }

    // Возвращение результата выполнения алгоритма
    return BellmanFordResult{distances, has_negative_cycles};
}

};  // namespace graph

#endif  // BELLMAN_FORD_HPP
