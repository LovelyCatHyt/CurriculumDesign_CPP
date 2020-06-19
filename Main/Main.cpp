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
//#define AUTOADMINLOGIN

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
	cout << "�����Ѷ�ȡ.\n";
	cfg.Init();
	cout << "���ó�ʼ�����.\n";

	//��ȡ�û�����
	UserMgr users = UserMgr::GetUsersFromFile(userFile);
	UserOper::Init(&users);
	User* currentUser = NULL;
	
#ifdef AUTOADMINLOGIN
	bool temp;
	currentUser = &users.Login("Admin", "114514", temp);
	cout << ces << "&4[Auto Admin Login]&r\n";
#else
	UserOper::LoginOrRegister(currentUser);
#endif // AUTOADMINLOGIN

	

	cout << ces << "&9��ӭ" << currentUser->Name() << ces << "ʹ�ñ�ϵͳ!&r\n";

	DataMgr dataMgr = DataMgr::ReadFromFile(currentUser->DataName());
	UserOper::DoOperations(currentUser, dataMgr);

	dataMgr.SaveToFile(currentUser->DataName());
	cout << ces << "&8����ʽ�����ѱ���\n&r";
	cfg.Save(configFile);
	cout << ces << "&8���������ѱ���\n&r";

	cout << ces << "&a��лʹ�ñ�ϵͳ!&r";
	return 0;
}