#ifndef KUHN_MATCHING_HPP
#define KUHN_MATCHING_HPP

#include <cstdint>
#include <vector>

#include "graph.hpp"

namespace graph {

template <typename edgeType>
class KuhnMatching {
public:
    explicit KuhnMatching(Graph<edgeType>& graph) : m_graph(graph) {}

    class MatchingResult {
    public:
        explicit MatchingResult(const std::vector<std::int32_t>& matching) : m_matching(matching) {}

        [[nodiscard]] const std::vector<std::int32_t>& matching() const { return m_matching; }

    private:
        std::vector<std::int32_t> m_matching;
    };

    // Метод для запуска алгоритма Куна
    MatchingResult run();

private:
    bool tryKuhn(std::int32_t v, std::vector<bool>& used, std::vector<std::int32_t>& matching);

    Graph<edgeType>& m_graph;
};

template <typename edgeType>
KuhnMatching(AdjacencyListGraph<Edge<edgeType>>&) -> KuhnMatching<edgeType>;

template <typename edgeType>
typename KuhnMatching<edgeType>::MatchingResult KuhnMatching<edgeType>::run() {
    std::vector<std::int32_t> matching(m_graph.numberVertices(), -1);
    std::vector<bool> used(m_graph.numberVertices(), false);

    for (std::int32_t v = 0; v < m_graph.numberVertices(); ++v) {
        if (matching[v] == -1) {
            used.assign(m_graph.numberVertices(), false);
            tryKuhn(v, used, matching);
        }
    }

    return MatchingResult{matching};
}

template <typename edgeType>
bool KuhnMatching<edgeType>::tryKuhn(std::int32_t v, std::vector<bool>& used,
                                     std::vector<std::int32_t>& matching) {
    if (used[v]) {
        return false;
    }
    used[v] = true;

    std::vector<Edge<edgeType>> neighbours;
    m_graph.getNeighbours(v, neighbours);
    for (const auto& edge : neighbours) {
        std::int32_t to = edge.to();
        if (matching[to] == -1 || tryKuhn(matching[to], used, matching)) {
            matching[to] = v;
            return true;
        }
    }

    return false;
}

};  // namespace graph

#endif  // KUHN_MATCHING_HPP
