#include <iostream>
#include "stack_packing_lot.h"
using namespace std;

void Stack::init(int msize = STACK_INIT_SIZE){
    Elem = new SNode[msize];
    top = -1;
    stacksize = msize;
}
bool Stack::push(int num, int start_time, int pay_time){
    if(getlength() == stacksize) return false;
    top++;
    Elem[top].number = num;
    Elem[top].start_time = start_time;
    Elem[top].pay_time = pay_time;
    return true;
}
void Stack::Delete(int p, int &start_time, int &pay_time){
    int i;
    start_time = Elem[p].start_time;
    pay_time = Elem[p].pay_time;
    for(i = p; i<top; i++) Elem[i] = Elem[i+1];
    top--;
}
bool Stack::lookingfor(int num, int &p){
    int i = 0;
    while(i<=top&&Elem[i].number !=num) i++;
    if(i<=top){
            p = i;return true;
    }
    return false;
}
int Stack::getlength(){
    return top+1;
}
void Stack::show(){
    int p=0;
    while(p<=top){
            cout<<Elem[p].number<<"==="<<Elem[p].start_time<<"==="<<Elem[p].pay_time<<"========="<<p<<endl;
            p++;
    }
}






