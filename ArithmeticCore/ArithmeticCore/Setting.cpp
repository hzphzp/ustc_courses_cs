//this is the implement of the method setting of class core
#include "core.h"
#include<fstream>
#include<iostream>
using namespace std;
bool core::Setting(string option, int key)
{//TODO ::to call the wrong parameter
	if (option == "calculate_kind")
	{
		config.calculate_kind = key;
	}
	if (option == "precision")
	{
		config.precision = key;
		return true;
	}
	if (option == "ProblemNum")
	{
		config.ProblemNum = key;
		return true;
	}
	if (option == "OperandNum")
	{
		config.OperandNum = key;
		return true;
	}
	if (option == "lrange")
	{
		config.lrange = key;
		return true;
	}
	if (option == "hrange")
	{
		config.hrange = key;
		return true;
	}
	return false;
}
bool core::Setting(char c, bool key)
{//TODO ::to call the wrong parameter
	if (c == '+')
	{
		if(key)
			config.KindofOperator.append("+");
		return true;
	}
	if (c == '-')
	{
		if(key)
			config.KindofOperator.append("-");
		return true;
	}
	if (c == '*')
	{
		if(key)	
			config.KindofOperator.append("*");
		return true;
	}
	if (c == '/')
	{
		if(key)
			config.KindofOperator.append("/");
		return true;
	}
	if (c == '^')
	{
		if(key)
			config.KindofOperator.append("^");
		return true;
	}

	return false;
}