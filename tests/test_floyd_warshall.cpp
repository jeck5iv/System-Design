#include "floyd_warshall.hpp"
#include "gtest/gtest.h"

TEST(FloydWarshallTest, BaseTestMatrix) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 1);

    graph::FloydWarshall floyd_warshall(graph);
    auto floyd_warshall_result = floyd_warshall.run();
    std::vector<std::vector<std::int64_t>> correct_distances = {
        {0, 3, 1, 2}, {3, 0, 2, 3}, {1, 2, 0, 1}, {2, 3, 1, 0}};
    ASSERT_EQ(floyd_warshall_result.distances(), correct_distances);
    ASSERT_EQ(floyd_warshall_result.has_negative_cycles(), false);
}

TEST(FloydWarshallTest, NegativeCycleTest) {
    graph::AdjacencyMatrixGraph<int> graph(3, false);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 0, -3);

    graph::FloydWarshall floyd_warshall(graph);
    auto floyd_warshall_result = floyd_warshall.run();
    ASSERT_EQ(floyd_warshall_result.has_negative_cycles(), true);
}

TEST(FloydWarshallTest, DisconnectedGraphTest) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 1, 1);
    graph.addEdge(2, 3, 1);

    const auto inf = std::numeric_limits<std::int64_t>::max();

    graph::FloydWarshall floyd_warshall(graph);
    auto floyd_warshall_result = floyd_warshall.run();
    std::vector<std::vector<std::int64_t>> correct_distances = {
        {0, 1, inf, inf}, {1, 0, inf, inf}, {inf, inf, 0, 1}, {inf, inf, 1, 0}};
    ASSERT_EQ(floyd_warshall_result.distances(), correct_distances);
    ASSERT_EQ(floyd_warshall_result.has_negative_cycles(), false);
}

TEST(FloydWarshallTest, SingleNodeGraphTest) {
    graph::AdjacencyMatrixGraph<int> graph(1, false);

    graph::FloydWarshall floyd_warshall(graph);
    auto floyd_warshall_result = floyd_warshall.run();
    std::vector<std::vector<std::int64_t>> correct_distances = {{0}};
    ASSERT_EQ(floyd_warshall_result.distances(), correct_distances);
    ASSERT_EQ(floyd_warshall_result.has_negative_cycles(), false);
}

TEST(FloydWarshallTest, FullyConnectedGraphTest) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(0, 3, 1);

    graph::FloydWarshall floyd_warshall(graph);
    auto floyd_warshall_result = floyd_warshall.run();
    std::vector<std::vector<std::int64_t>> correct_distances = {
        {0, 1, 2, 1}, {1, 0, 1, 2}, {2, 1, 0, 1}, {1, 2, 1, 0}};
    ASSERT_EQ(floyd_warshall_result.distances(), correct_distances);
    ASSERT_EQ(floyd_warshall_result.has_negative_cycles(), false);
}

TEST(FloydWarshallTest, NoEdgesGraphTest) {
    graph::AdjacencyMatrixGraph<int> graph(3, false);

    const auto inf = std::numeric_limits<std::int64_t>::max();

    graph::FloydWarshall floyd_warshall(graph);
    auto floyd_warshall_result = floyd_warshall.run();
    std::vector<std::vector<std::int64_t>> correct_distances = {
        {0, inf, inf}, {inf, 0, inf}, {inf, inf, 0}};
    ASSERT_EQ(floyd_warshall_result.distances(), correct_distances);
    ASSERT_EQ(floyd_warshall_result.has_negative_cycles(), false);
}