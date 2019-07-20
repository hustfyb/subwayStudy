#include "pch.h"
#include "CppUnitTest.h"
#include "../subway/Station.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SubwayUnitTest
{
	TEST_CLASS(StationManageTest)
	{
	public:
		
		TEST_METHOD(StationManage_addStation)
		{
			StationManage stationManager;
			stationManager.addStation("1", "a");

		}
	};
}
