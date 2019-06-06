#ifndef PIPE_H_INCLUDED
#define PIPE_H_INCLUDED
#include "ALGraph.h"
class pipe
{
public:
    pipe(string s);
    void show();
    void getdata();
    void getmst(int v0);
    ifstream infile;
private:
    ALGraph G;
    string method;
};




#endif // PIPE_H_INCLUDED
