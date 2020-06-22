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
	cout << "���ó�ʼ�����.\n";

	//��ȡ�û�����
	UserMgr users = UserMgr::GetUsersFromFile(userFile);
	UserOper::Init(&users);
	User* currentUser = NULL;
	
	UserOper::LoginOrRegister(currentUser);
	
	if (currentUser != NULL)
	{
		cout << ces << "&9��ӭ" << currentUser->Name() << ces << "ʹ�ñ�ϵͳ!&r\n";
		currentDataFile = currentUser->DataName();
		DataMgr dataMgr = DataMgr::ReadFromFile(currentDataFile);
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