#include<iostream>
using namespace std;
#ifndef CYCLELIST_H_INCLUDED
#define CYCLELIST_H_INCLUDED
typedef struct LNode{
    int num;
    int key;
    struct LNode *next;
}LNode, *LinkList;
class CycleList{
public:
    CycleList(){
        head=NULL;
    }
    void Append(int n,int k){
        LinkList p;
        p = new LNode;
        p->num = n;
        p->key = k;
        if(head == NULL){
                head = p;
                head ->next = p;
                return;
        }
        p->next = head->next;
        head->next = p;
        head = p;
    }
    bool Delete(LinkList prior, int &k, int &n){      //I set the parameter a prior *
        if(head == NULL) return false;
        LinkList q;
        q = prior->next;
        prior->next = q->next;
        k = q->key;
        n = q->num;
        if(q == head) head=prior;         //protect the head pointer
        if(prior == q) head = NULL;      //mark the empty list
        delete q;
        return true;
    }
    LinkList get_head(){
        return head;
    }
    bool ListEmpty(){
        if(head==NULL) return true;
        return false;
    }
private:
    LinkList head;
};







#endif // CYCLELIST_H_INCLUDED
