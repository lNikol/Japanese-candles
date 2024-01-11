#pragma once
#include "LineFile.h"
#include "FileSystem.h"
#include "Map.h"
#include "Controller.h"

struct Game
{
	int graphic_width;
	int graphic_height;

	int dataLength = 12;
	char* start_data = new char[dataLength];
	char* end_data = new char[dataLength];


	double minValue, maxValue, coefficient;
	Game(int graph_width = 200, int graph_h = 50) : graphic_width(graph_width), graphic_height(graph_h) {};
	LineFile* fileLines = new LineFile[graphic_width];
	Map map;

	/*Map(int graphSize, int graphHeight, double minLowValue, double maxVal, double coef) :
		GRAPH_SIZE(graphSize), graph_height(graphHeight), minLowVal(minLowValue), maxValue(maxVal), coefficient(coef) {
		createMap();
	};*/
	FileSystem fileSys;
	Controller controller;

	void initializeGame(int, int);
	void initializeGameDates(char*, char*);
	void createGameMap();
};