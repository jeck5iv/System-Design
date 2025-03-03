include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest)

add_library(GTest::Main INTERFACE IMPORTED)
target_link_libraries(GTest::Main INTERFACE gtest_main)

add_executable(tests
        test_bfs1k.cpp
        test_dijkstra.cpp
        test_graph.cpp
        test_floyd_warshall.cpp
        test_kuhn.cpp
        test_bellman_ford.cpp
        main.cpp
)

target_link_libraries(tests
        PRIVATE
        System_Design
        GTest::GTest
        GTest::Main
)

add_subdirectory(benchmarks)

enable_testing()
add_test(bfs1k_gtests tests)
