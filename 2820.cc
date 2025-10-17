#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
  public:
    explicit SegmentTree(const vector<int>& arr) : length_(arr.size()){
        tree_.resize(length_ * 4);
        lazy_.resize(length_ * 4);
        build(1, 0, length_ - 1, arr);
    }

    void update(int l, int r, int val){
        update(1, 0, length_ - 1, l, r, val);
    }

    int query(int l, int r){
        return query(1, 0, length_ - 1, l, r);
    }

  private:
    const int length_;
    vector<int> tree_;
    vector<int> lazy_;

    void build(int idx, int st, int en, const vector<int>& arr) {
        if(st == en){
            tree_[idx] = arr[st];
            return;
        }
        int mid = (st + en) / 2;
        build(idx * 2, st, mid, arr);
        build(idx * 2 + 1, mid + 1, en, arr);
    }

    void update(int idx, int st, int en, int l, int r, int val) {
        if(r < st || en < l) {
            return;
        }
        if(l <= st && en <= r) {
            tree_[idx] += val * (en - st + 1);
            lazy_[idx] += val;
            return;
        }
        push(idx, st, en);
        int mid = (st + en) / 2;
        update(idx * 2, st, mid, l, r, val);
        update(idx * 2 + 1, mid + 1, en, l, r, val);
    }

    int query(int idx, int st, int en, int l, int r){
        if(r < st || en < l){
            return 0LL;
        }
        if(l <= st && en <= r){
            return tree_[idx];
        }
        push(idx, st, en);
        int mid = (st + en) / 2;
        return query(idx * 2, st, mid, l, r) + query(idx * 2 + 1, mid + 1, en, l, r);
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

int cnt = 0;
vector<int> eulerTree(0);
vector<int> rev(0);

int dfs(const vector<vector<int>>& tree, vector<pair<int, int>>& res, int cur){
    int st = cnt, ma = cnt;
    rev[cur] = cnt++;

    for(int nxt : tree[cur]){
        ma = max(ma, dfs(tree, res, nxt));
    }
    res[cur] = {st, ma};
    return ma;
}

vector<pair<int, int>> eulerTour(const vector<vector<int>>& tree, int root, int size){
    vector<pair<int, int>> res(size);
    rev.resize(size);
    dfs(tree, res, root);
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> tree(n, vector<int>(0));
    vector<int> arr(n), euler(n);
    cin >> arr[0];

    for(int i = 1; i<n; i++){
        int s;
        cin >> arr[i] >> s;
        tree[s - 1].push_back(i);
    }

    vector<pair<int, int>> range = eulerTour(tree, 0, n);
    
    /*for(int i = 0; i<n; i++) {
        cout << "tree " << range[i].first << ' ' << range[i].second << endl;
    }*/
    
    for(int i = 0; i<n; i++){
        euler[rev[i]] = arr[i];
    }

    SegmentTree seg(euler);

    for(int i = 0; i<m; i++){
        char q;
        cin >> q;
        if(q == 'u') {
            int a;
            cin >> a;
            cout << seg.query(rev[a - 1], rev[a - 1]) << endl;
        }
        if(q == 'p'){
            int a, x;
            cin >> a >> x;
            seg.update(range[a - 1].first + 1, range[a - 1].second, x);
        }
    }
}