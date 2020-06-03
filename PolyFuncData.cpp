#include "PolyFuncData.h"
#include <vector>								//vector
#include <iostream>								//cout
#include "ColorfulConsole/ForeColorProxy.h"		//ForeColorProxy
#include "ColorfulConsole/GlobalEnvironment.h"	//GlobalEnvironment

using std::vector;
namespace Hyt
{
	PolyFuncData::PolyFuncData(const double& xmin, const double& xmax, uint count) : xmin(xmin), xmax(xmax), rms(0)
	{
		argsList = vector<double>(count);
		fitArgsList = vector<double>(argsList.size());
	}
	PolyFuncData::PolyFuncData(const vector<double>& argsList, const double& xmin, const double& xmax) : argsList(argsList), xmin(xmin), xmax(xmax), rms(0)
	{
		fitArgsList = vector<double>(argsList.size());
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
			std::cout << "x(" << x << ")超出了定义域:[" << xmin << ", " << xmax << "]!\n";
#endif // 
			return 0;
		}
	}
	void PolyFuncData::Input(const bool& useOutput)
	{
		//先定义一堆简写
		using std::cout;
		using std::cin;
		using namespace ColorfulConsole;
		using FCP = ForeColorProxy;
		using GloEnv = GlobalEnvironment;
		
		if(useOutput) cout << "请输入多项式的项数:\n>";
		uint count;
		cin >> count;
		if(useOutput) cout << "请输入定义域的" << FCP::LIGHTBLUE << "最小值" << GloEnv::GetFore() << "和" << FCP::LIGHTBLUE << "最大值" << GloEnv::GetFore() << ":\n>";
		cin >> xmin >> xmax;
		//Input All
		argsList.clear();
		if (useOutput) cout << "请输入" << FCP::LIGHTBLUE << count << GloEnv::GetFore() << "个参数:\n>";
		for (int i = 0; i < count; i++)
		{
			double temp;
			cin >> temp;
			argsList.push_back(temp);
		}
		if (useOutput) cout << count << "个参数已输入完毕.\n";
	}
	void PolyFuncData::Output(const bool& withTag)
	{
		//TODO
	}
	void to_json(nlohmann::json& j, const PolyFuncData& data)
	{
		j = nlohmann::json{
			{"xmin",data.xmin},
			{"xmax",data.xmax},
			{"argsList",data.argsList},
			{"fitArgsList",data.fitArgsList},
			{"rms",data.rms}
		};
	}
	void from_json(const nlohmann::json& j, PolyFuncData& data)
	{
		data.xmin = j["xmin"];
		data.xmax = j["xmax"];
		j.at("argsList").get_to<vector<double>>(data.argsList);
		j.at("fitArgsList").get_to<vector<double>>(data.fitArgsList);
		data.rms = j["rms"];
	}
	double GetPolyFuncValue(double x, vector<double> argList, int startTerm)
	{
		return startTerm < argList.size() - 1 ?
			argList[startTerm] + x * GetPolyFuncValue(x, argList, startTerm + 1) :
			argList[startTerm];
	}
}