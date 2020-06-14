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


//#define DEBUG

using std::cout;
using std::cin;
using std::endl;
using namespace ColorfulConsole;
using namespace nlohmann;
using namespace Hyt;
using namespace Hyt::Configration;

const string configFile = "TestData/Config.json";
const string userFile = "TestData/Users.json";

int main()
{
	Config cfg = Config::GetConfig(configFile);
	cout << "配置已读取.\n";
	cfg.Init();
	cout << "配置初始化完成.\n";

	//获取用户数据
	UserMgr users = UserMgr::GetUsersFromFile(userFile);

	string userName;
	string pw;
	bool success;
	User* currentUser = NULL;

	UserOper::LoginOrRegister(users, currentUser);

	cout << ces << "&9欢迎" << currentUser->Name() << ces << "使用本系统!&r\n";

	DataMgr mgr = DataMgr::ReadFromFile(currentUser->DataName());
	if (Hyt::QueryFlow::YesNoQuery("是否输入数据?")) mgr.Input();
	mgr.Print();
	mgr.GenerateSamples();
	mgr.SaveToFile(currentUser->DataName());

	cfg.Save(configFile);
	/*cout << ces << "cfg saved to file: &1Config.json\n";
	cout << ces << "&rEnd of main()";*/
	return 0;
}