#pragma once
struct LineFile {
	int data_size = 11;
	char* data = new char[data_size];
	double open, high, low, close;
};