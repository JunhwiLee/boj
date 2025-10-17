#include <bits/stdc++.h>
using namespace std;

vector<string> word;
vector<int> mask = {1, 3, 4, 5, 6, 7, 9, 10, 11, 12, 14, 15,
                    16, 17, 18, 20, 21, 22, 23, 24, 25};
vector<bool> know(26);
int Max = 0;

void check(){
    int cnt = 0;
    for(string str : word){
        bool check = true;
        for(char ch : str){
            if(!know[ch - 'a']) {
                check = false;
                break;
            }
        }
        if(check) cnt++;
    }
    Max = max(Max, cnt);
}

void learning(int k, int from){
    if(k <= 0){
        check();
        return;
    }
    for(int i = from; i < 21 - k + 1; i++){
        know[mask[i]] = true;
        learning(k - 1, i + 1);
        know[mask[i]] = false;
    }
}

int main(){
    int n, k;
    cin >> n >> k;

    if(k < 5){
        cout << 0 << endl;
        return 0;
    }

    for(int i = 0; i<n; i++){
        string str;
        cin >> str;
        word.push_back(str);
    }
    know['a' - 'a'] = true;
    know['c' - 'a'] = true;
    know['t' - 'a'] = true;
    know['n' - 'a'] = true;
    know['i' - 'a'] = true;
    learning(k - 5, 0);

    cout << Max << endl;
}