#include <bits/stdc++.h>
using namespace std;

long long modinv(long long a, long long mod) {
    long long b = mod, u = 1, v = 0;
    while(b) {
        int t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    if(a != 1) return -1;
    if(u < 0) u += mod;
    return ((u % mod) + mod) % mod;
}

inline long long next_time(long long cur, long long a, long long m){
    a %= m; if(a<0) a+=m;
    if(cur <= a) return a;
    long long k = (cur - a + m - 1) / m;
    return a + k * m;
}

struct Node{
    int n; long long w;
    Node(int n, long long w) : n(n), w(w) {};
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e;
    cin >> n >> e;

    const long long INF = 0x7fffffffffffffff;
    vector<vector<int>> steps(n, vector<int>(0));
    vector<int> term(n);

    vector<vector<vector<int>>> maze(1000001, vector<vector<int>>(0));

    for(int i = 0; i<n; i++){
        cin >> term[i];
        for(int j = 0; j<term[i]; j++){
            int k;
            cin >> k;
            steps[i].push_back(k);
            maze[k].push_back({i, j});
        }
    }

    auto cmp = [&](Node n1, Node n2) -> bool { return n1.w > n2.w; };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    vector<long long> dist(n, INF);
    vector<bool> visited(n);
    dist[0] = 0;
    pq.push(Node(0, 0));

    long long min = 0x7fffffffffffffff;

    while(!pq.empty()){
        Node cur = pq.top();
        pq.pop();

        if(visited[cur.n]) continue;
        visited[cur.n] = true;

        for(int cand : steps[cur.n]){
            if(cand == e){
                long long a;
                if(maze[cand][0][0] == cur.n) a = maze[cand][0][1];
                else a = maze[cand][1][1];

                long long w = next_time(cur.w, a, term[cur.n]);

                if(min > w) min = w;
            }

            if(maze[cand].size() != 2) continue;
            int nxt = 0, a1, a2;
            if(maze[cand][0][0] == cur.n) {
                nxt = maze[cand][1][0];
                a2 = maze[cand][1][1];
                a1 = maze[cand][0][1];
            }
            else {
                nxt = maze[cand][0][0];
                a2 = maze[cand][0][1];
                a1 = maze[cand][1][1];
            }

            long long n1 = term[cur.n], n2 = term[nxt];
            long long d = gcd(n1, n2);
            long long lcm = n1 / d * n2;
            if(a1 % d != a2 % d) continue;
            int x = (n1 * ((a2 - a1) / d) * modinv(n1 / d, n2 / d) + a1) % lcm;

            long long w = next_time(cur.w, x, lcm);

            if(dist[nxt] > w) {
                dist[nxt] = w;
                pq.push(Node(nxt, dist[nxt]));
            }
        }
    }

    cout << (min == 0x7fffffffffffffff ? -1 : min)<< '\n';
}