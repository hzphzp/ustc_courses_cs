#include "core.h"
using namespace std;
// calculate	
string core::Calc(string exp)
{
	string sur;
	string result;
	fraction fracs[arraysize];
	string::size_type idx;

	if (exp == "")
		return "";
	result = "ERROR: expression!";
	idx = exp.find("|");

	// check out the ERROR: character in this expression
	try
	{
		// throw exception
		ExceptChar(exp);
		FracOrInte(exp);
		MatchBracket(exp);
		ExceptConnection(exp);
		// no matching error or ERROR: character
		if (idx == string::npos)
		{
			try {
				sur = exp2suffix(exp);
				result = to_string_with_precision(calcInte(sur, 0, 99999), config.precision);
			}
			catch (const char* msg)
			{
				return result;
			}
		}
		else
		{
			try
			{
				GetFrac(exp, fracs);
				sur = exp2suffix(exp);
				result = Frac2Str(CalcFrac(sur, fracs, 0, 99999));
			}
			catch (const char* msg)
			{
				return result;
			}
		}
	}
	catch (const char* msg)
	{
		return result;
	}
	return result;
}