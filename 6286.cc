#include <bits/stdc++.h>
using namespace std;

const int MAXD = 60;
pair<deque<char>*, deque<char>*> add(deque<char>* a, deque<char>* b) {
    int carry = 0;
    deque<char>* res = new deque<char>;
    for(int i = 0; i < max(a->size(), b->size()); i++) {
        int d = 0;
        if(i < a->size()) {
            d += (*a)[i] - '0';
        }
        if(i < b->size()) {
            d += (*b)[i] - '0';
        }
        d += carry;

        res->push_back((d % 10) + '0');
        carry = d / 10;
    }

    delete a;
    if(carry) {
        res->push_back(carry + '0');
    }

    if(res->size() > MAXD) {
        deque<char>* temp = new deque<char>(res->begin() + 1, res->end());
        delete res;
        res = temp;
        temp = new deque<char>(b->begin() + 1, b->end());
        delete b;
        return {temp, res};
    }
    
    return {b, res};
}

pair<unsigned char, unsigned short int> encoding(int val) {
    return {(unsigned char)(val / 65536), (unsigned short int) (val % 65536)};
}

int type(unsigned char c, unsigned short int s) {
    int res = 0;
    res += c * 65536;
    return res + s;
}

struct Node {
    unsigned char nextc[10];
    unsigned short int nexts[10];
    unsigned char shc;
    unsigned short int shs;
    Node(int sh) : nextc(), nexts() {
        for(int i = 0; i< 10; i++) {
            nextc[i] = 0;
            nexts[i] = 0;
        }
        auto p = encoding(sh);
        shc = p.first;
        shs = p.second;
    }
};

deque<Node> pointer;

struct Trie {
    int head;
    Trie() : head(0) {
        pointer.push_back(Node(INT_MAX));
    }
    void insert(deque<char>& str, int sh) {
        int cur = head;
        for(char ch : str) {
            int nxt = type(pointer[cur].nextc[ch - '0'], pointer[cur].nexts[ch - '0']);
            if(nxt == 0) {
                pointer.push_back(Node(sh));
                int temp = pointer.size() - 1;
                auto pa = encoding(temp);
                pointer[cur].nextc[ch - '0'] = pa.first;
                pointer[cur].nexts[ch - '0'] = pa.second;

                nxt = type(pointer[cur].nextc[ch - '0'], pointer[cur].nexts[ch - '0']);
            }
            cur = nxt;

            int cur_sh = type(pointer[cur].shc, pointer[cur].shs);
            if(cur_sh > sh){
                auto p = encoding(sh);
                pointer[cur].shc = p.first;
                pointer[cur].shs = p.second;
            }
        }
    }
    int search(deque<char>& str) {
        int cur = head;
        for(char ch : str) {
            int nxt = type(pointer[cur].nextc[ch - '0'], pointer[cur].nexts[ch - '0']);
            if(nxt == 0) {
                return -1;
            }
            cur = nxt;
        }
        return type(pointer[cur].shc, pointer[cur].shs);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    deque<char>* a = new deque<char>();
    deque<char>* b = new deque<char>();

    a->push_back('1');
    b->push_back('1');

    Trie trie;
    trie.insert(*a, 0);

    for(int i = 2; i<100001; i++) {
        pair<deque<char>*, deque<char>*> p = add(a, b);

        a = p.first;
        b = p.second;
        
        reverse(b->begin(), b->end());
        auto v = new deque<char>(b->begin(), min(b->end(), b->begin() + 40));
        trie.insert(*(v), i);
        delete v;
        reverse(b->begin(), b->end());
    }

    int n;
    cin >> n;

    for(int i = 0; i<n; i++) {
        string str;
        cin >> str;
        std::deque<char>* v = new deque<char>(str.begin(), str.end());
        cout << "Case #" << i + 1 << ": " << trie.search(*v) << "\n";
        delete v;
    }
}