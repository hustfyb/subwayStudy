#pragma once
#include <list>
#include <string>
#include <memory>
using namespace std;
class Line
{
public:
	Line(string);
	bool hasStation(string stationName) const;
	void add(string stationName);
	void dump() const;
private:
	string name_;
	list<string> stations_;
};

