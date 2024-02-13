#include "Game.h"
#include <iostream>

void Game::initializeGame(int gr_w, int gr_h) {
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
	

}

void Game::initializeGameDates(char* startData, char* endData) {
	strcpy_s(start_data, sizeof(start_data), startData);
	strcpy_s(end_data, sizeof(end_data), endData);
}

//void Game::createGameMap(char type, int scale) {
//	coefficient = (maxValue - minValue) / (graphic_height - 2);
//	map.initializeMap(graphic_width, graphic_height, minValue, maxValue, coefficient, total_height);
//	map.createMap();
//	map.drawYValues();
//
//
//
//
//	switch (type) {
//	case 'd': 
//		for (int i = fileSys.start_data_x; i <= fileSys.end_data_x; i++) {
//			map.writeCandleToMap(i - fileSys.start_data_x, allCandles[i]);
//		}
//		break;
//	default:
//		for (int i = fileSys.start_data_x; i <= fileSys.end_data_x - scale; i++) {
//			if ((i - fileSys.start_data_x) % scale == 0) groupCandles(i, i + scale, scale_array, otherCounter);
//		}
//		int N = fileSys.size_data_x - scale * otherCounter;
//		if (N != 0) {
//			groupCandles(fileSys.start_data_x + scale * otherCounter, fileSys.end_data_x, scale_array, otherCounter);
//		}
//		std::cout << otherCounter << std::endl;
//		for (int i = 0; i < otherCounter; i++) {
//			map.writeCandleToMap(i, scale_array[i]);
//		}
//		  break;
//	}	
//
//	map.drawMap();
//}


void Game::createGameMap2(int candle_scale, int start_data_x, int end_data_x, int graph_height, int graph_size, int size_data_x) {
	coefficient = (maxValue - minValue) / (graphic_height - 2);
	map.initializeMap(graph_size, graph_height, minValue, maxValue, coefficient, total_height);
	map.createMap();
	map.drawYValues();
	
	for (int i = fileSys.start_data_x; i <= fileSys.end_data_x; i++) {
		strcpy_s(allCandles[i].data, sizeof(allCandles[i].data), fileLines[i].data);
		doCandle(fileLines[i].open, fileLines[i].close,
			fileLines[i].low, fileLines[i].high, allCandles[i]);
	}



	int lengthOfArray;
	if (size_data_x % candle_scale == 0)
	{
		lengthOfArray = size_data_x / candle_scale;
	}
	else {
		lengthOfArray = size_data_x / candle_scale + 1;
	}

	int size_data_scale_x = lengthOfArray;
	scale_array = new Candle[lengthOfArray];
	
	int j = 0;
	int end_candle_x = 0;
	for (int i = start_data_x + 1; i < end_data_x; i++)
	{
		if (i + candle_scale > end_data_x) {
			end_candle_x = end_data_x - i;
		}
		else {
			end_candle_x = candle_scale;
		}
		scale_array[j] = groupCandles(i, i + end_candle_x);
		i = i + end_candle_x - 1;
		j++;
	}

	int start_data_scale_x = 0;
	int end_data_scale_x = j;

	if (size_data_scale_x > graph_size) {
		start_data_scale_x = end_data_scale_x - graph_size + 1;
	}
	for (int k = start_data_scale_x; k <= end_data_scale_x; k++) {
		map.writeCandleToMap(k - start_data_scale_x, scale_array[k], scale_array, end_data_scale_x);
	}



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

	//arr[arrCounter] = candle;
	//arrCounter++;
}

// Записывать действия пользователя в файл .log. После каждого действия закрывать файл, 
// и при новом действии открывать и дописывать данные к файлу