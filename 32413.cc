#include <bits/stdc++.h>
using namespace std;

struct Node{
    vector<int> v;

    Node() = default;
    Node(int x) : v{ x } {}

    static Node merge(const Node& a, const Node& b) {
        Node res;
        res.v.resize(a.v.size() + b.v.size());
        std::merge(a.v.begin(), a.v.end(), b.v.begin(), b.v.end(), res.v.begin());
        return res;
    }

    int count_le(int x) const {
        return int(upper_bound(v.begin(), v.end(), x) - v.begin());
    }
};

class SegmentTree {
  public:
    explicit SegmentTree(const vector<int>& arr) : n(arr.size()) {
        tree.assign(4*n, Node());
        build(1, 0, n-1, arr);
    }

    int query(int l, int r, int k) const {
        l = max(l, 0); r = min(r, n-1);
        if (l > r) return 0;
        int len = r - l + 1;
        int le = query(1, 0, n-1, l, r, k);
        return len - le;
    }

  private:
    int n;
    vector<Node> tree;

    void build(int idx, int st, int en, const vector<int>& arr) {
        if (st == en) { tree[idx] = Node(arr[st]); return; }
        int mid = (st + en) >> 1;
        build(idx<<1, st, mid, arr);
        build(idx<<1|1, mid+1, en, arr);
        tree[idx] = Node::merge(tree[idx<<1], tree[idx<<1|1]);
    }

    int query(int idx, int st, int en, int l, int r, int x) const {
        if (r < st || en < l) return 0;
        if (l <= st && en <= r) return tree[idx].count_le(x);
        int mid = (st + en) >> 1;
        return query(idx<<1, st, mid, l, r, x)
             + query(idx<<1|1, mid+1, en, l, r, x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    if(!(cin >> n)) return 0;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];

    SegmentTree seg(a);

    int q; cin >> q;
    int last = 0;
    while(q--){
        int a, b, c;
        cin >> a >> b >> c;

        int i = a ^ last, j = b ^ last, k = c ^ last;

        last = seg.query(i - 1, j - 1, k);
        cout << last << '\n';
    }
    return 0;
}
