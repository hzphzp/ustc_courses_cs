#ifndef LNODE_H_INCLUDED
#define LNODE_H_INCLUDED
typedef struct LNode{
    int number;
    int start_time;
    int locate;
    struct LNode *next;
}LNode, *LinkList;
typedef struct SNode{
    int number;
    int start_time;
    int pay_time;
}SNode;

#endif // LNODE_H_INCLUDED
