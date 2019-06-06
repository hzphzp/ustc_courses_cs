#ifndef COUNTER_H_INCLUDED
#define COUNTER_H_INCLUDED
#include "hashtable.h"
class hashcounter
{
public:
    hashcounter();
    void input(char* s, int i);
    void show();
    void compute();
private:
    void copycount(int* x);
    bool isletter(char c);
    hashtable T;
    int number1[32];
    int number2[32];
};

#endif // COUNTER_H_INCLUDED
