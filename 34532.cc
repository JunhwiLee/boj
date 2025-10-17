#include <bits/stdc++.h>
using namespace std;

struct Segment {
    int n;
    vector<vector<int>> bucket;
    Segment(int n): n(n), bucket(4*n) {}

    void add(int node, int l, int r, int ql, int qr, int idx) {
        if(qr < l || r < ql) return;
        if(ql <= l && r <= qr) {
            bucket[node].push_back(idx);
            return;
        }
        int m = (l + r) / 2;
        add(node * 2, l, m, ql, qr, idx);
        add(node * 2 + 1, m+1, r, ql, qr, idx);
    }

    void add(int ql, int qr, int idx) { add(1, 1, n, ql, qr, idx); }

    void collect(int node, int l, int r, int pos, vector<int>& out) {
        if(!bucket[node].empty()) {
            out.insert(out.end(), bucket[node].begin(), bucket[node].end());
            bucket[node].clear();
        }
        if(l == r) return;
        int m = (l + r) / 2;
        if(pos <= m) collect(node * 2, l, m, pos, out);
        else collect(node * 2 + 1, m + 1, r, pos, out);
    }

    vector<int> collect(int pos) {
        vector<int> out;
        collect(1, 1, n, pos, out);
        return out;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> l(n), r(n);
    for(int i = 1; i <= n-1; i++)
        cin >> l[i] >> r[i];
    Segment seg(n);
    for(int i = 1; i <= n-1; i++)
        seg.add(l[i], r[i], i);

    vector<int> j(n+1, 0), visited(n+1, 0);
    queue<int> que;
    visited[n] = 1;
    que.push(n);
    int cnt = 1;

    while(!que.empty()) {
        int u = que.front();
        que.pop();
        const vector<int> cand = seg.collect(u);
        for(int v : cand) {
            if(!visited[v]) {
                visited[v] = 1;
                j[v] = u;
                que.push(v);
                cnt++;
            }
        }
    }

    if(cnt != n) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for(int i = 1; i <= n - 1; i++) {
        cout << j[i] << ' ';
    }
    cout << '\n';
    return 0;
}