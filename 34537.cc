#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int u_, v_;
    long long w_;
    int x_, y_, idx_;
    Edge(int u, int v, long long w, int x, int y, int idx) : u_(u), v_(v), w_(w), x_(x), y_(y), idx_(idx) {}

    bool operator<(const Edge& e) const {
        return this->w_ < e.w_;
    }

    friend ostream& operator<<(ostream&os, const Edge& e) {
        return os << e.u_ << ' ' << e.v_ << ' ' << e.w_;
    }
};

vector<int> par;

int find(int a){
    if(par[a] == a) return a;
    return par[a] = find(par[a]);
}

void unite(int a, int b){
    a = find(a);
    b = find(b);
    if(a == b) return;

    par[a] = b;
}

bool same(int a, int b){
    return find(a) == find(b);
}

vector<bool> isMst;
vector<Edge> edgeList;

bool possible(long long budget, long long weight, int n, int m){
    
    for(int i = 0; i<m; i++){
        isMst[i] = false;
    }
    for(int i = 0; i<n; i++){
        par[i] = i;
    }

    struct Cand { long long need; int u,v,idx; };
    vector<Cand> cand(m);
    
    for(Edge cur : edgeList){
        if(cur.w_ >= weight){
            if(same(cur.u_, cur.v_)) continue;
            unite(cur.u_, cur.v_);
        }
        else{
            long long need = ((weight - cur.w_) % cur.x_ == 0 ? (weight - cur.w_) / cur.x_ : (weight - cur.w_) / cur.x_ + 1) * cur.y_;
            cand.push_back({need, cur.u_, cur.v_, cur.idx_});
        }
    }

    sort(cand.begin(), cand.end(), [](const Cand& a, const Cand& b){
        return a.need < b.need;
    });

    for(const Cand& cur : cand){
        if(same(cur.u, cur.v)) continue;
        if(budget - cur.need < 0) {
            return false;
        }
        unite(cur.u, cur.v);
        budget -= cur.need;
        isMst[cur.idx] = true;
    }
    return true;
}

int main(){
    int n, m, b;
    cin >> n >> m >> b;

    int cnt = 0;

    for(int i = 0; i<m; i++){
        int u, v, w, x, y;
        cin >> u >> v >> w >> x >> y;
        Edge e(u - 1, v - 1, w, x, y, cnt++);
        edgeList.push_back(e);
    }

    par.resize(n);
    isMst.resize(m);

    int st = 0, en = 2000000000, mid = 0;
    while(st < en){
        mid = (st + en + 1) / 2;
        if(possible(edgeList, b, mid, n, m)) st = mid;
        else en = mid - 1;
    }

    cout << st << '\n';
    possible(edgeList, b, st, n, m);

    for(Edge e : edgeList){
        if(isMst[e.idx_]) cout << ((st - e.w_) % e.x_ == 0 ? (st - e.w_) / e.x_ : (st - e.w_) / e.x_ + 1) << '\n';
        else cout << "0\n";
    }
}