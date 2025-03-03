#include "gtest/gtest.h"
#include "dinics.hpp"

TEST(DinicsTest, BaseTest) {
    graph::Dinic<int> dinic(6);
    dinic.addEdge(0, 1, 10);
    dinic.addEdge(0, 2, 10);
    dinic.addEdge(1, 2, 2);
    dinic.addEdge(1, 3, 8);
    dinic.addEdge(2, 4, 9);
    dinic.addEdge(3, 5, 10);
    dinic.addEdge(4, 5, 10);

    int result = dinic.maxFlow(0, 5);
    ASSERT_EQ(result, 19);  // Максимальный поток в графе
}

TEST(DinicsTest, NoPath) {
    graph::Dinic<int> dinic(6);
    dinic.addEdge(0, 1, 10);
    dinic.addEdge(1, 2, 2);
    dinic.addEdge(2, 3, 10);

    int result = dinic.maxFlow(0, 5);
    ASSERT_EQ(result, 0);  // Нет пути от истока к стоку
}

TEST(DinicsTest, SimpleGraph) {
    graph::Dinic<int> dinic(4);
    dinic.addEdge(0, 1, 5);
    dinic.addEdge(1, 2, 5);
    dinic.addEdge(2, 3, 5);

    int result = dinic.maxFlow(0, 3);
    ASSERT_EQ(result, 5);  // Поток равен 5
}
