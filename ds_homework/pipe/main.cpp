#include <iostream>
#include "pipe.h"
using namespace std;

int main()
{
    int n;
    string s;
    cout<<"input the start place"<<endl;
    cin >> n;
    cout<<"input the name of method"<<endl;
    cin >> s;
    pipe p(s);
    p.getdata();
    p.show();
    p.getmst(n);
    return 0;
}

