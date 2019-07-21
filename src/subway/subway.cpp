// subway.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "getopt.h"
#include "subway.h"
#include <map>
#include "Station.h"
#include "Line.h"
#include "Station.h"
#include "StationManager.h"
#include <map>
using namespace std;
using json = nlohmann::json;
map<string, shared_ptr<Line>> g_lines;
StationManager g_stations;
void printUsage() {
	cout << "<-map filename> [-a stationName] [-o filename]";
}


int readFile(string fileName) {
	std::ifstream inFile(fileName);
	json data;
	try
	{
		inFile >> data;
		if (!data.is_array()) {
			cerr << "线路格式不对。";
			return -1;
		}
		for (auto line : data)
		{
			string lineName = line["name"];
			shared_ptr<Line> newLine = make_shared<Line>(lineName);
			if (!g_lines[lineName]) {
				g_lines[lineName] = newLine;
			}
			else
			{
				cerr << "线路重复" << endl;
				return -1;
			}
			shared_ptr<Station> prevStaion;
			for (auto stationName : line["stations"]) 
			{
				if (!newLine->hasStation(stationName))
				{
					if (g_stations.addStation(stationName, lineName) != 0)
					{
						return -1;
					};
					newLine->add(stationName);
				}
				else {
					cerr << "线路站点重复" << endl;
					return -1;
				}
				shared_ptr<Station> newStation = g_stations.getStation(stationName);
				if (prevStaion) {
					prevStaion->setNextStation(newStation,lineName);
					newStation->setNextStation(prevStaion, lineName);//反向路线
				}
				prevStaion = newStation;
			}
		}
		
	}
	catch (json::exception e)
	{
		cerr << e.what()<<endl;
		return -1;
	}
	return 0;
}

void dump() {
	for (auto linePair:g_lines)
	{
		linePair.second->dump();
	}
}
int main(int argc ,TCHAR **argv)
{
	char* fileName = NULL;
	string queryLine;
	string queryRouteStart;
	string queryRouteEnd;
	ofstream outStream;
	static struct option long_options[] =
	{
		{(TCHAR*)"map", required_argument,NULL, 'm'},
		{NULL, 0, NULL, 0},
	};
	int c;
	int option_index = 0;
	while ((c = getopt_long_only(argc, argv, _T("a:b:o:"), long_options, &option_index)) != -1)
	{
		switch (c)
		{
		case 'm':
			fileName = optarg;
			break;
		case 'a':
			queryLine = optarg;
			break;
		case 'b':
			queryRouteStart = optarg;
			if (argc > optind) {
				queryRouteEnd = argv[optind];
			}
			break;
		case 'o':
			outStream.open(optarg);
			break;
		default:
			printUsage();
			return 0;
		}
	}
	if (fileName == NULL) {
		std::cout << "缺少必要参数\n";
		printUsage();
		return -1;
	}

	if (readFile(fileName) == 0) {
		//单一路线查询
		if (!queryLine.empty()) {
			cout << "query line" << endl;
			auto iter = g_lines.find(queryLine);
			if (iter != g_lines.end()) {
				iter->second->dump();
			}
			else {
				cout << "线路不存在" << endl;
			}
		};
		//起始路线查询
		if (!queryRouteStart.empty() && !queryRouteEnd.empty()) {
			g_stations.queryRoute(queryRouteStart, queryRouteEnd);
			cout << "query route" << endl;
		}
	}
	else {
		cout << "读入文件失败,请检查文件是否存在，文件格式是否正确" << endl;
	};
	if (outStream.is_open()) outStream.close();
}
