#include "gtest/gtest.h"
#include "a_star.hpp"

double heuristic(int node, int goal) {
    // Простая эвристика: эвристика Манхэттенского расстояния
    return std::abs(node - goal);
}

TEST(AStarTest, BaseTest) {
    graph::AdjacencyMatrixGraph<int> graph(6, true);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(0, 3, 10);
    graph.addEdge(3, 4, 1);
    graph.addEdge(4, 2, 1);

    graph::AStar<int> astar(graph, heuristic);
    auto result = astar.run(0, 2);

    std::vector<int> expected_path = {0, 1, 2};
    ASSERT_EQ(result.getPath(), expected_path);
}

TEST(AStarTest, NoPath) {
    graph::AdjacencyMatrixGraph<int> graph(6, true);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);

    graph::AStar<int> astar(graph, heuristic);
    auto result = astar.run(0, 4);

    ASSERT_TRUE(result.getPath().empty());  // Путь не существует
}

TEST(AStarTest, SingleNode) {
    graph::AdjacencyMatrixGraph<int> graph(1, true);

    graph::AStar<int> astar(graph, heuristic);
    auto result = astar.run(0, 0);

    std::vector<int> expected_path = {0};
    ASSERT_EQ(result.getPath(), expected_path);
}

TEST(AStarTest, MultiplePaths) {
    graph::AdjacencyMatrixGraph<int> graph(6, true);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(0, 3, 5);
    graph.addEdge(3, 4, 1);
    graph.addEdge(4, 2, 1);
    graph.addEdge(2, 5, 1);

    graph::AStar<int> astar(graph, heuristic);
    auto result = astar.run(0, 5);

    std::vector<int> expected_path = {0, 1, 2, 5};
    ASSERT_EQ(result.getPath(), expected_path);
}
