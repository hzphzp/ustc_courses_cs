#include<iostream>
#include "grep.h"
#include<string.h>
using namespace std;
int grep::index(char *line, char *s){
    int i=0,j=0;
    while(i<(int)strlen(line)&&j<(int)strlen(s)){
            if(j == -1||line[i] == s[j]){
                    i++;
                    j++;
            }
            else j = next[j];
    }
    if(j ==(int)strlen(s))return (i-j);
    return -1;
}
void grep::get_next(char *s, int *next){
    int j =0, k = -1;
    next[0] = -1;
    while(j<=(int)strlen(s)-1)
        if(k ==-1||s[j] == s[k]){
                j++;k++;
                if(s[j] != s[k]) next[j] = k;
                else next[j] = next[k];
        }
        else k = next[k];
}
