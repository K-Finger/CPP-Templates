#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegmentTree {
    int n;
    vector<ll> tree;
    vector<ll> lazy;

    SegmentTree(int n) {
        this->n = n;
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }

    // EDIT THIS depending on the problem
    ll combine(ll a, ll b) {
        return max(a, b);
    }

    // EDIT THIS depending on combine()
    ll neutral() {
        return LLONG_MIN;
    }

    void push(int node) {
        if (lazy[node] == 0)
            return;

        tree[2 * node] += lazy[node];
        tree[2 * node + 1] += lazy[node];

        lazy[2 * node] += lazy[node];
        lazy[2 * node + 1] += lazy[node];

        lazy[node] = 0;
    }

    void update(int node, int l, int r,
                int ql, int qr, ll val) {

        // no overlap
        if (r < ql || l > qr)
            return;

        // total overlap
        if (ql <= l && r <= qr) {
            tree[node] += val;
            lazy[node] += val;
            return;
        }

        // partial overlap
        push(node);

        int mid = l + (r - l) / 2;

        update(2 * node, l, mid, ql, qr, val);
        update(2 * node + 1, mid + 1, r, ql, qr, val);

        tree[node] = combine(
            tree[2 * node],
            tree[2 * node + 1]
        );
    }

    ll query(int node, int l, int r,
             int ql, int qr) {

        // no overlap
        if (r < ql || l > qr)
            return neutral();

        // total overlap
        if (ql <= l && r <= qr)
            return tree[node];

        // partial overlap
        push(node);

        int mid = l + (r - l) / 2;

        ll left = query(2 * node, l, mid, ql, qr);
        ll right = query(2 * node + 1, mid + 1, r, ql, qr);

        return combine(left, right);
    }

    void update(int l, int r, ll val) {
        update(1, 0, n - 1, l, r, val);
    }

    ll query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
