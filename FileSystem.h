#pragma once
#include "LineFile.h"
#include <fstream>

struct FileSystem {
	LineFile* fileLines;

	std::ifstream file;
	float maxValue;
	float minValue;
	int infoLength = 0; // ilosc \n w pliku, czyli dni
	char defaultReadFile[259] = "intc_us_data.csv";
	char defaultOutputFile[259] = "chart.txt";


	int end_data_x;
	int end_data_user_x = -1;
	int start_data_x;
	int start_data_user_x = -1;
	int size_data_x;


	void readFile(char* readFile);

	void setGameFileLines(LineFile[]);
	void deleteFileLines();
	void findMaxMin();
	void findDate(char date[], int& dateIndex);
	void saveInfoToLog(const char info[]);
	void initializeFileSystem(char fileName[]);
};