#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long n, x0, a, b;
    cin >> n >> x0 >> a >> b;

    vector<long> X(n);
    X[0] = x0;

    for(int i = 1; i<n; i++) {
        X[i] = (X[i-1] * a + b) % (1000000007);
    }

    sort(X.begin(), X.end(), less<long>());

    int q;
    long res = 0;
    cin >> q;
    for(int i = 0; i<q; i++) {
        int idx; 
        cin >> idx;
        res += X[idx];
    }

    cout << res;
}