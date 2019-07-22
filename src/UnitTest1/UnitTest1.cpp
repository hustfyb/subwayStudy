#include "pch.h"
#include "CppUnitTest.h"
#include "../subway/Station.h"
#include "../subway/StationManager.h"
#include "../subway/subway.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SubwayUnitTest
{
	TEST_CLASS(StationManageTest)
	{
	public:

		TEST_METHOD(StationManage_queryRouteStartNotFound)
		{
			StationManager stationManager;
			map<string, shared_ptr<Line>> lines;
			readFile("D:\\work\\study\\subwayStudy\\src\\UnitTest1\\test.txt", stationManager, lines);
			auto rt = stationManager.queryRoute("x", "a");
			Assert::IsTrue(rt.first == StartNotFound);
		}
		TEST_METHOD(StationManage_queryRouteEndNotFound)
		{
			StationManager stationManager;
			map<string, shared_ptr<Line>> lines;
			readFile("D:\\work\\study\\subwayStudy\\src\\UnitTest1\\test.txt", stationManager, lines);
			auto rt = stationManager.queryRoute("a", "x");
			Assert::IsTrue(rt.first == EndNotFound);
		}
		TEST_METHOD(StationManage_queryRouteNotExsit)
		{
			StationManager stationManager;
			map<string, shared_ptr<Line>> lines;
			readFile("D:\\work\\study\\subwayStudy\\src\\UnitTest1\\test.txt", stationManager, lines);
			auto rt = stationManager.queryRoute("a", "n");
			Assert::IsTrue(rt.first == RouteDoesNotExist);
		}
		TEST_METHOD(StationManage_queryRoute)
		{
			StationManager stationManager;
			map<string, shared_ptr<Line>> lines;
			readFile("D:\\work\\study\\subwayStudy\\src\\UnitTest1\\test.txt", stationManager, lines);
			auto rt = stationManager.queryRoute("a", "f");
			rt.second->dump();
			Assert::IsTrue(rt.second->getStartStaion()->name_=="a");
			Assert::IsTrue(rt.second->getEndStaion()->name_=="f");
			Assert::IsTrue(rt.second->changeCount_==3);
		}
	};
}
