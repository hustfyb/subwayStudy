#include "Station.h"
#include <iostream>
#include "Line.h"

int StationManage::addStation(string stationName, shared_ptr<Line> line)
{
	if (!line->hasStation(stationName))
	{
		auto stationIter = stations.find(stationName);
		shared_ptr<Station> station;
		if (stationIter == stations.end()) {
			station = make_shared<Station>(stationName, line);
			stations[stationName] = station;
		}
		else {
			station = stationIter->second;
		}
		line->add(stationName);
	}
	else
	{
		cerr << "线路站点重复" << endl;
		return -1;
	}
	return 0;
}

Station::Station(string stationName, shared_ptr<Line> line)
	:name(stationName)
{
	
}
