#pragma once
#include "User.h"
#include "UserMgr.h"
#include "PolyFuncData.h"

namespace Hyt
{

	//用户操作: 与用户交互的静态类
	static class UserOper
	{
	private:
		//用户管理器 (本来想用引用的, 但是静态类不好初始化, 就写成指针了)
		static UserMgr* users;
	public:
		//初始化: 传入一个UserMgr
		static void Init(UserMgr* usersPtr);
		/*
		登录或注册
		currentUser: 用于保存当前用户的指针的引用
		*/
		static void LoginOrRegister(User*& currentUser, bool& success);
		static bool LoginOrRegister(User*& currentUser);
		/*
		显示菜单并执行任务
		0: 正常退出
		1: 账户登出
		其他: 意外情况发生
		*/
		static int DoOperations(User*& currentUser, DataMgr& data);
	private:
		//数据管理部分	-----------------------------------------------------------------
		//数据输入
		static void DataInput(DataMgr& data);
		//数据搜索
		static void SearchData(const DataMgr& data);
		//生成随机数据
		static void ArgsFiting(DataMgr& data);
		//编辑数据
		static void EditData(DataMgr& data);
		//打印数据
		static void ShowData(const DataMgr& data);
		//保存数据
		static void SaveData(const DataMgr& data);
		//删除数据
		static void DeleteData(DataMgr& data);
		//设置部分		-----------------------------------------------------------------
		static void Configuring();
		static void SetBgColor();
		static void SetFgColor();
		//用户管理部分	-----------------------------------------------------------------
		//用户中心
		static void UsersCenter(User*& currentUser, UserMgr& users);
		//改密码
		static void ChangePW(User& currentUser, UserMgr& users);
		//改用户名
		static void ChangeName(User& currentUser, UserMgr& users);
		//登出
		static void Logout(User*& currentUser);
		//管理员模块(当然只有Admin才能使用)
		static void ManagerModule(User& currentUser, UserMgr& mgr);
		static void DeleteUser(const std::string& currentUserName, UserMgr& mgr);
	};
}

