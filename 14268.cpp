#include <bits/stdc++.h>
using namespace std;

int cnt = 0;

void PrintVector (vector<int> vector) {
    for(int elem : vector) {
        cout << elem << ' ';
    }
    cout << '\n';
}

int EulerRoute(int node, vector<vector<int>>& tree, vector<int>& euler, vector<int>& treeRange) {
    euler[node] = cnt++;
    int size = 1;
    for(int nxt : tree[node]) {
        size += EulerRoute(nxt, tree, euler, treeRange);
    }
    treeRange[node] = size;
    return size;
}

class SegmentTree {
  public:
    explicit SegmentTree(const vector<long long>& arr) : length_(arr.size()){
        tree_.resize(length_ * 4);
        lazy_.resize(length_ * 4);
        build(1, 0, length_ - 1, arr);
    }

    void update(int l, int r, long long val){
        update(1, 0, length_ - 1, l, r, val);
    }

    long long query(int l, int r){
        return query(1, 0, length_ - 1, l, r);
    }

  private:
    const int length_;
    vector<long long> tree_;
    vector<long long> lazy_;

    void build(int idx, int st, int en, const vector<long long>& arr) {
        if(st == en){
            tree_[idx] = arr[st];
            return;
        }
        int mid = (st + en) / 2;
        build(idx * 2, st, mid, arr);
        build(idx * 2 + 1, mid + 1, en, arr);
        tree_[idx] = tree_[idx * 2] + tree_[idx * 2 + 1];
    }

    void update(int idx, int st, int en, int l, int r, long long val) {
        if(r < st || en < l) {
            return;
        }
        if(l <= st && en <= r) {
            tree_[idx] += val * (en - st + 1);
            lazy_[idx] += val;
            return;
        }
        //cout << "debuging" << endl;
        push(idx, st, en);
        int mid = (st + en) / 2;
        update(idx * 2, st, mid, l, r, val);
        update(idx * 2 + 1, mid + 1, en, l, r, val);
        tree_[idx] = tree_[idx * 2] + tree_[idx * 2 + 1];
    }

    long long query(int idx, int st, int en, int l, int r){
        if(r < st || en < l){
            return 0LL;
        }
        if(l <= st && en <= r){
            return tree_[idx];
        }
        push(idx, st, en);
        int mid = (st + en) / 2;
        return query(idx * 2, st, mid, l, r)
            + query(idx * 2 + 1, mid + 1, en, l, r);
    }

    void push(int idx, int st, int en) {
        if(lazy_[idx] == 0) return;
        int mid = (st + en) / 2;
        tree_[idx * 2] += lazy_[idx] * (mid - st + 1);
        lazy_[idx * 2] += lazy_[idx];
        tree_[idx * 2 + 1] += lazy_[idx] * (en - mid);
        lazy_[idx * 2 + 1] += lazy_[idx];
        lazy_[idx] = 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    int a;
    cin >> a;
    
    vector<vector<int>> tree(n, vector<int>(0));
    vector<int> euler(n), treeRange(n);
    
    for(int i = 1; i<n; i++) {
        int k;
        cin >> k;
        k--;
        
        tree[k].push_back(i);
    }

    EulerRoute(0, tree, euler, treeRange);

    //PrintVector(euler);
    //PrintVector(treeRange);

    vector<long long> init(n);
    SegmentTree seg(init);
    
    for(int i = 0; i<m; i++) {
        int a, c, w;
        cin >> a;

        if(a == 1) {
            cin >> c >> w;
            int st = euler[c - 1];
            int en = euler[c - 1] + treeRange[c - 1] - 1;
            seg.update(st, en, w);
        }
        if(a == 2) {
            cin >> c;
            cout << seg.query(euler[c - 1], euler[c - 1]) << '\n';
        }
    }
}