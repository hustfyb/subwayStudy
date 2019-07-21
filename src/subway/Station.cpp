#include "Station.h"
#include <iostream>
#include "Line.h"
Station::Station(string stationName, string lineName)
	:name_(stationName)
{
	lines_.insert(stationName);
}

void Station::addLine(string lineName)
{
	lines_.insert(lineName);
}

void Station::setNextStation(shared_ptr<Station> station, string routeLine)
{
	shared_ptr<NextStation> nextStation=make_shared<NextStation>();
	nextStation->routeLine = routeLine;
	nextStation->station = station;
	nextStations.push_back(nextStation);
}
