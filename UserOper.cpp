#include "UserOper.h"
#include "ColorfulConsole/CloEscString.h"
#include "QueryFlow.h"
#include "DataMgr.h"

using std::string;
using ColorfulConsole::ces;

namespace Hyt
{
	User adminTemplate = User("Admin", "123456", "TestData/Data1.json");
	void UserOper::LoginOrRegister(UserMgr& mgr, User*& currentUser, bool& success)
	{
		if (mgr.UserCount() == 0)
		{
			//һ���û���û��, �Ǿʹ���һ��Admin��ȥ
			mgr.Register(adminTemplate);
		}
		if (QueryFlow::ShowMenu("��¼\nע��", false) == 0)
		{
			//��¼
			string name;
			string pw;
			string dataName;
			cout << "�������û���:\n>";
			cin >> name;
			cout << "����������:\n>";
			cin >> pw;
			cout << ces << "&8������ҪƬ�̽�����֤, �����ĵȴ�!\n";
			mgr.Login(name, pw, success);
			currentUser = &mgr.FindUser(name, success);
		}
		else
		{
			//ע��
			string name;
			string pw;
			string dataName;
			do
			{
				cout << "�������û���:\n>";
				cin >> name;
				if (mgr.ExistUser(name))
				{
					cout << ces << "�û�\"&4" << name << ces << "&r\"�Ѵ���! ����������.\n";
					success = false;
					continue;
				}
				cout << "����������:\n>";
				cin >> pw;
				dataName = name + "_data.json";
				//Ĭ�ϵ�Ȼ����ͨȨ��
				mgr.Register(User(name, pw, dataName, 1));
				currentUser = &mgr.FindUser(name, success);
			} while (!success);
		}
	}
	bool UserOper::LoginOrRegister(UserMgr& mgr, User*& currentUser)
	{
		bool temp;
		LoginOrRegister(mgr, currentUser, temp);
		return temp;
	}
	void UserOper::DoOperations(User& currentUser, DataMgr& data)
	{
		bool loop = true;
		while (loop)
		{

			int flag = QueryFlow::ShowMenu({ "��ʾ����",
				"��������",
				"��������",
				"������ϲ���",
				"�༭����",
				"ɾ������",
				"&4�˳�ϵͳ" });
			switch (flag)
			{
			case 0:
				ShowData(data);
				
				break;
			case 1:
				DataInput(data);
				break;
			case 2:
				SearchData(data); 
				break;
			case 3:
				GenerateFitArgs(data); 
				break;
			case 4:
				EditData(data); 
				break;
			case 5:
				DeleteData(data);
				break;
			case 6:
				loop = !QueryFlow::YesNoQuery("&4�Ƿ��˳�����?&r");
				break;
			default:
				break;
			}
		}
	}
	void UserOper::DataInput(DataMgr& data)
	{
		data.Input();
	}
	void UserOper::SearchData(const DataMgr& data)
	{
		cout << "��ѡ���ѯ��ʽ:\n";
		int menuValue = QueryFlow::ShowMenu(vector<string>{"�����ƹؼ��ֲ�ѯ",
			"��������ѯ"});
		string keyWord;
		int argCount;
		DataMgr temp;
		switch (menuValue)
		{
		case 0:
			cout << "������Ҫ��ѯ�Ĺؼ���:\n>";
			cin >> keyWord;
			temp = data.SearchData(keyWord);
			if (temp.Count() == 0)
			{
				cout << ces << "δ���ҵ�����Ϊ\"&6" << keyWord << ces << "&r\"�Ķ���ʽ!\n";
			}
			else
			{
				cout << "��ѯ���:\n";
				temp.Print();
			}
			break;
		case 1:
			cout << "������Ҫ��ѯ�Ķ���ʽ����:\n>";
			cin >> argCount;
			temp = data.SearchData(argCount);
			if (temp.Count() == 0)
			{
				cout << ces << "δ���ҵ�����Ϊ\"&6" << argCount << ces << "&r\"�Ķ���ʽ!\n";
			}
			else
			{
				cout << "��ѯ���:\n";
				temp.Print();
			}
			break;
		}
	}
	void UserOper::GenerateFitArgs(DataMgr& data)
	{
		//TODO:�ֿ����������ǲ��Ǹ���?
		data.GenerateSamples();
	}
	void UserOper::EditData(DataMgr& data)
	{
		cout << "��ǰ��������: \n";
		data.Print();
		int index = QueryFlow::CheckedInput_int("������Ҫ�༭�����ݵı��, ��0��ʼ:\n>", "", "�����ڸñ��!", [&data](int num) {return num >= 0 && num < data.Count(); });
		data.Edit(index);
		
	}
	void UserOper::ShowData(const DataMgr& data)
	{
		data.Print();
	}
	void UserOper::DeleteData(DataMgr& data)
	{
		cout << "��ǰ��������:\n";
		data.Print();
		int index = QueryFlow::CheckedInput_int("������Ҫɾ�������ݱ��:\n>", 
			"���ݴ���!����������.", 
			"���Խ��!��������ȷ�ı��", 
			[&](int i) {return i >= 0 && i < data.Count(); });
		data.DeleteData(index);
	}
}
