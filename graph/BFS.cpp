//* TC = O(V + E)
//* SC = O(V) (excluding graph storage)

void bfs(vi adj[], int node, vi &vis) {
    queue<int> qu;
    qu.push(node);
    vis[node] = 1;  // mark start node visited

    vi ans;

    while (!qu.empty()) {
        int took = qu.front();
        qu.pop();
        ans.pb(took);

        for (auto it : adj[took]) {
            if (!vis[it]) {
                vis[it] = 1;   // ✅ correct
                qu.push(it);
            }
        }
    }
}
