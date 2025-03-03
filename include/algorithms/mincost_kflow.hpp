#ifndef MINCOST_KFLOW_HPP
#define MINCOST_KFLOW_HPP

#include <vector>
#include <queue>
#include <climits>
#include "graph.hpp"

namespace graph {

template <typename edgeType>
class MinCostKFlow {
public:
    MinCostKFlow(Graph<edgeType>& graph, int k)
        : m_graph(graph), m_k(k), m_flowCost(0), m_totalFlow(0) {}

    class MinCostKFlowResult {
    public:
        explicit MinCostKFlowResult(int flow, int cost)
            : m_flow(flow), m_cost(cost) {}

        int getFlow() const { return m_flow; }
        int getCost() const { return m_cost; }

    private:
        int m_flow;
        int m_cost;
    };

    MinCostKFlowResult run(int source, int sink);

private:
    Graph<edgeType>& m_graph;
    int m_k;
    int m_flowCost;
    int m_totalFlow;

    bool bellmanFord(int source, int sink, std::vector<int>& parent);
};

template <typename edgeType>
MinCostKFlow(AdjacencyListGraph<Edge<edgeType>>&) -> MinCostKFlow<edgeType>;

template <typename edgeType>
bool MinCostKFlow<edgeType>::bellmanFord(int source, int sink, std::vector<int>& parent) {
    std::vector<int> dist(m_graph.getSize(), INT_MAX);
    dist[source] = 0;
    parent.assign(m_graph.getSize(), -1);

    for (int i = 0; i < m_graph.getSize() - 1; ++i) {
        bool updated = false;
        for (int u = 0; u < m_graph.getSize(); ++u) {
            std::vector<Edge<edgeType>> neighbours;
            m_graph.getNeighbours(u, neighbours);

            for (const auto& edge : neighbours) {
                if (edge.flow() < edge.capacity() && dist[u] + edge.weight() < dist[edge.to()]) {
                    dist[edge.to()] = dist[u] + edge.weight();
                    parent[edge.to()] = u;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }

    return dist[sink] != INT_MAX;
}

template <typename edgeType>
MinCostKFlow<edgeType>::MinCostKFlowResult MinCostKFlow<edgeType>::run(int source, int sink) {
    std::vector<int> parent(m_graph.getSize(), -1);
    int totalFlow = 0;
    m_flowCost = 0;

    for (int i = 0; i < m_k; ++i) {
        if (!bellmanFord(source, sink, parent)) break;

        int flow = INT_MAX;
        for (int u = sink; u != source; u = parent[u]) {
            int v = parent[u];
            flow = std::min(flow, m_graph.getEdge(v, u).capacity() - m_graph.getEdge(v, u).flow());
        }

        for (int u = sink; u != source; u = parent[u]) {
            int v = parent[u];
            m_graph.getEdge(v, u).addFlow(flow);
            m_graph.getEdge(u, v).addFlow(-flow);
        }

        totalFlow += flow;
        m_flowCost += flow * m_graph.getEdge(parent[sink], sink).weight();
    }

    return MinCostKFlowResult(totalFlow, m_flowCost);
}

};  // namespace graph

#endif  // MINCOST_KFLOW_HPP
