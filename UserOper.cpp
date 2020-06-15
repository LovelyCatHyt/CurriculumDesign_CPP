#include "UserOper.h"
#include "ColorfulConsole/CloEscString.h"
#include "QueryFlow.h"

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
		if (QueryFlow::YesNoQuery("�Ƿ��¼?��ȷ�ϵ�¼, ����ע�����û�."))
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
				currentUser = &mgr.FindUser(name,success);
			} while (!success);
		}
	}
	bool UserOper::LoginOrRegister(UserMgr& mgr, User*& currentUser)
	{
		bool temp;
		LoginOrRegister(mgr, currentUser, temp);
		return temp;
	}
	void UserOper::DataInput(const User& currentUser, PolyFuncData& data)
	{
		//TODO
	}
	void UserOper::SearchData(const User& currentUser, const PolyFuncData& data)
	{
		//TODO
	}
	void UserOper::GenerateFitArgs(const User& currentUser, PolyFuncData& data)
	{
		//TODO
	}
	void UserOper::EditData(const User& currentUser, PolyFuncData& data)
	{
		//TODO
	}
}
