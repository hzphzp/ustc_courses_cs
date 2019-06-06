#include <iostream>
#include "waiting_queue.h"
using namespace std;

void Queue::init(int msize = QUEUE_INIT_SIZE){
    queuesize = msize;
    head = new LNode;
    head->locate = 0;
    head->next = NULL;
    rear = head;
}
bool Queue::enqueue(int num, int start_time){
    if(getlength() == queuesize) return false;
    LinkList p =new LNode;
    p->number = num;
    p->start_time = start_time;
    p->locate = rear->locate+1;
    rear->next= p;
    rear = p;
    rear->next = NULL;
    return true;
}
bool Queue::dequeue(int &num, int &start_time){

    if(head == rear) return false;
    LinkList p = head->next;
    num = p->number;
    start_time = p->start_time;
    head->next = p->next;
    locate_update(p);
    if(p == rear) rear = head;
    delete p;
    return true;
}
void Queue::locate_update(LinkList p){
    p = p->next;
    while(p!=NULL){
            p->locate--;
            p = p->next;
    }
}
void Queue::Delete(LinkList p, int &start_time){
    LinkList q = head;
    start_time = p->start_time;
    while(q->next != p) q = q->next;
    q->next = p->next;
    locate_update(p);
    if(p == rear) rear = head;
    delete p;
}

int Queue::getlength(){
    return rear->locate;
}
bool Queue::lookingfor(int num, LinkList &p){
    p = head->next;
    while(p&&p->number != num) p = p->next;
    if(p) return true;
    return false;
}
void Queue::show(){
    LinkList p = head->next;
    while(p){
            cout<<p->number<<"==="<<p->start_time<<"==========="<<p->locate<<endl;
            p = p->next;
    }
}














