#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

class SegmentTree {
  public:
    explicit SegmentTree(const vector<long long>& arr) : length_(arr.size()){
        tree_.resize(length_ * 4);
        lazy_add_.resize(length_ * 4);
        lazy_mul_.resize(length_ * 4, 1);
        build(1, 0, length_ - 1, arr);
    }

    void update(int l, int r, long long add, long long mul){
        update(1, 0, length_ - 1, l, r, add, mul);
    }

    long long query(int l, int r){
        return query(1, 0, length_ - 1, l, r) % MOD;
    }

  private:
    const int length_;
    vector<long long> tree_;
    vector<long long> lazy_add_;
    vector<long long> lazy_mul_;

    void build(int idx, int st, int en, const vector<long long>& arr) {
        if(st == en){
            tree_[idx] = arr[st];
            return;
        }
        int mid = (st + en) / 2;
        build(idx * 2, st, mid, arr);
        build(idx * 2 + 1, mid + 1, en, arr);
        tree_[idx] = (tree_[idx * 2] + tree_[idx * 2 + 1]) % MOD;
    }

    void update(int idx, int st, int en, int l, int r, long long add, long long mul) {
        if(r < st || en < l) {
            return;
        }
        if(l <= st && en <= r) {
            tree_[idx] *= mul;
            tree_[idx] += add * (en - st + 1);
            lazy_mul_[idx] *= mul;
            lazy_add_[idx] *= mul;
            lazy_add_[idx] += add;

            tree_[idx] %= MOD;
            lazy_mul_[idx] %= MOD;
            lazy_add_[idx] %= MOD;
            return;
        }
        push(idx, st, en);
        int mid = (st + en) / 2;
        update(idx * 2, st, mid, l, r, add, mul);
        update(idx * 2 + 1, mid + 1, en, l, r, add, mul);
        tree_[idx] = (tree_[idx * 2] + tree_[idx * 2 + 1]) % MOD;
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
        return (query(idx * 2, st, mid, l, r)
            + query(idx * 2 + 1, mid + 1, en, l, r)) % MOD;
    }

    void push(int idx, int st, int en) {
        if(lazy_add_[idx] == 0 && lazy_mul_[idx] == 0) return;
        int mid = (st + en) / 2;

        tree_[idx * 2] *= lazy_mul_[idx];
        tree_[idx * 2] += lazy_add_[idx] * (mid - st + 1);
        lazy_mul_[idx * 2] *= lazy_mul_[idx];
        lazy_add_[idx * 2] *= lazy_mul_[idx];
        lazy_add_[idx * 2] += lazy_add_[idx];
        tree_[idx * 2] %= MOD;
        lazy_add_[idx * 2] %= MOD;
        lazy_mul_[idx * 2] %= MOD;

        tree_[idx * 2 + 1] *= lazy_mul_[idx];
        tree_[idx * 2 + 1] += lazy_add_[idx] * (en - mid);
        lazy_mul_[idx * 2 + 1] *= lazy_mul_[idx];
        lazy_add_[idx * 2 + 1] *= lazy_mul_[idx];
        lazy_add_[idx * 2 + 1] += lazy_add_[idx];
        tree_[idx * 2 + 1] %= MOD;
        lazy_add_[idx * 2 + 1] %= MOD;
        lazy_mul_[idx * 2 + 1] %= MOD;

        tree_[idx] %= MOD;
        lazy_add_[idx] = 0;
        lazy_mul_[idx] = 1;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> arr(n); 

    for(int i = 0; i<n; i++){
        cin >> arr[i];
    }

    SegmentTree seg(arr);

    int m;
    cin >> m;

    for(int i = 0; i<m; i++){
        int a, x, y;
        long long v;
        cin >> a;

        switch(a){
            case 1:
                cin >> x >> y >> v;
                seg.update(x - 1, y - 1, v, 1);
                break;
            case 2:
                cin >> x >> y >> v;
                seg.update(x - 1, y - 1, 0, v);
                break;
            case 3:
                cin >> x >> y >> v;
                seg.update(x - 1, y - 1, v, 0);
                break;
            case 4:
                cin >> x >> y;
                cout << seg.query(x - 1, y - 1) << '\n';
                break;
        }
    }
}