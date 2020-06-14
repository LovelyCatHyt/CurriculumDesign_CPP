#include "pch.h"
#include "CppUnitTest.h"
#include "../UserMgr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Hyt;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(TestMethod1)
		{

			UserMgr mgr = json::parse("{\n    \"users\": [\n        {\n            \"dataName\": \"TestData\/Data1.json\",\n            \"pwHash\": \"$2a$12$qWQPLXAOJeV3ISZ7MDm7Wu4Z9gY6VGPTrTiVnrlqkQU6b34wV7We.\",\n            \"userName\": \"Admin\"\n        }\n    ]\n}");
			bool temp;
			User& result = mgr.FindUser("Admin", temp);
			Assert::AreEqual(temp, true);
			Assert::AreEqual(result.Name().c_str(), "Admin");
		}
	};
}
