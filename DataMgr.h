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
		DataMgr(vector<PolyFuncData> dataList = {});
		static DataMgr ReadFromFile(const string& fileName);
		//输入数据
		void Input();
		//打印数据
		void Print() const;
		//保存到文件
		void SaveToFile(const string& fileName) const;
		//搜索数据: 将结果以DataMgr的形式返回, 按关键字搜素
		DataMgr SearchData(const string& keyWord) const;
		//搜索数据: 将结果以DataMgr的形式返回, 按项数搜索
		DataMgr SearchData(const unsigned int& argCount) const;
		//生成样点
		void GenerateSamples();
		//编辑数据
		void Edit(const int& index);
		//删除数据
		void DeleteData(int index);
		//数据个数
		int Count() const;
		friend void to_json(json& j, const DataMgr& mgr);
		friend void from_json(const json& j, DataMgr& mgr);
	};
}
