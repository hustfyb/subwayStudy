#include "StationManager.h"
#include <iostream>
#include "subway.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

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

pair<QueryErrorCode, shared_ptr<Route>> StationManager::queryRoute(string startStationName, string endStationName)
{
	shared_ptr<Station> startStation = getStation(startStationName);
	shared_ptr<Station> endStation = getStation(endStationName);
	if (startStation == nullptr) {
		cerr << "起点找不到" << endl;
		return (pair <QueryErrorCode, shared_ptr<Route>>(StartNotFound,nullptr));
	
	}
	if (endStation == nullptr) {
		cerr << "终点找不到" << endl;
		return (pair <QueryErrorCode, shared_ptr<Route>>(EndNotFound, nullptr));
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
		return pair <QueryErrorCode, shared_ptr<Route>>(RouteDoesNotExist, nullptr);
	}

	shared_ptr<Route> minRoute = bingoRoutes_.front();
	for (auto route:bingoRoutes_)
	{
		if (minRoute->changeCount_ > route->changeCount_) {
			minRoute = route;
		}
	}
	return (pair <QueryErrorCode, shared_ptr<Route>>(NoError, minRoute));
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

int readFile(string fileName, StationManager& stations, map<string, shared_ptr<Line>>& lines)
{
	ifstream inFile(fileName);
	json data;
	try
	{
		inFile >> data;
		if (!data.is_array()) {
			cerr << "线路格式不对。";
			return -1;
		}
		for (auto line : data)
		{
			string lineName = line["name"];
			shared_ptr<Line> newLine = make_shared<Line>(lineName);
			if (!lines[lineName]) {
				lines[lineName] = newLine;
			}
			else
			{
				cerr << "线路重复" << endl;
				return -1;
			}
			shared_ptr<Station> prevStaion;
			for (auto stationName : line["stations"])
			{
				if (!newLine->hasStation(stationName))
				{
					if (stations.addStation(stationName, lineName) != 0)
					{
						return -1;
					};
					newLine->add(stationName);
				}
				else {
					cerr << "线路站点重复" << endl;
					return -1;
				}
				shared_ptr<Station> newStation = stations.getStation(stationName);
				if (prevStaion) {
					prevStaion->setNextStation(newStation, lineName);
					newStation->setNextStation(prevStaion, lineName);//反向路线
				}
				prevStaion = newStation;
			}
		}

	}
	catch (json::exception e)
	{
		cerr << e.what() << endl;
		return -1;
	}
	return 0;
}
