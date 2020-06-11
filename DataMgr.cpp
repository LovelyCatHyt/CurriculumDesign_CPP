#include <iostream>							//cout, cin
#include "DataMgr.h"
#include "FileIO.h"							//FileIO
#include "ColorfulConsole/CloEscString.h"	//ces
#include "QueryFlow.h"						//QueryFlow

using namespace Hyt::FileInOut;
using std::cin;
using std::cout;
using ColorfulConsole::ces;

namespace Hyt
{
	DataMgr::DataMgr() : dataList()
	{

	}
	DataMgr DataMgr::ReadFromFile(const string& fileName)
	{
		json j = json::parse(ReadAll(fileName));
		return j;
	}
	void DataMgr::Input()
	{
		uint index = 0;
		bool ifContinue = true;
		while (ifContinue)
		{
			cout << ces << "请输入第[&1" << (index + 1) << ces << "&r]个数据.\n";
			dataList.emplace_back();
			dataList[index].Input(true);
			ifContinue = QueryFlow::IfContinue();
			index++;
		}
	}
	void DataMgr::Print()
	{
		cout << ces << "&9当前数据&r如下:\n";
		cout << ces << "总数据量: &1" << dataList.size() << ces << "&r条\n";
		for (uint i = 0; i < dataList.size(); i++)
		{
			cout << ces << "第&1" << i << ces << "&r个数据:\n";
			dataList[i].Print(true);
		}
		cout << ces << "&a--------------------&r数据输出完毕&a------------------------------------\n";
	}
	void DataMgr::SaveToFile(const string& fileName)
	{
		WriteAll(fileName, json(*this).dump(4));
	}
	void DataMgr::GenerateSamples()
	{
		cout << ces << "&8正在辨识参数...&r\n";
		for (int i = 0; i < dataList.size(); i++)
		{
			cout << "[" << i << "]: ";
			dataList[i].GenerateSamples();
			cout << '\n';
		}
		cout << ces << "&a--------------------&r参数辨识完毕&a------------------------------------\n";
	}
	void to_json(json& j, const DataMgr& mgr)
	{
		j = mgr.dataList;
	}
	void from_json(const json& j, DataMgr& mgr)
	{
		mgr.dataList = j.get<vector<PolyFuncData>>();
	}
}
