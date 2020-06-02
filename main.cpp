#include <iostream>								//cin, cout, endl
#include <iomanip>								//setw

#include "ColorfulConsole/ForeColorProxy.h"		//ForeColorProxy
#include "ColorfulConsole/GlobalEnvironment.h"	//GlobalEnvironment
#include "json/json.hpp"						//json related
#include "Config.h"								//Config

using std::cout;
using std::cin;
using std::endl;
using namespace ColorfulConsole;
using namespace nlohmann;
using namespace Hyt::Configration;

int main()
{
	Config cfg = Config::GetConfig("Config.json");
	cout << "cfg Got.\n";
	cfg.Init();
	cout << "cfg Initialed.\n";
	cfg.Save("Config.json");
	cout << "cfg saved to file: " << ForeColorProxy(Color(true, false, false, false)) << "Config.json\n";
	cout << GlobalEnvironment::GetFore() << "End of main()";
	return 0;
}