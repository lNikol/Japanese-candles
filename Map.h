#pragma once
struct Map {
public:
	const int GRAPH_SIZE;
	const int LEFT_BORDER = 9; // zaczynamy od 0, musi byc 10 a nie 9
	const int RIGHT_BORDER = 1;
	const int TOTAL_WIDTH = GRAPH_SIZE + LEFT_BORDER + RIGHT_BORDER;
	const int GRAPH_HEIGHT;
	//const int TOP_HEIGHT = 0;
	const int DOWN_HEIGHT = 3; // 3 y to spacja 
	const int TOTAL_HEIGHT = GRAPH_HEIGHT + DOWN_HEIGHT+1;
	double minLowVal, maxValue;
	double coefficient;
	char **textMap = new char*[TOTAL_HEIGHT];

	double* allYVal = new double[GRAPH_HEIGHT];

	char cena[5] = "cena";
	Map(int graphSize, int graphHeight, double minLowValue, double maxVal, double coef) :
		GRAPH_SIZE(graphSize), GRAPH_HEIGHT(graphHeight), minLowVal(minLowValue), maxValue(maxVal), coefficient(coef) {
		createMap();
	};
	void createMap();
	void drawLeftBorder();
	void drawRightBorder();
	void drawYValues();
	void drawMap();
	void deleteMap();
};