#pragma once
#include <string>
#include "json/json.hpp"

using nlohmann::json;

namespace Hyt
{
	//用户
	class User
	{
		std::string pwHash;
		std::string userName;
		std::string dataName;
		std::string access_cipher;
		std::string secretKey;
	public:
		User(const std::string& userName = "", const std::string& pw = "", const std::string& dataName = "");
		User(const std::string& userName, const std::string& pw, const std::string& dataName, const int& access);
		bool Verify(const std::string& pw);
		void RefreshPw(const std::string& pw);
		std::string Name();
		std::string DataName();
		//根据密文获取权限数, 0: Admin, 1: Normal
		int Access(std::string ciphertext = "0");
		std::string GenerateSecretKey(const std::string& pw);
		friend void to_json(json& j, const User& user);
		friend void from_json(const json& j, User& user);
		friend class UserMgr;
	};
	std::string Encrypt(const std::string& raw, const std::string& secretKey);
	std::string Decrypt(const std::string& ciphertext, const std::string& secretKey);
}

