#ifndef FLOYD_WARSHALL_HPP
#define FLOYD_WARSHALL_HPP

#include <algorithm>
#include <limits>

#include "graph.hpp"

namespace graph {

template <typename edgeType>
class FloydWarshall {
public:
    // Конструктор, принимающий граф для выполнения алгоритма Флойда-Уоршелла
    explicit FloydWarshall(Graph<edgeType>& graph) : m_graph(graph) {}

    // Класс для хранения результата выполнения алгоритма Флойда-Уоршелла
    class FloydWarshallResult {
    public:
        // Конструктор, принимающий матрицу расстояний и флаг наличия отрицательных циклов
        FloydWarshallResult(std::vector<std::vector<std::int64_t>>& distances,
                            bool has_negative_cycles)
            : m_distances(distances), m_has_negative_cycles(has_negative_cycles) {}

        // Метод для получения матрицы расстояний
        [[nodiscard]] const std::vector<std::vector<std::int64_t>>& distances() const {
            return m_distances;
        }

        // Метод для проверки наличия отрицательных циклов
        [[nodiscard]] const bool has_negative_cycles() const { return m_has_negative_cycles; }

    private:
        std::vector<std::vector<std::int64_t>> m_distances;  // Матрица расстояний
        bool m_has_negative_cycles;  // Флаг наличия отрицательных циклов
    };

    // Метод для запуска алгоритма Флойда-Уоршелла
    FloydWarshallResult run();

private:
    Graph<edgeType>& m_graph;  // Ссылка на граф
};

// Дедукция шаблона для конструктора FloydWarshall
template <typename edgeType>
FloydWarshall(AdjacencyMatrixGraph<Edge<edgeType>>&, int, int) -> FloydWarshall<edgeType>;

// Реализация метода run() для алгоритма Флойда-Уоршелла
template <typename edgeType>
typename FloydWarshall<edgeType>::FloydWarshallResult FloydWarshall<edgeType>::run() {
    // Инициализация матрицы расстояний бесконечными значениями
    std::vector<std::vector<std::int64_t>> distances(
        m_graph.numberVertices(),
        std::vector<std::int64_t>(m_graph.numberVertices(),
                                  std::numeric_limits<std::int64_t>::max()));

    // Заполнение матрицы расстояний начальными значениями
    for (std::int32_t vertex = 0; vertex < m_graph.numberVertices(); vertex++) {
        distances[vertex][vertex] = 0;  // Расстояние от вершины до самой себя равно 0

        std::vector<Edge<edgeType>> neighbours;
        m_graph.getNeighbours(vertex, neighbours);
        for (const auto& edge : neighbours) {
            distances[vertex][edge.to()] =
                std::min(distances[vertex][edge.to()], static_cast<std::int64_t>(edge.edge()));
        }
    }

    // Основной цикл алгоритма Флойда-Уоршелла
    for (std::int32_t mid_vertex = 0; mid_vertex < m_graph.numberVertices(); mid_vertex++) {
        for (std::int32_t begin_vertex = 0; begin_vertex < m_graph.numberVertices();
             begin_vertex++) {
            for (std::int32_t end_vertex = 0; end_vertex < m_graph.numberVertices(); end_vertex++) {
                // Обновление расстояний через промежуточную вершину
                if (distances[begin_vertex][mid_vertex] !=
                        std::numeric_limits<std::int64_t>::max() &&
                    distances[mid_vertex][end_vertex] != std::numeric_limits<std::int64_t>::max()) {
                    distances[begin_vertex][end_vertex] = std::min(
                        distances[begin_vertex][end_vertex],
                        distances[begin_vertex][mid_vertex] + distances[mid_vertex][end_vertex]);
                }
            }
        }
    }

    // Проверка наличия отрицательных циклов
    bool has_negative_cycles = false;

    for (std::int32_t vertex = 0; vertex < m_graph.numberVertices(); vertex++) {
        has_negative_cycles |= (distances[vertex][vertex] != 0);
    }

    // Возвращение результата выполнения алгоритма
    return FloydWarshallResult{distances, has_negative_cycles};
}

};  // namespace graph

#endif  // FLOYD_WARSHALL_HPP
