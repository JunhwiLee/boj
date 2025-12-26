#include <bits/stdc++.h>
using namespace std;

void CalculateMobius(long long* mobius, int idx) {
    vector<bool> prime(50001, true);
    
    for(int i = 1; i<idx; i++) {
        mobius[i] = 1;
    }
    
    for(int i = 2; i<idx; i++) {
        if(prime[i]) {
            mobius[i] = -1;
            for(int j = 2 * i; j < idx; j += i) {
                prime[j] = false;
                mobius[j] *= -1;
            }
            
            for(long long j = 1LL * i * i; j < idx; j += (1LL * i * i)) {
                mobius[(int)j] = 0;
            }
        }
    }
}

void PrefixSum(long long *pref, long long *mobius, int idx) {
    pref[0] = 0;
    for(int i = 1; i < idx; i++) {
        pref[i] += pref[i - 1] + mobius[i];
    }
}

long long f(long long a, long long b, long long d, long long* mu, long long* pref) {
    long long A = a / d, B = b / d;
    long long n = min(A, B);
    long long res = 0;

    for (long long i = 1; i <= n; ) {
        long long x = A / i;
        long long y = B / i;
        long long r = min(A / x, B / y);
        res += (pref[r] - pref[i - 1]) * x * y;
        i = r + 1;
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int index = 50000;
    long long mu[index + 1];
    CalculateMobius(mu, index + 1);
    
    long long pref[index + 1];
    PrefixSum(pref, mu, index + 1);

    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        long long a, b, d;
        cin >> a >> b >> d;

        cout << f(a, b, d, mu, pref) << '\n';
    }
}