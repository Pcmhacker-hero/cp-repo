## Segment Tree — Range Minimum Query

### Complexity
- **Build:** `O(n)`
- **Range Query:** `O(log n)`
- **Point Update:** `O(log n)`
- **Space:** `O(n)`

---

## Segment Tree Range Query — 3 Cases

### 1. Partial Overlap
- Range partially overlaps with `[L, R]`
- Query both left and right children

### 2. No Overlap
- Range has no overlap with `[L, R]`
- Return `INT_MAX` for Range Minimum Query

### 3. Complete Overlap
- Current range is completely inside `[L, R]`
- Return `seg[ind]` directly
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> seg;

public:
    SegmentTree(int n) {
        seg.resize(4 * n + 1);
    }

    // Build Segment Tree
    void build(int arr[], int left, int right, int idx) {
        if (left == right) {
            seg[idx] = arr[left];
            return;
        }

        int mid = (left + right) / 2;

        build(arr, left, mid, 2 * idx + 1);
        build(arr, mid + 1, right, 2 * idx + 2);

        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    // Range Minimum Query
    int query(int idx, int l, int r, int left, int right) {

        // No Overlap
        if (right < l || r < left)
            return INT_MAX;

        // Complete Overlap
        if (left <= l && r <= right)
            return seg[idx];

        // Partial Overlap
        int mid = (l + r) / 2;

        int low = query(2 * idx + 1, l, mid, left, right);
        int high = query(2 * idx + 2, mid + 1, r, left, right);

        return min(low, high);
    }

    // Point Update
    void update(int idx, int pos, int val, int left, int right) {
        if (left == right) {
            seg[idx] = val;
            return;
        }

        int mid = (left + right) / 2;

        if (pos <= mid)
            update(2 * idx + 1, pos, val, left, mid);
        else
            update(2 * idx + 2, pos, val, mid + 1, right);

        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
};

int main() {
    int arr[] = {2, 3, 1, 0, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    SegmentTree st(n);

    // Build Segment Tree
    st.build(arr, 0, n - 1, 0);

    // Range Query [0, n-1]
    cout << st.query(0, 0, n - 1, 0, n - 1) << endl;

    // Update index 3 from 0 to 5
    st.update(0, 3, 5, 0, n - 1);

    // Range Query after update
    cout << st.query(0, 0, n - 1, 0, n - 1) << endl;

    return 0;
}
