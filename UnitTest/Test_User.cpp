#include "pch.h"
#include "CppUnitTest.h"
#include "../User.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Hyt;

namespace UnitTest
{
	TEST_CLASS(Test_User)
	{
	public:
		TEST_METHOD(Init)
		{
			User test = User("Admin", "114514", "NULL", 0);
			Assert::AreEqual(test.Access(), 0);
		}
		TEST_METHOD(PW_Veryfy)
		{
			User test = User("Admin", "114514", "NULL", 0);
			Assert::IsTrue(test.Verify("114514"));
		}
		TEST_METHOD(PW_Reset)
		{
			User test = User("Admin", "114514", "NULL", 0);
			test.RefreshPw("1919810");
			Assert::IsTrue(test.Verify("1919810"));
			Assert::AreEqual(test.Access(), 0);
		}
		TEST_METHOD(FromJson)
		{
			json j = json::parse("{\"dataName\": \"TestData\/Data2.json\","
				"\"pwHash\":\"$2a$12$qWQPLXAOJeV3ISZ7MDm7Wu4Z9gY6VGPTrTiVnrlqkQU6b34wV7We.\","
				"\"userName\": \"StudentA\","
				"\"access_cipher\": \"0\"}");
			User u = j;
			Assert::AreEqual(u.Name().c_str(), "StudentA");
			Assert::IsTrue(u.Verify("114514"));
		}
	};
}