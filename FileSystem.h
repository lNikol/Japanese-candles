#pragma once

class FileSystem {
private:
	
	
public:
	char defaultReadFile[50] = "intc_us_data.csv";
	char defaultOutputFile[50] = "chart.txt";
	void readFile(const char*, const char*, int, int);
	void readFileWithParams(const char*, const char*, int, int);
	void readFile2(int);
};