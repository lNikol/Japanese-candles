#pragma once
#include "Candle.h"

struct Map {
public:
	short graph_size;
	short left_border;
	short total_width;
	short graph_height;
	int number_of_dates;
	int spaceForTwoDates = 17; 

	short down_height;
	short total_height;
	float minLowVal, maxValue;
	float coefficient;
	char **textMap;

	float* allYVal;

	char cena[5] = "cena";
	
	void initializeMap(short, short, float, float, float);
	void createMap();
	void drawYValues();
	void drawMap();
	void deleteMap();
	void writeCandleToMap(int index, Candle candle, Candle arr[], int end_data_scale_x);
	void drawCandlesDates(int start_date_index, Candle arr[], int endT, int amountOfDates, int candle_scale);

};