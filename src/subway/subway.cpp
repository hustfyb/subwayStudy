// subway.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <fstream>
#include "getopt.h"
#include "subway.h"
void printUsage() {
	cout << "<-map filename> [-a stationName] [-o filename]";
}



int main(int argc ,TCHAR **argv)
{
	char* fileName = NULL;
	string queryLine;
	string queryRouteStart;
	string queryRouteEnd;
	ofstream outStream;
	StationManager stations;
	map<string, shared_ptr<Line>> lines;
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

	if (readFile(fileName, stations, lines) == 0) {
		//单一路线查询
		if (!queryLine.empty()) {
			cout << "query line" << endl;
			auto iter = lines.find(queryLine);
			if (iter != lines.end()) {
				outStream.is_open()?iter->second->dump(outStream): iter->second->dump();
			}
			else {
				cout << "线路不存在" << endl;
			}
		};
		//起始路线查询
		if (!queryRouteStart.empty() && !queryRouteEnd.empty()) {
			auto rt = stations.queryRoute(queryRouteStart, queryRouteEnd);
			if (rt.first==NoError) {
				outStream.is_open() ? (rt.second->dump(outStream), rt.second->dump()) : rt.second->dump();
			}
		}
	}
	else {
		cout << "读入文件失败,请检查文件是否存在，文件格式是否正确" << endl;
	};
	if (outStream.is_open()) outStream.close();
}
