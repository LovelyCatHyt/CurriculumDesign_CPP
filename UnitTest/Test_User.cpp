#include "pch.h"

#include <random>

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
			std::string newPw = "1919810";
			test.RefreshPw(newPw);
			Assert::IsTrue(test.Verify(newPw));
			Assert::AreEqual(test.Access(), 0);
		}
		TEST_METHOD(JsonConvert)
		{
			User test = User("Admin", "114514", "NULL", 0);
			json j = test;
			User u = j;
			Assert::AreEqual(u.Name().c_str(), "Admin");
			Assert::AreEqual(u.DataName().c_str(), "NULL");
			Assert::AreEqual(u.Access(), 0);
			Assert::IsTrue(u.Verify("114514"));
		}
		TEST_METHOD(Test_Encrypt)
		{
			std::string s = "";
			
			std::default_random_engine e;
			for (int i = 0; i <= 64; i++)
			{
				int p = e() % (26 + 26 + 10);

				if (p < 26) s += ('A' + p);
				else if (p < 26 + 26) s += ('a' + p - 26);
				else s += ('a' + p - 26 - 26);
			}
			
			User test = User("Admin", s, "NULL", 0);
			std::string raw = "114514";
			std::string secretKey = test.GenerateSecretKey(s);

			std::string encrypted = Encrypt(raw, secretKey);
			std::string decrypted = Decrypt(encrypted, secretKey);
			Assert::AreEqual(raw.c_str(), decrypted.c_str());
		}
	};
}