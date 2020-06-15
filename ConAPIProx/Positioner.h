#pragma once
#include <Windows.h>
#include "Position.h"

namespace ConAPIProx
{
	//��λ��: ������ƿ���̨�Ĺ��λ��
	class Positioner
	{
		static HANDLE GetHandle();
	public:
		static void SetCursorPosition(const Position& pos);
		static void ShiftCursorPosition(const Position& delta);
		static Position GetCursorPosition();		
	};
}

