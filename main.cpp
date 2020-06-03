#include <iostream>								//cin, cout, endl
#include <iomanip>								//setw

#include "ColorfulConsole/ForeColorProxy.h"		//ForeColorProxy
#include "ColorfulConsole/GlobalEnvironment.h"	//GlobalEnvironment
#include "json/json.hpp"						//json related
#include "Config.h"								//Config
#include "PolyFuncData.h"

using std::cout;
using std::cin;
using std::endl;
using namespace ColorfulConsole;
using namespace nlohmann;
using namespace Hyt::Configration;
using Hyt::PolyFuncData;

int main()
{
	Config cfg = Config::GetConfig("Config.json");
	cout << "cfg Got.\n";
	cfg.Init();
	cout << "cfg Initialed.\n";

	PolyFuncData data;
	data.Input(true);
	json data_json(data);
	cout << "输入的数据转为json如下:\n" << std::setw(4) << data_json;
	cout << "再转回原数据, 而后导出json为:" << std::setw(4) << json(data_json.get<PolyFuncData>());
	
	cfg.Save("Config.json");
	cout << "cfg saved to file: " << ForeColorProxy(Color(true, false, false, false)) << "Config.json\n";
	cout << GlobalEnvironment::GetFore() << "End of main()";
	return 0;
}