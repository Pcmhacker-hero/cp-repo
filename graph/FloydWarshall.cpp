// - Finds shortest path between all pairs
// - Works with negative edges (no negative cycle)
// - Time: O(n^3)
// - Best for small graphs

void floydWarshall(int n, vector<vector<ll>> &dist, vector<pii> adj[]) {
    const ll INF = 1e18;

    // initialize
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }

    // edges
    for (int i = 0; i < n; i++) {
        for (auto it : adj[i]) {
            dist[i][it.first] = min(dist[i][it.first], (ll)it.second);
        }
    }

    // main DP
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j],
                                     dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // negative cycle detection
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            cout << "Negative Cycle detected\n";
            return;
        }
    }
}
