#include <bits/stdc++.h>
using namespace std;

/* TYPES */
#define ll long long
#define pii pair<int,int>
#define vi vector<int>
#define pb push_back

/* PQ */
#define tp tuple<int,int,int>
#define minpq_tuple priority_queue<tp, vector<tp>, greater<tp>>

/*
🔹 Prim’s Algorithm (Lazy - Undirected Graph Only)

📌 Time: O(E log E)
📌 Space: O(E + V)

📌 Notes:
- Works ONLY for undirected graphs ❗
- No dist[] (lazy approach)
- vis[] avoids cycles
- Stores MST edges
*/

pair<int, vector<pii>> prims(vector<pii> adj[], int n, int src = 0) {
    minpq_tuple pq;
    pq.push({0, -1, src});

    vi vis(n, 0);
    vector<pii> edges;
    int mst = 0;

    while(!pq.empty()) {
        auto [w, p, u] = pq.top();
        pq.pop();

        if(vis[u]) continue;

        vis[u] = 1;
        mst += w;

        if(p != -1) edges.pb({p, u});

        for(auto &[v, wt] : adj[u]) {
            if(!vis[v]) pq.push({wt, u, v});
        }
    }
    return {mst, edges};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 5;
    vector<pii> adj[n];

    // Graph input
    adj[0].pb({1,2});
    adj[0].pb({3,6});

    adj[1].pb({0,2});
    adj[1].pb({2,3});
    adj[1].pb({3,8});
    adj[1].pb({4,5});

    adj[2].pb({1,3});
    adj[2].pb({4,7});

    adj[3].pb({0,6});
    adj[3].pb({1,8});

    adj[4].pb({1,5});
    adj[4].pb({2,7});

    auto [cost, mstEdges] = prims(adj, n);

    cout << "MST Weight: " << cost << "\n";
    cout << "Edges:\n";
    for(auto &e : mstEdges){
        cout << e.first << " - " << e.second << "\n";
    }

    return 0;
}
