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

		TEST_METHOD(FromJson)
		{

			UserMgr mgr = json::parse("{\n    \"users\": [\n        {\n            \"dataName\": \"TestData/Data1.json\",\n            \"pwHash\": \"$2a$12$qWQPLXAOJeV3ISZ7MDm7Wu4Z9gY6VGPTrTiVnrlqkQU6b34wV7We.\",\n            \"userName\": \"Admin\"\n        }\n    ]\n}");
			bool temp;
			User& result = mgr.Login("Admin", "114514", temp);
			Assert::AreEqual(temp, true);
		}

		TEST_METHOD(ToJson)
		{
			UserMgr mgr;
			mgr.Register(User("Admin", "114514", "TestData/Data1.json"));
			json j = mgr;
			UserMgr another = j;
			bool temp;
			another.Login("Admin","114514",temp);
			Assert::IsTrue(temp);
		}
	};
}