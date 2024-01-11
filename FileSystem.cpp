﻿#include "FileSystem.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <iomanip> // zobaczyc co robi
using namespace std;


void max_min(double& value, double& min, double& max) {
	if (min == -1) min = value;
	value > max ? max = value : 0;
	value < min ? min = value : 0;
}

void FileSystem::readFile(const char* readFile, const char* outFile, int GRAPHIC_WIDTH = 200, int data_size = 12) {//, int GRAPHIC_HEIGHT=50
	// lengthOfRead to samo co i GRAPHIC_WIDTH
	ofstream outputFile;
	ifstream file;
	if (strlen(readFile) > 2) strcpy_s(defaultReadFile, sizeof(defaultReadFile), readFile);
	if (strlen(outFile) > 2) strcpy_s(defaultOutputFile, sizeof(defaultOutputFile), outFile);
	file.open(defaultReadFile, ios::binary);
	if (!file.is_open()) {
		cout << "The file cannot be opened" << endl;
		return;
	}

	const int MAX_LENGTH = 128;
	char linia[MAX_LENGTH];
	int licznik_linii = 0;

	file.seekg(0, std::ios::end);
	int pozycja = file.tellg();

	while (--pozycja >= 0) {
		file.seekg(pozycja, ios::beg);
		char znak;
		file.get(znak);

		if (znak == '\n') {
			++licznik_linii;
			if (licznik_linii == GRAPHIC_WIDTH + 1) {
				break;
			}
		}
	}
	// nie uzywam data_size

	struct LineFile {
		char data[12];
		double open, high, low, close;
	};

	LineFile* fileLines = new LineFile[GRAPHIC_WIDTH];

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
			case 0: strcpy_s(fileLines[c].data, sizeof(fileLines[c].data), token); break;
			case 1: fileLines[c].open = token_value;
				max_min(token_value, minOpen, maxOpen); break;
			case 2: fileLines[c].high = token_value;
				max_min(token_value, minHigh, maxHigh); break;
			case 3: fileLines[c].low = token_value;
				max_min(token_value, minLow, maxLow); break;
			case 4: fileLines[c].close = token_value;
				max_min(token_value, minClose, maxClose); break;
			default: break;
			}
			token = strtok_s(nullptr, delimiter, &nextToken);
			counter++;
		}
		c++;
	}

	double maxValue = max(max(maxOpen, maxClose), max(maxLow, maxHigh));
	double minValue = min(min(minOpen, minClose), min(minLow, minHigh));

	Map map(GRAPHIC_WIDTH, 50, minLow, maxValue, 0.404);


	file.close();

}


void FileSystem::readFileWithParams(const char* readFileC, const char* outFile, int GRAPHIC_WIDTH = 200, int data_size = 12) {
	readFile(readFileC, outFile, GRAPHIC_WIDTH, data_size);
}

//void FileSystem::readFile2(int lengthOfRead = 100) {
//	ifstream file;
//	file.open(defaultReadFile, ios::binary);
//	if (!file.is_open()) {
//		cout << "The file cannot be opened" << endl;
//	}
//
//	const int MAX_LENGTH = 128;
//	int GRAPHIC_WIDTH = 200;
//	int GRAPHIC_HEIGHT = 50;
//	const int DATA_SIZE = 12;
//	const int NUMBER_OF_DATES = floor(GRAPHIC_WIDTH / (DATA_SIZE - 1)); //-1 bo koncowy symbol
//	char linia[MAX_LENGTH];
//	int licznik_linii = 0;
//
//	file.seekg(0, std::ios::end);
//	int pozycja = file.tellg();
//
//	while (--pozycja >= 0) {
//		file.seekg(pozycja, std::ios::beg);
//		char znak;
//		file.get(znak);
//
//		if (znak == '\n') {
//			++licznik_linii;
//			if (licznik_linii == GRAPHIC_WIDTH + 1) {
//				break;
//			}
//		}
//	}
//
//	struct LineFile {
//		char data[DATA_SIZE-1];
//		double open, high, low, close;
//	};
//
//	LineFile* fileLines = new LineFile[GRAPHIC_WIDTH];
//
//	double maxOpen = 0, maxClose = 0, maxLow = 0, maxHigh = 0;
//	double minOpen = -1, minClose = -1, minLow = -1, minHigh = -1;
//	int c = 0;
//	while (file.getline(linia, MAX_LENGTH)) {
//		char* nextToken;
//		char* token;
//		char delimiter[] = ",";
//		token = strtok_s(linia, delimiter, &nextToken);
//		int counter = 0;
//		while (counter != 5) {
//			double token_value = atof(token);
//			switch (counter) {
//			case 0: strcpy_s(fileLines[c].data, sizeof(fileLines[c].data), token); break;
//			case 1: fileLines[c].open = token_value;
//				max_min(token_value, minOpen, maxOpen); break;
//			case 2: fileLines[c].high = token_value;
//				max_min(token_value, minHigh, maxHigh); break;
//			case 3: fileLines[c].low = token_value;
//				max_min(token_value, minLow, maxLow); break;
//			case 4: fileLines[c].close = token_value;
//				max_min(token_value, minClose, maxClose); break;
//			default: break;
//			}
//			token = strtok_s(nullptr, delimiter, &nextToken);
//			counter++;
//		}
//		c++;
//	}
//
//	cout << "\nminOpen: " << minOpen << " minClose: " << minClose << " minLow: " << minLow << " minHigh: " << minHigh << endl;
//	cout << "\nmaxOpen: " << maxOpen << " maxClose: " << maxClose << " maxLow: " << maxLow << " maxHigh: " << maxHigh << endl;
//	double maxValue = max(max(maxOpen, maxClose), max(maxLow, maxHigh));
//	double wspl = (maxValue - min(min(minOpen, minClose), min(minLow, minHigh))) / (GRAPHIC_HEIGHT-2);
//	
//	//double avr_dlg = 0, avr_gor = 0, avr_dol = 0;
//	///* komorka 0 - wartosc miedzy 0 i minLow
//	//* komorka GRAPHIC_HEIGHT-1 - wartosc miedzy maxHigh i + liczba
//	//*/
//	//
//	//cout << "wspl: " << wspl << endl;
//	//for (int i = 0; i < GRAPHIC_WIDTH; ++i) {
//	//	cout << fileLines[i].data << endl;
//
//	//	double dlg_ciala = abs(fileLines[i].open - fileLines[i].close);
//	//	double wys_gor = fileLines[i].high - max(fileLines[i].open, fileLines[i].close);
//	//	double wys_dol = min(fileLines[i].open, fileLines[i].close) - fileLines[i].low;
//
//	//	cout << "O: " << fileLines[i].open << " C: " << fileLines[i].close
//	//		<< " L: " << fileLines[i].low << " H: " << fileLines[i].high;
//
//	//	cout << "\npocz sw (gorna) " << ceil(abs(max(max(fileLines[i].open, fileLines[i].close), max(fileLines[i].low, fileLines[i].high)) - minLow) / wspl);
//	//	cout << " kon sw(dolna) " << floor(abs(min(min(fileLines[i].open, fileLines[i].close), min(fileLines[i].low, fileLines[i].high)) - minLow) / wspl);
//
//	//	cout << "\n'gor' " << ceil(wys_gor / wspl);
//	//	if (fileLines[i].open < fileLines[i].close) {
//	//		
//	//		cout << " '0' " << ceil(dlg_ciala / wspl);
//	//		// poczatek swiecy (gorna czesc) - ceil(abs(fileLines[i].high-minLow)/wspl)
//
//	//		// koniec swiecy (dolna czesc) - ceil(abs(fileLines[i].low-minLow)/wspl)
//	//	}
//	//	else {
//	//		cout << " '#' " << ceil(dlg_ciala / wspl);
//
//	//	}
//	//	cout << " 'dol' " << ceil(wys_dol / wspl);
//
//	//cout << endl;
//
//	//	avr_dlg += dlg_ciala;
//	//	avr_gor += wys_gor;
//	//	avr_dol += wys_dol;
//	//	cout << "dlugosc ciala: " << dlg_ciala << endl;
//	//	cout << "wysokosc cienia gornego: " << wys_gor << endl;
//	//	cout << "wysokosc cienia dolnego: " << wys_dol << endl;
//	//	cout << endl;
//	//}
//	//cout << "Srednia dlugosc: " << avr_dlg / GRAPHIC_WIDTH << endl;
//	//cout << "Srednia wysokosc gorna: " << avr_gor / GRAPHIC_WIDTH << endl;
//	//cout << "Srednia wysokosc dolna: " << avr_dol / GRAPHIC_WIDTH << endl;
//	//cout << endl;
//
//
//	Map map(GRAPHIC_WIDTH, GRAPHIC_HEIGHT, minLow, maxValue, wspl);
//	/*int counter = 0;
//	for (int i = 0; i < 200; i++) {
//		if (i == 5 + 11 * counter) {
//			cout << "|";
//			++counter;
//		}
//		else {
//			cout << "-";
//		}
//		if (i == 199)cout << ">";
//	}
//	cout << endl;
//	counter = 0;
//	for (int i = 1; i < 201; i++) {
//		if (i == 1 + 11 * counter && counter<NUMBER_OF_DATES) {
//			cout << " " << fileLines[i-1].data;
//			++counter;
//		}
//		
//	}
//	cout << endl;*/
//
//
//
//
//	// szukac wspolczynnik podczas wczytywania danych z fileu
//
//	/*int GRAPHIC_HEIGHT = 50;
//	double wspl = (max(max(maxOpen, maxClose), max(maxLow, maxHigh)) - min(min(minOpen, minClose), min(minLow, minHigh))) / GRAPHIC_HEIGHT;
//	cout << wspl << endl;*/
//
//
//	file.close();
//
//}