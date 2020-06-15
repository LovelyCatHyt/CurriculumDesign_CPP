#include "pch.h"

#include <random>
#include <vector>
#include "CppUnitTest.h"
#include "../StringUtiliy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Hyt;
using std::vector;
using std::string;

namespace UnitTest
{
	TEST_CLASS(Test_Else)
	{
		TEST_METHOD(StringUtility_Split)
		{
			vector<string> test = StringSplit("1\n2\n3\n4", "\n");
			vector<string> target = vector<string>{ "1", "2", "3", "4" };
			for (int i = 0; i < 4; i++) Assert::AreEqual(test[i], target[i]);
		}
	};
}