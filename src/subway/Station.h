#pragma once
#include <string>
#include <map>
#include <memory>
#include "Line.h"
using namespace std;
class Station
{
public:
	Station(string stationName, shared_ptr<Line> line);
	string name;
	list<shared_ptr<Line>> lines;
};
class Line;
class StationManage {
public:
	int addStation(string name, shared_ptr<Line> line);
private:
	map<string,shared_ptr<Station> > stations;

};