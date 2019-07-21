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
		list<shared_ptr<Route>> prepareRoute;
		for (auto route : testRoutes_)
		{
			route->generateNextRoute(prepareRoute);
		}
		if (prepareRoute.empty()) break;
		checkRoutes(prepareRoute, endStation);
		testRoutes_ = prepareRoute;
	}

	return 0;
}

void StationManager::checkRoutes(list<shared_ptr<Route>>& prepareRoute, shared_ptr<Station> endStation)
{
	for (auto route : prepareRoute)
	{
		if (route->getEndStaion() == endStation) {
			bingoRoutes_.push_back(route);
			route->dump();
		}
	}
}

Route::Route(shared_ptr<Station> startStation)
	:changeCount_(0)
{
	shared_ptr<NextStation> station = make_shared<NextStation>();
	station->routeLine = "0";
	station->station = startStation;
	stations_.push_back(station);
}

int Route::addNextStation(shared_ptr<NextStation> station)
{
	if (station->routeLine != stations_.back()->routeLine) {
		changeCount_++;
	}
	if (find(stations_.begin(), stations_.end(), station) != stations_.end()) {
		//站点已经存在
		return -1;
	}
	stations_.push_back(station);
	return 0;
}

int Route::generateNextRoute(list<shared_ptr<Route>> &routes)
{
	shared_ptr<Station> endStaion = getEndStaion();
	for (auto station : endStaion->nextStations)
	{
		shared_ptr<Route> newRoute = make_shared<Route>(*this);
		if (newRoute->addNextStation(station) == 0) {
			routes.push_back(newRoute);
		};
	}
	return 0;
}

shared_ptr<Station> Route::getStartStaion()
{
	if (stations_.empty()) return nullptr;
	return (stations_.front()->station);
}

shared_ptr<Station> Route::getEndStaion()
{
	if (stations_.empty()) return nullptr;
	return (stations_.back()->station);
}

void Route::dump()
{
	if (stations_.empty()) return;
	cout << changeCount_ << endl;
	string lineName=stations_.front()->routeLine;
	for (auto station:stations_)
	{
		if (lineName != station->routeLine) {
			cout << station->routeLine<<endl;
			lineName = station->routeLine;
		};
		cout << station->station->name_ << endl;
	}
}
