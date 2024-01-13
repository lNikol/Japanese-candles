#pragma once
#include "LineFile.h"
#include <fstream>

class FileSystem {
private:
	LineFile* fileLines;
	
public:
	std::ofstream outputFile;
	std::ifstream file;
	double maxValue;
	double minValue;
	int graphic_width;
	char defaultReadFile[50] = "intc_us_data.csv";
	char defaultOutputFile[50] = "chart.txt";
	void readFile(LineFile gameFileLines[], double& minGameVal, double& maxGameVal, int graph_w = 200, 
		const char* readFile = "intc_us_data.csv", const char* outFile = "chart.txt");

	//void readFileWithParams(LineFile[], int, int, const char*, const char*);
	void setGameFileLines(LineFile[]);
};