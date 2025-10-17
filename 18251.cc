#include <bits/stdc++.h>
using namespace std;

int n;
vector<long long> arr;

struct Ret {
    long long L;
    long long R;
    long long S;
    long long B;
};

Ret dfs(int idx){
    if(idx * 2 > n) {
        cout << arr[idx] << ' ' << arr[idx] << ' ' << arr[idx] << ' ' << arr[idx] << endl;
        return {arr[idx], arr[idx], arr[idx], arr[idx]};
    }

    Ret left  = maxSum(idx * 2);
    Ret right = maxSum(idx * 2 + 1);

    long long v = arr[idx];

    long long L = max(left.L,  left.S + right.L + max(0LL, v));
    long long R = max(right.R, right.S + left.R + max(0LL, v));
    long long S = left.S + right.S + v;
    long long B = max({0LL, R, S ,left.R + right.L}) + max(0LL, v);
    cout << L << ' ' << R << ' ' << S << ' ' << B << endl;
    return {L, R, S, B};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    arr.resize(n + 1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];

    Ret res = dfs(1);
    cout << res.B << '\n';
    return 0;
}
