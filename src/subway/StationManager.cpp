#include "StationManager.h"
#include <iostream>

int StationManager::addStation(string stationName, string lineName)
{
	auto stationIter = stations_.find(stationName);
	shared_ptr<Station> station;
	if (stationIter == stations_.end()) {
		station = make_shared<Station>(stationName, lineName);
		stations_[stationName] = station;
	}
	else {
		station = stationIter->second;
		station->addLine(lineName);
	}
	return 0;
}

std::shared_ptr<Station> StationManager::getStation(string stationName)
{
	auto iter = stations_.find(stationName);
	return ((iter != stations_.end()) ? iter->second : nullptr);
}

int StationManager::queryRoute(string startStationName, string endStationName)
{
	shared_ptr<Station> startStation = getStation(startStationName);
	shared_ptr<Station> endStation = getStation(endStationName);
	if (startStation == nullptr) {
		cerr << "起点找不到" << endl;
		return -1;
	}
	if (endStation == nullptr) {
		cerr << "终点找不到" << endl;
		return -1;
	}

	bingoRoutes_.clear();
	testRoutes_.clear();
	testRoutes_.push_back(make_shared<Route>(startStation));
	while (bingoRoutes_.empty())
	{
		for (auto route : testRoutes_)
		{
			auto nextRoutes = route->generateNextRoute();
		}
		
		checkRoute(testRoutes);
	}

	return 0;
}

Route::Route(shared_ptr<Station> startStation)
	:changeCount_(0)
{
	shared_ptr<NextStation> station = make_shared<NextStation>();
	station->routeLine = "0";
	station->station = startStation;
	addNextStation(station);
}

void Route::addNextStation(shared_ptr<NextStation> station)
{
	stations_.push_back(station);
}

list<shared_ptr<Route>> Route::generateNextRoute()
{
	list<shared_ptr<Route>> routes;
	shared_ptr<Station> endStaion = getEndStaion();
	for (auto station : endStaion->nextStations)
	{
		shared_ptr<Route> newRoute = make_shared<Route>(shared_ptr)
	}
	return routes;
}

shared_ptr<Station> Route::getStartStaion()
{
	if (stations_.empty()) return nullptr;
	return ((*stations_.begin())->station);
}

shared_ptr<Station> Route::getEndStaion()
{
	if (stations_.empty()) return nullptr;
	return ((*(stations_.end()--))->station);
}
