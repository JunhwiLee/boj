#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#define ostringstream builder
using namespace std;

class Node{
    public:
        explicit Node(int val) : val_(val) {
            child[0] = child[1] = nullptr;
        }
        Node* child[2];
        int val_;
};

class Trie{
    public:
        explicit Trie() : head_(0) {}
        void insert(int num) {
            string str = bitset<32>(num).to_string();
            Node cur = head_;
            for(char ch : str){
                int val = ch - '0';
                if(cur.child[val] == nullptr){
                    Node nxt = Node(val);
                    cur.child[val] = &nxt;
                }
                cur = *cur.child[val];
            }
        }

        int find(){
            builder sb;
            return stoi(backtrack(*head_.child[0], *head_.child[1], sb, 0).str, nullptr, 2);
        }
        
    private:
        Node head_;
        builder backtrack(Node n, Node m, builder sb, int dep){
            if(dep == 32) return sb;
            if(&n == nullptr && &m == nullptr) return sb;
            if(&n == nullptr) {
                sb << "0";
                return backtrack(*m.child[0], *m.child[1], sb, dep + 1);
            }
            if(&m == nullptr) {
                sb << "0";
                return backtrack(*n.child[0], *n.child[1], sb, dep + 1);
            }

            if(n.val_ != m.val){
                
            }
        }
};

int main(){
    int n;
    cin >> n;

    Trie trie = Trie();
    for(int i = 0; i<n; i++){
        int a;
        cin >> a;
        trie.insert(a);
    }
    cout << trie.find() << endl:
    return 0;
}