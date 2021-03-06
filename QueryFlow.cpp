#include "QueryFlow.h"
#include <iostream>							//cout, cin
#include <string>							//string
#include <vector>
#include <functional>
#include <sstream>							//istringstream
#include "ColorfulConsole/CloEscString.h"	//ces
#include "ConAPIProx/AttrBrash.h"			//SetRectColor
#include "ConAPIProx/Rect.h"
#include "ConAPIProx/Positioner.h"			
#include "ColorfulConsole/GlobalEnvironment.h"
#include "ColorfulConsole/BackColorProxy.h"
#include "ConAPIProx/GetKey.h"
#include "StringUtiliy.h"


using std::cin;
using std::cout;
using std::istringstream;
using ColorfulConsole::ces;
using std::vector;

namespace Hyt
{
	bool QueryFlow::YesNoQuery(const string& queryWord, const bool& useCES)
	{
		using namespace ConAPIProx;
		using GloEnv = ColorfulConsole::GlobalEnvironment;
		using TAttr = ColorfulConsole::TextAttribute::WarpedTextAttr;
		using ColorfulConsole::Color;

		Position begin = Positioner::GetCursorPosition();
		Position current = begin;
		if (useCES) cout << ces << queryWord; else cout << queryWord;
		//char temp;

		cout << "\n";
		current = Positioner::GetCursorPosition();
		cout << "确认|取消\n";
		Rect leftZone(current, current + Position{ 3,0 });
		Rect rightZone(current + Position{ 5,0 }, current + Position{ 8,0 });
		AttrBrash::SetRectForeColor(leftZone, Color(1));
		AttrBrash::SetRectForeColor(rightZone, Color(8));
		bool yes = true;
		//按键判断
		bool getAction = false;
		while (!getAction)
		{
			switch (ConAPIProx::GetKey())
			{
			case ConAPIProx::LeftArrow:
				AttrBrash::SetRectForeColor(leftZone, Color(1));
				AttrBrash::SetRectForeColor(rightZone, Color(8));
				yes = true; break;
			case ConAPIProx::RightArrow:
				AttrBrash::SetRectForeColor(leftZone, Color(8));
				AttrBrash::SetRectForeColor(rightZone, Color(1));
				yes = false; break;
			case ConAPIProx::Esc:
				yes = false; getAction = true; break;
			case ConAPIProx::Enter:
				getAction = true; break;
			default:
				break;
			}
		}
		return yes;
		//cin >> temp;
		//if (cin.bad() || cin.eof() || cin.fail())
		//{
		//	//清除输入并返回false
		//	cin.clear();
		//	return false;
		//}
		//return temp == 'Y' || temp == 'y';
	}

	bool QueryFlow::IfContinue(const string& queryWord)
	{
		return YesNoQuery(queryWord, true);
	}
	int QueryFlow::ShowMenu(const string& content, const bool& useCES)
	{
		vector<string> temp = StringSplit(content, "\n");
		return ShowMenu(temp, useCES);
	}
	int QueryFlow::ShowMenu(const vector<string> contents, const bool& useCES)
	{
		using namespace ConAPIProx;
		int row = contents.size();
		int index = 0;
		Position beginPos = Positioner::GetCursorPosition();
		Position endPos;
		bool canExit = false;
		char tempKey;
		bool lastIsNumber = false;
		do
		{
			Positioner::SetCursorPosition(beginPos);
			for (int i = 0; i < row; i++)
			{
				if (useCES)
				{
					if (index == i) cout << ces << "&1→<" << ces << contents[i] << ces << "&1>←&r\n";
					else cout << ces << "&r  |" << ces << contents[i] << ces << "&r|  \n";
				}
				else
				{
					if (index == i) cout << ces << "&1→<" << contents[i] << ces << "&1>←&r\n";
					else cout << ces << "&r  |" << contents[i] << ces << "&r|  \n";
				}

				endPos = Positioner::GetCursorPosition();
			}
			tempKey = GetKey();
			switch (tempKey)
			{
			case KeyCodes::DownArrow:
			case KeyCodes::RightArrow:
				//往下
				if (index == row - 1) index = 0;
				else index++;
				break;
			case KeyCodes::UpArrow:
			case KeyCodes::LeftArrow:
				//往上
				if (index == 0) index = row - 1;
				else index--;
				break;
			case KeyCodes::Home:
				//到开头
				index = 0;
				break;
			case KeyCodes::End:
				//到结尾
				index = contents.size() - 1;
				break;
			case KeyCodes::Enter:
				canExit = true;
				break;
			default:
				break;
			}
			//输入了数字
			//TODO: 这个输入方法体验还不是很好
			tempKey -= '0';
			if (tempKey >= 0 && tempKey < contents.size())
			{
				if (lastIsNumber)
				{
					int temp = tempKey + index * 10;
					if (temp < contents.size()) index = temp;
					else index = tempKey;
				}
				else
				{
					index = tempKey;
					lastIsNumber = true;
				}
			}
			else
			{
				lastIsNumber = false;
			}
			//防止溢出
			if (index >= contents.size()) index = contents.size() - 1;
			if (index < 0) index = 0;

		} while (!canExit);

		return index;
	}
	ColorfulConsole::Color QueryFlow::SetColor(const string& queryWord)
	{
		using namespace ColorfulConsole;
		using namespace ConAPIProx;
		Color originBack = GlobalEnvironment::GetBack();
		//颜色编号, 同时也是颜色码
		int chosenIndex = 0;
		Color currentBack = Color(chosenIndex);
		//发出询问
		cout << queryWord;
		Position beginPosition = Positioner::GetCursorPosition();
		int tempKey = 0;
		bool loop = true;
		while (loop)
		{

			Positioner::SetCursorPosition(beginPosition);
			for (int i = 0; i < 16; i++)
			{
				//上色, 如果是选择的编号就加个'√'
				cout << ColorfulConsole::TextAttribute::WarpedTextAttr(Color(i ^ 15), Color(i));
				if (i == chosenIndex) cout << "√";
				else cout << "  ";
			}
			tempKey = GetKey();
			switch (tempKey)
			{
			case KeyCodes::RightArrow:
				//--→
				if (chosenIndex >= 15) chosenIndex = 0;
				else chosenIndex++;
				break;
			case KeyCodes::LeftArrow:
				//←--
				if (chosenIndex <= 0) chosenIndex = 15;
				else chosenIndex--;
				break;
			case KeyCodes::Enter:
				//√
				loop = false;
				break;
			case KeyCodes::Home:
				//Home
				chosenIndex = 0;
				break;
			case KeyCodes::End:
				//End
				chosenIndex = 15;
				break;
			default:
				break;
			}
			currentBack = Color(chosenIndex);
		}
		//GlobalEnvironment::SetBack(originBack);
		cout << '\n';
		return Color(chosenIndex);
	}
	int QueryFlow::CheckedInput_int(const string& queryWord, const string& failWord, const string& invalidWord, std::function<bool(int)> checkFunc, const bool& useCES)
	{
		return CheckedInput<int>(queryWord, failWord, invalidWord, checkFunc, useCES);
	}
	int QueryFlow::SaveInput_int(const std::string& queryWord, const std::string& failWord, const bool& useCES)
	{
		return BasicTypeInput<int>(queryWord, failWord, useCES);
	}
	float QueryFlow::SaveInput_float(const std::string& queryWord, const std::string& failWord, const bool& useCES)
	{
		return BasicTypeInput<float>(queryWord, failWord, useCES);
	}
	double QueryFlow::SaveInput_double(const std::string& queryWord, const std::string& failWord, const bool& useCES)
	{
		return BasicTypeInput<double>(queryWord, failWord, useCES);
	}
}