#include "gtest/gtest.h"
#include "tarjan_scc.hpp"

TEST(TarjanSCCTest, BaseTest) {
    graph::AdjacencyMatrixGraph<int> graph(5, true);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 0, 1);
    graph.addEdge(3, 4, 1);

    graph::TarjanSCC tarjan_scc(graph);
    auto scc_result = tarjan_scc.run();

    std::vector<std::vector<std::int32_t>> correct_scc = {
        {0, 1, 2},  // Первая сильно связная компонента
        {3, 4}      // Вторая сильно связная компонента
    };

    ASSERT_EQ(scc_result.getSCC(), correct_scc);
}

TEST(TarjanSCCTest, SingleNode) {
    graph::AdjacencyMatrixGraph<int> graph(1, true);

    graph::TarjanSCC tarjan_scc(graph);
    auto scc_result = tarjan_scc.run();

    std::vector<std::vector<std::int32_t>> correct_scc = {
        {0}  // Единственная компонента, содержащая только одну вершину
    };

    ASSERT_EQ(scc_result.getSCC(), correct_scc);
}

TEST(TarjanSCCTest, DisconnectedGraph) {
    graph::AdjacencyMatrixGraph<int> graph(6, true);
    graph.addEdge(0, 1, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(4, 5, 1);

    graph::TarjanSCC tarjan_scc(graph);
    auto scc_result = tarjan_scc.run();

    std::vector<std::vector<std::int32_t>> correct_scc = {
        {0, 1},  // Первая компонента
        {2, 3},  // Вторая компонента
        {4, 5}   // Третья компонента
    };

    ASSERT_EQ(scc_result.getSCC(), correct_scc);
}

TEST(TarjanSCCTest, SingleEdgeCycle) {
    graph::AdjacencyMatrixGraph<int> graph(3, true);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 0, 1);

    graph::TarjanSCC tarjan_scc(graph);
    auto scc_result = tarjan_scc.run();

    std::vector<std::vector<std::int32_t>> correct_scc = {
        {0, 1, 2}  // Единая компонента, состоящая из трех вершин, образующих цикл
    };

    ASSERT_EQ(scc_result.getSCC(), correct_scc);
}
