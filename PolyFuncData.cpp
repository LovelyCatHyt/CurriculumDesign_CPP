#include "PolyFuncData.h"
#include <vector>								//vector
#include <iostream>								//cout
#include <iomanip>								//setw
#include <stdlib.h>								//rand, srand, time
#include "ColorfulConsole/CloEscString.h"		//ces
#include "polyfit/polyfit.h"					//polyfit
#include "QueryFlow.h"							//QueryFlow
#include <iomanip>								//std:setw()
#include "StringUtiliy.h"

using std::vector;
using std::cout;	using std::cin;
using std::setw;	using std::setfill;
using namespace ColorfulConsole;

namespace Hyt
{
	enum DetailLevel;

	template <typename T>
	inline void PrintDataList(const vector<T>& list, const int& countPerRow = 5, const bool& withID = true)
	{
		int id = 0;
		int i = 0;
		while (id < list.size())
		{
			if (withID) cout << ces << "&8[" << std::right << setfill('0') << setw(2) << id << ces << "]&r ";
			cout << setfill(' ') << setw(5) << list[id] << ' ';
			if (i == 4)
			{
				cout << '\n';
				i = -1;
			}
			i++;
			id++;
		}
	}

	PolyFuncData::PolyFuncData(const double& xmin, const double& xmax, uint count, const string& name) : xmin(xmin), xmax(xmax), rms(0)
	{
		argsList = vector<double>(count);
		samples_X = vector<double>(0);
		samples_Y = vector<double>(0);
		if (name.empty())
		{
			char temp[10] = "";
			_itoa_s(count, temp, 10);
			this->name = temp;
		}
		else this->name = name;

	}
	PolyFuncData::PolyFuncData(const vector<double>& argsList, const double& xmin, const double& xmax, const string& name) : argsList(argsList), xmin(xmin), xmax(xmax), rms(0)
	{
		samples_X = vector<double>(0);
		samples_Y = vector<double>(0);
		if (name.empty())
		{
			char temp[10] = "";
			_itoa_s(argsList.size(), temp, 10);
			this->name = temp;
		}
		else this->name = name;
	}
	double PolyFuncData::GetValue(double x)
	{
		return GetPolyFuncValue(x, argsList);
	}
	double PolyFuncData::GetValue_s(double x, bool& inRange)
	{
		if (x >= xmin && x <= xmax)
		{
			inRange = true;
			return GetPolyFuncValue(x, argsList);
		}
		else
		{
			inRange = false;
#ifdef SHOWWARN
			std::cout << "x(" << x << ")�����˶�����:[" << xmin << ", " << xmax << "]!\n";
#endif // 
			return 0;
		}
	}
	void PolyFuncData::Input(const bool& useOutput)
	{
		if (useOutput) cout << "���������ʽ������:\n>";
		uint count;
		cin >> count;
		if (useOutput) cout << ces << "�����붨�����&1��Сֵ&r��&1���ֵ&r:\n>";
		cin >> xmin >> xmax;
		//Input All
		argsList.clear();

		if (useOutput) cout << ces << "������&1" << count << ces << "&r������:\n>";
		for (uint i = 0; i < count; i++)
		{
			double temp;
			cin >> temp;
			argsList.push_back(temp);
		}
		if (useOutput) cout << count << "���������������.\n";
		if (useOutput) cout << "���������ʽ������: \n>";
		cin >> name;
	}
	void PolyFuncData::Print(const bool& withTag, const DetailLevel& level) const
	{
		if (withTag)
		{
			cout << ces('r') << name << ": ����: " << std::left << setw(5) << argsList.size();
			cout << ces << "&2��Сֵ&r:&2 " << setw(10) << xmin << ces << "&4���ֵ&r:&4 " << setw(10) << xmax << ces << "&r\n";
		}
		switch (level)
		{
		case DetailLevel::Default:
			if (withTag)
			{
				cout << "ϵ���б�:\n";
				PrintDataList(argsList);
			}
			break;
		}
		cout << '\n';
	}
	void PolyFuncData::GenerateSamples(uint count)
	{
		if (count <= 0)
		{
			cout << ces << "&4����: û�в�������.\n&r";
			return;
		}
		if (xmin == xmax)
		{
			cout << ces << "&4����: ��������ͬ\n&r";
			return;
		}
		//�������
		samples_X.clear(); samples_Y.clear();
		srand(time(0));
		double step = (xmax - xmin) / count;
		//cout << ces << "&1Samples generating...&r\n";
		for (double x = xmin; x < xmax; x += step)
		{
			double r = rand() / 32768.0 - 0.5;
			samples_X.push_back(x);
			samples_Y.push_back(GetValue(x) + r);
			//cout << x << ' ' << (GetValue(x) + r) << '\n';
		}
		vector<double> fitargs(argsList.size());
		//����һ�����ӽ��в�����ʶ ע�������order��ָ����, "y=x+1" ����Ϊ1
		polyfit(samples_X.begin()._Ptr, samples_Y.begin()._Ptr, count, argsList.size() - 1, fitargs.begin()._Ptr);
		//if (/*QueryFlow::YesNoQuery("&8�Ƿ����&r��ʶ����?\n>")*/true)
		//{
		//	for (int i = 0; i < fitargs.size(); i++)
		//	{
		//		cout << i << ' ' << fitargs[i] << '\n';
		//	}
		//}
		vector<double> realY(count), fitY(count);
		double sqrDelta = 0;//ƫ���ƽ����
		for (uint i = 0; i < count; i++)
		{
			//��ʵֵ
			realY[i] = GetPolyFuncValue(samples_X[i], argsList);
			//����ֵ
			fitY[i] = GetPolyFuncValue(samples_X[i], fitargs);
			double temp = realY[i] - fitY[i];
			sqrDelta += temp * temp;
		}
		//��ӡ����
		PrintDataList(fitargs);
		cout << '\n';
		rms = sqrt(sqrDelta);
		cout << ces << "��Ͼ�����: " << rms << "\n";
		//Debug

	}
	void PolyFuncData::Edit()
	{
		PolyFuncData temp;
		temp.Input(true);
		cout << ces << "&2ԭ����&r:\n";
		Print(true);
		cout << ces << "&2������&r:\n";
		temp.Print(true);
		if (QueryFlow::YesNoQuery("�Ƿ�ȷ�ϱ��α༭?"))
		{
			*this = temp;
			cout << ces << "&8�������ѱ���.\n&r";
		}
		else
		{
			cout << ces << "&8ԭ����δ�����仯.\n";
		}
	}
	/*void PolyFuncData::Print(const bool& withTag, const DetailLevel& level)
	{

	}*/
	void to_json(nlohmann::json& j, const PolyFuncData& data)
	{
		j = nlohmann::json{
			{"name" ,GBKToUTF8(data.name.c_str())}, //jsonȡ��������utf8, Ҫת��
			{"xmin",data.xmin},
			{"xmax",data.xmax},
			{"argsList",data.argsList},
			{"samples_X",data.samples_X},
			{"samples_Y",data.samples_Y},
			{"rms",data.rms}
		};
	}
	void from_json(const nlohmann::json& j, PolyFuncData& data)
	{
		j["name"].get_to(data.name);
		data.name = UTF8ToGBK(data.name.c_str()); //jsonҪ�õ�utf8, ת��ȥ
		data.xmin = j["xmin"];
		data.xmax = j["xmax"];
		j.at("argsList").get_to<vector<double>>(data.argsList);
		j.at("samples_X").get_to<vector<double>>(data.samples_X);
		j.at("samples_Y").get_to<vector<double>>(data.samples_Y);
		data.rms = j["rms"];
	}
	double GetPolyFuncValue(double x, vector<double> argList, int startTerm)
	{
		if (startTerm > argList.size() - 1) return 0;
		else
			return startTerm < argList.size() - 1 ?
			argList[startTerm] + x * GetPolyFuncValue(x, argList, startTerm + 1) :
			argList[startTerm];
	}

}