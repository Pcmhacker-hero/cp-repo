/*
    Lazy Propagation Segment Tree
    -----------------------------
    Supports:
    1. Range Addition  : Add val to every element in [l, r]
    2. Range Sum Query : Find sum of elements in [l, r]

    Time Complexity:
    Build  : O(n)
    Update : O(log n)
    Query  : O(log n)

    Space Complexity:
    O(n)

    Lazy Idea:
    lzy[idx] stores a pending addition for the segment.
    It is pushed to the children only when required.
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

using vi = vector<int>;




class LazySegmentTree {
    vi seg, lzy;

public:
    LazySegmentTree(int n) {
        seg.resize(4 * n, 0);
        lzy.resize(4 * n, 0);
    }

    // Build the segment tree
    void build(int idx, int low, int high, vi& arr) {
        if (low == high) {
            seg[idx] = arr[low];
            return;
        }

        int mid = (low + high) / 2;

        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 2, mid + 1, high, arr);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    // Range Addition: add val to every element in [l, r]
    void update(int idx, int low, int high,
                int l, int r, int val) {

        // Apply pending lazy update
        if (lzy[idx] != 0) {
            seg[idx] += (high - low + 1) * lzy[idx];

            if (low != high) {
                lzy[2 * idx + 1] += lzy[idx];
                lzy[2 * idx + 2] += lzy[idx];
            }

            lzy[idx] = 0;
        }

        // No overlap
        if (high < l || r < low)
            return;

        // Complete overlap
        if (l <= low && high <= r) {
            seg[idx] += (high - low + 1) * val;

            if (low != high) {
                lzy[2 * idx + 1] += val;
                lzy[2 * idx + 2] += val;
            }

            return;
        }

        // Partial overlap
        int mid = (low + high) / 2;

        update(2 * idx + 1, low, mid, l, r, val);
        update(2 * idx + 2, mid + 1, high, l, r, val);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    // Range Sum Query: sum of elements in [l, r]
    int query(int idx, int low, int high,
              int l, int r) {

        // Apply pending lazy update
        if (lzy[idx] != 0) {
            seg[idx] += (high - low + 1) * lzy[idx];

            if (low != high) {
                lzy[2 * idx + 1] += lzy[idx];
                lzy[2 * idx + 2] += lzy[idx];
            }

            lzy[idx] = 0;
        }

        // No overlap
        if (high < l || r < low)
            return 0;

        // Complete overlap
        if (l <= low && high <= r)
            return seg[idx];

        // Partial overlap
        int mid = (low + high) / 2;

        int left = query(2 * idx + 1, low, mid, l, r);
        int right = query(2 * idx + 2, mid + 1, high, l, r);

        return left + right;
    }
};





void solve() {
    int n;
    cin >> n;

    vi arr(n);

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    LazySegmentTree st(n);

    st.build(0, 0, n - 1, arr);

    int q;
    cin >> q;

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            // Query: sum of [l, r]
            int l, r;
            cin >> l >> r;

            cout << st.query(0, 0, n - 1, l, r) << endl;
        }
        else {
            // Update: add val to [l, r]
            int l, r, val;
            cin >> l >> r >> val;

            st.update(0, 0, n - 1, l, r, val);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
