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
		//��ʾ�˵���ִ������, ����true������ִ�����, ����false��ѡ�����˳�ϵͳ
		static void DoOperations(User& currentUser, DataMgr& data);
		//��������
		static void DataInput(const User& currentUser, DataMgr& data);
		//��������
		static void SearchData(const User& currentUser, const DataMgr& data);
		//�����������
		static void GenerateFitArgs(const User& currentUser, DataMgr& data);
		//�༭����
		static void EditData(const User& currentUser, DataMgr& data);
	};
}

