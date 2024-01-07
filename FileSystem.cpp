#include "FileSystem.h"
#include <iostream>
#include <fstream>
using namespace std;

FileSystem::FileSystem() {
	for (int i = 0; i < maxRows; ++i) {
		dateArr[i] = new char[lengthOfRow];
	}
}

void FileSystem::readFile(int lengthOfRead = 100) {
	ifstream csvFile;
	ofstream outputFile;
	csvFile.open(defaultInputFile);
	if (csvFile.is_open()) {
		char line[128];
		char date[11];
		// otrzymam wartosci z A2
		csvFile.getline(line, 100);
		csvFile.getline(line, 100);
		int i = 1;
		while (i < 50) {
			cout << endl;
			char* nextToken;
			char* token;
			char test[128];
			char delimiter[] = ",";
			token = strtok_s(line, delimiter, &nextToken);
			int counter = 0;
			double info[4]; // 0 - open, 1 - high, 2 - low, 3 - close; 1 i 2 - długość cienia, 0 i 3 - długość ciała świecy 
			while (counter != 5) {
				if (counter >= 1)
				{
					info[counter - 1] = atof(token); // convert to double
				}
				else dateArr[i] = token;
				if (counter == 4) {
					cout << "h-l: " << info[1] - info[2] << endl;
					cout << "o-c: " << info[0] - info[3] << endl;
				}

				token = strtok_s(nullptr, delimiter, &nextToken);
				counter++;
			}
			csvFile.getline(line, 100); // 100 - size of information
			i++;
		}
		outputFile.open(defaultOutputFile, ios::in);
		if (outputFile.is_open()) {

			outputFile.close();
		}
		csvFile.close();
	}
}

void max_min(double& value, double& min, double& max) {
	if (min == -1) min = value;
	value > max ? max = value : 0;
	value < min ? min = value : 0;
}

void FileSystem::readFile2(int lengthOfRead = 100) {
	ifstream plik;
	plik.open(defaultInputFile, ios::binary);
	if (!plik.is_open()) {
		cout << "The file cannot be opened" << endl;
	}

	const int MAX_LENGTH = 128;
	const int NUMBER_OF_LINES = 200;
	const int COLS = 4;
	char linia[MAX_LENGTH];
	int licznik_linii = 0;

	plik.seekg(0, std::ios::end);
	int pozycja = plik.tellg();

	while (--pozycja >= 0) {
		plik.seekg(pozycja, std::ios::beg);
		char znak;
		plik.get(znak);

		if (znak == '\n') {
			++licznik_linii;
			if (licznik_linii == NUMBER_OF_LINES + 1) {
				break;
			}
		}
	}

	struct LineFile {
		char data[14];
		double open, high, low, close;
	};

	LineFile* fileLines = new LineFile[NUMBER_OF_LINES];




	double maxOpen = 0, maxClose = 0, maxLow = 0, maxHigh = 0;
	double minOpen = -1, minClose = -1, minLow = -1, minHigh = -1;
	int c = 0;
	while (plik.getline(linia, MAX_LENGTH)) {
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
	double avr_dlg = 0, avr_gor = 0, avr_dol = 0;

	cout << "\nminOpen: " << minOpen << " minClose: " << minClose << " minLow: " << minLow << " minHigh: " << minHigh << endl;
	cout << "\nmaxOpen: " << maxOpen << " maxClose: " << maxClose << " maxLow: " << maxLow << " maxHigh: " << maxHigh << endl;

	int graphic_height = 50;
	double wspl = (max(max(maxOpen, maxClose), max(maxLow, maxHigh)) - min(min(minOpen, minClose), min(minLow, minHigh))) / graphic_height;
	cout << "wspl: " << wspl << endl;


	for (int i = 0; i < NUMBER_OF_LINES; ++i) {
		cout << fileLines[i].data << endl;
		if (fileLines[i].open > maxOpen) maxOpen = fileLines[i].open;
		if (fileLines[i].close > maxClose) maxClose = fileLines[i].close;
		if (fileLines[i].low > maxLow) maxLow = fileLines[i].low;
		if (fileLines[i].high > maxHigh) maxHigh = fileLines[i].high;

		if (fileLines[i].open < minOpen) minOpen = fileLines[i].open;
		if (fileLines[i].close < minClose) minClose = fileLines[i].close;
		if (fileLines[i].low < minLow) minLow = fileLines[i].low;
		if (fileLines[i].high < minHigh) minHigh = fileLines[i].high;

		double dlg_ciala = abs(fileLines[i].open - fileLines[i].close);
		double wys_gor = fileLines[i].high - max(fileLines[i].open, fileLines[i].close);
		double wys_dol = min(fileLines[i].open, fileLines[i].close) - fileLines[i].low;


		cout << "O: " << fileLines[i].open << " C: " << fileLines[i].close
			<< " L: " << fileLines[i].low << " H: " << fileLines[i].high;


		cout << "\n'gor' " << ceil(wys_gor / wspl);
		if (fileLines[i].open < fileLines[i].close) {
			cout << " '0' " << ceil(dlg_ciala / wspl);
		}
		else {
			cout << " '#' " << ceil(dlg_ciala / wspl);

		}
		cout << " 'dol' " << ceil(wys_dol / wspl);

		cout << endl;

		avr_dlg += dlg_ciala;
		avr_gor += wys_gor;
		avr_dol += wys_dol;
		//cout << "dlugosc ciala: " << dlg_ciala << endl;
		//cout << "wysokosc cienia gornego: " << wys_gor << endl;
		//cout << "wysokosc cienia dolnego: " << wys_dol << endl;
		cout << endl;
	}
	cout << "Srednia dlugosc: " << avr_dlg / NUMBER_OF_LINES << endl;
	cout << "Srednia wysokosc gorna: " << avr_gor / NUMBER_OF_LINES << endl;
	cout << "Srednia wysokosc dolna: " << avr_dol / NUMBER_OF_LINES << endl;


	// szukac wspolczynnik podczas wczytywania danych z pliku

	/*int graphic_height = 50;
	double wspl = (max(max(maxOpen, maxClose), max(maxLow, maxHigh)) - min(min(minOpen, minClose), min(minLow, minHigh))) / graphic_height;
	cout << wspl << endl;*/


	plik.close();

	//for (int i = 0; i < NUMBER_OF_LINES; ++i) {
	//	for (int j = 0; j < COLS; ++j) {
	//		delete[] fileLines[i][j];
	//	}
	//	delete[] fileLines[i];
	//}
	//delete[] fileLines;

	//if (csvFile.is_open()) {
	//	char line[128];
	//	int i = 1;
	//	while (i < 2) {
	//		cout << endl;
	//		char* nextToken;
	//		char* token;
	//		char test[128];
	//		char delimiter[] = ",";
	//		token = strtok_s(line, delimiter, &nextToken);
	//		int counter = 0;
	//		double info[4]; // 0 - open, 1 - high, 2 - low, 3 - close; 1 i 2 - długość cienia, 0 i 3 - długość ciała świecy 
	//		while (counter != 5) {
	//			if (counter >= 1)
	//			{
	//				info[counter - 1] = atof(token); // convert to double
	//			}
	//			else dateArr[i] = token;
	//			if (counter == 4) {
	//				cout << "h-l: " << info[1] - info[2] << endl;
	//				cout << "o-c: " << info[0] - info[3] << endl;
	//			}

	//			token = strtok_s(nullptr, delimiter, &nextToken);
	//			counter++;
	//		}
	//		csvFile.getline(line, 100); // 100 - size of information
	//		i++;
	//	}
	//	outputFile.open(defaultOutputFile, ios::in);
	//	if (outputFile.is_open()) {

	//		outputFile.close();
	//	}
	//	csvFile.close();
	//}
}