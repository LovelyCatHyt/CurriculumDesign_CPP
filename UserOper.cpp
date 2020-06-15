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
			//一个用户都没有, 那就创建一个Admin进去
			mgr.Register(adminTemplate);
		}
		if (QueryFlow::YesNoQuery("是否登录?按确认登录, 否则注册新用户."))
		{
			//登录
			string name;
			string pw;
			string dataName;
			cout << "请输入用户名:\n>";
			cin >> name;
			cout << "请输入密码:\n>";
			cin >> pw;
			cout << ces << "&8可能需要片刻进行验证, 请耐心等待!\n";
			mgr.Login(name, pw, success);
			currentUser = &mgr.FindUser(name, success);
		}
		else
		{
			//注册
			string name;
			string pw;
			string dataName;
			do
			{
				cout << "请输入用户名:\n>";
				cin >> name;
				if (mgr.ExistUser(name))
				{
					cout << ces << "用户\"&4" << name << ces << "&r\"已存在! 请重新输入.\n";
					success = false;
					continue;
				}
				cout << "请输入密码:\n>";
				cin >> pw;
				dataName = name + "_data.json";
				//默认当然是普通权限
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
