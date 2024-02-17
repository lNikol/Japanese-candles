#pragma once
struct LineFile {
	short data_size = 11;
	char data[11];
	float open, high, low, close;
};