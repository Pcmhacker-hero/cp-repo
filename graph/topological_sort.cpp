#include <bits/stdc++.h>
using namespace std;

/* TYPES  */
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>
#define popcnt __builtin_popcount

/* FUNCTIONS */
#define f(i,s,e) for(long long int i=s;i<e;i++)
#define cf(i,s,e) for(long long int i=s;i<=e;i++)
#define rf(i,e,s) for(long long int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define debug(x) cout << #x << " = " << x << endl
#define sz(x) (int)(x).size()
#define maxpq priority_queue<int>
#define minpq priority_queue<int, vector<int>, greater<int>>
#define tp tuple<int,int,int>
#define minpq_tuple priority_queue<tp, vector<tp>, greater<tp>>
#define maxpq_tuple priority_queue<tp>

/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

void yes() {
    cout << "YES\n";
}

void no() {
    cout << "NO\n";
}

typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;


// ========================================================
//                 TOPOLOGICAL SORT
// ========================================================

// Topological Sort is possible only for a DAG
// DAG = Directed Acyclic Graph


// ================== DFS ==================
// TC = O(V + E)
// SC = O(V + E)

bool helper(int node, vi adj[], vi& vis, vi& pathVis, stack<int>& st) {

    vis[node] = 1;
    pathVis[node] = 1;

    for (auto it : adj[node]) {

        // If node is not visited
        if (!vis[it]) {
            if (helper(it, adj, vis, pathVis, st))
                return true;
        }

        // Node is already present in current DFS path
        else if (pathVis[it]) {
            return true;
        }
    }

    pathVis[node] = 0;

    st.push(node);

    return false;
}


void toposortDfs(vi adj[], int n) {

    stack<int> st;

    vi vis(n + 1, 0);
    vi pathVis(n + 1, 0);

    for (int i = 1; i <= n; i++) {

        if (!vis[i]) {

            if (helper(i, adj, vis, pathVis, st)) {
                cout << "Cycle detected\n";
                return;
            }
        }
    }

    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }

    cout << "\n";
}


// ================== BFS / Kahn's Algorithm ==================
// TC = O(V + E)
// SC = O(V + E)

void toposortBfs(vi adj[], int n) {

    vi inDegree(n + 1, 0);

    // Calculate indegree
    for (int i = 1; i <= n; i++) {

        for (auto it : adj[i]) {
            inDegree[it]++;
        }
    }

    queue<int> qu;

    // Push nodes having indegree = 0
    for (int i = 1; i <= n; i++) {

        if (inDegree[i] == 0) {
            qu.push(i);
        }
    }

    vi ans;

    while (!qu.empty()) {

        int node = qu.front();
        qu.pop();

        ans.pb(node);

        // Remove node from graph
        for (auto it : adj[node]) {

            inDegree[it]--;

            if (inDegree[it] == 0) {
                qu.push(it);
            }
        }
    }

    // If all nodes are not processed,
    // graph contains a cycle
    if (ans.size() != n) {
        cout << "Cycle detected\n";
        return;
    }

    // Print topological order
    for (auto x : ans) {
        cout << x << " ";
    }

    cout << "\n";
}


// ================== MAIN ==================

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vi adj[n + 1];

    for (int i = 0; i < m; i++) {

        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
    }

    // DFS
    toposortDfs(adj, n);

    // BFS / Kahn's Algorithm
    // toposortBfs(adj, n);

    return 0;
}
