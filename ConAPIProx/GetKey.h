#pragma once

namespace ConAPIProx
{
	enum KeyCodes { UpArrow = 38, LeftArrow = 37, DownArrow = 40, RightArrow = 39, Enter = 13, Esc = 27, End = 35, Home = 36 };
	/*
	��ȡһ������, ����������Ӧ
	����ֵΪ������ĸ��asciiֵ
	��������Ƚ�����(����������), ����ֵ��KeyCodes��
	*/
	int GetKey(void(*refreshFunc)() = 0);
	//int GetArrows(void(*refreshFunc)() = 0);
}