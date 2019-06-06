#ifndef _ARITHMETIC_H
#define _ARITHMETIC_H
#include <iostream>  
#include <string>  
#include <stack>  
#include <fstream> 
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;
extern int i;
#define arraysize 150

typedef struct
{
	int numerator;
	int denominator;
}fraction;

#include"arithmetic.h"
using namespace std;

string to_string_with_precision(double a_value, const int n = 3);
// Initialize the fraction array to store the fractions in one expression
void FracInit(fraction* fracs);

// transform a string to a fraction
void Str2Frac(int idx, int &len, string str, int &num);
string Frac2Str(fraction f);
// get all numbers as fraction from a string, store them in an array "fracs"
void GetFrac(string &str, fraction* fracs);

// simplify the fraction
fraction Simplify(fraction &frac);

// '+' operation of two fraction
fraction FracPlus(fraction opd1, fraction opd2);

// '-' operation of two fraction
fraction FracMinus(fraction opd1, fraction opd2);

// '*' operation of two fraction
fraction FracMul(fraction opd1, fraction opd2);

// '/' operation of two fraction
fraction FracDiv(fraction opd1, fraction opd2);

// '^' operation of two fraction
fraction FracPow(fraction opd1, fraction opd2);
// operate one step of caculation in fraction
fraction oprFrac(fraction opd1, char opt, fraction opd2, int lrange, int hrange);
// calcInte a fraction expression
fraction CalcFrac(string fracExp, fraction nums[], int lrange, int hrange);
// priority rank is one
bool isone(char opt);
// priority rank is two
bool istwo(char opt);
// priority rank is three
bool isthree(char opt);

// judge the operator
bool isOperator(char ch);

//
bool MatchBracket(string exp);

// judge exp is one specific kind expression
bool FracOrInte(string exp);
// exception char
bool ExceptChar(string exp);

// check out the operator connection 
bool ExceptConnection(string exp);

// transform integral expression to suffix
string exp2suffix(string exp);

// set the weight of one digit
double tentimes(int n);
// transform a string of digits to a double number
double str2double(string s);
// operate one step of caculation in integral
double oprInte(double opd1, char opt, double opd2, int lrange, int hrange);

// calcInte a integral expression
double calcInte(string s, int lrange, int hrange);
#endif
