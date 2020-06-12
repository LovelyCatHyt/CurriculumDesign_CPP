#pragma once
#include <string>
#include "json/json.hpp"

using nlohmann::json;

namespace Hyt
{
	//”√ªß
	class User
	{
		std::string pwHash;
		std::string userName;
		std::string dataName;
	public:
		User(const std::string& userName = "", const std::string& pw = "", const std::string& dataName = "");
		bool Verrify(const std::string& pw);
		void RefreshPw(const std::string& pw);
		std::string Name();
		std::string DataName();
		friend void to_json(json& j, const User& user);
		friend void from_json(const json& j, User& user);
		friend class UserMgr;
	};
}

