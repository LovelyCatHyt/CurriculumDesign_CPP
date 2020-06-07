#pragma once
#include <iostream>
#include <string>							//string
using std::cin;
using std::cout;
using std::string;

namespace Hyt 
{
	//常用询问流
	class QueryFlow
	{
	public:
		//只用回答是或否
		static bool YesNoQuery(const string& queryWord, const bool& useCES = true);
		static bool IfContinue(const string& queryWord = "是否继续?&8(方向键控制, 回车确定)");
	};
}

