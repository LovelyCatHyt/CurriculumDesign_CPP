#include <iostream>								//cin, cout, endl
#include <iomanip>								//setw

#include "ColorfulConsole/CloEscString.h"		//ces
#include "json/json.hpp"						//json related
#include "Config.h"								//Config
#include "PolyFuncData.h"						//PolyFuncData
#include "DataMgr.h"							//DataMgr

using std::cout;
using std::cin;
using std::endl;
using namespace ColorfulConsole;
using namespace nlohmann;
using namespace Hyt::Configration;
using Hyt::PolyFuncData;
using Hyt::DetailLevel;
using Hyt::DataMgr;

int main()
{
	Config cfg = Config::GetConfig("Config.json");
	cout << "配置已读取.\n";
	cfg.Init();
	cout << "配置初始化完成.\n";

	DataMgr mgr = DataMgr();
	mgr.Input();
	mgr.SaveToFile("Data.json");

	cfg.Save("Config.json");
	cout << ces << "cfg saved to file: &1Config.json\n";
	cout << ces << "&rEnd of main()";
	return 0;
}