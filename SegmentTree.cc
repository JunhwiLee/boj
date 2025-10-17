#include <bits/stdc++.h>
using namespace std;

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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<long long> arr(n);
    for(int i = 0; i<n; i++){
        cin >> arr[i];
    }

    SegmentTree seg(arr);

    for(int i = 0; i<m + k; i++){
        int a;
        cin >> a;
        if(a == 1) {
            int b, c;
            long long d;
            cin >> b >> c >> d;
            seg.update(b - 1, c - 1, d);
        }
        if(a == 2){
            int b, c;
            cin >> b >> c;
            cout << seg.query(b - 1, c - 1) << endl;
        }
    }

    return 0;
}