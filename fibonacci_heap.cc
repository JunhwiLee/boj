#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Compare>
class FiboHeap {
  public:
    FiboHeap(Compare comp) : comp_(comp) {}
  private:
    Compare comp_;
    struct BinomialTree;
    struct LinkedList {
        struct Node {
            BinomialTree* val;
            Node* next, prev;
        };

        Node* head_, tail_;

        LinkedList() {
            head_->next = tail_;
            tail_->prev = head_;
        }

        LinkedList(BinomialTree tree) {
            Node* n = new Node();
            n->val = tree;

            head_->next = n;
            tail_->prev = n;
            n->next = tail_;
            n->prev = head_;
        }

        void MergeList(LinkedList *list){
            tail_->prev->next = list->head_->next;
            list->head_->next->prev = tail_->prev;

            delete tail_;
            delete list->head_;

            tail_ = list->tail_;
        }
    };

    struct BinomialTree {
        T key;
        bool marked;
        int size_;
        LinkedList* children;

        BinomialTree* MergeTree(BinomialTree* tree) {
            size_++;
            children->MergeList(new LinkedList(tree));
            return this;
        }

        T top() {
            return key;
        }

        BinomialTree* pruning()
    };
    
    BinomialTree* MergeTree(BinomialTree* t1, BinomialTree* t2) {
        if(t1->size_ != t2->size_) 
            throw "Size dismatch";
        
        return t1->MergeTree(t2);
    }
};

int main() {

}