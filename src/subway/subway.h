#include <map>
#include <iostream>
#include <fstream>
#include "Station.h"
#include "Line.h"
#include "Station.h"
#include "StationManager.h"
using namespace std;
int readFile(string fileName, StationManager& stations, map<string, shared_ptr<Line>>& lines);
