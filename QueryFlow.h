#pragma once
//#include <iostream>							//?
#include <string>							//string
#include <vector>							//vector
#include "ColorfulConsole/CloEscString.h"	//ces
using std::cin;
using std::cout;
using std::string;
using std::vector;

namespace Hyt 
{
	//����ѯ����
	class QueryFlow
	{
		//��Ȼʹ��ģ��, ����Ϊ�˷�ֹ����������Ĭ�����͵Ĳ���, �Ͱ�����Ϊprivate��
		template<typename T>
		static T BasicTypeInput(const string& queryWord = "", const string& failWord = "", const bool& useCES = true)
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
		//ֻ�ûش��ǻ��
		static bool YesNoQuery(const string& queryWord, const bool& useCES = true);
		//�Ƿ����?
		static bool IfContinue(const string& queryWord = "�Ƿ����?&8(���������, �س�ȷ��)");
		//��ʾһ���˵�, ����ֵΪѡ������
		static int ShowMenu(const string& content);
		//��ʾһ���˵�, ����ֵΪѡ������, contentsһ��Ԫ����ʾһ��
		static int ShowMenu(const vector<string> contents);
		static int SaveInput_int(const string& queryWord = "", const string& failWord = "", const bool& useCES = true);
		static float SaveInput_float(const string& queryWord = "", const string& failWord = "", const bool& useCES = true);
		static double SaveInput_double(const string& queryWord = "", const string& failWord = "", const bool& useCES = true);
	};
}

