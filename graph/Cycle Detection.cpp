//⚡ Complexity

//* TC = O(V + E)
//* SC = O(V)

// ---> you can use the toposort by bfs for detection the cycle

bool dfs(int node, vector<vector<int>> &adj, vector<int> &vis, vector<int> &pathVis){
    vis[node] = 1;
    pathVis[node] = 1;

    for(auto it : adj[node]){
        if(!vis[it]){
            if(dfs(it, adj, vis, pathVis)) return true;
        }
        else if(pathVis[it]){
            return true; // cycle detected
        }
    }

    pathVis[node] = 0;
    return false;
}

bool isCycle(int n, vector<vector<int>> &adj){
    vector<int> vis(n+1, 0), pathVis(n+1, 0);

    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            if(dfs(i, adj, vis, pathVis)) return true;
        }
    }
    return false;
}



int main(){

  int n, m;
cin >> n >> m;

vector<vector<int>> adj(n+1);

for(int i = 0; i < m; i++){
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v); // directed
}

if(isCycle(n, adj)){
    cout << "Cycle detected\n";
} else {
    cout << "No cycle\n";
}
  
}
