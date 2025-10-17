#include <bits/stdc++.h>
using namespace std;

vector<long long> sum(1);

class SegmentTree {
  public:
    explicit SegmentTree(const vector<long long>& arr) : length_(arr.size()){
        tree_.resize(length_ * 4);
        lazyA_.resize(length_ * 4);
        lazyD_.resize(length_ * 4);
        build(1, 0, length_ - 1, arr);
    }

    void update(int l, int r){
        update(1, 0, length_ - 1, l, r);
    }

    long long query(int l, int r){
        return query(1, 0, length_ - 1, l, r);
    }

    void printTree(){
        cout << "tree : ";
        for(int i = 1; i<length_ * 2; i++){
            cout << tree_[i] << ' ';
        }
        cout << '\n';
        cout << "lazy a : ";
        for(int i = 1; i<length_ * 2; i++){
            cout << lazyA_[i] << ' ';
        }
        cout << '\n';
        cout << "lazy d : ";
        for(int i = 1; i<length_ * 2; i++){
            cout << lazyD_[i] << ' ';
        }
        cout << '\n';
    }

  private:
    const int length_;
    vector<long long> tree_;
    vector<long long> lazyA_;
    vector<long long> lazyD_;

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

    void update(int idx, int st, int en, int l, int r) {
        if(r < st || en < l) {
            return;
        }
        if(l <= st && en <= r) {
            tree_[idx] += sum[en - l + 1] - sum[st - l];
            lazyA_[idx] += st - l + 1;
            lazyD_[idx]++;
            return;
        }
        push(idx, st, en);
        int mid = (st + en) / 2;
        update(idx * 2, st, mid, l, r);
        update(idx * 2 + 1, mid + 1, en, l, r);
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

    long long geometric(long long a, long long d, long long n){
        return (2 * a + (n - 1) * d) * n / 2;
    }

    void push(int idx, int st, int en) {
        if(lazyD_[idx] == 0) return;
        int mid = (st + en) / 2;
        tree_[idx * 2] += geometric(lazyA_[idx], lazyD_[idx], mid - st + 1);
        lazyA_[idx * 2] += lazyA_[idx];
        lazyD_[idx * 2] += lazyD_[idx];
        tree_[idx * 2 + 1] += geometric(lazyA_[idx] + (mid - st + 1) * lazyD_[idx], lazyD_[idx], en - mid);
        lazyA_[idx * 2 + 1] += lazyA_[idx] + (mid - st + 1) * lazyD_[idx];
        lazyD_[idx * 2 + 1] += lazyD_[idx];
        lazyA_[idx] = 0;
        lazyD_[idx] = 0;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for(int i = 1; i<=100000; i++){
        sum.push_back(sum[i - 1] + i);
    }

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
        int a;
        cin >> a;

        if(a == 1) {
            int l, r;
            cin >> l >> r;
            seg.update(l - 1, r - 1);
        }
        if(a == 2) {
            int x;
            cin >> x;
            cout << seg.query(x - 1, x - 1) << '\n';
        }
        seg.printTree();
    }
}