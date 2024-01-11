#pragma once
#include "Map.h"
#include "FileSystem.h"

class Controller {
private:
	int DATA_SIZE = 12;

public:
	void defaultStart(FileSystem);
	void startWithFilesAndParams(FileSystem, char[], char[], int, int, int); //передать FileSystem по ссылке
};