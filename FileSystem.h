#pragma once

class FileSystem {
private:
	
	
public:
	FileSystem();
	int maxRows = 100;
	int lengthOfRow = 10;
	char** dateArr = new char* [maxRows];

	int defHeight = 50;
	int defReadLength = 200;
	int fileNameLength = 100;
	char* inputFileName = new char[fileNameLength];
	char* outputFileName = new char[fileNameLength];
	char defaultInputFile[50] = "intc_us_data.csv";
	char defaultOutputFile[50] = "data.txt";

	void readFile(int);
	void readFile2(int);
};