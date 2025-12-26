#include <bits/stdc++.h>
using namespace std;

vector<int> result;

class Node {
public:
    Node(char v, Node* p)
        : child_(0), par_(p), fail_(nullptr), val_(v), best_(0), end_(false) {}
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
    Node* insert(char ch, Node* par){
        child_.push_back({ch, new Node(ch, par)});
        return child_.back().second;
    }
    char val() const { return val_; }
    Node* par() const { return par_; }
    void setPar(Node* par) { par_ = par; } 
    Node* fail() const { return fail_; }
    void setFail(Node* fail) { fail_ = fail; }
    int best() const { return best_; }
    void setBest(int best) { best_ = best;}
    bool end() const { return end_; }
    void setEnd(bool end) { end_ = end; };
private:
    vector<pair<char, Node*>> child_;
    Node *par_, *fail_;
    char val_;
    int best_;
    bool end_;
};


class AhoCorasick{
public:
    AhoCorasick() {
        head_ = new Node('.', nullptr);
        head_->setPar(head_);
        head_->setFail(head_);
    }

    void insert(const string& str){
        Node* cur = head_;
        for(char ch : str) {
            if(!cur->lookup(ch))
                cur = cur->insert(ch, cur);
            else cur = cur->trans(ch);
        }
        cur->setEnd(true);
        cur->setBest(str.size());
    }

    void failure() {
        queue<Node*> que;
        head_->setFail(head_);
        que.push(head_);

        while(!que.empty()){
            Node* cur = que.front();
            que.pop();

            Node* fail = cur->par();
            while(fail != head_){
                fail = fail->fail();
                if(fail->lookup(cur->val())) {
                    fail = fail->trans(cur->val());
                    break;
                }
            }
            cur->setFail(fail);
            if(fail->end()) {
                cur->setBest(max(cur->best(), fail->best()));
                cur->setEnd(true);
            }
            
            for(int i = 0; i<26; i++){
                if(cur->lookup((char)(i + 'a')))
                    que.push(cur->trans((char)(i + 'a')));
            }
        }
    }

    int search(string str) {
        int res = 0;
        Node* cur = head_;
        int i = 0;
        for(char ch : str){
            if(cur->lookup(ch)){
                cur = cur->trans(ch);
            }
            else{
                while(cur != head_){
                    cur = cur->fail();
                    if(cur->lookup(ch)){
                        cur = cur->trans(ch);
                        break;
                    }
                }
            }
            if(cur->end()) {
                result[i] = cur->best();
            }
            i++;
        }
        if(cur->end()) {
                result[i - 1] = cur->best();
        }
        
        return res;
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

    result.resize(n, -1);

    AhoCorasick aho;

    for(int i = 0; i<m; i++){
        string pattern;
        cin >> pattern;
        aho.insert(pattern);
    }
    aho.failure();
    aho.search(str);

    /*for(int i = 0; i<n; i++) {
        cout << result[i] << ' ';
    }
    cout << '\n';*/

    int res = 0;
    int cnt = 0;

    for(int i = n - 1; i >= 0; i--){
        if(result[i] == -1) {
            if(cnt > 0) {
                cnt--;
            }else{
                res++;
            }
        }
        else {
            cnt = max(result[i] - 1, cnt - 1);
        }
    }

    cout << res << endl;
}