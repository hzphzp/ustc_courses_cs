/*
this files is the head file of a function named getallfiles
to get all the files and subfiles under the homepath
*/
#ifndef _GETALLFILES_H
#define _GETALLFILES_H
#include<string>
#include<vector>
using namespace std;
#define LETTERH 64
#define LETTERL 96
#define NUMBER 48
#define DELIMITER 0
extern long SumofChar;
extern long SumofWord;
extern long Sumofline;
extern long SumofPhrase;
extern int formarindex;
void getallfiles(string homepath, vector<string> &files);
void getcontent(string path, char* &buffer, long &size);
void statistics(char* buffer, long size);
void outputresult();
void Low(char* sample);
#endif
