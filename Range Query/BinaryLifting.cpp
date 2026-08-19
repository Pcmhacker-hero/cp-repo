/*
============================================================
             BINARY LIFTING + LCA TEMPLATE
============================================================

Complexity:
    Preprocessing : O(N log N)
    K-th Ancestor : O(log N)
    LCA           : O(log N)
    Space         : O(N log N)

Important:
    addEdge() builds the tree.
    build(root) creates depth[] and up[][].
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class BinaryLifting {
    int n, LOG;

    // up[node][j] = 2^j-th ancestor
    vector<vector<int>> up;

    // depth[node] = distance from root
    vector<int> depth;

    // Tree
    vector<vector<int>> adj;

public:
    BinaryLifting(int n) {
        this->n = n;

        LOG = 1;
        while ((1LL << LOG) <= n)
            LOG++;

        up.assign(n + 1, vector<int>(LOG));
        depth.assign(n + 1, 0);
        adj.resize(n + 1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int node, int parent) {
        up[node][0] = parent;

        // Build binary lifting table
        for (int j = 1; j < LOG; j++) {
            up[node][j] =
                up[up[node][j - 1]][j - 1];
        }

        for (int child : adj[node]) {
            if (child == parent)
                continue;

            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    }

    void build(int root = 1) {
        dfs(root, root);
    }

    // K-th ancestor of node
    int kthAncestor(int node, int k) {
        for (int j = 0; j < LOG; j++) {
            if (k & (1LL << j)) {
                node = up[node][j];
            }
        }

        return node;
    }

    // Lowest Common Ancestor
    int lca(int u, int v) {

        // Make depths equal
        if (depth[u] < depth[v])
            swap(u, v);

        u = kthAncestor(u, depth[u] - depth[v]);

        if (u == v)
            return u;

        // Lift both nodes without crossing the LCA
        for (int j = LOG - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    BinaryLifting bl(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        bl.addEdge(u, v);
    }

    bl.build(1);

    int q;
    cin >> q;

    while (q--) {
        int u, v;
        cin >> u >> v;

        cout << bl.lca(u, v) << '\n';
    }

    return 0;
}
