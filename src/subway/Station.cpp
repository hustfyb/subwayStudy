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
	NextStation next;
	next.routeLine = routeLine;
	next.station = station;
	nextStations.push_back(next);
}
