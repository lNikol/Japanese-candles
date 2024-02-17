#include "Game.h"
#include <iostream>

	void Game::initializeGame(int gr_w, int gr_h) {
	std::cout << "in initializeGame\n";
	graphic_width = gr_w;
	graphic_height = gr_h;
	otherCounter = 0;
	amountOfDates = fileSys.infoLength;

	fileSys.findMaxMin();

	maxValue = fileSys.maxValue;
	minValue = fileSys.minValue;

	fileLines = new LineFile[amountOfDates];
	allCandles = new Candle[amountOfDates];

	fileSys.setGameFileLines(fileLines);


	for (int i = 0; i < amountOfDates; i++) {
		Candle candle = Candle();
		allCandles[i] = candle;
		allCandles[i].initializeCandle(graphic_height);
	}
	std::cout << "in initializeGame after code\n";

}

void Game::createGameMap(int candle_scale, int start_data_x, int end_data_x, int graph_height, int graph_size, int size_data_x) {
	coefficient = (maxValue - minValue) / (graphic_height - 2);
	map.initializeMap(graph_size, graph_height, minValue, maxValue, coefficient, total_height);
	map.createMap();
	map.drawYValues();
	
	for (int i = fileSys.start_data_x; i <= fileSys.end_data_x; i++) {
		strcpy_s(allCandles[i].data, sizeof(allCandles[i].data), fileLines[i].data);
		doCandle(fileLines[i].open, fileLines[i].close,
			fileLines[i].low, fileLines[i].high, allCandles[i]);
	}

	length_of_scale_array = 0;
	if (size_data_x % candle_scale == 0 && size_data_x > 1) length_of_scale_array = size_data_x / candle_scale;
	else length_of_scale_array = size_data_x / candle_scale + 1;

	int size_data_scale_x = length_of_scale_array;
	scale_array = new Candle[length_of_scale_array];
	
	int j = 0;
	int end_candle_x = 0; // indeks ostatniej swiecy
	for (int i = start_data_x; i <= end_data_x; i++) // start_data_x + 1
	{
		if (i + candle_scale > end_data_x) end_candle_x = end_data_x - i;
		else if (i + candle_scale == end_data_x) {}
		else {
			end_candle_x = candle_scale;
		}
		scale_array[j] = groupCandles(i, i + end_candle_x);
		i = end_candle_x == 0 ? i : i + end_candle_x - 1;
		j++;
	}

	int start_data_scale_x = 0;
	int end_data_scale_x = j - 1;
	if (size_data_scale_x > graph_size) {
		start_data_scale_x = abs(end_data_scale_x - graph_size + 1);
		std::cout << "The number of candles exceeds the width of the graphic\n"
			<< "the last " << abs(end_data_scale_x - start_data_scale_x + 1)
			<< " positions will be shown" << std::endl; // czy trzeba tu +1?
		// jesli trzeba bedzie zapisac dane do pliku, to trzeba sprawdzic czy poprawnie zapisane
	}
	for (int k = start_data_scale_x; k <= end_data_scale_x - 1; k++) {
		map.writeCandleToMap(k - start_data_scale_x, scale_array[k], scale_array, end_data_scale_x);
	}

	map.drawCandlesDates(start_data_scale_x, scale_array, end_data_scale_x, end_data_scale_x - start_data_scale_x + 1, candle_scale);


}

	//масштаб candle_scale = 10
		// game.fileSys.start_data_x - начало расчета  =  101
		// game.fileSys.end_data_x - конец расчета по оси иксов = 6100
		// graph_height - высота графика = 100
		// graph_size - ширина графика  = 200
		// game.fileSys.size_data_x - размер в точках (кол-во дат) = game.fileSys.end_data_x - game.fileSys.start_data_x + 1;
		// };


void Game::doCandle(double open, double close, double low, double high, Candle& candle) {
	candle.calcBody(open, close, coefficient, map.allYVal);
	candle.calcTopShadow(low, high, coefficient, map.allYVal);
	candle.calcDownShadow(low, high, coefficient, map.allYVal);
}

Candle Game::groupCandles(int start_ind, int end_ind) {
	// start_ind - index of start candle
	// end_ind - index of end candle
	double lowVal = allCandles[start_ind].candle_low;
	double maxVal = allCandles[start_ind].candle_high;
	for (int i = start_ind; i <= end_ind; i++) {
		if (allCandles[i].candle_low < lowVal) {
			lowVal = allCandles[i].candle_low;
		}
		if (allCandles[i].candle_high > maxVal) {
			maxVal = allCandles[i].candle_high;
		}
	}

	Candle candle = Candle();
	candle.initializeCandle(graphic_height);
	candle.candle_open = allCandles[start_ind].candle_open;
	candle.candle_close = allCandles[end_ind].candle_close;
	candle.candle_low = lowVal;
	candle.candle_high = maxVal;

	strcpy_s(candle.data, sizeof(candle.data), allCandles[end_ind].data);

	doCandle(candle.candle_open, candle.candle_close, candle.candle_low, candle.candle_high, candle);
	return candle;
}



void Game::defaultMap(char inputFileName[], int cndle_scale) {
	fileSys.readFile(inputFileName);
	fileSys.size_data_x = 200;
	if (cndle_scale == 1) {
		fileSys.start_data_x = fileSys.end_data_x - 200;
		fileSys.size_data_x = fileSys.end_data_x - fileSys.start_data_x + 1;
	}
	fileSys.findMaxMin();
	initializeGame(200, 50);
	createGameMap(cndle_scale, fileSys.start_data_x, fileSys.end_data_x, 50, 200, fileSys.size_data_x);
}

void Game::deleteGameInfo() {
	std::cout << "in deleteGameInfo\n";
	for (int i = 0; i < amountOfDates; i++) {
		allCandles[i].deleteCandle();
	}
	std::cout << "after for_1 in deleteGameInfo\n";
	for (int i = 0; i < length_of_scale_array; ++i) {
		scale_array[i].deleteCandle();
	}
	std::cout << "after for_2 in deleteGameInfo\n";

	//delete[] allCandles;
	//delete[] scale_array;
	//delete[] fileLines;
}