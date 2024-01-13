#include "FileSystem.h"
#include <iostream>
#include <fstream>
#include <iomanip> // zobaczyc co robi
using namespace std;


void max_min(double& value, double& min, double& max) {
	if (min == -1) min = value;
	value > max ? max = value : 0;
	value < min ? min = value : 0;
}

void FileSystem::setGameFileLines(LineFile gameFileLines[]) {
	for (int i = 0; i < graphic_width; i++) {
		gameFileLines[i] = fileLines[i];
	}
}


void FileSystem::readFile(LineFile gameFileLines[], double& minGameVal, double& maxGameVal, int graph_w, const char* readFile, const char* outFile) {
	// lengthOfRead to samo co i graphic_width
	graphic_width = graph_w;

	// доделать проверку на имя файла
	// если отстувтует .csv, то дописать
	// иначе прочитать файл по имени

	if (readFile == "") strcpy_s(defaultReadFile, sizeof(defaultReadFile), readFile);
	else readFile = readFile;

	if (outFile == "") strcpy_s(defaultOutputFile, sizeof(defaultOutputFile), outFile);
	else outFile = outFile;

	// длина данных 6015

	file.open(defaultReadFile, ios::binary);
	if (!file.is_open()) {
		cout << "The file cannot be opened (or the file does not exist, or select another file)" << endl;
		return;
	}

	const int MAX_LENGTH = 128;
	char linia[MAX_LENGTH];
	int licznik_linii = 0;

	file.seekg(0, ios::end);
	int pozycja = file.tellg();

	while (--pozycja >= 0) {
		file.seekg(pozycja, ios::beg); // przesuniecie pozycji
		char znak;
		file.get(znak);
		if (znak == '\n') {
			++licznik_linii;
			if (licznik_linii == graphic_width + 1) {
				break;
			}
		}
	}

	fileLines = new LineFile[graphic_width];

	double maxOpen = 0, maxClose = 0, maxLow = 0, maxHigh = 0;
	double minOpen = -1, minClose = -1, minLow = -1, minHigh = -1;
	int c = 0;
	while (file.getline(linia, MAX_LENGTH)) {
		char* nextToken;
		char* token;
		char delimiter[] = ",";
		token = strtok_s(linia, delimiter, &nextToken);
		int counter = 0;
		while (counter != 5) {
			double token_value = atof(token);
			switch (counter) {
			case 0: strcpy_s(fileLines[c].data, fileLines[c].data_size, token); break;
			case 1: fileLines[c].open = token_value; cout << "o- " << token_value << " ";
				max_min(token_value, minOpen, maxOpen); break;
			case 2: fileLines[c].high = token_value; cout << "h- " << token_value << " ";
				max_min(token_value, minHigh, maxHigh); break;
			case 3: fileLines[c].low = token_value; cout << "l- " << token_value << " ";
				max_min(token_value, minLow, maxLow); break;
			case 4: fileLines[c].close = token_value; cout << "c- " << token_value << " ";
				max_min(token_value, minClose, maxClose); break;
			default: break;
			}
			token = strtok_s(nullptr, delimiter, &nextToken);
			counter++;
		}
		c++;
		cout << endl;
	}

	maxValue = max(max(maxOpen, maxClose), max(maxLow, maxHigh));
	minValue = min(min(minOpen, minClose), min(minLow, minHigh));

	maxGameVal = maxValue;
	minGameVal = minValue;
	
	setGameFileLines(gameFileLines);

	file.close();

}


//void FileSystem::readFileWithParams(LineFile gameFileLines[], int minGameVal, int maxGameVal, const char* readUserFile, const char* outUserFile) {
//	readFile(gameFileLines, minGameVal, maxGameVal, readUserFile, outUserFile);
//}