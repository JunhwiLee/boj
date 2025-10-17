#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

class Node {
public:
    Node(char v, Node* p, int L)
        : child_(0), par_(p), fail_(nullptr), val_(v), len_(L), end_(false), outLen_(0) {}
    bool lookup(char ch) const { 
        for(pair<char, Node*> child : child_){
            if(child.first == ch)
                return true;
        }
        return false;
    }
    Node* trans(char ch) const {
        for(pair<char, Node*> child : child_){
            if(child.first == ch)
                return child.second;
        }
        return nullptr;
    }
    Node* insert(char ch, Node* par, int len){
        child_.push_back({ch, new Node(ch, par, len)});
        return child_.back().second;
    }
    char val() const { return val_; }
    Node* par() const { return par_; }
    void setPar(Node* par) { par_ = par; } 
    Node* fail() const { return fail_; }
    void setFail(Node* fail) { fail_ = fail; }
    int len() const { return len_; }
    bool end() const { return end_; }
    void setEnd(bool end) { end_ = end; };
    int outLen() const { return outLen_; }
    void setOutLen(int L) { outLen_ = L; }
private:
    vector<pair<char, Node*>> child_;
    Node *par_, *fail_;
    char val_;
    int len_, outLen_;
    bool end_;
};


class AhoCorasick{
public:
    AhoCorasick() {
        head_ = new Node('.', nullptr, 0);
        head_->setPar(head_);
        head_->setFail(head_);
    }

    void insert(const string& str){
        Node* cur = head_;
        for(char ch : str) {
            if(!cur->lookup(ch))
                cur = cur->insert(ch, cur, cur->len() + 1);
            else cur = cur->trans(ch);
        }
        cur->setEnd(true);
        cur->setOutLen(max(cur->outLen(), cur->len()));
    }

    void failure() {
        queue<Node*> q;
        head_->setFail(head_);

        for (int i = 0; i < 26; ++i) {
            char c = char('a' + i);
            if (!head_->lookup(c)) continue;
            Node* v = head_->trans(c);
            v->setFail(head_);
            if (v->fail()->outLen() > v->outLen())
                v->setOutLen(v->fail()->outLen());
            if (v->fail()->end()) v->setEnd(true);

            q.push(v);
        }

        while (!q.empty()) {
            Node* v = q.front(); q.pop();
            for (int i = 0; i < 26; ++i) {
                char c = char('a' + i);
                if (!v->lookup(c)) continue;

                Node* u = v->trans(c);
                Node* f = v->fail();
                while (f != head_ && !f->lookup(c)) f = f->fail();
                if (f->lookup(c)) f = f->trans(c);
                else f = head_;

                u->setFail(f);

                if (u->fail()->outLen() > u->outLen())
                    u->setOutLen(u->fail()->outLen());
                if (u->fail()->end()) u->setEnd(true);
                q.push(u);
            }
        }
    }

    int search(const string& s) {
        const int n = (int)s.size();
        vector<int> bestEnd(n, 0);

        Node* cur = head_;
        for (int i = 0; i < n; ++i) {
            char ch = s[i];
            while (cur != head_ && !cur->lookup(ch)) cur = cur->fail();
            if (cur->lookup(ch)) cur = cur->trans(ch);

            int L = cur->outLen();
            if (L > 0) bestEnd[i] = L;
        }

        int covered = 0;
        int curL = 1, curR = 0;
        for (int i = 0; i < n; ++i) {
            int L = bestEnd[i];
            if (L == 0) continue;
            int a = i - L + 1;

            if (curL > curR) {
                curL = a; curR = i;
            } else if (a > curR + 1) {
                covered += curR - curL + 1;
                curL = a; curR = i;
            } else {
                if (a < curL) curL = a;
                if (i > curR) curR = i;
            }
        }
        if (curL <= curR) covered += curR - curL + 1;
        return covered;
    }

private:
    Node* head_;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    string str;
    cin >> n >> str >> m;

    AhoCorasick aho = AhoCorasick();

    for(int i = 0; i<m; i++){
        string pattern;
        cin >> pattern;
        aho.insert(pattern);
    }
    aho.failure();

    cout << n - aho.search(str) << endl;
}