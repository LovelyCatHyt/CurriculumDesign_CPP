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
		Config Config::config = Config();
		void from_json(const json& j, Config& cfg)
		{
			cfg.bgColor = j["bgColor"];
			cfg.fgColor = j["fgColor"];
			cfg.autoSave = j["autoSave"];
		}
		void to_json(json& j, const Config& cfg)
		{
			j["bgColor"] = cfg.bgColor;
			j["fgColor"] = cfg.fgColor;
			j["autoSave"] = cfg.autoSave;
		}
		Config::Config()
		{
			bgColor = Color(1, 1, 1, 1);
			fgColor = Color(0, 0, 0, 0);
			autoSave = true;
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
		Config& Config::GetConfigRef()
		{
			return config;
		}
		Config& Config::GetConfigFromFile(string fullPath)
		{
			try
			{
				config = json::parse(FileInOut::ReadAll(fullPath));
			}
			catch (const nlohmann::json::exception&)
			{
				std::cout << "Cannot parse the string into json object!\n";
			}
			
			return config;
		}
	}
}
