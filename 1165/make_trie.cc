#include <bits/stdc++.h>
using namespace std;

struct Node {
    bool end = false;
    Node* children[26];
    bool lookup(char ch) {
        return children[ch - 'A'] != nullptr;
    }
    void insert(char ch, Node *child) {
        children[ch - 'A'] = child;
    }
    Node *trans(char ch) {
        return children[ch - 'A'];
    }
};

struct Trie {
    Node *head;

    Trie() : head(new Node()) {}
    void insert(string& str) {
        Node *cur = head;
        for(char ch : str) {
            if(!cur->lookup(ch)) {
                cur->insert(ch, new Node());
            }
            cur = cur->trans(ch);
        }
        cur->end = true;
    }

    string str;

    void dfs(Node *cur) {
        //cout << "0\n";
        for(int i = 0; i<26; i++) {
            if(cur->lookup(i + 'A')) {
                str += (char)(i + 'A');
                if(cur->end) str += '.';
                dfs(cur->trans(i + 'A'));
                str += (char)(i + 'A');
            }
        }
    }

    string MakeString() {
        str = "";
        dfs(head);
        return str;
    }

};

int main() {
    Trie trie;

    ifstream fin("dict.txt");
    if (!fin.is_open()) {
        cerr << "Failed to open dict.txt\n";
        return 1;
    }

    string word;
    while(fin >> word) {
        //cout << word << '\n';
        trie.insert(word);
    }
    fin.close();

    ofstream fout("trie.txt");
    if (!fout.is_open()) {
        cerr << "Failed to open trie.txt\n";
        return 1;
    }

    fout << trie.MakeString();
    fout.close();

    return 0;
}