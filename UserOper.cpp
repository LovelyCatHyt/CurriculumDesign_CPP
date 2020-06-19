#include "UserOper.h"
#include "ColorfulConsole/CloEscString.h"
#include "QueryFlow.h"
#include "DataMgr.h"

using std::string;
using ColorfulConsole::ces;

namespace Hyt
{
	UserMgr* UserOper::users = NULL;
	User adminTemplate = User("Admin", "123456", "TestData/Data1.json");
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
				cout << ces << "&8������ҪƬ�̽�����֤, �����ĵȴ�!\n";
				users->Login(name, pw, success);
				if (!success)
				{
					cout << ces << "&4�û������������!&r\n";
					continue;
				}
				currentUser = &users->FindUser(name, success);
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
			currentUser == NULL;
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
				"�û�����",
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
				UsersCenter(currentUser, *users);
				break;
			case 7:
				if (QueryFlow::YesNoQuery("&4�Ƿ��˳�����?&r")) return 0;
				break;
			default:
				break;
			}
			if (currentUser == NULL)
			{
				loop = false;	//��ע������ʽ�˳�
				return 1;
			}
				
		}
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
			data.ShowSamples();
			break;
		case 2:
			data.FitArgs();
			break;
		default:
			cout << ces << "&8������Ϲ������˳�\n";
			break;
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
				ChangePW(*currentUser);
				break;
			case 1:
				ChangeName(*currentUser);
				break;
			case 2:
				ManagerModule(*currentUser);
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
				ChangePW(*currentUser);
				break;
			case 1:
				ChangeName(*currentUser);
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
	void UserOper::ChangePW(User& currentUser)
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
	void UserOper::ChangeName(User& currentUser)
	{
		//TODO
		string temp;
		cout << "���������û���:\n>";
		cin >> temp;
		cout << ces << "�û������޸�Ϊ&6\"" << currentUser.Name(temp) << ces << "\"&r\n";
	}
	void UserOper::Logout(User*& currentUser)
	{
		if (QueryFlow::YesNoQuery("�Ƿ��˳��˺�?"))
		{
			currentUser = NULL;
		}
	}
	void UserOper::ManagerModule(User& currentUser)
	{
		//TODO
		cout << "ManagerModule not implemented yet.\n";
	}
}
