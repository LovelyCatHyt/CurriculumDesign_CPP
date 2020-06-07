#include "Positioner.h"

namespace ConAPIProx
{
	HANDLE Positioner::GetHandle()
	{
		static HANDLE handle = NULL;
		if(handle == NULL) handle = GetStdHandle(STD_OUTPUT_HANDLE);
		return handle;
	}

	void Positioner::SetCursorPosition(const Position& pos)
	{
		SetConsoleCursorPosition(GetHandle(), pos);
	}
	void Positioner::ShiftCursorPosition(const Position& delta)
	{
		SetCursorPosition(delta + GetCursorPosition());
	}
	Position Positioner::GetCursorPosition()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		GetConsoleScreenBufferInfo(GetHandle(), &csbiInfo);
		return csbiInfo.dwCursorPosition;
	}
}