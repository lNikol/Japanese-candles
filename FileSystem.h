#pragma once
#include "LineFile.h"
#include <fstream>

struct FileSystem {
	LineFile* fileLines;

	std::ofstream outputFile;
	std::ifstream file;
	double maxValue;
	double minValue;
	int graphic_width;
	int amountOfRead;
	int infoLength = 0; // ilosc \n w pliku, czyli dni
	char defaultReadFile[259] = "intc_us_data.csv";
	char defaultOutputFile[259] = "chart.txt";


	int end_data_x;
	int end_data_user_x;
	int start_data_x;
	int start_data_user_x;
	int size_data_x;


	void readFile(char* readFile);

	//void readFileWithParams(LineFile[], int, int, const char*, const char*);
	void setGameFileLines(LineFile[]);
	void deleteFileLines();
	void findMaxMin();
	void findDate(char date[], int& dateIndex);
	void saveInfoToLog(const char info[]);
	void initializeFileSystem();
};