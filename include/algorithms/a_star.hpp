#ifndef A_STAR_HPP
#define A_STAR_HPP

#include <cmath>
#include <functional>
#include <queue>
#include <unordered_map>
#include <vector>

#include "graph.hpp"

namespace graph {

template <typename edgeType>
class AStar {
public:
    AStar(Graph<edgeType>& graph, std::function<double(int, int)> heuristic)
        : m_graph(graph), m_heuristic(heuristic) {}

    // Результат работы алгоритма: кратчайший путь от start до goal
    class AStarResult {
    public:
        explicit AStarResult(std::vector<int> path) : m_path(std::move(path)) {}

        [[nodiscard]] const std::vector<int>& getPath() const { return m_path; }

    private:
        std::vector<int> m_path;
    };

    AStarResult run(int start, int goal);

private:
    Graph<edgeType>& m_graph;
    std::function<double(int, int)> m_heuristic;
};

template <typename edgeType>
AStar(AdjacencyListGraph<Edge<edgeType>>&) -> AStar<edgeType>;

template <typename edgeType>
typename AStar<edgeType>::AStarResult AStar<edgeType>::run(int start, int goal) {
    std::unordered_map<int, double> gScore;
    std::unordered_map<int, double> fScore;
    std::unordered_map<int, int> cameFrom;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>>
        openSet;

    gScore[start] = 0;
    fScore[start] = m_heuristic(start, goal);
    openSet.push({fScore[start], start});

    while (!openSet.empty()) {
        int current = openSet.top().second;
        openSet.pop();

        if (current == goal) {
            std::vector<int> path;
            while (cameFrom.find(current) != cameFrom.end()) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return AStarResult{path};
        }

        std::vector<Edge<edgeType>> neighbors;
        m_graph.getNeighbours(current, neighbors);

        for (const auto& edge : neighbors) {
            int neighbor = edge.to();
            double tentative_gScore = gScore[current] + edge.weight();

            if (gScore.find(neighbor) == gScore.end() || tentative_gScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                fScore[neighbor] = gScore[neighbor] + m_heuristic(neighbor, goal);
                openSet.push({fScore[neighbor], neighbor});
            }
        }
    }

    return AStarResult{{}};  // Путь не найден
}

};  // namespace graph

#endif  // A_STAR_HPP
