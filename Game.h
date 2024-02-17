#pragma once
#include "LineFile.h"
#include "FileSystem.h"
#include "Map.h"
#include "Candle.h"

struct Game
{
	short graphic_width;
	short graphic_height;
	int amountOfDates;
	int length_of_scale_array;
	short dataLength = 11;

	float minValue, maxValue, coefficient;
	Game(short graph_width = 200, short graph_h = 50) : graphic_width(graph_width), graphic_height(graph_h) {};

	LineFile* fileLines;
	Candle* allCandles;
	Candle* scale_array;

	Map map;
	FileSystem fileSys;

	void initializeGame(short, short);
	void createGameMap(short candle_scale, int start_data_x, int end_data_x, short graph_height, short graph_size, int size_data_x);
	void doCandle(float open, float close, float low, float high, Candle& candle);
	Candle groupCandles(int start_ind, int end_ind);


	void defaultMap(char[], short);
	void deleteGameInfo();
}; 