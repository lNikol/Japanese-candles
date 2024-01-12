#pragma once
struct LineFile {
	int data_size;
	LineFile(int dataSize = 11) :data_size(dataSize) {};
	char* data = new char[data_size];
	double open, high, low, close;
};