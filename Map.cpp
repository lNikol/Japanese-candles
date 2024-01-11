#include <iostream>
#include "Map.h"
#include "LineFile.h"

using namespace std;


void Map::initializeMap(int gr_size, int gr_height, double minVal, double maxVal, double coef) {
	left_border = 9; // zaczynamy od 0, musi byc 10 a nie 9
	right_border = 1;
	graph_size = gr_size;
	total_width = graph_size + left_border + right_border;
	graph_height = gr_height;
	down_height = 3; // 3 y to spacja 
	total_height = graph_height + down_height + 1;

	minLowVal = minVal;
	maxValue = maxVal;
	coefficient = coef;
	textMap = new char*[total_height];
	allYVal = new double[graph_height];

}


void Map::createMap() {
	for (int i = 0; i < total_height; i++) {
		
		textMap[i] = new char[total_width];
		for (int j = 0; j < total_width; j++) {
			// drawing Ox
			if (i == down_height - 1) {
				if (j == left_border) textMap[i][j] = '+';
				else if (j == total_width - 1) textMap[i][j] = '>';
				else textMap[i][j] = '-';
			}
			else if (i == total_height - 1 && j == left_border-5) {
				for (int k = 0; k < strlen(cena); k++) {
					textMap[i][j+k] = cena[k];
				}
			}
		
			else if (j == left_border) {
				// drawing Oy
				if (i == total_height - 1) textMap[i][j] = '^';
				else {
					if (i % 2 == 0) {
						if (i == total_height - 2) textMap[i][j] = '+';
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

;
}


void Map::drawYValues() {
	int c = 0;
	double tempVal = minLowVal;
	while (c < graph_height - 1) {
		allYVal[c] = tempVal;
		cout << "c= " << c << ", Yval = " << allYVal[c] << endl;
		tempVal += coefficient;
		++c;

	}
	int i = down_height+1;
	for (int k = 0; k < graph_height - 1; k++) {
		char buf[8]; // liczba typu 22.2222
		cout << k << ' ' << allYVal[k] << "all k " << endl;
		sprintf_s(buf, sizeof(buf), "%.4f", allYVal[k]);
		for (int l = 0; l < strlen(buf); l++) {
			if(k%2==0)	textMap[k + i][left_border - 8 + l] = buf[l];
		}
	}
}

void Map::drawMap() {
	for (int i = total_height - 1; i >= 0; i--) {
		for (int j = 0; j < total_width; j++) {
			cout << textMap[i][j];
		}
		//cout << endl;
	}
}


void Map::deleteMap() {
	for (int i = 0; i < total_height; i++) {
		delete[] textMap[i];
	}
	delete[] textMap;

}

void Map::drawCandle() {
	for (int i = total_height - 1; i >= 0; i--) {
		//cout << endl;
	}
}

void Map::calcPixels() {

}