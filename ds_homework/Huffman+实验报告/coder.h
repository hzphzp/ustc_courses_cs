#ifndef CODER_H_INCLUDED
#define CODER_H_INCLUDED
#include<fstream>
#include "struct.h"
class Coder
{
public:
    void initialization();
    void print_codefile();
    void print_haffmantree(int, int, bool);
    void encoder();
    void decoder();
private:
    int m;
    int n;
    ifstream infile;
    ofstream outfile;
    Hufftree HT;                                                //a struct to complete
    char *ch;
    char **HC;
    void HuffmanCoding();
    void create_tree(int *w);
    int letter_to_number(char c);
    void coding(int root, SqStack &S);               //a struct to complete
};
void select(Hufftree HT, int i, int &s1, int &s2);



#endif // CODER_H_INCLUDED
