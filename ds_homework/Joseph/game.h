#include "cyclelist.h"
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
class game
{
public:
    void gamestart();
    void killprocess();
private:
    CycleList L;
    LinkList p;
    int n;
    int killer(int k);
};
#endif // GAME_H_INCLUDED
