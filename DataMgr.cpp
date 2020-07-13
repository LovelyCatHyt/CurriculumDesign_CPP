#include <iostream>							//cout, cin
#include <string>
#include "DataMgr.h"
#include "FileIO.h"							//FileIO
#include "ColorfulConsole/CloEscString.h"	//ces
#include "QueryFlow.h"						//QueryFlow
#include "Config.h"

using namespace Hyt::FileInOut;
using std::cin;
using std::cout;
using ColorfulConsole::ces;
std::string currentDataFile = "";

namespace Hyt
{
	void DataMgr::AutoSaveIfConfigered()
	{
		if (Configration::Config::GetConfigRef().autoSave)
		{
			SaveToFile(currentDataFile);
		}
	}
	DataMgr::DataMgr(vector<PolyFuncData> dataList) : dataList(dataList)
	{

	}
	DataMgr DataMgr::ReadFromFile(const string& fileName)
	{
		string fileContent = ReadAll(fileName);
		if (fileContent.empty())
		{
			return DataMgr();
		}
		else
		{
			try
			{
				json j = json::parse(fileContent); 
				return j;
			}
			catch (const json::exception e)
			{
				cout << ces << "&4Error: Cannot parse json file. Return default empty data.&r\n";
				return DataMgr();
			}
			
			
		}
	}
	void DataMgr::Input()
	{
		uint index = dataList.size();
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
	void DataMgr::Print() const
	{
		cout << ces << "总数据量: &1" << dataList.size() << ces << "&r条\n";
		for (uint i = 0; i < dataList.size(); i++)
		{
			cout << ces << "[&1" << i << ces << "&r]: ";
			dataList[i].Print(true);
			cout << '\n';
		}
	}
	void DataMgr::SaveToFile(const string& fileName) const
	{
		WriteAll(fileName, json(*this).dump(4));
	}
	DataMgr DataMgr::SearchData(const string& keyWord) const
	{
		DataMgr temp;
		for (auto data : dataList)
		{
			//关键字则添加进去
			if (data.name.find(keyWord) != string::npos) temp.dataList.push_back(data);
		}
		return temp;
	}
	DataMgr DataMgr::SearchData(const unsigned int& argCount) const
	{
		DataMgr temp;
		for (auto data : dataList)
		{
			//项数符合条件则添加进去
			if (data.argsList.size() == argCount) temp.dataList.push_back(data);
		}
		return temp;
	}
	void DataMgr::GenerateSamples()
	{
		cout << ces << "&8正在生成样本...&r\n";
		for (int i = 0; i < dataList.size(); i++)
		{
			cout << "[" << i << "]: ";
			dataList[i].GenerateSamples();
			cout << '\n';
		}
		AutoSaveIfConfigered();
	}
	void DataMgr::ShowSamples()
	{
		for (int i = 0; i < dataList.size(); i++)
		{
			cout << "[" << i << "]: ";
			dataList[i].ShowSamples();
			cout << '\n';
		}
	}
	void DataMgr::FitArgs()
	{
		for (int i = 0; i < dataList.size(); i++)
		{
			cout << "[" << i << "]: ";
			dataList[i].FitArgs();
			cout << '\n';
		}
		AutoSaveIfConfigered();
	}
	void DataMgr::Edit(const int& index)
	{
		cout << ces << "正在编辑编号为&1" << index << ces << "&r的数据\n";
		dataList[index].Edit();
		AutoSaveIfConfigered();
	}
	void DataMgr::DeleteData(int index)
	{
		cout << "要删除的数据为:\n";
		dataList[index].Print(true);
		if (QueryFlow::YesNoQuery("确定要&4删除&r该数据吗?"))
		{
			dataList.erase(dataList.begin() + index);
			cout << ces << "&8数据已删除\n";
		}
		else
		{
			cout << ces << "&8数据未发生变化\n";
		}
		AutoSaveIfConfigered();
	}
	int DataMgr::Count() const
	{
		return dataList.size();
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
