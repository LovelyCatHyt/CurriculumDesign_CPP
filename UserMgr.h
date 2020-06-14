#pragma once
#include "User.h"
#include <vector>
#include "json/json.hpp"

namespace Hyt
{
	//用户管理器
	class UserMgr
	{
		std::vector<User> usersList;
	public: 
		UserMgr();
		static UserMgr GetUsersFromFile(std::string fileName);
		void SaveToFile(std::string fileName);
		//注册, 用户已存在则返回false
		bool Register(const User& newUser);
		//存在用户
		bool ExistUser(std::string name);
		//寻找用户
		User& FindUser(std::string name, bool& success);
		//登录, 登录成功则返回true, user为当前用户的指针
		User& Login(std::string userName, std::string pw, bool& success);
		size_t UserCount();
		friend void to_json(nlohmann::json& j, const UserMgr& mgr);
		friend void from_json(const nlohmann::json& j, UserMgr& mgr);
	};
}

