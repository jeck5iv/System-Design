include(FetchContent)

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.6.0
)
set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_MakeAvailable(benchmark)

add_executable(benchmarks
        benchmarks_bfs1_k.cpp
        benchmarks_dijkstra.cpp
        main.cpp
)

target_link_libraries(benchmarks
        PRIVATE
        System_Design
        GTest::GTest
        GTest::Main
        benchmark
)
