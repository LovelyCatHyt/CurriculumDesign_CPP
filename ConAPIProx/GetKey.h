#pragma once

namespace ConAPIProx
{
	enum KeyCodes { UpArrow = 38, LeftArrow = 37, DownArrow = 40, RightArrow = 39, Enter = 13, Esc = 27, End = 35, Home = 36 };
	/*
	获取一个按键, 按下立即响应
	返回值为按下字母的ascii值
	如果按键比较特殊(如上下左右), 返回值在KeyCodes中
	*/
	int GetKey(void(*refreshFunc)() = 0);
	//int GetArrows(void(*refreshFunc)() = 0);
}