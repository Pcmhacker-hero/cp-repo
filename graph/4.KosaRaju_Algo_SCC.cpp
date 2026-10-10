#include <bits/stdc++.h>
using namespace std;

/*
🧠 Topic: Kosaraju's Algorithm (SCC) + assign()

Time Complexity (TC): O(V + E)
Space Complexity (SC): O(V + E)

assign() → reset vector
vis.assign(n, 0); // clear + resize + fill

--------------------------------------------------
Steps:
1. DFS and store nodes in stack (finish time order)
2. Reverse graph (transpose)
3. DFS in stack order on transpose → SCC
--------------------------------------------------
*/

#define vi vector<int>

// Step 1: DFS to fill stack
void dfsFill(int node, vi adj[], vi &vis, stack<int> &st) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        if (!vis[it]) dfsFill(it, adj, vis, st);
    }
    st.push(node);
}

// Step 3: DFS on transpose graph
void dfsTranspose(int node, vi &vis, vi adj[], vi &component) {
    vis[node] = 1;
    component.push_back(node);
    for (auto it : adj[node]) {
        if (!vis[it]) dfsTranspose(it, vis, adj, component);
    }
}

// Kosaraju main function
vector<vi> kosaraju(vi adj[], int n) {

    vi vis(n, 0);
    stack<int> st;

    // Step 1: Fill stack
    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfsFill(i, adj, vis, st);
    }

    // Step 2: Transpose graph
    vi transpose[n];
    for (int i = 0; i < n; i++) {
        for (auto it : adj[i]) {
            transpose[it].push_back(i);
        }
    }

    // Reset visited using assign()
    vis.assign(n, 0);

    // Step 3: Process stack
    vector<vi> scc;
    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (!vis[node]) {
            vi component;
            dfsTranspose(node, vis, transpose, component);
            scc.push_back(component);
        }
    }

    return scc;
}

// Example usage
int main() {
    int n = 5;
    vi adj[n];

    // Example graph
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);
    adj[1].push_back(3);
    adj[3].push_back(4);

    vector<vi> result = kosaraju(adj, n);

    // Print SCCs
    for (auto &comp : result) {
        for (auto node : comp) {
            cout << node << " ";
        }
        cout << "\n";
    }

    return 0;
}
