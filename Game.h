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
	int dataLength = 11;
	int weekCounter = 0;
	int monthCounter = 0;
	char* start_data = new char[dataLength];
	char* end_data = new char[dataLength];


	double minValue, maxValue, coefficient;
	Game(int graph_width = 200, int graph_h = 50) : graphic_width(graph_width), graphic_height(graph_h) {};


	// переписать graphic_width на переменную пользователя по кол-ву вводных данных

	LineFile* fileLines = new LineFile[graphic_width];
	Candle* allCandles = new Candle[graphic_width];
	Candle* weeks_Candles = new Candle[graphic_width / 5];
	Candle* month_Candles = new Candle[graphic_width / 20];

	Map map;
	FileSystem fileSys;
	Controller controller;

	void initializeGame(int, int);
	void initializeGameDates(char*, char*);
	void createGameMap(Candle arr[], int graphic_w);
	void calcPixels(Candle arr[], int graphic_w);
	void doCandle(double open, double close, double low, double high, Candle& candle);

	void groupCandles(int start_ind, int end_ind, Candle one, Candle two, Candle arr[], int& counter);

}; 