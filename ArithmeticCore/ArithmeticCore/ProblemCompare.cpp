#include"core.h"
using namespace std;
bool core::ProblemCompare(string formar, string latter)
{
	return (Calc(formar) == Calc(latter));
}