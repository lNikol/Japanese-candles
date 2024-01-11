#include <iostream>
#include "Map.h"
using namespace std;

void Map::createMap() {
	for (int i = 0; i < TOTAL_HEIGHT; i++) {
		
		textMap[i] = new char[TOTAL_WIDTH];
		for (int j = 0; j < TOTAL_WIDTH; j++) {
			// drawing Ox
			if (i == DOWN_HEIGHT - 1) {
				if (j == LEFT_BORDER) textMap[i][j] = '+';
				else if (j == TOTAL_WIDTH - 1) textMap[i][j] = '>';
				else textMap[i][j] = '-';
			}
			else if (i == TOTAL_HEIGHT - 1 && j == LEFT_BORDER-5) {
				for (int k = 0; k < strlen(cena); k++) {
					textMap[i][j+k] = cena[k];
				}
			}
		
			else if (j == LEFT_BORDER) {
				// drawing Oy
				if (i == TOTAL_HEIGHT - 1) textMap[i][j] = '^';
				else {
					if (i % 2 == 0) {
						if (i == TOTAL_HEIGHT - 2) textMap[i][j] = '+';
						else textMap[i][j] = '-';
					}
					else textMap[i][j] = '|';
					//else textMap[i][j] = '|';
				}
			}
			else {
				if (textMap[i][j] <= 0)	textMap[i][j] = '*';
				// zapytac na konsultacji jak wyswietlic spacje 
				// (nie chce normalne to sie wyswietlac)
			}
		}
	}

	drawYValues();

	drawMap();
}

void Map::drawLeftBorder() {

}
void Map::drawYValues() {
	int c = 0;
	double tempVal = minLowVal;
	while (c<GRAPH_HEIGHT-1) {
		allYVal[c] = tempVal;
		cout << "c= " << c << ", Yval = " << allYVal[c] << endl;
		tempVal += coefficient;
		++c;

	}
	int i = DOWN_HEIGHT+1;
	for (int k = 0; k < GRAPH_HEIGHT-1; k++) {
		char buf[8]; // liczba typu 22.2222
		cout << k << ' ' << allYVal[k] << "all k " << endl;
		sprintf_s(buf, sizeof(buf), "%.4f", allYVal[k]);
		for (int l = 0; l < strlen(buf); l++) {
			if(k%2==0)	textMap[k + i][LEFT_BORDER - 8 + l] = buf[l];
		}
	}


	
}
void Map::drawRightBorder() {

}

void Map::drawMap() {
	for (int i = TOTAL_HEIGHT - 1; i >= 0; i--) {
		for (int j = 0; j < TOTAL_WIDTH; j++) {
			cout << textMap[i][j];
		}
		//cout << endl;
	}
}


void Map::deleteMap() {
	for (int i = 0; i < TOTAL_HEIGHT; i++) {
		delete[] textMap[i];
	}
	delete[] textMap;

}