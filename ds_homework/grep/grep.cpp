#include <iostream>
#include <fstream>
using namespace std;
#include "grep.h"
#include<string.h>

grep::grep(int msize = STRING_INIT_SIZE){
    line = new char[msize];
}
void grep::lockfile(char *f){
    infile.open( f, ios::in);
    if(!infile) cout<<"open wrong"<<endl;
}
void grep::lookingfor(char *s){
    bool flag = false;
    linenumber = 1;
    next = new int[strlen(s)+1];
    get_next(s,next);
    while(infile.getline(line,400)){
            if(index(line,s)!=-1){
                    cout<<s<<" is in line "<<linenumber<<endl;
                    cout<<line<<endl;
                    flag = true;
            }
            linenumber++;
    }
    if(!flag) cout<<"can not find the word"<<endl;
}
void grep::closefile(){
    infile.close();
}

