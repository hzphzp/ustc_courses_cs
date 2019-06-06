#include "account.h"
#include<iostream>
using namespace std;
#include<iomanip>
#include<stdio.h>
account::account(){
    key2 = -1;  //说明该空间没有被利用
    number[0] = '\0';
    bills = 0;
    lchild = NULL;
    rchild = NULL;
}

record::record(){
    number[0] = '\0';
    type = true;
    time = 0;
    key1 = 0;
    key2 = 0;
}
void get_account(account *list, record r){
    accptr p,q;
    int k;
    if(!find_user(list,r,p)){    //冲突且没有找到
        q = new account;
        q->key2 = r.key2;
        for(k = 0 ; k<12; k++) q->number[k] = r.number[k];
        q -> lchild = NULL;
        q -> rchild = NULL;
        if(q->key2 <= p->key2) p -> lchild = q;
        else p -> rchild = q;
        p = q;
    }
    if(r.type) p->bills +=40*((r.time+59)/60);
    else p->bills += 20*((r.time+59)/60);
}

bool find_user(account *list, record r, accptr &p){//需要申请空间返回false， 否则返回true
    accptr q; // 跟随
    int i;
    i = Hash(r.key1);
    if(list[i].key2 == -1){
        p = &list[i];
        p->key2 = r.key2;
        for(int k = 0 ; k<12; k++) p->number[k] = r.number[k];
        return true;  //不冲突
    }
    p = q = &list[i];
    while(p&&r.key2!=p->key2){
        q =p;
        p = (r.key2<=p->key2) ?(p->lchild) :(p->rchild);
    }
    if(p) return true;//找到了
    else {
        p = q;
        return false;//没有找到
    }
}

void get_record(char*c, record &r){
    int i;
    char k1[6],k2[4],b,t[5];
    for(i=0;i<3;i++) k2[i] = c[i+3];
    for(i = 0; i<5;i++) k1[i] = c[i+6];
    b= c[12];
    for(i = 0;i<4;i++) t[i] = c[i+13];
    k1[5] = k2[3] = t[4] = '\0';
    r.key1 = atoi(k1);
    r.key2 = atoi(k2);
    r.time = atoi(t);
    if(b == 0) r.type = true;
    else r.type = false;
	for(i = 0;i<11;i++)r.number[i] = c[i];
    r.number[11] = '\0';
}
int Hash(int key1){
    return key1%100000;
}
void preorder(accptr p,FILE* fp){
    if(!p) return;
    fprintf(fp,"%s%10d\n", p->number,p->bills);
    preorder(p->lchild,fp);
    preorder(p->rchild,fp);
}
