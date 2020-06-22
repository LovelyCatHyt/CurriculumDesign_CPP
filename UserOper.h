#pragma once
#include "User.h"
#include "UserMgr.h"
#include "PolyFuncData.h"

namespace Hyt
{

	//�û�����: ���û������ľ�̬��
	static class UserOper
	{
	private:
		//�û������� (�����������õ�, ���Ǿ�̬�಻�ó�ʼ��, ��д��ָ����)
		static UserMgr* users;
	public:
		//��ʼ��: ����һ��UserMgr
		static void Init(UserMgr* usersPtr);
		/*
		��¼��ע��
		currentUser: ���ڱ��浱ǰ�û���ָ�������
		*/
		static void LoginOrRegister(User*& currentUser, bool& success);
		static bool LoginOrRegister(User*& currentUser);
		/*
		��ʾ�˵���ִ������
		0: �����˳�
		1: �˻��ǳ�
		����: �����������
		*/
		static int DoOperations(User*& currentUser, DataMgr& data);
	private:
		//���ݹ�����-----------------------------------------------------------------
		//��������
		static void DataInput(DataMgr& data);
		//��������
		static void SearchData(const DataMgr& data);
		//�����������
		static void ArgsFiting(DataMgr& data);
		//�༭����
		static void EditData(DataMgr& data);
		//��ӡ����
		static void ShowData(const DataMgr& data);
		//ɾ������
		static void DeleteData(DataMgr& data);
		//����
		static void Configuring();
		//�û�������-----------------------------------------------------------------
		//�û�����
		static void UsersCenter(User*& currentUser, UserMgr& users);
		//������
		static void ChangePW(User& currentUser, UserMgr& users);
		//���û���
		static void ChangeName(User& currentUser, UserMgr& users);
		//�ǳ�
		static void Logout(User*& currentUser);
		//����Աģ��(��Ȼֻ��Admin����ʹ��)
		static void ManagerModule(User& currentUser, UserMgr& mgr);
		static void DeleteUser(const std::string& currentUserName, UserMgr& mgr);
	};
}

