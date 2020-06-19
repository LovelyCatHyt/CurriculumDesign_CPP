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

	
	if (currentUser != NULL)
	{
		cout << ces << "&9��ӭ" << currentUser->Name() << ces << "ʹ�ñ�ϵͳ!&r\n";
		string dataFile = currentUser->DataName();
		DataMgr dataMgr = DataMgr::ReadFromFile(dataFile);
		bool loop = true;
		while (loop)
		{
			switch (UserOper::DoOperations(currentUser, dataMgr))
			{
			case 0:
				//�����˳�
				loop = false;
				break;
			case 1:
				//�˳��˻�
				if (!UserOper::LoginOrRegister(currentUser)) loop = false;
				break;
			default:
				//?
				break;
			}
		}
		dataMgr.SaveToFile(dataFile);
		cout << ces << "&8����ʽ�����ѱ���\n&r";
		users.SaveToFile(userFile);
		cout << ces << "&8�û���Ϣ�ѱ���\n&r";
		cfg.Save(configFile);
		cout << ces << "&8���������ѱ���\n&r";
		
		cout << ces << "&a��лʹ�ñ�ϵͳ!&r";
	}
	else
	{
		cout << ces << "&8ϵͳ���˳�&r\n";
	}
	
	return 0;
}