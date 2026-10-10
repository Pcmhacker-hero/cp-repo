/*
Dijkstra's Algorithm (Shortest Path)
✅ Works when:
* Graph is weighted
* All edge weights are non-negative/positive
* Works on both DAG and cyclic graphs

Time: O((V + E) log V)
*/
#include <bits/stdc++.h>
using namespace std;

void dijkstra(
    int n,
    vector<vector<pair<int, int>>>& adj,
    int src,
    int dest
) {
    vector<int> dist(n + 1, INT_MAX);
    vector<int> parent(n + 1);

    // Initially, every node is its own parent
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    // {distance, node}
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {

        auto [d, node] = pq.top();
        pq.pop();

        // Ignore outdated entry
        if (d > dist[node])
            continue;

        for (auto [nextNode, weight] : adj[node]) {

            // Relaxation
            if (d + weight < dist[nextNode]) {

                dist[nextNode] = d + weight;

                // Remember where we came from
                parent[nextNode] = node;

                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    // Destination is unreachable
    if (dist[dest] == INT_MAX) {
        cout << "No path exists\n";
        return;
    }

    // Reconstruct path
    vector<int> path;

    int node = dest;

    while (parent[node] != node) {
        path.push_back(node);
        node = parent[node];
    }

    path.push_back(src);

    // Reverse because we built the path backwards
    reverse(path.begin(), path.end());

    cout << "Shortest distance: " << dist[dest] << "\n";

    cout << "Shortest path: ";

    for (int x : path) {
        cout << x << " ";
    }

    cout << "\n";
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++) {

        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});

        // For undirected graph:
        // adj[v].push_back({u, w});
    }

    int src, dest;
    cin >> src >> dest;

    dijkstra(n, adj, src, dest);

    return 0;
}
