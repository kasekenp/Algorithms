#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from, to, rEdge;
    long long capacity;
    Edge(int f, int t, int r, long long c) {
        from = f;
        to = t;
        rEdge = r;
        capacity = c;
    }
};

struct Graph {
    vector<vector<Edge>> graph;
    Graph(int n) { graph.resize(n); }

    Edge &rEdge(Edge &e) { return graph[e.to][e.rEdge]; }

    vector<Edge> &at(int v) { return graph.at(v); }

    int size() { return graph.size(); }

    void addEdge(int from, int to, int capacity) {
        graph[from].push_back(Edge(from, to, graph[to].size(), capacity));
        graph[to].push_back(Edge(to, from, graph[from].size() - 1, 0));
    }
};

class FordFulkerson {
   private:
    vector<bool> used;
    // NOTE: フロー増加路を探し、増加分のフローを返す
    long long dfs(Graph &graph, int v, int goal, long long curFlow) {
        if (v == goal) {
            return curFlow;
        }
        used.at(v) = true;
        for (auto &e : graph.at(v)) {
            if (used.at(e.to) || e.capacity <= 0) {
                continue;
            }
            auto finalFlow = dfs(graph, e.to, goal, min(curFlow, e.capacity));
            if (finalFlow > 0) {
                e.capacity -= finalFlow;
                graph.rEdge(e).capacity += finalFlow;
                return finalFlow;
            }
        }
        return 0;
    }

   public:
    long long maxFlow(Graph &graph, int start, int goal) {
        long long flow = 0;
        while (true) {
            used.assign(graph.size(), 0);
            auto addedFlow = dfs(graph, start, goal, (1LL << 62));
            if (addedFlow == 0) {
                return flow;
            }
            flow += addedFlow;
        }
        return flow;
    }
};

int main() {
    int v, e;
    cin >> v >> e;
    Graph graph(v);
    for (int i = 0; i < e; i++) {
        int from, to, cap;
        cin >> from >> to >> cap;
        graph.addEdge(from, to, cap);
    }
    FordFulkerson ff;
    cout << ff.maxFlow(graph, 0, v - 1) << endl;
}