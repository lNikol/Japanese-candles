#pragma once
#include "Candle.h"

struct Map {
public:
	int graph_size;
	int left_border; 
	int right_border;
	int total_width;
	int graph_height;
	int number_of_dates;
	int spaceForTwoDates = 17; //11 * 2 + 1

	int down_height; 
	int total_height;
	double minLowVal, maxValue;
	double coefficient;
	char **textMap;

	double* allYVal;

	char cena[5] = "cena";
	
	void initializeMap(int, int, double, double, double, int&);
	void createMap();
	void drawYValues();
	void drawMap();
	void deleteMap();
	void writeCandleToMap(int index, Candle candle, Candle arr[], int end_data_scale_x, int amountOfDates);
	void drawCandlesDates(int start_date_index, Candle arr[], int endT, int amountOfDates, int candle_scale);

};