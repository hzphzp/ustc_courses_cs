#include "pipe.h"
pipe::pipe(string s){
    if(s == "Prim") method = s;
    else if(s == "Kruskal") method = s;
    else cout<< "wrong method name , please check it out"<<endl;
}
void pipe::getdata(){
    G. creategraph();
}
void pipe::getmst(int v0){
    if(method == "Prim") G.Prim(v0);
    if(method == "Kruskal") G.Kruskal(v0);
}
void pipe::show(){
    G.print();
}
