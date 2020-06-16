#include "pch.h"
#include "CppUnitTest.h"
#include "../PolyFuncData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Hyt;

namespace UnitTest
{
	TEST_CLASS(Test_PolyFuncData)
	{
		TEST_METHOD(GetValue)
		{
			PolyFuncData test = PolyFuncData({ 1,1,1 }, 0, 1000);
			Assert::AreEqual(test.GetValue(3), 3 * 3 + 3 + 1.0);
			Assert::AreEqual(test.GetValue(2), 2 * 2 + 2 + 1.0);
			Assert::AreEqual(test.GetValue(4), 4 * 4 + 4 + 1.0);
		}
	};
}