#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, n;
    cin >> c >> n;

    const long long INF = (long long)4e18;
    vector<long long> dp(c + 1, INF);
    dp[0] = 0;

    for(int i = 0; i<n; i++) {
        int cost, people;
        cin >> cost >> people;
        for (int j = 0; j<=c; j++) {
            if (dp[j] == INF) continue;
            int nj = min(c, j + people);
            dp[nj] = min(dp[nj], dp[j] + cost);
        }
    }

    cout << dp[c] << "\n";
}
