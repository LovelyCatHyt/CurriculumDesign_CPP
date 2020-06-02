#pragma once
#include <string>	//string

using std::string;

namespace Hyt
{
	namespace FileInOut
	{
		string ReadAll(string fullPath);
		void WriteAll(string fullPath, string content, bool append = false);
	}
}