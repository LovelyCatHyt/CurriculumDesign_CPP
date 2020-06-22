#pragma once
#include "User.h"
#include <vector>
#include "json/json.hpp"

namespace Hyt
{
	const std::string userFile = "TestData/Users.json";
	//用户管理器
	class UserMgr
	{
		std::vector<User> usersList;
		//若已设置自动保存则保存
		void AutoSaveIfConfigered();
	public: 
		UserMgr();
		static UserMgr GetUsersFromFile(std::string fileName);
		void SaveToFile(std::string fileName);
		//注册, 用户已存在则返回false
		bool Register(const User& newUser);
		//返回某个用户
		User& operator[](int index);
		//通过用户名获取用户编号
		int GetUserIndex(std::string name);
		//存在用户
		bool ExistUser(std::string name);
		//寻找用户
		User& FindUser(std::string name, bool& success);
		//登录, 登录成功则返回true, user为当前用户的指针
		User& Login(std::string userName, std::string pw, bool& success);
		//打印用户信息, 仅序号和用户名
		void PrintUsers();
		//删除用户
		void DeleteUser(int index);
		size_t UserCount();
		friend void to_json(nlohmann::json& j, const UserMgr& mgr);
		friend void from_json(const nlohmann::json& j, UserMgr& mgr);
	};
}

