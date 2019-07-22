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
	Station(string stationName);
	void addLine(string lineName);
	void setNextStation(shared_ptr<Station> station, string routeLine);
	list<shared_ptr<NextStation>> nextStations;
	string name_;
//private:
//	set<string> lines_;
};
