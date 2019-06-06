#ifndef GREP_H_INCLUDED
#define GREP_H_INCLUDED
#include <fstream>
#define STRING_INIT_SIZE 400
using namespace std;
class grep
{
public:
    grep(int msize);
    void lockfile(char *f);
    void lookingfor(char *s);
    void closefile();
private:
    char *line;
    int *next;
    int linenumber;
    ifstream infile;
    int index(char *line,char *s);
    void get_next(char *s, int *next);
};
#endif // GREP_H_INCLUDED
