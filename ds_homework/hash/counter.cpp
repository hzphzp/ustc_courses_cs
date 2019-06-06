#include "counter.h"
#include<fstream>
#include<iostream>
#include<math.h>
#include<iomanip>

using namespace std;
hashcounter::hashcounter(){
    ifstream infile("keywords.txt");
    string s;
    while(!infile.eof()){
        infile>>s;
        T.insertword(s);
    }
    infile.close();
}

void hashcounter::input(char* s, int i){
    char c;
    string str;
    LHNodeptr p;
    ifstream infile(s);
    if(!infile.is_open()){
        cout<<"the file is not open"<<endl;
        return;
    }
    while(!infile.eof()){
        infile.get(c);
        if(isletter(c)) {                                 //a function to complete
                str = str +c;
                continue;
        }
        else if(str!=""){
            if(T.searchword(str,p) == -2) p->data.num++;           //problem
            cout<<str<<"  ";
            str = "";
        }
    }
    cout<<endl;
    if(i == 1) copycount(number1);
    if(i == 2) copycount(number2);
    T.reset();
}
bool hashcounter::isletter(char c){
    if(c>=65&&c<=90) return true;
    if(c>=97&&c<=122) return true;
    return false;
}


void hashcounter::copycount(int* x) {
    int i = 0, k;
    LHNodeptr p;
    for(k = 0;k<T.sizeindex;k++){
        if(T.elem[k]){
            p = T.elem[k];
            while(p){
                x[i] = p->data.num;
                i++;
                p = p->next;
            }
        }
    }
}


void hashcounter::show(){
    cout<<setw(8)<<"keyword"<<"              "<<"the first code"<<"              "<<"the second code"<<endl;
    int i = 0, k= 0;
    LHNodeptr p;
    for(k = 0;k<T.sizeindex;k++){
        if(T.elem[k]){
            p = T.elem[k];
            while(p){
                cout<<setw(8)<<p->data.key<<"                    "<<number1[i]<<"                      "<<number2[i]<<endl;
                i++;
                p = p->next;
            }
        }
    }
}

void hashcounter::compute(){
    int c1 = 0,c2 = 0,c3 = 0;
    for(int i = 0;i<T.countnum;i++){
        c1 += number1[i]*number2[i];
        c2 += number1[i]*number1[i];
        c3 += number2[i]*number2[i];
    }

    cout<<c1/(sqrt(c2)*sqrt(c3));
}






