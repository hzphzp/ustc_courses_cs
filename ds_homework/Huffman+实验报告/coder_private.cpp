#include<iostream>
#include "coder.h"
#include<string.h>
using namespace std;
void Coder::HuffmanCoding(){
    //to encode the leaves in the huffmantree and put the result in char *HC
    SqStack S;                                                    //TODO
    coding(2*n-1,S);
    HC[0] = "\0";
}
void Coder::coding(int root,SqStack &S){
    //a function to complete HuffmanCoding()
    char c;
    if(root!= 0){
            if(HT[root].lchild == 0){
                    S.push('\0');                                //TODO
                    HC[root] = new char[S.StackLength()];                 //TODO
                    strcpy(HC[root], S.Elem);
                    S.pop(c);
            }
            S.push('0');
            coding(HT[root].lchild,S);
            S.pop(c);
            S.push('1');
            coding(HT[root].rchild,S);
            S.pop(c);
    }
}
void Coder::create_tree(int *w){
    int i,s1,s2;
    HT = new HTNode[m+1];
    for(i = 1; i<=m;i++){
            HT[i].weight = i<=n?w[i]:0;
            HT[i].lchild = HT[i].rchild = HT[i].parent = 0;                       //I am not sure if it is correct
    }
    for(i = n+1; i<=m;i++){
            select(HT,i,s1,s2);           //to find tow nodes which have the smallest weight from 1 to i-1, and its parent should be 0
            HT[i].lchild = s1;
            HT[i].rchild = s2;
            HT[i].weight = HT[s1].weight +HT[s2].weight;
            HT[s1].parent = HT[s2].parent = i;
    }
}
int Coder::letter_to_number(char c){
    int i=0;
    while(i<n&&ch[i]!=c) i++;
    return i;
}

