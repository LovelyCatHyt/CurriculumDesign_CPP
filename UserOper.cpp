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
			//һ���û���û��, �Ǿʹ���һ��Admin��ȥ
			users->Register(adminTemplate);
		}
		string name;
		string pw;
		string dataName;
		switch (QueryFlow::ShowMenu("��¼\nע��\n�˳�", false))
		{
		case 0:
			//��¼
			success = false;
			while (!success)
			{
				cout << "�������û���:\n>";
				cin >> name;
				cout << "����������:\n>";
				cin >> pw;
				cout << ces << "&8������ҪƬ�̽�����֤, �����ĵȴ�!&r\n";
				users->Login(name, pw, success);
				if (!success)
				{
					cout << ces << "&4�û������������!&r\n";
					continue;
				}
				//��ֵ��Ӧ��User
				currentUser = &users->FindUser(name, success);
				//�ɹ���ˢ������(����ˢ����������ȷ��Կ)
				cout << ces << "&1��¼�ɹ�! ���ڳ�ʼ���û���Ϣ...&r\n";
				currentUser->RefreshPw(pw);
			}
			break;
		case 1:
			//ע��
			do
			{
				cout << "�������û���:\n>";
				cin >> name;
				if (users->ExistUser(name))
				{
					cout << ces << "�û�\"&4" << name << ces << "&r\"�Ѵ���! ����������.\n";
					success = false;
					continue;
				}
				cout << "����������:\n>";
				cin >> pw;
				dataName = name + "_data.json";
				//Ĭ�ϵ�Ȼ����ͨȨ��
				users->Register(User(name, pw, dataName, 1));
				currentUser = &users->FindUser(name, success);
			} while (!success);
			break;
		case 2:
			//�˳�
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
			cout << "��ѡ��Ҫʹ�õĹ���:\n";
			int flag = QueryFlow::ShowMenu({ "��ʾ����",
				"��������",
				"��������",
				"�������",
				"�༭����",
				"ɾ������",
				"��������",
				"�û�����",
				"ϵͳ����",
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
				if (QueryFlow::YesNoQuery("&4�Ƿ��˳�����?&r")) return 0;
				break;
			}
			if (Configration::Config::GetConfigRef().autoSave)
			{
				users->SaveToFile(userFile);
			}
			if (currentUser == NULL)
			{
				loop = false;	//��ע������ʽ�˳�
				return 1;
			}
			
		}
		return -1;	//loop���ڷǳ������ԭ����false, ����while�漣������ѭ��, �Ż��ܵ�����ط�
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
	void UserOper::ArgsFiting(DataMgr& data)
	{
		bool loop = true;
		while (loop)
		{
			cout << "��ѡ��Ҫ���еľ������:\n";
			int flag = QueryFlow::ShowMenu(vector<string>{
				"�鿴��������",
					"������������",
					"������ϲ���",
					"�������˵�  "});
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
				cout << ces << "&8������Ϲ������˳�&r\n";
				loop = false;
				break;
			}
		}
		
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
	void UserOper::SaveData(const DataMgr& data)
	{
		data.SaveToFile(currentDataFile);
		cout << ces << "&8�����ѱ���!\n&r";
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

	void UserOper::Configuring()
	{
		int flag;
		bool loop = true;
		Configration::Config& config = Configration::Config::GetConfigRef();
		while (loop)
		{
			cout << "��ѡ��Ҫ�༭��������:\n";
			flag = QueryFlow::ShowMenu("ǰ��ɫ\n����ɫ\n�Զ�����\n�˳�����");
			switch (flag)
			{
			case 0:
				config.fgColor = QueryFlow::SetColor("��ѡ���µ�ǰ��ɫ:\n");
				config.Init();
				cout << "ǰ��ɫ���޸�\n";
				break;
			case 1:
				config.bgColor = QueryFlow::SetColor("��ѡ���µı���ɫ:\n");
				config.Init();
				cout << "����ɫ���޸�\n"; 
				break;
			case 2:
				config.autoSave = QueryFlow::YesNoQuery("�Ƿ��Զ�����? ѡ���Զ�����, �����û������ݵĸĶ��󶼻��Զ�����; ������Ϣ����Ӱ��\n");
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
		cout << "��ѡ��Ҫʹ�õĹ���:\n";
		int flag = 0;
		switch (currentUser->Access())
		{
		case 0:
			//Admin
			flag = QueryFlow::ShowMenu(vector<string>{"�޸�����", "�޸��û���", "����Աģ��", "�ǳ�", "�������˵�"});
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
			flag = QueryFlow::ShowMenu(vector<string>{"�޸�����", "�޸��û���", "�ǳ�", "�������˵�"});
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
		//	//�ѵǳ�
		//	//����ɶҲ���ø�
		//}
	}
	void UserOper::ChangePW(User& currentUser, UserMgr& users)
	{
		string pw_a = "", pw_b = "";
		while (true)
		{
			cout << "������������:\n>";
			cin >> pw_a;
			cout << "��������һ������ȷ��:\n>";
			cin >> pw_b;
			if (pw_a == pw_b) break;
			//ûbreak, ����һ��
			cout << "�����������벻ͬ!";
		}
		currentUser.RefreshPw(pw_a);
		cout << "�������޸�!\n";
	}
	void UserOper::ChangeName(User& currentUser, UserMgr& users)
	{
		string temp;
		cout << "���������û���:\n>";
		cin >> temp;
		cout << ces << "�û������޸�Ϊ&6\"" << currentUser.Name(temp) << ces << "\"&r\n";
		if (Configration::Config::GetConfigRef().autoSave)
		{
			users.SaveToFile(userFile);
		}
	}
	void UserOper::Logout(User*& currentUser)
	{
		if (QueryFlow::YesNoQuery("�Ƿ��˳��˺�?"))
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
			cout << "��ѡ��Ҫ���е��û�����: \n";
			flag = QueryFlow::ShowMenu("��ʾ�û���Ϣ\nɾ���û�\n�˳��û�����");
			switch (flag)
			{
			case 0:
				cout << "��ǰ���ڵ��û�����: \n";
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
		cout << "��ǰ���ڵ��û�����: \n";
		mgr.PrintUsers();
		int index = QueryFlow::CheckedInput_int("��ѡ��Ҫɾ�����û��ı��:\n>", "&4�������ʹ���!&r\n", "&4�û����Խ��!\n&r", [&](int num) {
			return num >= 0 && num < mgr.UserCount(); });
		if (index == mgr.GetUserIndex(currentUserName))
		{
			//����ɾ�Լ�
			cout << ces << "&4����: ����ɾ���Լ�!\n";
			return;
		}
		std::ostringstream ostr;
		ostr << "ȷ��Ҫɾ�����Ϊ&6[" << index << "]&r���û���?";	ostr.flush();
		if (QueryFlow::YesNoQuery(ostr.str()))
		{
			mgr.DeleteUser(index);
			cout << "&8���û���ɾ��\n&r";
		}
		else
		{
			cout<<ces << "&8�û��б�δ�����仯\n&r";
		}
		
	}
	
}
