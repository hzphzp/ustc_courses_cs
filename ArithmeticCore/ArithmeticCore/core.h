//to link the lib of jsoncpp which can control the data through the json file
#ifndef _CORE_H
#define _CORE_H

//#include<json/json.h>
#include "arithmetic.h"
//#pragma comment(lib, "json_vc71_libmtd.lib")
#include<string>

using namespace std;
typedef struct
{
	int ProblemNum;
	int precision;
	int OperandNum;
	int lrange;
	int hrange;
	int calculate_kind;
	string KindofOperator;
}Config;
class __declspec(dllexport) core
{
public:
	core();
	string Calc(string exp);

	// generate the expressions randomly with settings
	void Generate(string* &problem, string* &result);

	// recieve the initializations from json

	bool Setting(string option, int key);
	bool Setting(char option, bool key);

// subfunction for generate function
private:
	double random(double low, double high);
	string AddBracket(string OriginalProblem);
	bool ProblemCompare(string formar, string latter);
	int random(int low, int high);

	//frature mode TODO
	//char ConfigPath[20] = "config.json";
	//Json::Value config;
	Config config;
};

#endif // !_CORE_H
