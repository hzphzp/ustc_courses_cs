#ifndef STACK_PACKING_LOT_H_INCLUDED
#define STACK_PACKING_LOT_H_INCLUDED
#include "LNode.h"
#define STACK_INIT_SIZE 10
class Stack                                                        //I am not preparing to write the method of destroy
{
public:
    void init(int n);
    bool push(int num, int start_time, int pay_time);                                       //already update the in_in_lot and the time
    int getlength();
    bool lookingfor(int num, int &p);
    void Delete(int p, int &start_time, int &pay_time);
    void show();
private:
    SNode *Elem;
    int top;
    int stacksize;
};





#endif // STACK_PACKING_LOT_H_INCLUDED
