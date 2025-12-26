#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long n, x0, a, b;
    cin >> n >> x0 >> a >> b;
    
    int q;
    cin >> q;

    vector<int> queries(q);
    vector<int> lo(q, 0);
    vector<int> hi(q, MOD - 1);
    
    for(int i = 0; i<q; i++) {
        cin >> queries[i];
    }
    
    sort(queries.begin(), queries.end(), less<int>());
    
    while(true) {
        long cur = x0;
        vector<int> cnt(q, 0);
        
        for(int i = 0; i<n; i++) {
            int low = 0, high = q - 1;

            while(low <= high) {
                int mid = (low + high) / 2;
                if((lo[mid] + hi[mid]) / 2 < cur) {
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }  

            if(low != -1 && low != q) {
                cnt[low]++;
            }

            cur = (cur * a + b) % MOD;
        }

        int count = 0;

        for(int i = 0; i<q; i++) {
            count += cnt[i];
            int mid = (lo[i] + hi[i]) / 2;

            if(count >= queries[i] + 1) {
                hi[i] = mid;
            }
            else {
                lo[i] = mid + 1;
            }
        }

        bool done = true;
        for(int i = 0; i < q; ++i) {
            if(lo[i] < hi[i]) { 
                done = false; break; 
            }
        }
        if(done) break;
    }
    
    long res = 0;
    for(int i = 0; i < q; i++) {
        res += lo[i];
    }

    cout << res;

    return 0;
}