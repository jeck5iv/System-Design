#include "gtest/gtest.h"
#include "kuhn.hpp"

TEST(KuhnMatchingTest, BaseTestBipartiteGraph) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 2, 1);  // Ребро между первой долей (0, 1) и второй долей (2, 3)
    graph.addEdge(0, 3, 1);
    graph.addEdge(1, 2, 1);

    graph::KuhnMatching kuhn_matching(graph);
    auto kuhn_matching_result = kuhn_matching.run();
    std::vector<std::int32_t> correct_matching = {-1, -1, 1, 0};  // Ожидаемое паросочетание
    ASSERT_EQ(kuhn_matching_result.matching(), correct_matching);
}

TEST(KuhnMatchingTesta, BaseTestBipartiteGraph) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 2, 1);  // Ребро между первой долей (0, 1) и второй долей (2, 3)
    graph.addEdge(0, 3, 1);
    graph.addEdge(1, 2, 1);

    graph::KuhnMatching kuhn_matching(graph);
    auto kuhn_matching_result = kuhn_matching.run();
    std::vector<std::int32_t> correct_matching = {-1, -1, 1, 0};  // Ожидаемое паросочетание
    ASSERT_EQ(kuhn_matching_result.matching(), correct_matching);
}

TEST(KuhnMatchingTestb, BaseTestBipartiteGraph) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 2, 1);  // Ребро между первой долей (0, 1) и второй долей (2, 3)
    graph.addEdge(0, 3, 1);
    graph.addEdge(1, 2, 1);

    graph::KuhnMatching kuhn_matching(graph);
    auto kuhn_matching_result = kuhn_matching.run();
    std::vector<std::int32_t> correct_matching = {-1, -1, 1, 0};  // Ожидаемое паросочетание
    ASSERT_EQ(kuhn_matching_result.matching(), correct_matching);
}

TEST(KuhnMatchingTestc, BaseTestBipartiteGraph) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 2, 1);  // Ребро между первой долей (0, 1) и второй долей (2, 3)
    graph.addEdge(0, 3, 1);
    graph.addEdge(1, 2, 1);

    graph::KuhnMatching kuhn_matching(graph);
    auto kuhn_matching_result = kuhn_matching.run();
    std::vector<std::int32_t> correct_matching = {-1, -1, 1, 0};  // Ожидаемое паросочетание
    ASSERT_EQ(kuhn_matching_result.matching(), correct_matching);
}

TEST(KuhnMatchingTestd, BaseTestBipartiteGraph) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 2, 1);  // Ребро между первой долей (0, 1) и второй долей (2, 3)
    graph.addEdge(0, 3, 1);
    graph.addEdge(1, 2, 1);

    graph::KuhnMatching kuhn_matching(graph);
    auto kuhn_matching_result = kuhn_matching.run();
    std::vector<std::int32_t> correct_matching = {-1, -1, 1, 0};  // Ожидаемое паросочетание
    ASSERT_EQ(kuhn_matching_result.matching(), correct_matching);
}

TEST(KuhnMatchingTeste, BaseTestBipartiteGraph) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 2, 1);  // Ребро между первой долей (0, 1) и второй долей (2, 3)
    graph.addEdge(0, 3, 1);
    graph.addEdge(1, 2, 1);

    graph::KuhnMatching kuhn_matching(graph);
    auto kuhn_matching_result = kuhn_matching.run();
    std::vector<std::int32_t> correct_matching = {-1, -1, 1, 0};  // Ожидаемое паросочетание
    ASSERT_EQ(kuhn_matching_result.matching(), correct_matching);
}
