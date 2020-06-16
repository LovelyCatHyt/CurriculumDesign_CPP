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
			bool failed = false;
			while (cin.fail() | cin.bad() | cin.eof())
			{
				//���״̬
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
		//ֻ�ûش��ǻ��
		static bool YesNoQuery(const string& queryWord, const bool& useCES = true);
		//�Ƿ����?
		static bool IfContinue(const string& queryWord = "�Ƿ����?&8(���������, �س�ȷ��)");
		//��ʾһ���˵�, ����ֵΪѡ������
		static int ShowMenu(const string& content, const bool& useCES = true);
		//��ʾһ���˵�, ����ֵΪѡ������, contentsһ��Ԫ����ʾһ��
		static int ShowMenu(const vector<string> contents, const bool& useCES = true);
		static int CheckedInput_int(const string& queryWord, const string& failWord, const string& invalidWord, std::function<bool(int)> checkFunc, const bool& useCES = true);
		static int SaveInput_int(const string& queryWord = "", const string& failWord = "", const bool& useCES = true);
		static float SaveInput_float(const string& queryWord = "", const string& failWord = "", const bool& useCES = true);
		static double SaveInput_double(const string& queryWord = "", const string& failWord = "", const bool& useCES = true);
	};
}

