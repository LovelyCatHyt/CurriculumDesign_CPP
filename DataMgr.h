#pragma once
#include "PolyFuncData.h"	//PolyFuncData
#include <string>			//string
#include <vector>			//vector
#include "json/json.hpp"	//json

using std::vector;
using std::string;
using nlohmann::json;

namespace Hyt
{
	class PolyFuncData;
	class DataMgr
	{
		vector<PolyFuncData> dataList;
	public:
		DataMgr();
		static DataMgr ReadFromFile(const string& fileName);
		void Input();
		void Print() const;
		void SaveToFile(const string& fileName) const;
		void GenerateSamples();
		//±à¼­Êý¾Ý
		void Edit(const int& index);
		int Count() const;
		friend void to_json(json& j, const DataMgr& mgr);
		friend void from_json(const json& j, DataMgr& mgr);
	};
}
