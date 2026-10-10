void helper(int node, vi adj[], vi& vis, vi& ans){
    ans.pb(node);
    vis[node] = 1;
    for(auto it : adj[node]){
        if(!vis[it]){
            helper(it, adj, vis, ans);
        }
    }
}
void dfs(vi adj[], int node, int n){
    vi vis(n+1, 0), ans;
    helper(node, adj, vis, ans);
    for(auto x : ans) cout << x << " ";
}
