#include <iostream>
#include "stack_packing_lot.h"
#include "waiting_queue.h"
#include "packing_process.h"
using namespace std;

int main()
{
    int n,m,price;
    cout<<"input the size of the stack and the size of the queue and the price"<<endl;
    cin>>n>>m>>price;
    lot lt(n,m,price);
    lt.incommand(true);
    return 0;
}
