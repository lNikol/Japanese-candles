#define _CRT_SECURE_NO_WARNINGS
#include "FileSystem.h"
#include <iostream>
#include <fstream>

using namespace std;


void max_min(double& value, double& min, double& max) {
	if (min == -1) min = value;
	value > max ? max = value : 0;
	value < min ? min = value : 0;
}

void FileSystem::initializeFileSystem() {
	end_data_x = infoLength - 1;
	start_data_x = 0;
	size_data_x = end_data_x - start_data_x;
}

void FileSystem::setGameFileLines(LineFile gameFileLines[]) {
	for (int i = 0; i < infoLength; i++) {
		gameFileLines[i] = fileLines[i];
	}
}


void FileSystem::readFile(char* readFile) {

	//bool withDot = false;
	//for (int i = 0; i < strlen(readFile); i++) {
	//	if (readFile[i] == '.') withDot = true;
	//}

	// доделать проверку на имя файла
	// если отсутствует .csv, то дописать
	// иначе прочитать файл по имени
	const char X[259] = "X";

	file.open(readFile, ios::binary);
	while (!file.is_open()) {
		cout << "The file cannot be opened (or the file does not exist, or select another file or write X to select default file)" << endl;
		cin >> readFile;
		//bool withDot = false;
		//for (int i = 0; i < strlen(readFile); i++) {
		//	if (readFile[i] == '.') { withDot = true; break; }
		//}
		//if (!withDot) strcat_s(readFile, sizeof(readFile), ".csv");
		if (strcmp(readFile, X) == 0) {
			cout << "The default file was selected\n";
			readFile = defaultReadFile;
			//strcpy_s(readFile, sizeof(readFile), defaultReadFile);
		}
		file.open(readFile, ios::binary);

	}

	int licznik_linii = 0;
	file.seekg(0, ios::end);
	streampos amountOfSymbols = file.tellg(); // przesuniecie wskaznika pozycji odczytu


	int position = file.tellg();
	int t = 0; // t liczy ilosc \n od konca pliku
	char znak = '\n' - 1;

	while (--position >= 0 && znak <= '\n') {
		file.seekg(position, ios::beg); // przesuniecie pozycji
		file.get(znak);
		if (znak == '\n') ++t;
	}

	file.seekg(0, ios::beg);
	position = file.tellg();
	while (++position <= amountOfSymbols) {
		file.seekg(position, ios::beg); // przesuniecie pozycji
		char zn;
		file.get(zn);
		if (zn == '\n') {
			++licznik_linii;
		}
	}

	infoLength = licznik_linii - 1 - t; // t liczy ilosc \n od konca pliku
	fileLines = new LineFile[infoLength];
	file.close();

	file.open(readFile, ios::binary);
	if (!file.is_open()) {
		cout << "The file cannot be opened" << endl;
		return;
	}
	file.seekg(0, ios::beg);

	int c = 0;
	const int MAX_LENGTH = 128;
	char linia[MAX_LENGTH];
	file.getline(linia, MAX_LENGTH); // nie czytam linii z "Date, Open, Low..."
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
			case 1: fileLines[c].open = token_value; break;
			case 2: fileLines[c].high = token_value; break;
			case 3: fileLines[c].low = token_value; break;
			case 4: fileLines[c].close = token_value; break;
			default: break;
			}
			token = strtok_s(nullptr, delimiter, &nextToken);
			counter++;
		}
		c++;
	}

	end_data_x = infoLength - 1;
	start_data_x = 0;
	size_data_x = end_data_x - start_data_x;
	
	file.close();
}

void FileSystem::findMaxMin() {
	double maxOpen = 0, maxClose = 0, maxLow = 0, maxHigh = 0;
	double minOpen = -1, minClose = -1, minLow = -1, minHigh = -1;
	for (int i = start_data_x; i < end_data_x; i++) {
		max_min(fileLines[i].open, minOpen, maxOpen);
		max_min(fileLines[i].close, minClose, maxClose);

		max_min(fileLines[i].high, minHigh, maxHigh);
		max_min(fileLines[i].low, minLow, maxLow);
	}

	maxValue = max(max(maxOpen, maxClose), max(maxLow, maxHigh));
	minValue = min(min(minOpen, minClose), min(minLow, minHigh));

}


void FileSystem::findDate(char date[], int& dateIndex) {
	for (int i = 0; i < infoLength; i++) {
		if (strcmp(date, fileLines[i].data) == 0 && i >= start_data_user_x) { dateIndex = i; break; }
		else { if (i == infoLength - 1) strcpy_s(date, sizeof(date), "false"); }
	}
}


void FileSystem::saveInfoToLog(const char info[]) {
	time_t currentTime = time(nullptr);

	struct tm* localTime = localtime(&currentTime);

	ofstream outputFile("log.log", ios::app);

	if (!outputFile.is_open()) {
		cerr << "File opening error!" << endl;
	}

	outputFile << "[" << localTime->tm_year + 1900 << "-";
	if ((localTime->tm_mon + 1) < 10) {
		outputFile << "0" << localTime->tm_mon + 1;
	}
	else outputFile << localTime->tm_mon + 1;
	outputFile << "-" << localTime->tm_mday << " " << localTime->tm_hour << ":";

	if ((localTime->tm_min) < 10) {
		outputFile << "0" << localTime->tm_min<<":";
	}
	else outputFile << localTime->tm_min<<":";

	if ((localTime->tm_sec) < 10) {
		outputFile << "0" << localTime->tm_sec<<"]       : ";
	}
	else outputFile << localTime->tm_sec<<"]       : ";

	outputFile << info << endl;
	outputFile.close();
}