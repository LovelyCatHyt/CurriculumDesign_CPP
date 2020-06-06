#include "QueryFlow.h"
#include <iostream>							//cout, cin
#include <string>							//string
#include "ColorfulConsole/CloEscString.h"	//ces

using std::cin;
using std::cout;
using ColorfulConsole::ces;

namespace Hyt
{
	bool Hyt::QueryFlow::YesNoQuery(const string& queryWord, const bool& useCES)
	{
		if (useCES) cout << ces << queryWord; else cout << queryWord;
		char temp;
		cin >> temp;
		if (cin.bad() || cin.eof() || cin.fail())
		{
			//清除输入并返回false
			cin.clear();
			return false;
		}
		return temp == 'Y' || temp == 'y';
	}

	bool Hyt::QueryFlow::IfContinue(const string& queryWord)
	{
		return YesNoQuery(queryWord, true);
	}
}