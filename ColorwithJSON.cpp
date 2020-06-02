#include "ColorwithJSON.h"

namespace ColorfulConsole
{
	void __cdecl to_json(json& j, const Color& color)
	{
		j["r"] = color.red;
		j["g"] = color.green;
		j["b"] = color.blue;
		j["i"] = color.intense;
	}

	void __cdecl from_json(const json& j, Color& color)
	{
		color.red = j["r"];
		color.green = j["g"];
		color.blue = j["b"];
		color.intense = j["i"];
	}

}