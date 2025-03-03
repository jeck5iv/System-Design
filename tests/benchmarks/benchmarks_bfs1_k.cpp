#include <benchmark/benchmark.h>

#include <chrono>
#include <random>

#include "bfs_1k.hpp"

static std::mt19937 myRandom(std::chrono::steady_clock::now().time_since_epoch().count());

static constexpr std::int32_t STEP = 2;

static constexpr std::int32_t NUMBER_OF_EDGES_ADJLIST = 10;
static constexpr std::int32_t MIN_NUMBER_OF_VERTEXES_ADJLIST = 10;
static constexpr std::int32_t MAX_NUMBER_OF_VERTEXES_ADJLIST = 100000;

static void BM_BFS_AdjacencyListGraph(benchmark::State &state) {
    const std::int32_t numberOfVertexes = state.range(0);
    const std::int32_t numberOfEdges = NUMBER_OF_EDGES_ADJLIST * numberOfVertexes;
    const std::int32_t maxWeight = numberOfVertexes;
    graph::AdjacencyListGraph<int> graph(numberOfVertexes, false);
    for (int i = 0; i < numberOfEdges; i++) {
        std::int32_t vertex1 = myRandom() % numberOfVertexes;
        std::int32_t vertex2 = myRandom() % numberOfVertexes;
        std::int32_t weight = myRandom() % maxWeight + 1;
        graph.addEdge(vertex1, vertex2, weight);
    }
    for (auto _ : state) {
        graph::BFS_1k bfs(graph, maxWeight);
        benchmark::DoNotOptimize(bfs.run(0));
    }
}

BENCHMARK(BM_BFS_AdjacencyListGraph)
    ->Range(MIN_NUMBER_OF_VERTEXES_ADJLIST, MAX_NUMBER_OF_VERTEXES_ADJLIST)
    ->RangeMultiplier(STEP);

static constexpr std::int32_t NUMBER_OF_EDGES_ADJMATRIX = 3;
static constexpr std::int32_t MIN_NUMBER_OF_VERTEXES_ADJMATRIX = 10;
static constexpr std::int32_t MAX_NUMBER_OF_VERTEXES_ADJMATRIX = 10000;

static void BM_BFS_AdjacencyMatrixGraph(benchmark::State &state) {
    const std::int32_t numberOfVertexes = state.range(0);
    const std::int32_t numberOfEdges = NUMBER_OF_EDGES_ADJMATRIX * numberOfVertexes;
    const std::int32_t maxWeight = numberOfVertexes;
    graph::AdjacencyMatrixGraph<int> graph(numberOfVertexes, false);
    for (int i = 0; i < numberOfEdges; i++) {
        std::int32_t vertex1 = myRandom() % numberOfVertexes;
        std::int32_t vertex2 = myRandom() % numberOfVertexes;
        std::int32_t weight = myRandom() % maxWeight + 1;
        graph.addEdge(vertex1, vertex2, weight);
    }
    for (auto _ : state) {
        graph::BFS_1k bfs(graph, maxWeight);
        benchmark::DoNotOptimize(bfs.run(0));
    }
}

BENCHMARK(BM_BFS_AdjacencyMatrixGraph)
    ->Range(MIN_NUMBER_OF_VERTEXES_ADJMATRIX, MAX_NUMBER_OF_VERTEXES_ADJMATRIX)
    ->RangeMultiplier(STEP);
