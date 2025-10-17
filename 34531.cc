#include <bits/stdc++.h>
using namespace std;

int binarySearch(int m, const vector<int>& arr){
    int st = 0;
    int en = arr.size() - 1;

    while(st < en){
        int mid = (st + en) / 2;
        if(arr[mid] > m) en = mid;
        else if(arr[mid] < m) st = mid + 1;
        else return m;
    }
    return arr[st];
}

void f(){
    int n, m;
    cin >> n >> m;
    
    vector<int> item(n);
    vector<int> head(m);

    for(int i = 0; i<n; i++){
        cin >> item[i];
        item[i]--;
    }
    
    for(int i = 0; i<m; i++){
        cin >> head[i];
        head[i]--;
    }
    
    vector<bool> v(m);
    vector<int> where(m);
    vector<vector<int>> cycles;
    
    int cnt = 0;
    for(int i = 0; i<m; i++){
        if(!v[i]){
            int cur = i;
            vector<int> cycle;
            while(!v[cur]){
                v[cur] = true;
                where[cur] = cnt;
                cycle.push_back(cur);
                cur = head[cur];
            }
            sort(cycle.begin(), cycle.end(), less<int>());
            cycles.push_back(cycle);
            cnt++;
        }
    }

    int mi = 0;
    for(int i = 0; i<n; i++){
        int b = binarySearch(mi, cycles[where[item[i]]]);
        //cout << mi << ' ' << b << '\n';
        if(mi > b) {
            cout << "NO\n";
            return;
        }
        mi = b;
    }
    cout << "YES\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t){
        t--;
        f();
    }
}