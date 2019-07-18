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
#include <map>
using namespace std;
using json = nlohmann::json;
map<string, shared_ptr<Line>> g_lines;
StationManage staionManager;
void printUsage() {
	cout << "<-map filename> [-o filename]";
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
			string name = line["name"];
			shared_ptr<Line> newLine = make_shared<Line>(name);
			g_lines[name] = newLine;
			for (auto station : line["stations"]) {
				if (staionManager.addStation(station, newLine) != 0) {
					return -1;
				};
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
	static struct option long_options[] =
	{
		{(TCHAR*)"map", required_argument,NULL, 'm'},
		{NULL, 0, NULL, 0},
	};
	int c;
	int option_index = 0;
	while ((c = getopt_long_only(argc, argv, _T("a::b::o::b::"), long_options, &option_index)) != -1)
	{
		switch (c)
		{
		case 'm':
			fileName = optarg;
			break;
		//case 'b':
		//	bflag = 1;
		//	break;
		//case 'c':
		//	cvalue = optarg;
		//	break;
		//case '?':
		//	if (optopt == 'c')
		//		_ftprintf(stderr, _T("Option -%c requires an argument.\n"), optopt);
		//	else if (isprint(optopt))
		//		_ftprintf(stderr, _T("Unknown option `-%c'.\n"), optopt);
		//	else
		//		_ftprintf(stderr, _T("Unknown option character `\\x%x'.\n"), optopt);
		//	return 1;
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
		dump();
	}
	else {
		cout << "读入文件失败,请检查文件是否存在，文件格式是否正确" << endl;
	};
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
