/*
==========================================================
                    SPARSE TABLE
==========================================================

Sparse Table

    Used for static range queries.

    Best suited for idempotent operations:

    - Minimum

    - Maximum

    - GCD

    - Bitwise AND / OR

    Time Complexity:

    Build  : O(n log n)

    Query  : O(1)

    Space  : O(n log n)

    Key idea:

    Precompute answers for ranges of length 2^k.

    For idempotent operations, overlapping ranges

    can be combined safely.
    -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Use:
    Range queries on a STATIC array.

Best for:
    - Range Minimum Query (RMQ)
    - Range Maximum Query
    - GCD queries

Complexity:
    Preprocessing : O(N log N)
    Query         : O(1)
    Update        : Not supported efficiently
    Space         : O(N log N)

Idea:
    st[i][j] stores the answer for the range:

        [i ... i + 2^j - 1]

    Therefore:
        j = 0 -> range length 1
        j = 1 -> range length 2
        j = 2 -> range length 4
        j = 3 -> range length 8

Transition:

    st[i][j] =
        min(
            st[i][j-1],
            st[i + 2^(j-1)][j-1]
        )

For a query [l, r]:

    len = r - l + 1
    k = floor(log2(len))

    Answer:

        min(
            st[l][k],
            st[r - 2^k + 1][k]
        )

==========================================================
*/

#include "bits/stdc++.h"
using namespace std;

class SparseTable {
private:
    int n;
    int LOG;
    vector<vector<int>> st;
    vector<int> lg;

public:

    SparseTable(vector<int>& a) {

        n = a.size();

        // Maximum power of 2 needed
        LOG = log2(n) + 1;

        st.assign(n, vector<int>(LOG));

        // Precompute logarithms
        lg.resize(n + 1);

        lg[1] = 0;

        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i / 2] + 1;
        }

        // j = 0 -> ranges of length 1
        for (int i = 0; i < n; i++) {
            st[i][0] = a[i];
        }

        // Build Sparse Table
        for (int j = 1; j < LOG; j++) {

            for (int i = 0;
                 i + (1 << j) <= n;
                 i++) {

                st[i][j] = min(
                    st[i][j - 1],
                    st[i + (1 << (j - 1))][j - 1]
                );
            }
        }
    }

    // Minimum in range [l, r]
    int query(int l, int r) {

        int len = r - l + 1;

        int k = lg[len];

        return min(
            st[l][k],
            st[r - (1 << k) + 1][k]
        );
    }
};


int main() {

    vector<int> a = {
        4, 2, 7, 1, 5, 3, 6
    };

    SparseTable st(a);

    // Minimum from index 1 to 5
    cout << st.query(1, 5) << '\n';

    // Minimum from index 2 to 6
    cout << st.query(2, 6) << '\n';

    return 0;
}
