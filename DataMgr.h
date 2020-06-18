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
		//��������
		void Input();
		//��ӡ����
		void Print() const;
		//���浽�ļ�
		void SaveToFile(const string& fileName) const;
		//��������: �������DataMgr����ʽ����, ���ؼ�������
		DataMgr SearchData(const string& keyWord) const;
		//��������: �������DataMgr����ʽ����, ����������
		DataMgr SearchData(const unsigned int& argCount) const;
		//��������
		void GenerateSamples();
		//�༭����
		void Edit(const int& index);
		//ɾ������
		void DeleteData(int index);
		//���ݸ���
		int Count() const;
		friend void to_json(json& j, const DataMgr& mgr);
		friend void from_json(const json& j, DataMgr& mgr);
	};
}
