#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<pair<int, int>> sw;
    vector<vector<int>> row(n);
    vector<vector<int>> col(m);

    for(int i = 0; i<k; i++) {
        int x, y;
        cin >> x >> y;

        sw.push_back({x, y});
        row[x].push_back(sw.size() - 1);
        col[y].push_back(sw.size() - 1);
    }

    int x = 0;
    int y = 0;
}