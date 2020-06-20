#include "GetKey.h"
#include <conio.h>
#include "Positioner.h"
//#define DEBUG
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif // DEBUG

namespace ConAPIProx
{
	int GetKey(void(*refreshFunc)())
	{
		while (!_kbhit()) if (refreshFunc != 0) refreshFunc();
		int temp;

		if ((temp = _getche()) == 224)
		{
			switch (temp = _getche())
			{
			case 71:temp = KeyCodes::Home; break;
			case 79:temp = KeyCodes::End; break;
			case 72:temp = KeyCodes::UpArrow; break;
			case 75:temp = KeyCodes::LeftArrow; break;
			case 77:temp = KeyCodes::RightArrow; break;
			case 80:temp = KeyCodes::DownArrow; break;
			}
			Positioner::ShiftCursorPosition({ -1, 0 });
			_putch(' ');
			Positioner::ShiftCursorPosition({ -1, 0 });
		}
		if (temp == KeyCodes::Esc) _putch('a'); //Esc��_getche()��ȡʱ�ᵼ�º���һ���ַ����̵� ̫�Ի���
		//Ȼ����ȥ��һ���ַ�
		Positioner::ShiftCursorPosition({ -1, 0 });
		_putch(' ');
		Positioner::ShiftCursorPosition({ -1, 0 });
		return temp;
	}
	/*int GetArrows(void(*refreshFunc)())
	{
		return 0;
	}*/
}
