#include "Line.h"
#include <algorithm>
#include <iostream>

Line::Line(string name):name_(name)
{

}

bool Line::hasStation(string stationName) const
{
	auto iter = find_if(stations_.begin(), stations_.end(), [&](string name) {
		return (name == stationName);
		});
	return (iter != stations_.end());
}

void Line::add(string stationName)
{
	stations_.push_back(stationName);
}

void Line::dump(ostream &stream=cout) const
{
	for (auto staion : stations_)
	{
		stream << " " << staion;
	}
	stream << endl;
}

