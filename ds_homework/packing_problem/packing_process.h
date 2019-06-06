#ifndef PACKING_PROCESS_H_INCLUDED
#define PACKING_PROCESS_H_INCLUDED
#include "stack_packing_lot.h"
#include "waiting_queue.h"
class lot
{
public:
    lot(int n, int m,int p);
    void incommand(bool ifshow);
    void show();
private:
    Stack s;
    Queue q;
    int price;
    void add(int n,int t);
    void leave(int n, int t);
};


#endif // PACKING_PROCESS_H_INCLUDED
