#include <iostream>
#include"counter.h"
using namespace std;

int main()
{
    char c;
    char s[15];
    hashcounter h;
    cout<<"input the name of the first codefile"<<endl;
    cin>>s;
    h.input(s, 1);
    cout<<"input the name of the second codefile"<<endl;
    cin>>s;
    h.input(s, 2);
    cout<<"if you want to see the number of each key word?(y/n)"<<endl;
    cin>>c;
    if(c == 'y') h.show();
    cout<<"the similarity degree of the two codes is "<<endl;
    h.compute();
    return 0;

}
