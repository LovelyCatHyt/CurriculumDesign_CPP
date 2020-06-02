#pragma once

#include "ColorfulConsole/Color.h"
#include "json/json.hpp"

using ColorfulConsole::Color;
using namespace nlohmann;

namespace ColorfulConsole
{
	void __cdecl to_json(json& j, const Color& color);
	void __cdecl from_json(const json& j, Color& color);
}