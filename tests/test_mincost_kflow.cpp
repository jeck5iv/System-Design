#include "gtest/gtest.h"
#include "mincost_kflow.hpp"

TEST(MinCostKFlowTest, BaseTest) {
    graph::AdjacencyMatrixGraph<int> graph(6, true);
    graph.addEdge(0, 1, 1, 10);
    graph.addEdge(1, 2, 1, 10);
    graph.addEdge(0, 3, 1, 5);
    graph.addEdge(3, 4, 1, 5);
    graph.addEdge(4, 2, 1, 10);
    graph.addEdge(2, 5, 1, 10);
    graph.addEdge(3, 5, 1, 15);

    graph::MinCostKFlow<int> minCostKFlow(graph, 2);
    auto result = minCostKFlow.run(0, 5);

    ASSERT_EQ(result.getFlow(), 2);
    ASSERT_EQ(result.getCost(), 25);
}

TEST(MinCostKFlowTest, NoPath) {
    graph::AdjacencyMatrixGraph<int> graph(6, true);
    graph.addEdge(0, 1, 1, 10);
    graph.addEdge(1, 2, 1, 10);

    graph::MinCostKFlow<int> minCostKFlow(graph, 2);
    auto result = minCostKFlow.run(0, 5);

    ASSERT_EQ(result.getFlow(), 0);
    ASSERT_EQ(result.getCost(), 0);
}

TEST(MinCostKFlowTest, SingleFlow) {
    graph::AdjacencyMatrixGraph<int> graph(6, true);
    graph.addEdge(0, 1, 1, 10);
    graph.addEdge(1, 2, 1, 10);
    graph.addEdge(2, 5, 1, 10);

    graph::MinCostKFlow<int> minCostKFlow(graph, 1);
    auto result = minCostKFlow.run(0, 5);

    ASSERT_EQ(result.getFlow(), 1);
    ASSERT_EQ(result.getCost(), 30);
}

TEST(MinCostKFlowTest, MultipleFlows) {
    graph::AdjacencyMatrixGraph<int> graph(6, true);
    graph.addEdge(0, 1, 1, 5);
    graph.addEdge(1, 2, 1, 5);
    graph.addEdge(2, 5, 1, 5);
    graph.addEdge(0, 3, 1, 3);
    graph.addEdge(3, 4, 1, 3);
    graph.addEdge(4, 5, 1, 3);

    graph::MinCostKFlow<int> minCostKFlow(graph, 2);
    auto result = minCostKFlow.run(0, 5);

    ASSERT_EQ(result.getFlow(), 2);
    ASSERT_EQ(result.getCost(), 16);
}
