#include <iostream>
using namespace std;
#ifndef SQSTACK_H_INCLUDED
#define SQSTACK_H_INCLUDED
#define  STACK_INIT_SIZE  10
#define INCREMENT 5
typedef struct{
    int weight;
    int parent;
    int lchild;
    int rchild;
}HTNode, *Hufftree;
typedef HTNode *Huffmantree;
typedef char ElemType;
class SqStack{
public:
    SqStack( int msize = STACK_INIT_SIZE){
        Elem = new ElemType[msize];
        top =-1;
        stacksize = msize;
    }
    void DestoryStack(){
        delete Elem;
        top = -1;
        stacksize = 0;
    }
    void ClearStack(){
        top = -1;
    }
    bool StackEmpty(){
        return (top == -1);
    }
    int StackLength(){
        return top+1;
    }
    bool GetTop(ElemType &e){
        if(top == -1) return false;
        e = Elem[top];
        return true;
    }
    void push(ElemType e){
        if(top == stacksize - 1) Increment();
        top++;
        Elem[top] = e;
    }
    bool pop(ElemType &e){
        if(top == -1) return false;
        e = Elem[top];
        top--;
        return true;
    }
    void StackTranvers(){
        ElemType  e;
        while(pop(e)) cout<<e;
        cout<<endl;
    }                                                         //I am not sure 'couse in this way, the Stack will become empty and loss all of its data;
    void Increment(){
        int i=0,j=0;
        ElemType *t;
        t = new ElemType[stacksize+INCREMENT];
        for(; i<=top;i++,j++) t[j]= Elem[i];
        delete Elem;
        Elem =t;
    }
    ElemType *Elem;
private:
    int stacksize;
    int top;
};


#endif // STRUCT_H_INCLUDED
