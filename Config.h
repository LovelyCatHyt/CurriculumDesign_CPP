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
			//����ɫ
			Color bgColor;
			//ǰ��ɫ
			Color fgColor;
			//�Զ�����
			bool autoSave;
			//��ʼ��
			void Init();
			//���浽·����
			void Save(string fullPath);
			static Config& GetConfigRef();
			static Config& GetConfigFromFile(string fullPath);
		};
		void from_json(const json& j, Config& cfg);
		void to_json(json& j, const Config& cfg);
	}
}

