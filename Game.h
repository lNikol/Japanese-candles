#pragma once
#include "LineFile.h"
#include "FileSystem.h"
#include "Map.h"
#include "Candle.h"

struct Game
{
	int graphic_width;
	int graphic_height;
	int total_height;
	int down_height;
	int amountOfDates;

	int dataLength = 11;
	int otherCounter = 0;
	char* start_data = new char[dataLength];
	char* end_data = new char[dataLength];
	bool isCreated = false;

	double minValue, maxValue, coefficient;
	Game(int graph_width = 200, int graph_h = 50) : graphic_width(graph_width), graphic_height(graph_h) {};

	LineFile* fileLines;
	Candle* allCandles;
	Candle* scale_array;

	Map map;
	FileSystem fileSys;

	void initializeGame(int, int);
	void createGameMap(int, int, int, int, int, int);
	void doCandle(double open, double close, double low, double high, Candle& candle);
	Candle groupCandles(int start_ind, int end_ind);


	void defaultMap(char[], int);
}; 