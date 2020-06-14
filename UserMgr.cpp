#include "UserMgr.h"
#include "FileIO.h"
#include "json/json.hpp"
#include <iostream>

namespace Hyt
{
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
			//´æÔÚÔò·µ»Øfalse
			return false;
		}
		else
		{
			usersList.push_back(newUser);
			return true;
		}
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
