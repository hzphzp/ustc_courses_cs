//this is the test entrance of the dll project
#include <iostream>
#include "core.h"
using namespace std;
int main()
{
	core firstcore;
	firstcore.Setting("calculate_kind", 2);
	firstcore.Setting("ProblemNum", 10);
	firstcore.Setting("OperandNum", 6);
	firstcore.Setting("lrange", 0);
	firstcore.Setting("hrange", 25);
	firstcore.Setting("precision", 2);
	firstcore.Setting('+', true);
	firstcore.Setting('-', true);
	firstcore.Setting('*', true);
	firstcore.Setting('/', true);
	firstcore.Setting('^', true);
	string* problem;
	string* result;
	firstcore.Generate(problem, result);
	for (int i = 0; i < 10; i++)
	{
		cout << problem[i] << endl;
		cout << result[i] << endl;
	}
	return 0;
}

