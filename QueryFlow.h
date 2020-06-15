#pragma once
#include <iostream>
#include <string>							//string
#include "ColorfulConsole/CloEscString.h"
using std::cin;
using std::cout;
using std::string;


namespace Hyt 
{
	//常用询问流
	class QueryFlow
	{
		//虽然使用模板, 但是为了防止塞入其他非默认类型的参数, 就把它设为private了
		template<typename T>
		static T BasicTypeInput(const std::string& queryWord = "", const std::string& failWord = "", const bool& useCES = true)
		{
			using ColorfulConsole::ces;

			T temp;
			if (useCES) cout << ces << queryWord;
			else cout << queryWord;
			cin >> temp;
			while (cin.fail() | cin.bad() | cin.eof())
			{
				if (useCES) cout << ces << failWord;
				else cout << failWord;
				cin.clear();
				cin.ignore();
				cin >> temp;
			}
			return temp;
		}
	public:
		//只用回答是或否
		static bool YesNoQuery(const string& queryWord, const bool& useCES = true);
		//是否继续?
		static bool IfContinue(const string& queryWord = "是否继续?&8(方向键控制, 回车确定)");
		static int SaveInput_int(const std::string& queryWord = "", const std::string& failWord = "", const bool& useCES = true);
		static float SaveInput_float(const std::string& queryWord = "", const std::string& failWord = "", const bool& useCES = true);
		static double SaveInput_double(const std::string& queryWord = "", const std::string& failWord = "", const bool& useCES = true);
	};
}

