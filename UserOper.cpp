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
			//一个用户都没有, 那就创建一个Admin进去
			mgr.Register(adminTemplate);
		}
		if (QueryFlow::ShowMenu("登录\n注册", false) == 0)
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

			int flag = QueryFlow::ShowMenu({ "显示数据",
				"数据输入",
				"数据搜索",
				"生成拟合参数",
				"编辑数据",
				"&4退出系统" });
			switch (flag)
			{
			case 0:
				ShowData(data);
				
				break;
			case 1:
				DataInput(currentUser, data);
				break;
			case 2:
				SearchData(currentUser, data); 
				break;
			case 3:
				GenerateFitArgs(currentUser, data); 
				break;
			case 4:
				EditData(currentUser, data); 
				break;
			case 5:
				loop = !QueryFlow::YesNoQuery("&4是否退出程序?&r");
				break;
			default:
				break;
			}
		}
	}
	void UserOper::DataInput(const User& currentUser, DataMgr& data)
	{
		data.Input();
	}
	void UserOper::SearchData(const User& currentUser, const DataMgr& data)
	{
		//TODO
		cout << ces << "&4Not implemented yet!\n";
	}
	void UserOper::GenerateFitArgs(const User& currentUser, DataMgr& data)
	{
		//TODO
		data.GenerateSamples();
	}
	void UserOper::EditData(const User& currentUser, DataMgr& data)
	{
		cout << "当前数据如下: \n";
		data.Print();
		int index = QueryFlow::CheckedInput_int("请输入要编辑的数据的编号, 从0开始:\n>", "", "不存在该编号!", [&data](int num) {return num >= 0 && num < data.Count(); });
		cout << "Get an valid index: " << index << '\n';
		data.Edit(index);
		
	}
	void UserOper::ShowData(const DataMgr& data)
	{
		data.Print();
	}
}
