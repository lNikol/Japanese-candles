#include "Controller.h"

void Controller::defaultStart() {
	filesys.readFile("", "", 200, DATA_SIZE);
}
void Controller::startWithFilesAndParams(char inFile[], char outFile[], int data_size, int graphic_size, int graphic_height) {
	filesys.readFileWithParams(inFile, outFile, graphic_size, graphic_height);
}

//	double wspl = (maxValue - minValue) / (GRAPHIC_HEIGHT - 2);