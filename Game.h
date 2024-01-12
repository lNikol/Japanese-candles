#pragma once
#include "LineFile.h"
#include "FileSystem.h"
#include "Map.h"
#include "Controller.h"
#include "Candle.h"

struct Game
{
	int graphic_width;
	int graphic_height;
	int total_height;
	int down_height;
	int dataLength = 12;
	char* start_data = new char[dataLength];
	char* end_data = new char[dataLength];


	double minValue, maxValue, coefficient;
	Game(int graph_width = 200, int graph_h = 50) : graphic_width(graph_width), graphic_height(graph_h) {};

	LineFile* fileLines = new LineFile[graphic_width];
	Candle* allCandles = new Candle[graphic_width];
	Candle* weeks_Candles = new Candle[graphic_width / 5];
	Candle* month_Candles = new Candle[graphic_width / 20];

	Map map;
	FileSystem fileSys;
	Controller controller;

	void initializeGame(int, int);
	void initializeGameDates(char*, char*);
	void createGameMap();
	void calcPixels();
	void doCandle(double open, double close, double low, double high, Candle& candle);
};