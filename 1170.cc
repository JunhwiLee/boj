#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;
vector<int> cycle;
vector<vector<bool>> used_edge;
vector<int> sta;

bool check_cycle(int u) {
    int ptr = sta.size() - 1;

    while(sta[ptr] != u) {
        cycle[sta[ptr]] += 1;
        if(cycle[sta[ptr]] > 1)
            return false;
        ptr -= 1;
    }
    cycle[sta[ptr]] += 1;
    if(cycle[sta[ptr]] > 1)
        return false;
    return true;
}

bool dfs(int cur, int pre) {
    if(visited[cur])
        return check_cycle(cur);
    visited[cur] = true;
    sta.push_back(cur);

    for(int nxt : graph[cur]) {
        if(used_edge[cur][nxt]) continue;
        used_edge[cur][nxt] = true;
        used_edge[nxt][cur] = true;

        if(!dfs(nxt, cur)) return false;
    }
    sta.pop_back();
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n, vector<int>(0));
    visited.resize(n, false);
    cycle.resize(n, 0);
    used_edge.resize(n, vector<bool>(n, false));

    for(int i = 0; i<m; i++) {
        int u, v;
        cin >> u >> v;

        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    int cnt = 0;

    for(int i = 0; i<n; i++) {
        if(!visited[i]) {
            if(dfs(i, -1)){
                cnt ++;
            }
        }
    }
    cout << cnt << "\n";
    return 0;
}