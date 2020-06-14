#pragma once
#include "User.h"
#include "UserMgr.h"

namespace Hyt
{

	//用户操作
	class UserOper
	{
	public:
		/*
		登录或注册
		currentUser: 用于保存当前用户的指针的引用
		*/
		static void LoginOrRegister(UserMgr& mgr, User*& currentUser, bool& success);
		static bool LoginOrRegister(UserMgr& mgr, User*& currentUser);
	};
}

