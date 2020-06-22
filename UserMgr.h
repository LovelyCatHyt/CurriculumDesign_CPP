#pragma once
#include "User.h"
#include <vector>
#include "json/json.hpp"

namespace Hyt
{
	const std::string userFile = "TestData/Users.json";
	//�û�������
	class UserMgr
	{
		std::vector<User> usersList;
		//���������Զ������򱣴�
		void AutoSaveIfConfigered();
	public: 
		UserMgr();
		static UserMgr GetUsersFromFile(std::string fileName);
		void SaveToFile(std::string fileName);
		//ע��, �û��Ѵ����򷵻�false
		bool Register(const User& newUser);
		//����ĳ���û�
		User& operator[](int index);
		//ͨ���û�����ȡ�û����
		int GetUserIndex(std::string name);
		//�����û�
		bool ExistUser(std::string name);
		//Ѱ���û�
		User& FindUser(std::string name, bool& success);
		//��¼, ��¼�ɹ��򷵻�true, userΪ��ǰ�û���ָ��
		User& Login(std::string userName, std::string pw, bool& success);
		//��ӡ�û���Ϣ, ����ź��û���
		void PrintUsers();
		//ɾ���û�
		void DeleteUser(int index);
		size_t UserCount();
		friend void to_json(nlohmann::json& j, const UserMgr& mgr);
		friend void from_json(const nlohmann::json& j, UserMgr& mgr);
	};
}

