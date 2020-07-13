#include "User.h"

//#include <random>
#include <sstream>
#include "libbcrypt/include/bcrypt/BCrypt.hpp"
#include "AES/AES.h"
#include "cpp-base64/base64.h"
#include "PicoSHA2/picosha2.h"

using std::stringstream;

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
		access_cipher = Encrypt("1", secretKey);
	}
	User::User(const std::string& userName, const std::string& pw, const std::string& dataName, const int& access) :
		userName(userName), pwHash(BCrypt::generateHash(pw)), dataName(dataName)
	{
		GenerateSecretKey(pw);
		stringstream str;
		str << access<<' '; //要加上这个空格, 否则会有非常魔幻的问题出现
		access_cipher = Encrypt(str.str(), secretKey);
	}
	bool User::Verify(const std::string& pw)
	{
		return BCrypt::validatePassword(pw, pwHash);
	}
	void User::RefreshPw(const std::string& pw)
	{
		pwHash = BCrypt::generateHash(pw);
		GenerateSecretKey(pw);
		int accessBefore = Access();
		stringstream str;
		str << accessBefore << ' '; //要加上这个空格, 否则会有非常魔幻的问题出现
		access_cipher = Encrypt(str.str(), secretKey);
	}
	std::string User::Name()
	{
		return userName;
	}
	std::string User::Name(std::string newName)
	{
		return userName = newName;
	}
	std::string User::DataName()
	{
		return this->dataName;
	}
	int User::Access()
	{
		return atoi(Decrypt(access_cipher, secretKey).c_str());
	}
	std::string User::GenerateSecretKey(const std::string& pw)
	{
		std::vector<unsigned char> hash(picosha2::k_digest_size);
		picosha2::hash256(pw.begin(), pw.end(), hash.begin(), hash.end());		
		return secretKey = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
	}
	std::string Encrypt(const std::string& raw, const std::string& secretKey)
	{
		unsigned char* plain = (unsigned char*)raw.c_str();
		unsigned int plainLen = raw.length();
		unsigned char* key = (unsigned char*)secretKey.c_str();
		
		unsigned int outLen = 0;

		AES aes(256);
		unsigned char* c = aes.EncryptECB(plain, plainLen, key, outLen);
		std::string result = std::string((char*)c);
		
		delete[] c;
		
		return base64_encode(result);
	}
	std::string Decrypt(const std::string& ciphertext, const std::string& secretKey)
	{
		std::string chipher = base64_decode(ciphertext);
		unsigned char* content = (unsigned char*)(chipher).c_str();
		unsigned int contentLen = chipher.size();
		unsigned char* key = (unsigned char*)secretKey.c_str();

		AES aes(256);
		unsigned char* c = aes.DecryptECB(content, contentLen << 2, key);//别问, 问就是玄学

		std::string result = std::string((char*)c);
		
		delete[] c;
		
		return result;
	}
}
