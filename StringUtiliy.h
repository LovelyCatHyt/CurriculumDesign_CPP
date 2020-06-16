#pragma once
#include <string>
#include <vector>
#include <windows.h>

namespace Hyt
{
	//×Ö·û´®·Ö¸îº¯Êý
	std::vector<std::string> StringSplit(std::string str, std::string pattern);
	std::string UTF8ToGBK(const char* strUTF8);
	std::string GBKToUTF8(const char* strGBK);
}