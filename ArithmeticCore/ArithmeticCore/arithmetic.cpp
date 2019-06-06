#include"arithmetic.h"
using namespace std;
string to_string_with_precision(const double a_value, const int n)
{
	ostringstream out;
	out.precision(n);
	out.setf(ios::fixed);
	out << a_value;
	return out.str();
}
// Initialize the fraction array to store the fractions in one expression
void FracInit(fraction* fracs)
{
	int i;
	for (i = 0; i < arraysize; i++)
	{
		fracs[i].numerator = 0;
		fracs[i].denominator = 1;
	}
}

// transform a string to a fraction
void Str2Frac(int idx, int &len, string str, int &num)
{
	num = (int)(str.at(idx + len) - '0');
	for (len++; idx + len < str.size() && str.at(idx + len) >= '0' && str.at(idx + len) <= '9'; len++)
	{
		num *= 10;
		num += (int)(str.at(idx + len) - '0');
	}
}
string Frac2Str(fraction f)
{
	if (f.denominator == 1)
		return to_string(f.numerator);
	return to_string(f.numerator) + "|" + to_string(f.denominator);
}

// get all numbers as fraction from a string, store them in an array "fracs"
void GetFrac(string &str, fraction* fracs)
{
	int number_length;
	int idx = 0;
	char q;//代替换字符

	FracInit(fracs);

	for (int i = 0; i < str.size(); i++)//i为当前位置
	{
		number_length = 0;//已存入分数中的字符个数
		if (str.at(i) >= '0' && str.at(i) <= '9')
		{
			Str2Frac(i, number_length, str, fracs[idx].numerator);
			if (i + number_length < str.size() && str.at(i + number_length) == '|')
			{
				number_length++;
				Str2Frac(i, number_length, str, fracs[idx].denominator);
			}
			q = (char)((int)'0' + idx);
			str.replace(i, number_length, 1, q);
			idx++;
		}
	}
}

// simplify the fraction
fraction Simplify(fraction &frac)
{
	for (int i = 2; i <= frac.denominator; i++)
	{
		if (frac.numerator%i == 0 && frac.denominator%i == 0)
		{
			frac.numerator /= i;
			frac.denominator /= i;
			i = 1;
		}
	}
	return frac;
	//cout << nume << '/' << deno << endl;
}

// '+' operation of two fraction
fraction FracPlus(fraction opd1, fraction opd2)
{
	fraction res;
	res.denominator = opd1.denominator * opd2.denominator;
	res.numerator = opd1.numerator * opd2.denominator + opd2.numerator * opd1.denominator;
	return Simplify(res);
}

// '-' operation of two fraction
fraction FracMinus(fraction opd1, fraction opd2)
{
	fraction res;
	res.denominator = opd1.denominator * opd2.denominator;
	res.numerator = opd1.numerator * opd2.denominator - opd2.numerator * opd1.denominator;
	if (res.numerator < 0)
	{
		throw "ERROR: temperary result less than 0";
	}
	return Simplify(res);
}

// '*' operation of two fraction
fraction FracMul(fraction opd1, fraction opd2)
{
	fraction res;
	res.denominator = opd1.denominator * opd2.denominator;
	res.numerator = opd1.numerator * opd2.numerator;
	return Simplify(res);
}

// '/' operation of two fraction
fraction FracDiv(fraction opd1, fraction opd2)
{
	fraction res;
	if (opd2.numerator == 0)
	{
		throw "ERROR: divisor can not be 0";
	}
	res.denominator = opd1.denominator * opd2.numerator;
	res.numerator = opd1.numerator * opd2.denominator;
	return Simplify(res);
}

// '^' operation of two fraction
fraction FracPow(fraction opd1, fraction opd2)
{
	fraction res;
	double power;

	res.numerator = 1;
	res.denominator = 1;
	power = opd2.numerator / opd2.denominator;

	if (opd1.numerator * opd1.denominator == 0 && opd2.numerator * opd2.denominator <= 0)
	{
		throw "ERROR: base 0 can be with an negtive or zeroth index";
	}
	res.numerator = int(pow(opd1.numerator, power));
	res.denominator = int(pow(opd1.denominator, power));
	return res;
}

// operate one step of caculation in fraction
fraction oprFrac(fraction opd1, char opt, fraction opd2, int lrange, int hrange)
{
	fraction res;
	res.denominator = 1;
	res.numerator = 1;

	if (opd1.denominator == 0 || opd2.denominator == 0)
	{
		throw "ERROR: denominator can not be 0!";
	}
	switch (opt){
	case '+':
		res = FracPlus(opd1, opd2);
		break;
	case '-':
		res = FracMinus(opd1, opd2);
		if (res.numerator < 0)
		{
			throw "ERROR: temperary result less than 0" ;
		}
		break;
	case '*':
		res = FracMul(opd1, opd2);
		break;
	case '/':
		if (opd2.numerator == 0)
		{
			throw "ERROR: divisor can not be 0";
		}
		else
		{
			res = FracDiv(opd1, opd2);
		}
		break;
	case '^':
		if (opd1.numerator == 0 && opd2.numerator == 0)
		{
			throw "ERROR: base 0 can be with an negtive or zeroth index" ;
		}
		else
		{
			if ((double)opd2.numerator / (double)opd2.denominator - int(opd2.numerator / opd2.denominator) != 0)
			{
				throw "ERROR: this pow can not be calculate easily";
			}
			if (opd2.numerator / opd2.denominator > 10 && opd1.numerator / opd1.denominator > 10)
			{
				throw "ERROR: too big number may cause overflow!";
			}
			res = FracPow(opd1, opd2);
		}
		break;
	default:
		throw "ERROR: operator";
		break;
	}
	if (res.numerator < lrange || res.denominator < lrange || res.numerator > hrange ||  res.denominator >hrange)
	{
		throw "ERROR: temporary result surpass the range";
	}
	return res;
}

// calcInte a fraction expression
fraction CalcFrac(string fracExp, fraction nums[], int lrange, int hrange)
{
	fraction operand1;
	fraction operand2;
	fraction result;
	stack<fraction> numStack;
	string temp;
	int i;
	for (i = 0; i < fracExp.size(); i++){
		temp = "";
		if (isdigit(fracExp[i]) || fracExp[i] == '.'){
			while (isdigit(fracExp[i]) || fracExp[i] == '.')
			{
				temp += fracExp[i++];
			}
			numStack.push(nums[stoi(temp)]);
		}
		else{
			operand2 = numStack.top();
			numStack.pop();
			operand1 = numStack.top();
			result = oprFrac(operand1, fracExp[i], operand2, lrange, hrange);
			numStack.pop();
			numStack.push(result);
		}
	}
	result = numStack.top();
	return result;
}

// priority rank is one
bool isone(char opt){
	return (opt == '+' || opt == '-');
}
// priority rank is two
bool istwo(char opt){
	return (opt == '*' || opt == '/');
}
// priority rank is three
bool isthree(char opt){
	return (opt == '^');
}

// judge the operator
bool isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
	{
		return true;
	}
	if (ch == '.' || ch == '|')
	{
		return true;
	}
	if (isdigit(ch))
	{
		return false;
	}
}

//
bool MatchBracket(string exp)
{
	int matchstat = 1;
	stack<char> charStack;
	
	for (int i = 0; i < exp.size(); i++)
	{
		switch(exp[i])
		{
		case'(':
			charStack.push(exp[i]);
			break;
		case')':
			if (charStack.empty())
			{
				matchstat = 0;
			}
			else if (charStack.top() != '(')
			{
				charStack.pop();
				matchstat = 0;
			}
			else if (charStack.top() == '(')
			{
				charStack.pop();
			}
			break;
		default:
			break;
		}
	}
	if (matchstat == 1 && charStack.empty())
	{
		return true;
	}
	throw "ERROR: bracket matching!";
	return false;
}

// judge exp is one specific kind expression
bool FracOrInte(string exp)
{
	string::size_type idx1;
	string::size_type idx2;
	idx1 = exp.find(".");
	idx2 = exp.find("|");
	if (idx1 != string::npos && idx2 != string::npos)
	{
		throw "ERROR: fraction expression can't contain float";
	}
	return true;
}
// exception char
bool ExceptChar(string exp)
{
	for (int i = 0; i < exp.size(); i++)
	{
		char ch = exp.at(i);
		if (!isdigit(ch) && ch != '.' && ch != '|')
		{
			if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '^')
			{
				if (ch != '(' && ch != ')')
				{
					throw "ERROR: character in this expression!";
				}
			}
		}
	}
	return true;
}

// check out the operator connection 
bool ExceptConnection(string exp)
{
	for (int i = 0; i < exp.size(); i++)
	{
		if (isOperator(exp[i]))
		{
			// check out the connection between operators
			if (i == 0)
			{
				throw "ERROR: operator can not be in the start";
			}
			if (i + 1 == exp.size())
			{
				throw "ERROR: operator can not be in the end";
			}
			if (exp[i - 1] == '(')
			{
				throw "ERROR: operation connection!";
			}
			if (exp[i + 1] == ')')
			{
				throw "ERROR: operation connection!";
			}
			if (isOperator(exp[i + 1]))
			{
				throw "ERROR: operation connection!";
			}
			if (exp[i] == '.' || exp[i] == '|')
			{
				if (exp[i + 1] == '(' || exp[i+1] == '|' || exp[i + 1] == '.')
					throw "ERROR: operation connection!";
			}
			// end check
		}
	}
	return true;
}

// transform integral expression to suffix
string exp2suffix(string exp){
	stack<char> s;
	string sur;
	int i;
	char w;
	sur;

	// travel loop
	for (i = 0; i < exp.size(); i++){
		if (isdigit(exp[i]) || exp[i] == '.'){
			while (isdigit(exp[i]) || exp[i] == '.')
			{
				sur += exp[i++];
			}
			i--;
			sur += ' ';
		}
		// if it is + or -
		else if (isone(exp[i]))
		{
			while (s.size() && (isone(s.top()) || istwo(s.top()) || isthree(s.top())))
			{
				sur += s.top();
				s.pop();
			}
			s.push(exp[i]);
		}
		// if it is ( or )
		else if (exp[i] == ')')
		{
			while (s.top() != '(')
			{
				sur += s.top();
				s.pop();
			}
			s.pop();
		}
		// if it is * or /
		else if (istwo(exp[i])){
			while (s.size() && (istwo(s.top()) || isthree(s.top())))
			{
				sur += s.top();
				s.pop();
			}
			s.push(exp[i]);
		}
		// if it is ^
		else if (isthree(exp[i]))
		{
			while (s.size() && isthree(s.top()))
			{
				sur += s.top();
				s.pop();
			}
			s.push(exp[i]);
		}
		// other character('(')
		else
		{
			s.push(exp[i]);
		}
	}
	while (s.size())
	{
		sur += s.top();
		s.pop();
	}
	return sur;
}

// set the weight of one digit
double tentimes(int n){
	double res = 1;
	for (int i = 0; i<n; i++){
		res *= 10;
	}
	return res;
}

// transform a string of digits to a double number
double str2double(string s){
	double res = 0;
	char c;
	int dec = 0;
	int point_number = 0;

	for (int i = 1; i <= s.size(); i++){
		c = s[i - 1];
		if (c == '.') {
			dec = i;
			point_number++;
		}
		else if (!dec) res = res * 10 + c - '0';
		else res += (c - '0') / tentimes(i - dec);
	}
	if (point_number > 1)
	{
		throw "ERROR: redunctant point!";
	}
	return res;
}

// operate one step of caculation in integral
double oprInte(double opd1, char opt, double opd2, int lrange, int hrange)
{
	double res;

	switch (opt){
	case '+':
		res = opd1 + opd2;
		break;
	case '-':
		if (opd1 < opd2)
		{
			throw "ERROR: temperary result less than 0";
		}
		res = opd1 - opd2;
		break;
	case '*':
		res = opd1  * opd2;
		break;
	case '/':
		if (opd2 == 0)
		{
			throw "ERROR: divisor can not be 0";
		}
		else if (opd1 - int(opd1) == 0)
		{
			if (opd1 / opd2 - int(opd1 / opd2) != 0)
				throw "ERROR: integal divide should not be float";
		}
		res = opd1 / opd2;
		break;
	case '^':
		if (opd1 == 0 && opd2 <= 0)
		{
			throw "ERROR: base 0 can be with an negtive or zeroth index";
		}
		else
		{
			if (opd2 - int(opd2) != 0)
			{
				throw "ERROR: this pow can not be calculate easily";
			}
			if (opd2 > 10 && opd1 > 10)
			{
				throw "ERROR: '^' operate may cause overflow!";
			}
			res = pow(opd1, opd2);
		}
		break;
	default:
		throw "fatal ERROR:ERROR: operator";
		system("pause");
		break;
	}
	
	if (res < lrange || res > hrange)
	{
		throw "ERROR: temporary result surpass the range";
	}
	return res;
}

// calcInte a integral expression
double calcInte(string s, int lrange, int hrange){
	double operand1;
	double operand2;
	double result;
	stack<double> num;
	string temp;
	int i;

	for (i = 0; i<s.size(); i++){
		temp = "";
		if (isdigit(s[i]) || s[i] == '.'){
			while (isdigit(s[i]) || s[i] == '.')
			{
				temp += s[i++];
			}//如果最后一位是数字，这样做会出错   
			num.push(str2double(temp));
		}
		else{
			operand2 = num.top();
			num.pop();
			operand1 = num.top();
			result = oprInte(operand1, s[i], operand2, lrange, hrange);
			num.pop();
			num.push(result);
		}
	}
	result = num.top();
	return result;
}


