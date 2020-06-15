#pragma once
#include "User.h"
#include "UserMgr.h"
#include "PolyFuncData.h"

namespace Hyt
{

	//用户操作: 与用户交互的静态类
	static class UserOper
	{
	public:
		/*
		登录或注册
		currentUser: 用于保存当前用户的指针的引用
		*/
		static void LoginOrRegister(UserMgr& mgr, User*& currentUser, bool& success);
		static bool LoginOrRegister(UserMgr& mgr, User*& currentUser);
		//显示菜单并执行任务, 返回true则任务执行完毕, 返回false则选择了退出系统
		static void DoOperations(User& currentUser, DataMgr& data);
		//数据输入
		static void DataInput(const User& currentUser, DataMgr& data);
		//数据搜索
		static void SearchData(const User& currentUser, const DataMgr& data);
		//生成随机数据
		static void GenerateFitArgs(const User& currentUser, DataMgr& data);
		//编辑数据
		static void EditData(const User& currentUser, DataMgr& data);
	};
}

