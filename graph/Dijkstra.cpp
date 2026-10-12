/*
Dijkstra's Algorithm (Shortest Path)
✅ Works when:
* Graph is weighted
* All edge weights are positive
* Works on both DAG and cyclic graphs

Time: O((V + E) log V)
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX / 4;

void dijkstra(int n, vector<vector<pair<int, ll>>>& adj,
              int src, int dest) {
    vector<ll> dist(n + 1, INF);
    vector<int> par(n + 1, -1);

    priority_queue<pair<ll, int>,
        vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[src] = 0;
    par[src] = src;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (w > INF - d) continue;

            if (d + w < dist[v]) {
                dist[v] = d + w;
                par[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[dest] == INF) {
        cout << "No path exists\n";
        return;
    }

    cout << "Shortest distance: " << dist[dest] << '\n';

    vector<int> path;
    for (int u = dest; u != src; u = par[u])
        path.push_back(u);

    path.push_back(src);
    reverse(path.begin(), path.end());

    cout << "Shortest path: ";
    for (int u : path) cout << u << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, ll>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w}); // Directed
        // adj[v].push_back({u, w}); // Undirected
    }

    int src, dest;
    cin >> src >> dest;

    dijkstra(n, adj, src, dest);
    return 0;
}
