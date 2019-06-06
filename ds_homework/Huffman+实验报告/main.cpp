#include <iostream>

using namespace std;
#include "app.h"
int main()
{
    app a;                          //the highest class to control the interface
    a.show();
    while(a.cycle());
    return 0;
}
