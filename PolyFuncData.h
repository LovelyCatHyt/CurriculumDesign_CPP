#pragma once

//#include <iostream>			//istream, ostream
#include <vector>
#include "json/json.hpp"	//json
#include "DataMgr.h"		//DataMgr
#include <string>			//string

using uint = unsigned int;
using nlohmann::json;
using std::string;

namespace Hyt
{
	enum DetailLevel
	{
		Default,
		Simple,
		All
	};
	//Polynomial function data多项式函数数据
	class PolyFuncData
	{
	private:
		//多项式的名字
		string name;
		//x最小值
		double xmin;
		//x最大值
		double xmax;
		//参数列表
		std::vector<double> argsList;
		//样本点_X
		std::vector<double> samples_X;
		//样本点_Y
		std::vector<double> samples_Y;
		//偏差均方根
		double rms;
		std::vector<double> fitArgs;
	public:
		friend class DataMgr;
		PolyFuncData(const double& xmin = 0, const double& xmax = 1, uint count = 1, const string& name = "");
		PolyFuncData(const std::vector<double>& argsList, const double& xmin = 0, const double& xmax = 1, const string& name = "");
		//根据多项式获取一个值
		double GetValue(double x);
		//根据多项式在定义域内取一个值, 超出则返回NaN
		double GetValue_s(double x, bool& inRange);
		//与用户进行交互, 输入数据
		void Input(const bool& useOutput = false);
		//输出数据到cout
		void Print(const bool& withTag = false, const enum DetailLevel& level = DetailLevel::Default) const;
		//生成样本数据
		void GenerateSamples(uint count = 50);
		//打印样本数据
		void ShowSamples();
		//参数拟合
		void FitArgs();
		//编辑数据
		void Edit();
		friend void to_json(json& j, const PolyFuncData& data);
		friend void from_json(const json& j, PolyFuncData& data);
	};
	

	void to_json(json& j, const PolyFuncData& data);
	void from_json(const json& j, PolyFuncData& data);
	//计算多项式函数的函数值
	double GetPolyFuncValue(double x, std::vector<double> argList, int startTerm = 0);
}
