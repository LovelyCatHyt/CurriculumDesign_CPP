#include "User.h"
#include "libbcrypt/include/bcrypt/BCrypt.hpp"

namespace Hyt
{
	void to_json(json& j, const User& user)
	{
		j["pwHash"] = user.pwHash;
		j["userName"] = user.userName;
		j["dataName"] = user.dataName;
		j["access_cipher"] = user.access_cipher;
	}
	void from_json(const json& j, User& user)
	{
		j["pwHash"].get_to(user.pwHash);
		j["userName"].get_to(user.userName);
		j["dataName"].get_to(user.dataName);
		j["access_cipher"].get_to(user.access_cipher);
	}
	User::User(const std::string& userName, const std::string& pw, const std::string& dataName) :
		userName(userName), pwHash(BCrypt::generateHash(pw)), dataName(dataName)
	{
		GenerateSecretKey(pw);
		access_cipher = Encrypt(pw, secretKey);
	}
	User::User(const std::string& userName, const std::string& pw, const std::string& dataName, const int& access) :
		userName(userName), pwHash(BCrypt::generateHash(pw)), dataName(dataName)
	{
		GenerateSecretKey(pw);
		char temp[16];
		_itoa_s(access, temp, 16, 10);
		access_cipher = Encrypt(temp, secretKey);
	}
	bool User::Verify(const std::string& pw)
	{
		return BCrypt::validatePassword(pw, pwHash);
	}
	void User::RefreshPw(const std::string& pw)
	{
		pwHash = BCrypt::generateHash(pw);
		GenerateSecretKey(pw);
		access_cipher = Encrypt(pw, secretKey);
	}
	std::string User::Name()
	{
		return userName;
	}
	std::string User::DataName()
	{
		return this->dataName;
	}
	int User::Access(std::string ciphertext)
	{
		return atoi(Decrypt(ciphertext, secretKey).c_str());
	}
	void User::GenerateSecretKey(const std::string& pw)
	{
		//TODO
		secretKey = pw;
	}
	std::string Encrypt(const std::string& raw, const std::string& secretKet)
	{
		//TODO
		return raw;
	}
	std::string Decrypt(const std::string& ciphertext, const std::string& secretKet)
	{
		//TODO
		return ciphertext;
	}
}
