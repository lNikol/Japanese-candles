#pragma once
#include "Map.h"
#include "FileSystem.h"

class Controller {
private:
	FileSystem filesys;
	int DATA_SIZE = 12;

public:
	void defaultStart();
	void startWithFilesAndParams(char[], char[], int, int, int);
};