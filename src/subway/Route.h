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
	int addNextStation(shared_ptr<NextStation> station);
	int generateNextRoute(list<shared_ptr<Route>>& routes);
	shared_ptr<Station> getStartStaion();
	shared_ptr<Station> getEndStaion();
	void dump(ostream& stream = cout) const;
	int changeCount_;
private:
	list<shared_ptr<NextStation>> stations_;
};
