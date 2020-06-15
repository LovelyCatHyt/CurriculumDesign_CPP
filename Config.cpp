#include "Config.h"								//Self

#include "FileIO.h"								//Read/Write
#include <iostream>								//cout
#include <string>								//string
#include "json/json.hpp"
#include "ColorwithJSON.h"						//json & Color
#include "ColorfulConsole/GlobalEnvironment.h"	//GlobalEnvironment

using namespace ColorfulConsole;
using std::string;

namespace Hyt
{
	namespace Configration
	{
		void from_json(const json& j, Config& cfg)
		{
			cfg.bgColor = j["bgColor"];
			cfg.fgColor = j["fgColor"];
		}
		void to_json(json& j, const Config& cfg)
		{
			j["bgColor"] = cfg.bgColor;
			j["fgColor"] = cfg.fgColor;
		}
		void Config::Init()
		{
			GlobalEnvironment::Init(fgColor, bgColor);
		}
		void Config::Save(string fullPath)
		{
			json j = *this;
			FileInOut::WriteAll(fullPath, j.dump(4));
		}
		Config Config::GetConfig(string fullPath)
		{
			Config temp;
			try
			{
				temp = json::parse(FileInOut::ReadAll(fullPath));
			}
			catch (const nlohmann::json::exception&)
			{
				std::cout << "Cannot parse the string into json object!\n";
			}
			
			return temp;
		}
	}
}
