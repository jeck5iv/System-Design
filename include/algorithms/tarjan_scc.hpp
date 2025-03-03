#ifndef TARJAN_SCC_HPP
#define TARJAN_SCC_HPP

#include <algorithm>
#include <cstdint>
#include <stack>
#include <vector>

#include "graph.hpp"

namespace graph {

template <typename edgeType>
class TarjanSCC {
public:
    explicit TarjanSCC(Graph<edgeType>& graph) : m_graph(graph) {}

    // Результат работы алгоритма: список сильно связных компонент
    class SCCResult {
    public:
        explicit SCCResult(std::vector<std::vector<std::int32_t>> scc) : m_scc(std::move(scc)) {}

        [[nodiscard]] const std::vector<std::vector<std::int32_t>>& getSCC() const { return m_scc; }

    private:
        std::vector<std::vector<std::int32_t>> m_scc;
    };

    SCCResult run();

private:
    void dfs(std::int32_t v, std::vector<std::int32_t>& lowLink,
             std::vector<std::int32_t>& preOrder, std::vector<bool>& onStack,
             std::stack<std::int32_t>& stack, std::vector<std::vector<std::int32_t>>& result);

    Graph<edgeType>& m_graph;
};

template <typename edgeType>
TarjanSCC(AdjacencyListGraph<Edge<edgeType>>&) -> TarjanSCC<edgeType>;

template <typename edgeType>
typename TarjanSCC<edgeType>::SCCResult TarjanSCC<edgeType>::run() {
    std::vector<std::int32_t> lowLink(m_graph.numberVertices(), -1);
    std::vector<std::int32_t> preOrder(m_graph.numberVertices(), -1);
    std::vector<bool> onStack(m_graph.numberVertices(), false);
    std::stack<std::int32_t> stack;
    std::vector<std::vector<std::int32_t>> result;
    std::int32_t currentOrder = 0;

    for (std::int32_t v = 0; v < m_graph.numberVertices(); ++v) {
        if (preOrder[v] == -1) {
            dfs(v, lowLink, preOrder, onStack, stack, result);
        }
    }

    return SCCResult{result};
}

template <typename edgeType>
void TarjanSCC<edgeType>::dfs(std::int32_t v, std::vector<std::int32_t>& lowLink,
                              std::vector<std::int32_t>& preOrder, std::vector<bool>& onStack,
                              std::stack<std::int32_t>& stack,
                              std::vector<std::vector<std::int32_t>>& result) {
    preOrder[v] = lowLink[v] = currentOrder++;
    stack.push(v);
    onStack[v] = true;

    std::vector<Edge<edgeType>> neighbours;
    m_graph.getNeighbours(v, neighbours);
    for (const auto& edge : neighbours) {
        std::int32_t to = edge.to();
        if (preOrder[to] == -1) {
            dfs(to, lowLink, preOrder, onStack, stack, result);
            lowLink[v] = std::min(lowLink[v], lowLink[to]);
        } else if (onStack[to]) {
            lowLink[v] = std::min(lowLink[v], preOrder[to]);
        }
    }

    if (lowLink[v] == preOrder[v]) {
        std::vector<std::int32_t> scc;
        while (true) {
            std::int32_t w = stack.top();
            stack.pop();
            onStack[w] = false;
            scc.push_back(w);
            if (w == v) break;
        }
        result.push_back(std::move(scc));
    }
}

};  // namespace graph

#endif  // TARJAN_SCC_HPP
