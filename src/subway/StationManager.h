#pragma once
#include <map>
#include <string>
#include <memory>
#include "Station.h"
using namespace std;
class Route
{
public:
	Route(shared_ptr<Station> startStation);
	void addNextStation(shared_ptr<NextStation> station);
	list<shared_ptr<Route>> generateNextRoute();
	shared_ptr<Station> getStartStaion();
	shared_ptr<Station> getEndStaion();
private:
	list<shared_ptr<NextStation>> stations_;
	int changeCount_;
};

class StationManager {
public:
	int addStation(string stationName, string lineName);
	shared_ptr<Station> getStation(string stationName);
	int queryRoute(string startStation, string endStation);
private:
	map<string, shared_ptr<Station>> stations_;
	list<shared_ptr<Route>> bingoRoutes_;
	list<shared_ptr<Route>> testRoutes_;
};