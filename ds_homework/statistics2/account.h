#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED
#include<stdio.h>
typedef struct record{
    record();
    char number[12];
    bool type;
    int time;
    int key1;//用于哈希散列
    int key2;//用于排序二叉树
}record;

typedef struct account{
    account();
    int key2;//用于排序二叉树
    char number[12];
    int bills;
    struct account* lchild;
    struct account* rchild;
}account, *accptr;

void get_account(account *list, record r);
bool find_user(account *list, record r, accptr &p);
int Hash(int key1);
void get_record(char* c, record &r);
void preorder(accptr p,FILE* fp);


#endif
