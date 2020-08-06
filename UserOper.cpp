#include <sstream>
#include "Config.h"
#include "UserOper.h"
#include "ColorfulConsole/CloEscString.h"
#include "QueryFlow.h"
#include "DataMgr.h"

using std::string;
using ColorfulConsole::ces;
//extern const string Hyt::Configration::configFile;
extern string userFile;

namespace Hyt
{
	UserMgr* UserOper::users = NULL;
	User adminTemplate = User("Admin", "123456", "Data1.json", 0);
	void UserOper::Init(UserMgr* usersPtr)
	{
		users = usersPtr;
	}
	void UserOper::LoginOrRegister(User*& currentUser, bool& success)
	{
		if (users->UserCount() == 0)
		{
			//一个用户都没有, 那就创建一个Admin进去
			users->Register(adminTemplate);
		}
		string name;
		string pw;
		string dataName;
		switch (QueryFlow::ShowMenu("登录\n注册\n退出", false))
		{
		case 0:
			//登录
			success = false;
			while (!success)
			{
				cout << "请输入用户名:\n>";
				cin >> name;
				cout << "请输入密码:\n>";
				cin >> pw;
				cout << ces << "&8可能需要片刻进行验证, 请耐心等待!&r\n";
				users->Login(name, pw, success);
				if (!success)
				{
					cout << ces << "&4用户名或密码错误!&r\n";
					continue;
				}
				//赋值对应的User
				currentUser = &users->FindUser(name, success);
				//成功则刷新密码(必须刷新以生成正确密钥)
				cout << ces << "&1登录成功! 正在初始化用户信息...&r\n";
				currentUser->RefreshPw(pw);
			}
			break;
		case 1:
			//注册
			do
			{
				cout << "请输入用户名:\n>";
				cin >> name;
				if (users->ExistUser(name))
				{
					cout << ces << "用户\"&4" << name << ces << "&r\"已存在! 请重新输入.\n";
					success = false;
					continue;
				}
				cout << "请输入密码:\n>";
				cin >> pw;
				dataName = name + "_data.json";
				//默认当然是普通权限
				users->Register(User(name, pw, dataName, 1));
				currentUser = &users->FindUser(name, success);
			} while (!success);
			break;
		case 2:
			//退出
			currentUser = NULL;
			success = false;
			break;
		} 
			
		
	}
	bool UserOper::LoginOrRegister(User*& currentUser)
	{
		bool temp;
		LoginOrRegister(currentUser, temp);
		return temp;
	}
	int UserOper::DoOperations(User*& currentUser, DataMgr& data)
	{
		bool loop = true;
		while (loop)
		{
			cout << "请选择要使用的功能:\n";
			int flag = QueryFlow::ShowMenu({ "显示数据",
				"数据输入",
				"数据搜索",
				"数据拟合",
				"编辑数据",
				"删除数据",
				"保存数据",
				"用户中心",
				"系统设置",
				"&4退出系统" });
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
				ArgsFiting(data);
				break;
			case 4:
				EditData(data);
				break;
			case 5:
				DeleteData(data);
				break;
			case 6:
				SaveData(data);
				break;
			case 7:
				UsersCenter(currentUser, *users);
				break;
			case 8:
				Configuring();
				break;
			default:
				if (QueryFlow::YesNoQuery("&4是否退出程序?&r")) return 0;
				break;
			}
			if (Configration::Config::GetConfigRef().autoSave)
			{
				users->SaveToFile(userFile);
			}
			if (currentUser == NULL)
			{
				loop = false;	//以注销的形式退出
				return 1;
			}
			
		}
		return -1;	//loop由于非常神奇的原因变成false, 或者while奇迹地脱离循环, 才会跑到这个地方
	}
	void UserOper::DataInput(DataMgr& data)
	{
		data.Input();
	}
	void UserOper::SearchData(const DataMgr& data)
	{
		cout << "请选择查询方式:\n";
		int menuValue = QueryFlow::ShowMenu(vector<string>{"按名称关键字查询",
			"按项数查询"});
		string keyWord;
		int argCount;
		DataMgr temp;
		switch (menuValue)
		{
		case 0:
			cout << "请输入要查询的关键字:\n>";
			cin >> keyWord;
			temp = data.SearchData(keyWord);
			if (temp.Count() == 0)
			{
				cout << ces << "未能找到名称为\"&6" << keyWord << ces << "&r\"的多项式!\n";
			}
			else
			{
				cout << "查询结果:\n";
				temp.Print();
			}
			break;
		case 1:
			cout << "请输入要查询的多项式项数:\n>";
			cin >> argCount;
			temp = data.SearchData(argCount);
			if (temp.Count() == 0)
			{
				cout << ces << "未能找到项数为\"&6" << argCount << ces << "&r\"的多项式!\n";
			}
			else
			{
				cout << "查询结果:\n";
				temp.Print();
			}
			break;
		}
	}
	void UserOper::ArgsFiting(DataMgr& data)
	{
		bool loop = true;
		while (loop)
		{
			cout << "请选择要进行的具体操作:\n";
			int flag = QueryFlow::ShowMenu(vector<string>{
				"查看样本数据",
					"生成样本数据",
					"计算拟合参数",
					"返回主菜单  "});
			switch (flag)
			{
			case 0:
				data.ShowSamples();
				break;
			case 1:
				data.GenerateSamples();
				break;
			case 2:
				data.FitArgs();
				break;
			default:
				cout << ces << "&8数据拟合功能已退出&r\n";
				loop = false;
				break;
			}
		}
		
	}
	void UserOper::EditData(DataMgr& data)
	{
		cout << "当前数据如下: \n";
		data.Print();
		int index = QueryFlow::CheckedInput_int("请输入要编辑的数据的编号, 从0开始:\n>", "", "不存在该编号!", [&data](int num) {return num >= 0 && num < data.Count(); });
		data.Edit(index);

	}
	void UserOper::ShowData(const DataMgr& data)
	{
		data.Print();
	}
	void UserOper::SaveData(const DataMgr& data)
	{
		data.SaveToFile(currentDataFile);
		cout << ces << "&8数据已保存!\n&r";
	}
	void UserOper::DeleteData(DataMgr& data)
	{
		cout << "当前数据如下:\n";
		data.Print();
		int index = QueryFlow::CheckedInput_int("请输入要删除的数据编号:\n>",
			"数据错误!请输入整数.",
			"编号越界!请输入正确的编号",
			[&](int i) {return i >= 0 && i < data.Count(); });
		data.DeleteData(index);
	}

	void UserOper::Configuring()
	{
		int flag;
		bool loop = true;
		Configration::Config& config = Configration::Config::GetConfigRef();
		while (loop)
		{
			cout << "请选择要编辑的设置项:\n";
			flag = QueryFlow::ShowMenu("前景色\n背景色\n自动保存\n退出设置");
			switch (flag)
			{
			case 0:
				config.fgColor = QueryFlow::SetColor("请选择新的前景色:\n");
				config.Init();
				cout << "前景色已修改\n";
				break;
			case 1:
				config.bgColor = QueryFlow::SetColor("请选择新的背景色:\n");
				config.Init();
				cout << "背景色已修改\n"; 
				break;
			case 2:
				config.autoSave = QueryFlow::YesNoQuery("是否自动保存? 选择自动保存, 所有用户和数据的改动后都会自动保存; 设置信息不受影响\n");
				config.Init();
				break;
			default:
				loop = false;
				break;
			}
			
		}		
		config.Save(Configration::configFile);
	}

	void UserOper::UsersCenter(User*& currentUser, UserMgr& users)
	{
		cout << "请选择要使用的功能:\n";
		int flag = 0;
		switch (currentUser->Access())
		{
		case 0:
			//Admin
			flag = QueryFlow::ShowMenu(vector<string>{"修改密码", "修改用户名", "管理员模块", "登出", "返回主菜单"});
			switch (flag)
			{
			case 0:
				ChangePW(*currentUser, users);
				break;
			case 1:
				ChangeName(*currentUser, users);
				break;
			case 2:
				ManagerModule(*currentUser, *UserOper::users);
				break;
			case 3:
				Logout(currentUser);
				break;
			default:
				//Nothing
				break;
			}
			break;
		case 1:
			//Normal
			flag = QueryFlow::ShowMenu(vector<string>{"修改密码", "修改用户名", "登出", "返回主菜单"});
			switch (flag)
			{
			case 0:
				ChangePW(*currentUser, users);
				break;
			case 1:
				ChangeName(*currentUser, users);
				break;
			case 2:
				Logout(currentUser);
				break;
			default:
				//Nothing
				break;
			}
			break;
		}
		//if (currentUser == NULL)
		//{
		//	//已登出
		//	//好像啥也不用干
		//}
	}
	void UserOper::ChangePW(User& currentUser, UserMgr& users)
	{
		string pw_a = "", pw_b = "";
		while (true)
		{
			cout << "请输入新密码:\n>";
			cin >> pw_a;
			cout << "请再输入一遍密码确认:\n>";
			cin >> pw_b;
			if (pw_a == pw_b) break;
			//没break, 再来一次
			cout << "两次输入密码不同!";
		}
		currentUser.RefreshPw(pw_a);
		cout << "密码已修改!\n";
	}
	void UserOper::ChangeName(User& currentUser, UserMgr& users)
	{
		string temp;
		cout << "请输入新用户名:\n>";
		cin >> temp;
		cout << ces << "用户名已修改为&6\"" << currentUser.Name(temp) << ces << "\"&r\n";
		if (Configration::Config::GetConfigRef().autoSave)
		{
			users.SaveToFile(userFile);
		}
	}
	void UserOper::Logout(User*& currentUser)
	{
		if (QueryFlow::YesNoQuery("是否退出账号?"))
		{
			currentUser = NULL;
		}
	}
	void UserOper::ManagerModule(User& currentUser, UserMgr &mgr)
	{
		int flag;
		bool loop = true;
		while (loop)
		{
			cout << "请选择要进行的用户操作: \n";
			flag = QueryFlow::ShowMenu("显示用户信息\n删除用户\n退出用户管理");
			switch (flag)
			{
			case 0:
				cout << "当前存在的用户如下: \n";
				mgr.PrintUsers();
				break;
			case 1:
				DeleteUser(currentUser.Name(), mgr);
				break;
			case 2:
				loop = false;
				break;
			}
		}
	}

	void UserOper::DeleteUser(const string& currentUserName,UserMgr& mgr)
	{
		cout << "当前存在的用户如下: \n";
		mgr.PrintUsers();
		int index = QueryFlow::CheckedInput_int("请选择要删除的用户的编号:\n>", "&4数据类型错误!&r\n", "&4用户编号越界!\n&r", [&](int num) {
			return num >= 0 && num < mgr.UserCount(); });
		if (index == mgr.GetUserIndex(currentUserName))
		{
			//不能删自己
			cout << ces << "&4错误: 不能删除自己!\n";
			return;
		}
		std::ostringstream ostr;
		ostr << "确定要删除编号为&6[" << index << "]&r的用户吗?";	ostr.flush();
		if (QueryFlow::YesNoQuery(ostr.str()))
		{
			mgr.DeleteUser(index);
			cout << "&8该用户已删除\n&r";
		}
		else
		{
			cout<<ces << "&8用户列表未发生变化\n&r";
		}
		
	}
	
}
