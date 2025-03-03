#ifndef DINICS_HPP
#define DINICS_HPP

#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace graph {

template <typename T>
class Dinic {
public:
    Dinic(int n) : n(n), graph(n), level(n), ptr(n) {}

    void addEdge(int u, int v, T cap) {
        graph[u].emplace_back(v, cap, graph[v].size());
        graph[v].emplace_back(u, 0, graph[u].size() - 1);
    }

    T maxFlow(int source, int sink);

private:
    struct Edge {
        int v;
        T cap;
        size_t rev;

        Edge(int v, T cap, size_t rev) : v(v), cap(cap), rev(rev) {}
    };

    bool bfs(int source, int sink);
    T dfs(int u, int sink, T flow);

    int n;
    std::vector<std::vector<Edge>> graph;
    std::vector<int> level;
    std::vector<size_t> ptr;
};

template <typename T>
bool Dinic<T>::bfs(int source, int sink) {
    std::fill(level.begin(), level.end(), -1);
    level[source] = 0;

    std::queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const Edge& e : graph[u]) {
            if (level[e.v] == -1 && e.cap > 0) {
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
    }

    return level[sink] != -1;
}

template <typename T>
T Dinic<T>::dfs(int u, int sink, T flow) {
    if (u == sink) return flow;

    for (size_t& i = ptr[u]; i < graph[u].size(); ++i) {
        Edge& e = graph[u][i];
        if (e.cap > 0 && level[u] + 1 == level[e.v]) {
            T cur_flow = std::min(flow, e.cap);
            T pushed = dfs(e.v, sink, cur_flow);
            if (pushed > 0) {
                e.cap -= pushed;
                graph[e.v][e.rev].cap += pushed;
                return pushed;
            }
        }
    }

    return 0;
}

template <typename T>
T Dinic<T>::maxFlow(int source, int sink) {
    T totalFlow = 0;

    while (bfs(source, sink)) {
        std::fill(ptr.begin(), ptr.end(), 0);

        while (T flow = dfs(source, sink, std::numeric_limits<T>::max())) {
            totalFlow += flow;
        }
    }

    return totalFlow;
}

};  // namespace graph

#endif  // DINICS_HPP
