#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> graph;
vector<char> visited;
vector<int> cycle;
vector<char> used;
vector<int> sta;

bool check_cycle(int u) {
    int ptr = (int)sta.size() - 1;

    while (sta[ptr] != u) {
        cycle[sta[ptr]] += 1;
        if (cycle[sta[ptr]] > 1) return false;
        ptr -= 1;
    }
    cycle[sta[ptr]] += 1;
    if (cycle[sta[ptr]] > 1) return false;
    return true;
}

bool dfs(int cur, int pre) {
    if(visited[cur])
        return check_cycle(cur);

    visited[cur] = true;
    sta.push_back(cur);

    for(auto [nxt, id] : graph[cur]) {
        if(used[id]) continue;
        used[id] = true;

        if(!dfs(nxt, cur)) return false;
    }

    sta.pop_back();
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    graph.resize(n);
    visited.assign(n, false);
    cycle.assign(n, 0);
    used.assign(m, false);

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;

        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
    }

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            if(!dfs(i, -1)) {
                cout << "Not cactus\n";
                return 0;
            }
        }
    }
    cout << "Cactus\n";
    return 0;
}
