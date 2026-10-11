#include <bits/stdc++.h>
using namespace std;

/* TYPES */
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

// Topological sorting is possible only for a DAG.
// DAG = Directed Acyclic Graph.
// Vertices are numbered from 1 to n.

// ================== DFS ==================
// TC = O(V + E)
// SC = O(V + E)

bool helper(int node, const vector<vi>& adj,
            vi& vis, vi& pathVis, stack<int>& st) {

    vis[node] = 1;
    pathVis[node] = 1;

    for (auto it : adj[node]) {

        // If the neighbor has not been visited
        if (!vis[it]) {
            if (helper(it, adj, vis, pathVis, st)) {
                return true;
            }
        }

        // Neighbor is already in the current DFS path
        else if (pathVis[it]) {
            return true;
        }
    }

    pathVis[node] = 0;
    st.push(node);

    return false;
}


bool toposortDfs(const vector<vi>& adj, int n, vi& ans) {

    stack<int> st;

    vi vis(n + 1, 0);
    vi pathVis(n + 1, 0);

    for (int i = 1; i <= n; i++) {

        if (!vis[i]) {
            if (helper(i, adj, vis, pathVis, st)) {
                return false;
            }
        }
    }

    while (!st.empty()) {
        ans.pb(st.top());
        st.pop();
    }

    return true;
}


// ================== BFS / Kahn's Algorithm ==================
// TC = O(V + E)
// SC = O(V + E)

bool toposortBfs(const vector<vi>& adj, int n, vi& ans) {

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

    while (!qu.empty()) {

        int node = qu.front();
        qu.pop();

        ans.pb(node);

        // Remove node from the graph
        for (auto it : adj[node]) {

            inDegree[it]--;

            if (inDegree[it] == 0) {
                qu.push(it);
            }
        }
    }

    // If not all vertices were processed, a cycle exists
    return (int)ans.size() == n;
}


// ================== MAIN ==================

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Standard C++ adjacency list; 1-based indexing
    vector<vi> adj(n + 1);

    for (int i = 0; i < m; i++) {

        int u, v;
        cin >> u >> v;

        adj[u].pb(v);
    }

    // ================== DFS ==================

    vi ans;

    if (toposortDfs(adj, n, ans)) {

        for (auto node : ans) {
            cout << node << " ";
        }

        cout << "\n";

    } else {
        cout << "Cycle detected\n";
    }

    // ================== BFS / Kahn's Algorithm ==================
    // Uncomment this block and comment out the DFS block above
    // if you want to use Kahn's algorithm.

    /*
    ans.clear();

    if (toposortBfs(adj, n, ans)) {

        for (auto node : ans) {
            cout << node << " ";
        }

        cout << "\n";

    } else {
        cout << "Cycle detected\n";
    }
    */

    return 0;
}
