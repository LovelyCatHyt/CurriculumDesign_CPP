#include "pch.h"
#include "CppUnitTest.h"
#include "AES/AES.h"
#include "cpp-base64/base64.h"
#include <string>
#include <vector>
#include <PicoSHA2/picosha2.h>
using std::string;
using std::vector;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(Test_AES)
	{
		std::string GenerateSecretKey(const std::string& pw)
		{
			std::vector<unsigned char> hash(picosha2::k_digest_size);
			picosha2::hash256(pw.begin(), pw.end(), hash.begin(), hash.end());
			return picosha2::bytes_to_hex_string(hash.begin(), hash.end());
		}
		TEST_METHOD(Test_DEBUG)
		{
			string raw = "0 ";
			string secretKey = GenerateSecretKey("123456");
			//string secretKey = "0123456701234567012345670123456701234567012345670123456701234567000000000000000000000000000000000000";
			unsigned char* plain = (unsigned char*)raw.c_str();
			unsigned int plainLen = raw.length();
			unsigned char* key = (unsigned char*)secretKey.c_str();

			unsigned int outLen = 0;

			AES aes(256);
			unsigned char* c = aes.EncryptECB(plain, plainLen, key, outLen);

			std::string chipher = std::string((char*)c);
			delete[] c;
			chipher = base64_encode(chipher);
			//-------------------------------
			chipher = base64_decode(chipher);
			unsigned char* content = (unsigned char*)(chipher).c_str();
			unsigned int contentLen = chipher.length();

			c = aes.DecryptECB(content, contentLen, key);

			std::string result = std::string((char*)c);

			//delete[] c;
			Assert::AreEqual(raw, result);
		}
	};
}