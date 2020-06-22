#include <iostream>
#include <string>
#include "ColorfulConsole/CloEscString.h"
#include "UserMgr.h"
#include "FileIO.h"
#include "json/json.hpp"

using ColorfulConsole::ces;
using std::cout;
extern std::string userFile;

namespace Hyt
{
	void UserMgr::AutoSaveIfConfigered()
	{
	}
	UserMgr::UserMgr() : usersList(0)
	{
	}
	UserMgr UserMgr::GetUsersFromFile(std::string fileName)
	{
		try
		{

		return json::parse(FileInOut::ReadAll(fileName)).get<UserMgr>();
		}
		catch(nlohmann::json::exception e)
		{
			std::cout << "Excption: " << e.what() << '\n';
			return UserMgr();
		}
	}
	void UserMgr::SaveToFile(std::string fileName)
	{
		FileInOut::WriteAll(fileName, nlohmann::json(*this).dump(4));
	}
	bool UserMgr::Register(const User& newUser)
	{
		if (ExistUser(newUser.userName))
		{
			//已存在则返回false
			return false;
		}
		else
		{
			usersList.push_back(newUser);
			AutoSaveIfConfigered();
			return true;
		}
	}
	User& UserMgr::operator[](int index)
	{
		return usersList[index];
	}
	int UserMgr::GetUserIndex(std::string name)
	{
		//假定名字不重复
		for (int i = 0; i < usersList.size(); i++)
		{
			if (usersList[i].userName == name) return i;
		}
		//不存在? 那就是-1
		return -1;
	}
	bool UserMgr::ExistUser(std::string name)
	{
		for (auto each : usersList)
		{
			if (each.userName == name) return true;
		}
		return false;
	}

	User& UserMgr::FindUser(std::string name, bool& success)
	{
		for (int i = 0; i < usersList.size(); i++)
		{
			if (usersList[i].userName == name)
			{
				success = true;
				return usersList[i];
			}
		}
		success = false;
		return *(User*)(NULL);
	}

	User& UserMgr::Login(std::string userName, std::string pw, bool& success)
	{
		User& temp = FindUser(userName, success);
		if (!success)
		{
			return *(User*)NULL;
		}
		if (temp.Verify(pw))
		{
			success = true;
			return temp;
		}
		else
		{
			success = false;
			return *(User*)NULL;
		}
	}

	void UserMgr::PrintUsers()
	{
		for (int i = 0; i < usersList.size(); i++)
		{
			std::cout << ces << "&6[" << i << ces << "]&r " << usersList[i].userName << '\n';
		}
	}

	void UserMgr::DeleteUser(int index)
	{
		//先检查越界再删除
		if (index > 0 && index < usersList.size()) usersList.erase(usersList.begin() + index);
		else
		{
			cout << ces << "&4错误: 用户编号越界!\n";
		}
		AutoSaveIfConfigered();
	}

	size_t UserMgr::UserCount()
	{
		return usersList.size();
	}
	
	void to_json(nlohmann::json& j, const UserMgr& mgr)
	{
		j["users"] = mgr.usersList;
	}

	void from_json(const nlohmann::json& j, UserMgr& mgr)
	{
		mgr.usersList = j["users"].get<std::vector<User>>();
	}

}
