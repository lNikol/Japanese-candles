#pragma once
struct Map {
public:

	int graph_size;
	int left_border; 
	int right_border;
	int total_width;
	int graph_height;
	//const int TOP_HEIGHT = 0;
	int down_height; // 3 y to spacja 
	int total_height;
	double minLowVal, maxValue;
	double coefficient;
	char **textMap;

	double* allYVal;

	char cena[5] = "cena";
	
	void initializeMap(int, int, double, double, double);
	void createMap();
	void drawYValues();
	void drawMap();
	void drawCandle();
	void calcPixels();
	void deleteMap();
};