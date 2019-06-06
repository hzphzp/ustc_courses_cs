#include <iostream>
using namespace std;
#include "packing_process.h"
lot::lot(int n, int m,int p){
    s.init(n);
    q.init(m);
    price = p;
}
void lot::incommand(bool ifshow){
    char mode;
    int num;
    int t;
    while(1){
        cout<<"input your command"<<endl;
        cin>>mode>>num>>t;
        if(mode =='E') break;
        else if(mode == 'A') add(num,t);
        else if(mode == 'D') leave(num,t);
        if(ifshow)show();
    }
}
void lot::add(int num, int t){
    if(s.push(num, t, t)) cout<<"the car is in the lot, its locate is "<<s.getlength()<<endl;       //a int function to complete
    else{
            cout<<"the lot is full, please enter the waiting hallway"<<endl;
            if(q.enqueue(num,t)) cout<<"the car is in the waiting hallway, its locate is "<< q.getlength()<<endl;  // a int function to complete
            else cout<<"waiting hallway is full full too, we are so sorry, please looking for another lot"<<endl;
    }
}
void lot::leave(int num,int t){
    int start_time,pay_time;
    LinkList p;
    int p_;
    if(q.lookingfor(num,p)){             //a bool function to complete
            q.Delete(p, start_time);      //function to complete
            cout<<"the car is parking for "<<t-start_time<<" minutes"<<"you do not need to pay for anything"<<endl;// price parameter to complete
            return;
    }
    if(s.lookingfor(num,p_)){     //a bool function to complete
            int n, t_;
            s.Delete(p_, start_time, pay_time);      //function to complete
            cout<<"the car is parking for "<<t-start_time<<"minutes"<<" and should pay "<<price*(t-pay_time)<<" dollars"<<endl;
            if(q.dequeue(n, t_)) s.push(n, t_, t);
            return;
    }
    cout<<"we are sorry, can't find the car, please check you car number"<<endl;
    return;
}
void lot::show(){
    cout<<"===============in the lot============="<<endl;
    s.show();
    cout<<"===============in the waiting hallway========"<<endl;
    q.show();
}





