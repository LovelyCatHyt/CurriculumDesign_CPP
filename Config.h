#pragma once
#include <string>					//string
#include "json/json.hpp"
#include "ColorfulConsole/Color.h"

using std::string;
using namespace nlohmann;
using namespace ColorfulConsole;

namespace Hyt
{
	namespace Configration
	{
		const string configFile = "Config.json";
		class Config
		{
			static Config config;
		public:
			Config();
			//背景色
			Color bgColor;
			//前景色
			Color fgColor;
			//自动保存
			bool autoSave;
			//初始化
			void Init();
			//保存到路径中
			void Save(string fullPath);
			static Config& GetConfigRef();
			static Config& GetConfigFromFile(string fullPath);
		};
		void from_json(const json& j, Config& cfg);
		void to_json(json& j, const Config& cfg);
	}
}

