#include <bits/stdc++.h>
using namespace std;

long long power(long long x, long long e, long long MOD){
    if(e == 0) return 1;
    long long p = power(x, e/2, MOD);
    if(e % 2 == 1)
        return (((p * p) % MOD) * x) % MOD;
    return (p * p) % MOD;
}

int seed = 10093;
int rand(int MOD){
    seed = (29 * seed) % 10597;
    return seed % MOD;
}

bool MillarRabin(long long n){
    long long d = n - 1; int s = 0;
    while ((d & 1) == 0) { d >>= 1; ++s; }
    
    int ss = rand(s - 1);
    int tt = 1;
    for(int i = 0; i<ss; i++){
        tt *= 2;
    }
    int a = rand(n - 1);
    
    return power(a, d, n) % n == 1 || power(a, tt * d, n) % n == n - 1;
}

bool isPrime(long long n){
    for(int i = 0; i<4; i++){
        if(!MillarRabin(n)) return false;
    }
    return true;
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    for(int i = 2; i<100; i++){
        cout << i << " : " << isPrime(i) << '\n';
    }
    
    long long p, a;
    
    cin >> p >> a;
    while(p != 0 && a != 0){
        if(power(a, p, p) % p == a % p && !isPrime(p)){
            cout << "yes\n";
        }
        else{
            cout << "no\n";
        }
        cin >> p >> a;
    }
}