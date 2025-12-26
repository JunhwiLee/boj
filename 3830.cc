#include <bits/stdc++.h>
using namespace std;

int *par;
long *dif;

pair<int, long> find(int a) {
    if(par[a] == a)
        return {a, 0};
    pair<int, long> pr = find(par[a]);

    par[a] = pr.first;
    dif[a] += pr.second;

    return {par[a], dif[a]};
}

void uni(int a, int b, long d) {
    pair<int, long> pra = find(a);
    pair<int, long> prb = find(b);

    a = pra.first;
    b = prb.first;
    long d1 = pra.second;
    long d2 = prb.second;

    if(a == b)
        return;

    par[a] = b;
    dif[a] = d2 - d1 - d;

    return;
}

string check(int a, int b) {
    pair<int, long> pra = find(a);
    pair<int, long> prb = find(b);

    a = pra.first;
    b = prb.first;
    long d1 = pra.second;
    long d2 = prb.second;

    if(a != b)
        return "UNKNOWN";

    return to_string(d2 - d1);
}

void eval(int n, int m) {
    par = new int[n];
    dif = new long[n];
    for(int i = 0; i<n; i++) {
        par[i] = i;
        dif[i] = 0;
    }

    for(int i = 0; i<m; i++) {
        char ch;
        cin >> ch;

        if(ch == '?'){
            int a, b;
            cin >> a >> b;

            cout << check(a - 1, b - 1) << '\n';
        } 
        if(ch == '!') {
            int a, b;
            long d;
            cin >> a >> b >> d;

            uni(a - 1, b - 1, d);
        }
    }
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;

    cin >> n >> m;

    while(n != 0 || m != 0) {
        eval(n, m);

        cin >> n >> m;
    }
}