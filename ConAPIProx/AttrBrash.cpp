#include "AttrBrash.h"
#include <Windows.h>
#include "../ColorfulConsole/TextAttribute.h"

namespace ConAPIProx
{
	HANDLE AttrBrash::GetHandle()
	{
		static HANDLE handle = NULL;
		if (handle == NULL) handle = GetStdHandle(STD_OUTPUT_HANDLE);
		return handle;
	}
	void AttrBrash::SetRectColor(const Rect& r, const WORD& attr)
	{
		COORD cdCurrent;
		DWORD dwTemp;
		for (cdCurrent = r.leftUp; cdCurrent.Y <= r.rightDown.y; cdCurrent.Y++)
		{
			FillConsoleOutputAttribute(GetHandle(), attr, r.Width(), cdCurrent, &dwTemp);
		}
	}
	void AttrBrash::SetRectForeColor(const Rect& r, const ColorfulConsole::Color& c)
	{
		using namespace ColorfulConsole;
		SetRectColor(r, (WORD)TextAttribute::WarpedTextAttr(c, GlobalEnvironment::GetBack()));
	}
	void AttrBrash::SetRectBackColor(const Rect& r, const ColorfulConsole::Color& c)
	{
		using namespace ColorfulConsole;
		SetRectColor(r, (WORD)TextAttribute::WarpedTextAttr(GlobalEnvironment::GetFore(), c));
	}
}