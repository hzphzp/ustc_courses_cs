#include <iostream>
#include "grep.h"
using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 3){
            cout<<"unavailable argument amount for grep"<<endl;
            return -1;
    }
    grep g(400);
    g.lockfile(argv[1]);
    g.lookingfor(argv[2]);
    return 0;
}
