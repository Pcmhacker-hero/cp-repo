/*
Bellman-Ford Algorithm:
- Works with negative edge weights
- Can detect negative cycles
- Time: O(V * E)
- Use when Dijkstra fails
*/
//O(E) + O(nE) + O(nE) ≈ O(nE)

#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int u, v, w;
};

vector<int> bellmanFord(int n, vector<Edge> &edges, int src) {
    vector<int> dist(n + 1, 1e9);
    dist[src] = 0;

    // Relax edges (n-1) times
    for (int i = 1; i <= n - 1; i++) {
        for (auto &e : edges) {
            if (dist[e.u] != 1e9 && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    // Check for negative cycle
    for (auto &e : edges) {
        if (dist[e.u] != 1e9 && dist[e.u] + e.w < dist[e.v]) {
            cout << "Negative cycle detected\n";
            return {};
        }
    }

    return dist;
}
