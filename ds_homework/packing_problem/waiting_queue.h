#ifndef WAITING_QUEUE_H_INCLUDED
#define WAITING_QUEUE_H_INCLUDED
#include "LNode.h"
#define QUEUE_INIT_SIZE 10
class Queue
{
public:
    void init(int m);
    bool enqueue(int num, int start_time);
    bool dequeue(int &num, int &start_time);
    void locate_update(LinkList p);             //using before delete
    int getlength();
    bool lookingfor(int num, LinkList &p);
    void Delete(LinkList p, int &start_time);
    void show();
private:
    LinkList head;
    LinkList rear;
    int queuesize;
};


#endif // WAITING_QUEUE_H_INCLUDED
