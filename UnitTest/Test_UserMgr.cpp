#include "pch.h"
#include "CppUnitTest.h"
#include "../UserMgr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Hyt;

namespace UnitTest
{
	TEST_CLASS(Test_UserMgr)
	{
	public:
		TEST_METHOD(Register)
		{
			UserMgr mgr;
			mgr.Register(User("Admin", "114514", "balabala"));
			bool tmp;
			mgr.FindUser("Admin", tmp);
			Assert::IsTrue(tmp);
		}

		TEST_METHOD(JsonConvert)
		{
			UserMgr mgr;
			mgr.Register(User("Admin", "114514", "TestData/Data1.json",0));
			json j = mgr;
			UserMgr another = j;
			bool temp;
			User& result = mgr.Login("Admin", "114514", temp);
			Assert::IsTrue(temp);
			Assert::IsTrue(result.Access() == 0);
			Assert::IsTrue(result.DataName() == "TestData/Data1.json");
			Assert::IsTrue(result.Name() == "Admin");
		}
	};
}