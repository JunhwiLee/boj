#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, k;
    cin >> n >> k;

    vector<vector<int>> dp(n+1, vector<int>(k + 1));

    for(int i = 1; i<=n; i++){
        int w, v;
        cin >> w >> v;

        for(int j = 1; j<=k; j++){
            dp[i][j] = dp[i - 1][j];
            if(j >= w){
                dp[i][j] = max(dp[i][j], dp[i - 1][j - w] + v);
            }
        }
    }

    cout << dp[n][k] << endl;
}