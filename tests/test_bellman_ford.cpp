#include "bellman_ford.hpp"
#include "gtest/gtest.h"
#include "utility.hpp"

TEST(BellmanFordTest, BaseTest) {
    graph::AdjacencyMatrixGraph<int> graph(4, true);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 1);

    graph::BellmanFord<int> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);
    std::vector<std::int64_t> correct_distances = {0, 1, 3, 4};
    ASSERT_EQ(bellman_ford_result.distances(), correct_distances);
    ASSERT_EQ(bellman_ford_result.has_negative_cycles(), false);
}

TEST(BellmanFordTest, CustomEdgeTest) {
    graph::AdjacencyMatrixGraph<Edge> graph(5, true);
    graph.addEdge(0, 1, Edge(1, "aaa"));
    graph.addEdge(1, 2, Edge(2, "bbb"));
    graph.addEdge(2, 3, Edge(3, "ccc"));

    graph::BellmanFord<Edge> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);
    std::vector<std::int64_t> correct_distances = {0, 1, 3, 6,
                                                   std::numeric_limits<std::int64_t>::max()};
    ASSERT_EQ(bellman_ford_result.distances(), correct_distances);
}

TEST(BellmanFordTest, NegativeCycleTest) {
    graph::AdjacencyMatrixGraph<int> graph(3, true);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 0, -3);

    graph::BellmanFord<int> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);
    ASSERT_EQ(bellman_ford_result.has_negative_cycles(), true);
}

TEST(BellmanFordTest, DisconnectedGraphTest) {
    graph::AdjacencyMatrixGraph<int> graph(4, true);
    graph.addEdge(0, 1, 1);

    const auto inf = std::numeric_limits<std::int64_t>::max();

    graph::BellmanFord<int> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);
    std::vector<std::int64_t> correct_distances = {0, 1, inf, inf};
    ASSERT_EQ(bellman_ford_result.distances(), correct_distances);
    ASSERT_EQ(bellman_ford_result.has_negative_cycles(), false);
}

TEST(BellmanFordTest, SingleNodeGraphTest) {
    graph::AdjacencyMatrixGraph<int> graph(1, true);

    graph::BellmanFord<int> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);
    std::vector<std::int64_t> correct_distances = {0};
    ASSERT_EQ(bellman_ford_result.distances(), correct_distances);
    ASSERT_EQ(bellman_ford_result.has_negative_cycles(), false);
}

TEST(BellmanFordTest, FullyConnectedGraphTest) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 3);
    graph.addEdge(0, 3, 10);

    graph::BellmanFord<int> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);
    std::vector<std::int64_t> correct_distances = {0, 1, 3, 6};
    ASSERT_EQ(bellman_ford_result.distances(), correct_distances);
    ASSERT_EQ(bellman_ford_result.has_negative_cycles(), false);
}

TEST(BellmanFordTest, NoEdgesGraphTest) {
    graph::AdjacencyMatrixGraph<int> graph(3, true);

    const auto inf = std::numeric_limits<std::int64_t>::max();

    graph::BellmanFord<int> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);
    std::vector<std::int64_t> correct_distances = {0, inf, inf};
    ASSERT_EQ(bellman_ford_result.distances(), correct_distances);
    ASSERT_EQ(bellman_ford_result.has_negative_cycles(), false);
}

TEST(BellmanFordTest, AllNegativeWeightsTest) {
    graph::AdjacencyMatrixGraph<int> graph(3, false);
    graph.addEdge(0, 1, -1);
    graph.addEdge(1, 2, -2);
    graph.addEdge(0, 2, -4);

    graph::BellmanFord<int> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);

    ASSERT_EQ(bellman_ford_result.has_negative_cycles(), true);

    std::vector<std::int64_t> correct_distances = {0, -1, -3};
    ASSERT_TRUE(bellman_ford_result.distances()[0] <= correct_distances[0]);
    ASSERT_TRUE(bellman_ford_result.distances()[1] <= correct_distances[1]);
    ASSERT_TRUE(bellman_ford_result.distances()[2] <= correct_distances[2]);
}

TEST(BellmanFordTest, PathWithZeroWeightEdgesTest) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 1, 0);
    graph.addEdge(1, 2, 0);
    graph.addEdge(2, 3, 0);

    graph::BellmanFord<int> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);
    std::vector<std::int64_t> correct_distances = {0, 0, 0, 0};
    ASSERT_EQ(bellman_ford_result.distances(), correct_distances);
    ASSERT_EQ(bellman_ford_result.has_negative_cycles(), false);
}

TEST(BellmanFordTest, GuaranteedNegativeCycleLargeGraphTest) {
    const int num_vertices = 100;
    graph::AdjacencyMatrixGraph<int> graph(num_vertices, false);

    for (int i = 0; i < num_vertices - 1; ++i) {
        graph.addEdge(i, i + 1, 1);
    }

    graph.addEdge(num_vertices - 1, 0, -num_vertices);

    graph::BellmanFord<int> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);

    ASSERT_EQ(bellman_ford_result.has_negative_cycles(), true);
}

TEST(BellmanFordTest, NegativeCycleWithMultiplePathsTest) {
    graph::AdjacencyMatrixGraph<int> graph(4, true);
    graph.addEdge(0, 1, 5);
    graph.addEdge(1, 2, -10);
    graph.addEdge(2, 3, 5);
    graph.addEdge(3, 1, -5);

    graph::BellmanFord<int> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);

    ASSERT_EQ(bellman_ford_result.has_negative_cycles(), true);
}

TEST(BellmanFordTest, SelfLoopTest) {
    graph::AdjacencyMatrixGraph<int> graph(2, true);

    graph.addEdge(0, 0, -5);
    graph.addEdge(0, 1, 10);

    graph::BellmanFord<int> bellman_ford(graph);
    auto bellman_ford_result = bellman_ford.run(0);

    ASSERT_EQ(bellman_ford_result.has_negative_cycles(), true);
}
