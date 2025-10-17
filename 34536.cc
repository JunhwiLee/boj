#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, k;
    cin >> n >> k;

    vector<long long> a(n), b(n), c(n);

    for(int i = 0; i<n; i++){
        cin >> a[i];
    }

    for(int i = 0; i<n; i++){
        cin >> b[i];
    }

    for(int i = 0; i<n; i++){
        cin >> c[i];
    }

    sort(a.begin(), a.end(), less<long long>());
    sort(b.begin(), b.end(), greater<long long>());
    sort(c.begin(), c.end(), less<long long>());

    long long target = 2 * k - (c[0] + c[n - 1]);

    int pointer1 = 0;
    int pointer2 = 0;
    long long closest = a[0] + b[n - 1];

    while(pointer1 < n && pointer2 < n){
        long long cur = a[pointer1] + b[pointer2];
        if(abs(target - closest * 2) > abs(target - cur * 2))
            closest = cur;

        if(cur * 2 < target){
            pointer1++;
        }
        else if(cur * 2 > target){
            pointer2++;
        }
        else{
            break;
        }
    }

    cout << target << ' ' << closest << '\n';
    
    if(abs(closest + c[0] - k) > abs(closest + c[n - 1] - k))
        cout << abs(closest + c[0] - k) << endl;
    else
        cout << abs(closest + c[n - 1] - k) << endl;
}