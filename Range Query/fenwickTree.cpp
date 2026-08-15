/*
==========================================================
                    FENWICK TREE
                 (Binary Indexed Tree)
==========================================================

What:
    Fenwick Tree is a data structure used for:
        - Prefix Sum
        - Point Update
        - Range Sum

Indexing:
    Fenwick Tree uses 1-based indexing.

Core Formula:
    lowbit(i) = i & (-i)

Operations:
    update(i, val) -> Add val at index i
    sum(i)        -> Prefix sum [1 ... i]
    query(l, r)   -> Range sum [l ... r]

Complexity:
    Build      : O(N log N)
    Update     : O(log N)
    Prefix Sum : O(log N)
    Range Sum  : O(log N)
    Space      : O(N)

Important:
    update -> i += i & (-i)
    query  -> i -= i & (-i)

Example:
    v = {1, 2, 3, 4, 5, 6}

    sum(3)       = 1 + 2 + 3 = 6
    update(1, 3) -> add 3 to index 1
    sum(3)       = 4 + 2 + 3 = 9

==========================================================
*/

#include <bits/stdc++.h>
using namespace std;


class FenwickTree {
private:
    int n;
    vector<int> BIT;

public:
    FenwickTree(vector<int>& v) {
        n = v.size();
        BIT.resize(n + 1, 0);

        for (int i = 0; i < n; i++) {
            update(i + 1, v[i]);
        }
    }

    void update(int idx, int val) {
        while (idx <= n) {
            BIT[idx] += val;


            idx += (idx & -idx);
        }
    }

    int sum(int idx) {
        int ans = 0;

        while (idx > 0) {
            ans += BIT[idx];

            idx -= (idx & -idx);
        }

        return ans;
    }


    int query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};


int main() {

    vector<int> v = {1, 2, 3, 4, 5, 6};

    FenwickTree ft(v);

    // Prefix sum: 1 + 2 + 3
    cout << ft.sum(3) << '\n';

    // Add 3 to index 1
    ft.update(1, 3);

    // Prefix sum: 4 + 2 + 3
    cout << ft.sum(3) << '\n';

    // Range sum: 2 + 3 + 4
    cout << ft.query(2, 4) << '\n';

    return 0;
}
