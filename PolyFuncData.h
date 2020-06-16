#pragma once

//#include <iostream>			//istream, ostream
#include <vector>
#include "json/json.hpp"	//json
#include "DataMgr.h"		//DataMgr

using uint = unsigned int;
using nlohmann::json;

namespace Hyt
{
	enum DetailLevel
	{
		Default,
		Simple,
		All
	};
	//Polynomial function data����ʽ��������
	class PolyFuncData
	{
	private:
		//x��Сֵ
		double xmin;
		//x���ֵ
		double xmax;
		//�����б�
		std::vector<double> argsList;
		//������_X
		std::vector<double> samples_X;
		//������_Y
		std::vector<double> samples_Y;
		//ƫ�������
		double rms;
	public:
		friend class DataMgr;
		PolyFuncData(const double& xmin = 0, const double& xmax = 1, uint count = 1);
		PolyFuncData(const std::vector<double>& argsList, const double& xmin = 0, const double& xmax = 1);
		//���ݶ���ʽ��ȡһ��ֵ
		double GetValue(double x);
		//���ݶ���ʽ�ڶ�������ȡһ��ֵ, �����򷵻�NaN
		double GetValue_s(double x, bool& inRange);
		//���û����н���, ��������
		void Input(const bool& useOutput = false);
		//������ݵ�cout
		void Print(const bool& withTag = false, const enum DetailLevel& level = DetailLevel::Default) const;
		//������������
		void GenerateSamples(uint count = 50);
		//�༭����
		void Edit();
		friend void to_json(json& j, const PolyFuncData& data);
		friend void from_json(const json& j, PolyFuncData& data);
	};
	

	void to_json(json& j, const PolyFuncData& data);
	void from_json(const json& j, PolyFuncData& data);
	//�������ʽ�����ĺ���ֵ
	double GetPolyFuncValue(double x, std::vector<double> argList, int startTerm = 0);
}
