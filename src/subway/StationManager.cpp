#include "StationManager.h"
#include <iostream>

int StationManager::addStation(string stationName, string lineName)
{
	auto stationIter = stations_.find(stationName);
	shared_ptr<Station> station;
	if (stationIter == stations_.end()) {
		station = make_shared<Station>(stationName);
		stations_[stationName] = station;
	}
	return 0;
}

std::shared_ptr<Station> StationManager::getStation(string stationName)
{
	auto iter = stations_.find(stationName);
	return ((iter != stations_.end()) ? iter->second : nullptr);
}

shared_ptr<Route> StationManager::queryRoute(string startStationName, string endStationName)
{
	shared_ptr<Station> startStation = getStation(startStationName);
	shared_ptr<Station> endStation = getStation(endStationName);
	if (startStation == nullptr) {
		cerr << "起点找不到" << endl;
		return nullptr;
	}
	if (endStation == nullptr) {
		cerr << "终点找不到" << endl;
		return nullptr;
	}

	bingoRoutes_.clear();
	testRoutes_.clear();
	testRoutes_.push_back(make_shared<Route>(startStation));
	while (bingoRoutes_.empty())
	{
		list<shared_ptr<Route>> prepareRoute;
		for (auto route : testRoutes_)
		{
			route->generateNextRoute(prepareRoute);
		}
		if (prepareRoute.empty()) break;
		checkRoutes(prepareRoute, endStation);
		testRoutes_ = prepareRoute;
	}

	if (bingoRoutes_.empty()) {
		return nullptr;
	}

	shared_ptr<Route> minRoute = bingoRoutes_.front();
	for (auto route:bingoRoutes_)
	{
		if (minRoute->changeCount_ > route->changeCount_) {
			minRoute = route;
		}
	}
	return minRoute;
}

void StationManager::checkRoutes(list<shared_ptr<Route>>& prepareRoute, shared_ptr<Station> endStation)
{
	for (auto route : prepareRoute)
	{
		if (route->getEndStaion() == endStation) {
			bingoRoutes_.push_back(route);
		}
	}
}
