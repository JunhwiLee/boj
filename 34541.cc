#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int x, y;
    cin >> n >> x >> y;

    int ax, ay;
    int bx, by;
    int cx, cy;
    int dx, dy;

    ax = 0, ay = 0;

    cout << 4 * x + 4 * y + 6 <<endl;

    if(n == 2){
        cout << "C 1 1" << endl;
        cout << "B 0 1" << endl;
        cout << "D 1 0" << endl;
        bx = 0, by = 1;
        cx = 1, cy = 1;
        dx = 1, dy = 0;
    }
    else{
        cout << "C " << n / 2 << ' ' << n / 2 << endl;
        cout << "B 0 " << n / 2 << endl;
        cout << "D " << n / 2 << " 0" << endl;
        bx = 0, by = n / 2;
        cx = n / 2, cy = n / 2;
        dx = n / 2, dy = 0;
    }

    for(int i = 0; i<x; i++){
        cx++;
        cout << "C " << cx << ' ' << cy << endl;
        dx++;
        cout << "D " << dx << ' ' << dy << endl;
        bx++;
        cout << "B " << bx << ' ' << by << endl;
        ax++;
        cout << "A " << ax << ' ' << ay << endl;
    }
    
    for(int i = 0; i<y; i++){
        by++;
        cout << "B " << bx << ' ' << by << endl;
        cy++;
        cout << "C " << cx << ' ' << cy << endl;
        dy++;
        cout << "D " << dx << ' ' << dy << endl;
        ay++;
        cout << "A " << ax << ' ' << ay << endl;
    }

    dx = x + n;
    cout << "D " << dx << ' ' << dy << endl;
    by = y + n;
    cout << "B " << bx << ' ' << by << endl;
    cx = x + n; cy = y + n;
    cout << "C " << cx << ' ' << cy << endl;
}