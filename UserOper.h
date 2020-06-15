#pragma once
#include "User.h"
#include "UserMgr.h"
#include "PolyFuncData.h"

namespace Hyt
{

	//�û�����: ���û������ľ�̬��
	static class UserOper
	{
	public:
		/*
		��¼��ע��
		currentUser: ���ڱ��浱ǰ�û���ָ�������
		*/
		static void LoginOrRegister(UserMgr& mgr, User*& currentUser, bool& success);
		static bool LoginOrRegister(UserMgr& mgr, User*& currentUser);
		//��������
		static void DataInput(const User& currentUser, PolyFuncData& data);
		//��������
		static void SearchData(const User& currentUser, const PolyFuncData& data);
		//�����������
		static void GenerateFitArgs(const User& currentUser, PolyFuncData& data);
		//�༭����
		static void EditData(const User& currentUser, PolyFuncData& data);
	};
}

