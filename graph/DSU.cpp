#include <bits/stdc++.h>
using namespace std;

/*
========================================
        DISJOINT SET (DSU)
========================================

Time Complexity:
- Find: O(α(N))  ~ almost constant
- Union: O(α(N))

Space Complexity:
- O(N)

Important Info:
- Used for dynamic connectivity problems
- Detect cycle in graph
- Used in Kruskal’s Algorithm (MST)
- Two optimizations:
    1. Path Compression (in find)
    2. Union by Rank / Size

NOTE:
- Use either unionByRank OR unionBySize
- Do NOT mix both in the same problem

========================================
*/

/* MACROS */
#define vi vector<int>
#define f(i, s, e) for (int i = s; i < e; i++)

/* DSU IMPLEMENTATION */
struct DSU {
    vi parent, rank, size;

    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        f(i, 0, n + 1) parent[i] = i;
    }

    // Path Compression
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    // Union by Rank (tree height)
    void unionByRank(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return;

        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[px] = py;
            rank[py]++;
        }
    }

    // Union by Size (component size)
    void unionBySize(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return;

        if (size[px] < size[py]) {
            parent[px] = py;
            size[py] += size[px];
        } else {
            parent[py] = px;
            size[px] += size[py];
        }
    }
};

/* MAIN FUNCTION */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    DSU dsu(7);

    // Using ONLY unionBySize (recommended)
    dsu.unionBySize(1, 2);
    dsu.unionBySize(2, 3);
    dsu.unionBySize(4, 5);
    dsu.unionBySize(6, 7);
    dsu.unionBySize(5, 6);
    dsu.unionBySize(3, 4);

    if (dsu.find(3) == dsu.find(7)) {
        cout << "Same\n";
    } else {
        cout << "Not Same\n";
    }

    return 0;
}
