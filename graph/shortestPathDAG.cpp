#include <bits/stdc++.h>
using namespace std;

/*
    Shortest Path in DAG using Topological Sort
    Time Complexity: O(V + E)
    Can handle negative weights (no cycles → safe)
*/

#define pii pair<int, int>
#define vi vector<int>

// DFS helper for topological sort
void topoDFS(int node, vector<pii> adj[], vector<int> &vis, stack<int> &st) {
    vis[node] = 1;

    for (auto &it : adj[node]) {
        int v = it.first;
        if (!vis[v]) {
            topoDFS(v, adj, vis, st);
        }
    }

    st.push(node);
}

// Function to find shortest path in DAG
vector<int> shortestPathDAG(int src, vector<pii> adj[], int n) {
    vector<int> vis(n + 1, 0);
    stack<int> st;

    // Step 1: Topological Sort
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            topoDFS(i, adj, vis, st);
        }
    }

    // Step 2: Initialize distances
    vector<int> dist(n + 1, 1e9);
    dist[src] = 0;

    // Step 3: Relax edges in topological order
    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (dist[u] != 1e9) {
            for (auto &it : adj[u]) {
                int v = it.first;
                int w = it.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    // Step 4: Mark unreachable nodes
    for (int i = 1; i <= n; i++) {
        if (dist[i] == 1e9) dist[i] = -1;
    }

    return dist;
}

//https://takeuforward.org/data-structure/shortest-path-in-directed-acyclic-graph-topological-sort-g-27/
