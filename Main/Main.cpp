#include <iostream>								//cin, cout, endl
#include <iomanip>								//setw

#include "../ColorfulConsole/CloEscString.h"	//ces
#include "../json/json.hpp"						//json related
#include "../Config.h"							//Config
#include "../PolyFuncData.h"					//PolyFuncData
#include "../DataMgr.h"							//DataMgr
#include "../QueryFlow.h"
#include "../UserMgr.h"							//UserMgr, User
#include "../UserOper.h"						//UserOper

using std::cout;
using std::cin;
using std::endl;
using namespace ColorfulConsole;
using namespace nlohmann;
using namespace Hyt;
using namespace Hyt::Configration;

extern const string Configration::configFile;
extern const string Hyt::userFile;
string currentDataFile = "";

int main()
{
	Config& cfg = Config::GetConfigFromFile(configFile);
	cfg.Init();
	cout << "配置已初始化\n";

	//获取用户信息
	UserMgr users = UserMgr::GetUsersFromFile(userFile);
	UserOper::Init(&users);
	User* currentUser = NULL;
	
	UserOper::LoginOrRegister(currentUser);
	
	if (currentUser != NULL)
	{
		cout << ces << "&9欢迎" << currentUser->Name() << ces << "使用本系统!&r\n";
		currentDataFile = currentUser->DataName();
		DataMgr dataMgr = DataMgr::ReadFromFile(currentDataFile);
		bool loop = true;
		while (loop)
		{
			switch (UserOper::DoOperations(currentUser, dataMgr))
			{
			case 0:
				//正常退出
				loop = false;
				break;
			case 1:
				//注销
				if (!UserOper::LoginOrRegister(currentUser)) loop = false;
				break;
			default:
				//?
				break;
			}
		}
		cout << ces << "&a感谢使用本系统!&r";
	}
	else
	{
		cout << ces << "&8系统已退出&r\n";
	}
	
	return 0;
}