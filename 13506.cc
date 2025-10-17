#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string str;
    cin >> str;
    int sz = str.size();
    vector<int> fail(sz, -1);

    for(int i = 1; i<sz; i++){
        int idx = i - 1;
        while(idx > -1){
            idx = fail[idx];
            if(str[idx + 1] == str[i]){
                idx += 1;
                break;
            }
        }
        fail[i] = idx;
    }

    vector<bool> chk(sz, false);

    int idx = fail.back();
    while(idx > -1){
        chk[idx] = true;
        idx = fail[idx];
    }

    int m = -1;
    for(int i = 1; i<sz - 1; i++){
        if(chk[fail[i]]) {
            m = max(m, fail[i]);
        }
    }

    if(m == -1){
        cout << -1 << endl;
        return 0;
    }

    for(int i = 0; i<m+1; i++){
        cout << str[i];
    }
    cout << endl;
}