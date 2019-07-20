#pragma once
#include <string>
#include <map>
#include <memory>
#include <set>
#include "Line.h"
using namespace std;
class Station;
typedef struct  
{
	string routeLine;
	shared_ptr<Station> station;
}NextStation;
class Station
{
public:
	Station(string stationName, string lineName);
	void addLine(string lineName);
	void setNextStation(shared_ptr<Station> station, string routeLine);
	list<NextStation> nextStations;
private:
	string name_;
	set<string> lines_;
};
