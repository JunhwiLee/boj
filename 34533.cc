#include <bits/stdc++.h>
using namespace std;


pair<int, string> dfs(vector<vector<int>> tree, int cur) {
    vector<pair<int, string>> sub(0);
    for(int nxt : tree[cur]){
        sub.push_back(dfs(tree, cur));
    }

    
}

void f(){
    int n;
    cin >> n;

    vector<vector<int>> tree(n, vector<int>(0));

    int a;
    cin >> a;

    for(int i = 1; i<n; i++){
        int s;
        cin>> s;
        tree[s - 1] = i;
    }

    dfs(tree);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for(int i = 0; i<t; i++)
        f();
}