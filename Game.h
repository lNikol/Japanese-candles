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
	int weekCounter = 0;
	int monthCounter = 0;
	int otherCounter = 0;
	char* start_data = new char[dataLength];
	char* end_data = new char[dataLength];


	double minValue, maxValue, coefficient;
	Game(int graph_width = 200, int graph_h = 50) : graphic_width(graph_width), graphic_height(graph_h) {};


	// переписать graphic_width на переменную пользователя по кол-ву вводных данных

	LineFile* fileLines;
	Candle* allCandles;
	Candle* weeks_Candles;
	Candle* month_Candles;
	Candle* other_Candles;

	Map map;
	FileSystem fileSys;

	void initializeGame(int, int);
	void initializeGameDates(char*, char*);
	void createGameMap(char type, int scale);
	void doCandle(double open, double close, double low, double high, Candle& candle);

	void groupCandles(int start_ind, int end_ind, Candle arr[], int& arrCounter);

}; 