#include "FileIO.h"     //Self
#include <iostream>     //cout
#include <fstream>      //ifstream, ofstream, ios

using std::ifstream;
using std::ofstream;
using std::ios;

namespace Hyt
{
	namespace FileInOut
	{
		string ReadAll(string fullPath)
		{
            string content = "";
            std::ifstream infile;
            char* fileBuffer = NULL;
            infile.open(fullPath, ios::in);
            if (infile.is_open())
            {
                infile.seekg(0, ios::end);
                auto len = infile.tellg();  //获取文件长度
                infile.seekg(0, ios::beg);  //设置读取位置为起始位置

                fileBuffer = new char[(size_t)len + 1];
                memset(fileBuffer, 0, (size_t)len + 1);
                infile.read(fileBuffer, len);
                content = fileBuffer;
                delete[] fileBuffer;
            }
            else
            {
                std::cout << '\"' << fullPath << "\" not found!\n";
            }

            infile.close();
            return content;
		}
		void WriteAll(string fullPath, string content, bool append)
		{
			
            ofstream o(fullPath, ios::out | (append ? ios::app : false));
            o.write(content.c_str(), content.length());
            o.close();
            return;
		}
	}
}