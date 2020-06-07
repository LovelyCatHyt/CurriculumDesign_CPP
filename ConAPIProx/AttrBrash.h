#pragma once
#include "Rect.h"
#include "../ColorfulConsole/GlobalEnvironment.h"
#include "../ColorfulConsole/Color.h"

namespace ConAPIProx
{
	class AttrBrash
	{
		static HANDLE GetHandle();
	public:
		static void SetRectColor(const Rect& r, const WORD& attr);
		static void SetRectForeColor(const Rect& r, const ColorfulConsole::Color& c);
		static void SetRectBackColor(const Rect& r, const ColorfulConsole::Color& c);
	};
}