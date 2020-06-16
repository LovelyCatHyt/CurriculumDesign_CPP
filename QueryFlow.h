#pragma once
//#include <iostream>							//?
#include <string>							//string
#include <vector>							//vector
#include "ColorfulConsole/CloEscString.h"	//ces
#include <functional>
using std::cin;
using std::cout;
using std::string;
using std::vector;
using ColorfulConsole::ces;

namespace Hyt
{
	//常用询问流
	class QueryFlow
	{
		//虽然使用模板, 但是为了防止塞入其他非默认类型的参数, 就把它设为private了
		template<typename T>
		static T BasicTypeInput(const string& queryWord = "", const string& failWord = "", const bool& useCES = true)
		{
			using ColorfulConsole::ces;

			T temp;
			if (useCES) cout << ces << queryWord;
			else cout << queryWord;
			cin >> temp;
			bool failed = false;
			while (cin.fail() | cin.bad() | cin.eof())
			{
				//清除状态
				cin.clear();
				cin.ignore();
				if (useCES) cout << ces << failWord;
				else cout << failWord;
				if (useCES) cout << ces << queryWord;
				else cout << queryWord;

				cin >> temp;
			}
			return temp;
		}

		template<typename T>
		static T CheckedInput(const string& queryWord, const string& failWord, const string& invalidWord, std::function<bool(T)> checkFunc, const bool& useCES = true)
		{
			bool valid = false;
			T temp;
			while (!valid)
			{
				temp = BasicTypeInput<T>(queryWord, failWord, useCES);
				if (!(valid = checkFunc(temp)))
				{
					if (useCES) cout << ces << invalidWord;
					else cout << invalidWord;
				}
			}
			return temp;
		}
	public:
		//只用回答是或否
		static bool YesNoQuery(const string& queryWord, const bool& useCES = true);
		//是否继续?
		static bool IfContinue(const string& queryWord = "是否继续?&8(方向键控制, 回车确定)");
		//显示一个菜单, 返回值为选项索引
		static int ShowMenu(const string& content, const bool& useCES = true);
		//显示一个菜单, 返回值为选项索引, contents一个元素显示一行
		static int ShowMenu(const vector<string> contents, const bool& useCES = true);
		static int CheckedInput_int(const string& queryWord, const string& failWord, const string& invalidWord, std::function<bool(int)> checkFunc, const bool& useCES = true);
		static int SaveInput_int(const string& queryWord = "", const string& failWord = "", const bool& useCES = true);
		static float SaveInput_float(const string& queryWord = "", const string& failWord = "", const bool& useCES = true);
		static double SaveInput_double(const string& queryWord = "", const string& failWord = "", const bool& useCES = true);
	};
}

