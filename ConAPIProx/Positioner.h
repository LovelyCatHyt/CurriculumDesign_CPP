#pragma once
#include <Windows.h>
#include "Position.h"

namespace ConAPIProx
{
	//定位器: 方便控制控制台的光标位置
	class Positioner
	{
		static HANDLE GetHandle();
	public:
		static void SetCursorPosition(const Position& pos);
		static void ShiftCursorPosition(const Position& delta);
		static Position GetCursorPosition();		
	};
}

