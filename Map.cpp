#include <iostream>
#include "Map.h"
#include "LineFile.h"
using namespace std;

void Map::initializeMap(int gr_size, int gr_height, double minVal, double maxVal, double coef, int& totalGameHeight) {
	left_border = 8; // zaczynamy od 0
	right_border = 1;
	graph_size = gr_size;
	total_width = graph_size + left_border + right_border;
	graph_height = gr_height;
	down_height = 3; // 3 y to minValue 
	total_height = graph_height + down_height;
	totalGameHeight = total_height;
	minLowVal = minVal;
	maxValue = maxVal;
	coefficient = coef;
	textMap = new char* [total_height];
	allYVal = new double [graph_height];

	number_of_dates = floor(graph_size / (10));

	int c = 0;
	double tempVal = minLowVal;
	while (c < graph_height - 1) {
		allYVal[c] = tempVal;
		tempVal += coefficient;
		++c;
	}
}


void Map::createMap() {
	int counter = 1;

	for (int i = 0; i < total_height; i++) {
		textMap[i] = new char[total_width];
	}

	for (int i = 0; i < total_height; i++) {
		for (int j = 0; j < total_width; j++) {
			// drawing Ox
			if (i == 1) {
				for (int l = 0; l < total_width - 1; l++) {
					textMap[i][l] = '-';
				}
				textMap[1][total_width - 1] = '>';
				//if (j == (9 + counter * 5)) {
				//	textMap[1][j] = '+';
				//	counter++;
				//}

			}
			else if (i == total_height - 1 && j == left_border - 5) {
				for (int k = 0; k < strlen(cena); k++) {
					textMap[i][j + k] = cena[k];
				}
			}
			
			else if (j == 8) {
				// drawing Oy
				textMap[total_height - 1][j] = '^';
				textMap[total_height - 2][j] = '+';

				for (int k = 1; k < total_height - 2; k++) {
					if (k % 2 == 0)
					{
						textMap[k][j] = '|';
					}
					else textMap[k][j] = '-';

				}
				textMap[1][8] = '+';
				textMap[0][8] = '|';
			}
			else {
				if (textMap[i][j] <= 0)	textMap[i][j] = ' ';
				// zapytac na konsultacji jak wyswietlic spacje 
				// (nie chce normalne to sie wyswietlac)
			}
		}
	}
}

// y = 0 - daty |

// zmienic warunek dla wyswietlania allYval
void Map::drawYValues() {
	int i = 3;
	for (int k = 0; k < graph_height - 1; k++) {
		char buf[8]; // liczba typu 22.2222
		sprintf_s(buf, sizeof(buf), "%.4f", allYVal[k]);
		for (int l = 0; l < strlen(buf); l++) {
			textMap[k + i][left_border - 8 + l] = buf[l]; //if (k % 2 == 0)	
		}
	}
}

void Map::drawMap() {
	for (int i = total_height - 1; i >= 0; i--) {
		for (int j = 0; j < total_width; j++) {
			cout << textMap[i][j];
		}
		if (i > 0)	cout << "\n";
	}

}


void Map::deleteMap() {
	for (int i = 0; i < total_height; i++) {
		delete[] textMap[i];
	}
	delete[] textMap;

}

void Map::writeCandleToMap(int index, Candle candle) {
	//if ((index - 5) % 12 == 0) {
	//	for (int k = 0; k < 11; k++) {
	//		textMap[0][index + k] = candle.data[k];
	//	}
	//}
	// writing candle shadows
	for (int i = 0; i < graph_height; i++) {
		if (allYVal[i] == candle.top_gr_minY_value) {
			for (int k = 0; k < candle.top_shadow_height; k++) {
				textMap[down_height + i + k][9 + index] = candle.top_shadow[k];
			}
		}
		if (allYVal[i] == candle.bottom_gr_minY_value) {
			for (int k = 0; k < candle.bottom_shadow_height; k++) {
				textMap[down_height + i + k][9 + index] = candle.bottom_shadow[k];
			}
		}
	}
	// writing candle body
	for (int i = 0; i < graph_height; i++) {
		if (allYVal[i] == candle.bottom_gr_maxY_value) {
			for (int k = 0; k < candle.body_height; k++) {
				textMap[down_height + i + k][9 + index] = candle.body[k];
			}
		}
	}

}