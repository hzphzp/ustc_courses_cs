#include"core.h"
#include<vector>
using namespace std;
string core::AddBracket(string OriginalProblem)
{
	int IndexofRightB, IndexofLeftB;//index of left and right brackets
	vector<int> OperatorIndex;
	int LeftOperator; //to mark the Operator located in the left of the bracket's rank
	int RightOperator;
	string OriginalSuffix = exp2suffix(OriginalProblem);
	string suffix;//to store the suffix of the problem and to compare with the OriginalSuffix
	string problem = OriginalProblem;
	int choice; // to decide whetcher to add more brackects
	//to get the number of the Operator, thus the number of the operand substract 1
	for (int i = 0; i < OriginalProblem.size(); i++)
	{
		if ((OriginalProblem[i] >= '0' && OriginalProblem[i] <= '9')||(OriginalProblem[i] == '(' || OriginalProblem[i] == ')' || OriginalProblem[i] == '.'|| OriginalProblem[i] == '|'))
			continue;
		OperatorIndex.push_back(i);
	}
	if (OperatorIndex.size() <= 2)
		return OriginalProblem;
	//to generate to index of Operator meet the requriment
	do
	{
		LeftOperator = random(-1, OperatorIndex.size());
		RightOperator = random(-1, OperatorIndex.size());
	} while (!((LeftOperator + 1 < RightOperator)));
	if (LeftOperator == -1)
	{
		problem.insert(0, 1, '(');
		IndexofLeftB = 0;
	}
	else
	{
		problem.insert(OperatorIndex[LeftOperator] + 1, 1, '(');
		IndexofLeftB = OperatorIndex[LeftOperator] + 1;
	}
	if (RightOperator == OperatorIndex.size())
	{
		problem += ')';
		IndexofRightB = problem.size() - 1;
	}
	else
	{
		problem.insert(OperatorIndex[RightOperator] + 1, 1, ')');
		IndexofRightB = OperatorIndex[RightOperator] + 1;
	}
	suffix = exp2suffix(problem);
	if (suffix == OriginalSuffix)
		return OriginalProblem;
	else
	{
		choice = random(0, 4);
		switch (choice)//TODO:we can define the difficult rank though change the case 
		{
		case 0: return problem;
		case 1:
		{
			string str1 = problem.substr(0, IndexofLeftB + 1);
			string str2 = problem.substr(IndexofLeftB + 1, IndexofRightB - IndexofLeftB - 1);
			string str3 = problem.substr(IndexofRightB, problem.size() - IndexofRightB);
			return str1 + AddBracket(str2) + str3;
		}
		case 2:
		{
			string str1 = problem.substr(0, IndexofLeftB + 1);
			string str2 = problem.substr(IndexofLeftB + 1, IndexofRightB - IndexofLeftB - 1);
			string str3 = problem.substr(IndexofRightB, problem.size() - IndexofRightB);
			return str1 + AddBracket(str2) + str3;
		}
		case 3:
		{
			string str1 = problem.substr(0, IndexofLeftB + 1);
			string str2 = problem.substr(IndexofLeftB + 1, IndexofRightB - IndexofLeftB - 1);
			string str3 = problem.substr(IndexofRightB, problem.size() - IndexofRightB);
			if (str1 == "(" && str3 == ")")
				return str1 + str2 + str3;
			if (str1 == "(" && str3 != ")")
				return str1 + str2 + ")"+ str3[1]+ AddBracket(str3.substr(2, str3.size() - 2));
			if (str1 != "(" && str3 == ")")
				return AddBracket(str1.substr(0, str1.size() - 2)) + str1[str1.size() - 2] + "(" + str2 + str3;
			if (str1 != "(" && str3 != ")")
				return AddBracket(str1.substr(0, str1.size() - 2)) + str1[str1.size() - 2] + "(" + str2 + ")" + str3[1] + AddBracket(str3.substr(2, str3.size() - 2));
		}
		case 4:
		{
			string str1 = problem.substr(0, IndexofLeftB + 1);
			string str2 = problem.substr(IndexofLeftB + 1, IndexofRightB - IndexofLeftB - 1);
			string str3 = problem.substr(IndexofRightB, problem.size() - IndexofRightB);
			if (str1 == "(" && str3 == ")")
				return str1 + str2 + str3;
			if (str1 == "(" && str3 != ")")
				return str1 + str2 + ")" + str3[1] + AddBracket(str3.substr(2, str3.size() - 2));
			if (str1 != "(" && str3 == ")")
				return AddBracket(str1.substr(0, str1.size() - 2)) + str1[str1.size() - 2] + "(" + str2 + str3;
			if (str1 != "(" && str3 != ")")
				return AddBracket(str1.substr(0, str1.size() - 2)) + str1[str1.size() - 2] + "(" + str2 + ")" + str3[1] + AddBracket(str3.substr(2, str3.size() - 2));
		}
		}
	}
}

// transform integral expression to suffix
