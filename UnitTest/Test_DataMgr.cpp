#include "pch.h"
#include "CppUnitTest.h"
#include "../DataMgr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Hyt;

namespace UnitTest
{
	TEST_CLASS(Test_DataMgr)
	{
		TEST_METHOD(SearchData_ByArgCount)
		{
			DataMgr test(vector<PolyFuncData>
			{
				PolyFuncData(vector<double>{ 0,0,0,0 }),
				PolyFuncData(vector<double>{ 0,0,0,0 }),
				PolyFuncData(vector<double>{ 0,0,0,0 }),
				PolyFuncData(vector<double>{ 0,0,0,0 }),
				PolyFuncData(vector<double>{ 0,0,0,0,0 }),
				PolyFuncData(vector<double>{ 0,0,0,0,0 }),
				PolyFuncData(vector<double>{ 0,0,0,0,0 }),
				PolyFuncData(vector<double>{ 0,0,0,0,0 })
			});
			DataMgr resultA = test.SearchData(4);
			DataMgr resultB = test.SearchData(5);
			Assert::AreEqual(resultA.Count(), 4);
			Assert::AreEqual(resultB.Count(), 4);
		}
		TEST_METHOD(SearchData_ByKeyWord)
		{
			//下面的表格不要用格式清理 不然sb VS整出来的格式非常丑
			DataMgr test(vector<PolyFuncData>
			{
					PolyFuncData({ 0 },0,1,"HaHaHa"),
					PolyFuncData({ 0 },0,1,"HaHaHa"),
					PolyFuncData({ 0 },0,1,"HaHaHa"),
					PolyFuncData({ 0 },0,1,"HaHaHa"),
					PolyFuncData({ 0 },0,1,"HiHiHi"),
					PolyFuncData({ 0 },0,1,"HiHiHi"),
					PolyFuncData({ 0 },0,1,"HiHiHi"),
					PolyFuncData({ 0 },0,1,"HiHiHi")
			});
			DataMgr resultA = test.SearchData("Ha");
			DataMgr resultB = test.SearchData("Hi");
			Assert::AreEqual(resultA.Count(), 4);
			Assert::AreEqual(resultB.Count(), 4);
		}
	};
}