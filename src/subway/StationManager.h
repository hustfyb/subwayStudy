#pragma once
#include <map>
#include <string>
#include <memory>
#include "Station.h"
#include "Route.h"
using namespace std;
typedef enum {
	NoError = 0,
	StartNotFound,
	EndNotFound,
	RouteDoesNotExist
}QueryErrorCode;
class StationManager {
public:
	int addStation(string stationName, string lineName);
	shared_ptr<Station> getStation(string stationName);
	pair<QueryErrorCode,shared_ptr<Route>> queryRoute(string startStation, string endStation);
private:
	map<string, shared_ptr<Station>> stations_;
	list<shared_ptr<Route>> bingoRoutes_;
	list<shared_ptr<Route>> testRoutes_;
	void checkRoutes(list<shared_ptr<Route>>& prepareRoute, shared_ptr<Station>);
};
