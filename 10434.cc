#include <bits/stdc++.h>
using namespace std;

bool wilson(int n) {
    if(n == 1) return false;
    int res = 1;
    for(int i = 1; i<n; i++) {
        res *= i;
        res %= n;
    }

    return res % n == n - 1;
}

vector<bool> happy(10001);
vector<bool> visited(10001);

bool FindHappy(int n){
    if(visited[n]) return happy[n];
    visited[n] = true;

    string str = to_string(n);

    int nxt = 0;
    for(char ch : str){
        nxt += (ch - '0') * (ch - '0');
    }

    return happy[n] = FindHappy(nxt);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    happy[1] = true;
    visited[1] = true;
    for(int i = 2; i<10001; i++){
        FindHappy(i);
    }

    int n;
    cin >> n;
    
    for(int i = 0; i<n; i++){
        int c, m;
        cin >> c >> m;
        cout << c << ' ' << m << ' ' << (wilson(m) && happy[m] ? "YES" : "NO") << '\n';
    }

    return 0;
}