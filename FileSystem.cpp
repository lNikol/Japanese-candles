#define _CRT_SECURE_NO_WARNINGS
#include "FileSystem.h"
#include <iostream>
#include <fstream>

using namespace std;


void max_min(float& value, float& min, float& max) {
	if (min == -1) min = value;
	value > max ? max = value : 0;
	value < min ? min = value : 0;
	return;
}


void FileSystem::deleteFileLines() {
	cout << "before delete[] fileLines\n";
	delete[] fileLines;
	cout << "after delete[] fileLines\n";
	return;

}

void FileSystem::initializeFileSystem(char fileName[]) {
	cout << "in initializeFileSystem\n";

	deleteFileLines();
	readFile(fileName);
	end_data_x = end_data_user_x == -1 ? infoLength - 1 : end_data_user_x;
	start_data_x = start_data_user_x == -1 ? 0 : start_data_user_x;
	cout << "end_data_user_x: " << end_data_user_x << " end_data_x: " << end_data_x << endl;
	cout << "start_data_user_x: " << start_data_user_x << " start_data_x: " << start_data_x << endl;
	size_data_x = end_data_x - start_data_x;
	cout << "size_data_x: " << size_data_x << endl;
	cout << "after initializeFileSystem\n";
	return;

}

void FileSystem::setGameFileLines(LineFile gameFileLines[]) {
	for (int i = 0; i < infoLength; i++) {
		gameFileLines[i] = fileLines[i];
	}
	return;

}


void FileSystem::readFile(char* readFile) {
	const char X[259] = "X";

	file.open(readFile, ios::binary);
	while (!file.is_open()) {
		cout << "The file cannot be opened (or the file does not exist, or select another file or write X to select default file)" << endl;
		cin >> readFile;
		if (strcmp(readFile, X) == 0) {
			cout << "The default file was selected\n";
			readFile = defaultReadFile;
			//strcpy_s(readFile, sizeof(readFile), defaultReadFile);
		}
		file.open(readFile, ios::binary);

	}

	short licznik_linii = 0;

	file.seekg(0, ios::beg);
	int position = file.tellg();
	cout << "before ++position, position = "<< position<<"\n";
	while (++position && file.eof() == false) {
		file.seekg(position, ios::beg); // przesuniecie pozycji
	//	cout<<"in ++: ";
		char zn;
		file.get(zn);

		if (zn == '\n' && file.eof() == false) {
			++licznik_linii;
		}
		else if(file.eof()==true) {
			cout << "file.eof: " << file.eof() << " licznik_linii: " << licznik_linii << " ";
		}
	}
	cout << "\nafter ++position, position = " << position << "\n";

	cout<< "l_l: " << licznik_linii << endl;
	infoLength = licznik_linii - 1; 
	cout<<"infoLength: " << infoLength << endl;
	fileLines = new LineFile[infoLength];
	cout << "after fileLines = new " << endl;
	file.close();

	file.open(readFile, ios::binary);
	if (!file.is_open()) {
		cout << "The file cannot be opened" << endl;
		return;
	}
	file.seekg(0, ios::beg);
	cout << "before c=0 \n";
	int c = 0;
	const short MAX_LENGTH = 128;
	char linia[MAX_LENGTH];
	cout << "before file.getline(date,open..) \n";
	file.getline(linia, MAX_LENGTH); // nie czytam linii z "Date, Open, Low..."
	cout << "after file.getline(date,open..) \n";

	while (file.getline(linia, MAX_LENGTH) && linia[0] != '\n' && linia[0] != '\0') {
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
		//cout << int(linia[0]) << " c: " << c << " ";

	}
	cout << "last data: "<<fileLines[infoLength-1].data << endl;
	end_data_x = infoLength - 1;
	start_data_x = 0;
	size_data_x = end_data_x - start_data_x;
	
	file.close();
	return;

}

void FileSystem::findMaxMin() {
	float maxOpen = 0, maxClose = 0, maxLow = 0, maxHigh = 0;
	float minOpen = -1, minClose = -1, minLow = -1, minHigh = -1;
	for (int i = start_data_x; i <= end_data_x; i++) {
		max_min(fileLines[i].open, minOpen, maxOpen);
		max_min(fileLines[i].close, minClose, maxClose);

		max_min(fileLines[i].high, minHigh, maxHigh);
		max_min(fileLines[i].low, minLow, maxLow);
	}

	maxValue = max(max(maxOpen, maxClose), max(maxLow, maxHigh));
	minValue = min(min(minOpen, minClose), min(minLow, minHigh));
	return;
}


void FileSystem::findDate(char date[], int& dateIndex) {
	for (int i = 0; i < infoLength; i++) {
		if (strcmp(date, fileLines[i].data) == 0 && i >= start_data_user_x) { dateIndex = i; break; }
		else { if (i == infoLength - 1) strcpy_s(date, sizeof(date), "false"); }
	}
	return;

}


void FileSystem::saveInfoToLog(const char info[]) {
	time_t currentTime = time(nullptr);

	struct tm* localTime = localtime(&currentTime);
	cout << "in saveInfoToLog before open\n";
	ofstream outputFile("log.log", ios::app);
	cout << "in saveInfoToLog after open\n";

	if (!outputFile.is_open()) {
		cerr << "File opening error!" << endl;
		return;
	}
	cout << "before tm_year ";
	outputFile << "[" << localTime->tm_year + 1900 << "-";
	cout << "after tm_year ";
	cout << "before tm_mon ";

	if ((localTime->tm_mon + 1) < 10) {
		outputFile << "0" << localTime->tm_mon + 1;
	}
	else outputFile << localTime->tm_mon + 1;
	cout << "after tm_mon ";
	cout << "before tm_mday i tm_hour ";

	outputFile << "-" << localTime->tm_mday << " " << localTime->tm_hour << ":";
	cout << "after tm_mday i tm_hour ";
	cout << "before tm_min ";

	if ((localTime->tm_min) < 10) {
		outputFile << "0" << localTime->tm_min<<":";
	}
	else outputFile << localTime->tm_min<<":";
	cout << "after tm_min ";
	cout << "before tm_sec ";

	if ((localTime->tm_sec) < 10) {
		outputFile << "0" << localTime->tm_sec<<"]       : ";
	}
	else outputFile << localTime->tm_sec<<"]       : ";
	cout << "after tm_sec \n";
	cout << "before << info ";

	outputFile << info << endl;
	cout << "after << info ";
	cout << "before close ";

	outputFile.close();
	cout << "after close\n";

	cout << "in saveInfoToLog after all\n";
	return;

}