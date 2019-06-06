#include "core.h"

using namespace std;
int tofinddiv(int todiv)
{
	int i = todiv;
	if (i == 0)
		return 1;
	for (i = todiv - 1; i > 0; i--)
	{
		if (todiv%i == 0)
			return i;
	}
}
string to_unicode(string exp)
{
	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == '*')
			exp[i] = 'x';
		else if (exp[i] == '|')
			exp[i] = '/';
		else if (exp[i] == '/')
		{
			exp.erase(i, 1);
			exp.insert(i, "¡Â");
		}
	}
	return exp;
}

void core::Generate(string* &Problem, string* &result)
{
	int test;
	vector<int> DivoperatorIndex;
	vector<int> PowoperatorIndex;
	int m;// for loop
	int overflow = 0;
	int calculate_kind = config.calculate_kind;
	if (calculate_kind != 1)
	{
		config.precision = 0;
	}
	int precision = config.precision;
	const int ProblemNum = config.ProblemNum;//the number of the problems
	const int OperandNum = config.OperandNum;//the number of the operands
	string KindofOperator = config.KindofOperator;//all of the kind of the operators
	if (KindofOperator.find("+") != string::npos)
		KindofOperator.append(30, '+');
	if (KindofOperator.find("-") != string::npos)
		KindofOperator.append(30, '-');
	if (KindofOperator.find("*") != string::npos)
		KindofOperator.append(10, '*');
	if (KindofOperator.find("/") != string::npos)
		KindofOperator.append(20, '/');
	if (KindofOperator.find("^") != string::npos)
		KindofOperator.append(8, '^');
	const int lrange = config.lrange; const int hrange = config.hrange;// the range of the operator and the result
	int* IntOperand;
	double *FloatOperand;//to store the operands, and to get their index
	IntOperand = new int[OperandNum];
	FloatOperand = new double[OperandNum];
	fraction *FractionOperand;
	FractionOperand = new fraction[OperandNum];
	char *Operator;// to store the operators, and to get their index
	Operator = new char[OperandNum];

	Problem = new string[ProblemNum];
	result = new string[ProblemNum];
	string OriginalProblem = "";
	int j;
	for (j = 0; j < ProblemNum && overflow < 10000*ProblemNum ; j++, overflow++)
	{
		PowoperatorIndex.clear();
		DivoperatorIndex.clear();
		
		OriginalProblem = "";
		for (int i = 0; i < OperandNum - 1; i++)
		{
			Operator[i] = KindofOperator[random(0, KindofOperator.size() - 1)];
			if (Operator[i] == '^')
				PowoperatorIndex.push_back(i);
			if (Operator[i] == '/')
				DivoperatorIndex.push_back(i);
		}
		if (calculate_kind == 0)
		{
			for (int i = 0; i < OperandNum; i++)
			{
				IntOperand[i] = random(lrange, hrange);
			}
			for (int i = 0; i < PowoperatorIndex.size(); i++)
			{
				IntOperand[PowoperatorIndex[i] + 1] = random(0, 3);
			}
			for (int i = DivoperatorIndex.size()-1; i >= 0 ; i--)
			{
				IntOperand[DivoperatorIndex[i] + 1] = tofinddiv(IntOperand[DivoperatorIndex[i]]);
			}

			for (int i = 0; i < OperandNum - 1; i++)
			{
				OriginalProblem += to_string(IntOperand[i]);
				OriginalProblem += Operator[i];
			}

			OriginalProblem += to_string(IntOperand[OperandNum - 1]);

			
		}
		if (calculate_kind == 1)
		{
			for (int i = 0; i < OperandNum; i++)
			{
				FloatOperand[i] = random((float)lrange, (float)hrange);
			}
			for (int i = 0; i < PowoperatorIndex.size(); i++)
			{
				FloatOperand[PowoperatorIndex[i] + 1] = random(0, 3);
			}
			
			for (int i = 0; i < OperandNum - 1; i++)
			{
				OriginalProblem += to_string_with_precision(FloatOperand[i], precision);
				OriginalProblem += Operator[i];
			}

			OriginalProblem += to_string_with_precision(FloatOperand[OperandNum - 1], precision);
		}
		if (calculate_kind == 2)
		{
			for (int i = 0; i < OperandNum; i++)
			{
				FractionOperand[i].denominator = random(lrange, hrange);
				FractionOperand[i].numerator = random(lrange, hrange);
				FractionOperand[i] = Simplify(FractionOperand[i]);
			}
			for (int i = 0; i < PowoperatorIndex.size(); i++)
			{
				FractionOperand[PowoperatorIndex[i] + 1].numerator = random(0, 3);
				FractionOperand[PowoperatorIndex[i] + 1].denominator = 1;
				FractionOperand[PowoperatorIndex[i] + 1] = Simplify(FractionOperand[PowoperatorIndex[i] + 1]);
			}
			for (int i = 0; i < OperandNum - 1; i++)
			{
				OriginalProblem += Frac2Str(FractionOperand[i]);
				OriginalProblem += Operator[i];
			}
			OriginalProblem += Frac2Str(FractionOperand[OperandNum - 1]);
		}
		Problem[j] = AddBracket(OriginalProblem);
		cout << Problem[j] << endl;
		if (Calc(Problem[j]) == "ERROR: expression!")
		{
			j--;
			continue;
		}
		//cout << Problem[j] << endl;
		for (m = 0; m < j; m++)
		{
			if (ProblemCompare(Problem[m], Problem[j]))//TODO
			{
				break;
			}
		}
		if (m != j)//
		{
			j--;
			continue;
		}//TODO::
	}
	if (overflow == 10000 * ProblemNum)
	{
		for (int i = j; i < ProblemNum; i++)
			Problem[i] = "";
	}

	for (int i = 0; i < ProblemNum; i++)
	{
		result[i] = Calc(Problem[i]);
		//Problem[i] = to_unicode(Problem[i]);
		//result[i] = to_unicode(result[i]);
	}
}