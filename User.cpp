#include "User.h"
#include "libbcrypt/include/bcrypt/BCrypt.hpp"

namespace Hyt
{
	void to_json(json& j, const User& user)
	{
		j["pwHash"] = user.pwHash;
		j["userName"] = user.userName;
		j["dataName"] = user.dataName;
	}
	void from_json(const json& j, User& user)
	{
		j["pwHash"].get_to(user.pwHash);
		j["userName"].get_to(user.userName);
		j["dataName"].get_to(user.dataName);
	}
	User::User(const std::string& userName, const std::string& pw, const std::string& dataName) : userName(userName), pwHash(BCrypt::generateHash(pw)), dataName(dataName)
	{
	}
	bool User::Verrify(const std::string& pw)
	{
		return BCrypt::validatePassword(pw, pwHash);
	}
	void User::RefreshPw(const std::string& pw)
	{
		pwHash = BCrypt::generateHash(pw);
	}
	std::string User::Name()
	{
		return userName;
	}
	std::string User::DataName()
	{
		return this->dataName;
	}
}
