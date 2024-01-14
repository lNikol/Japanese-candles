#include "Game.h"
#include <iostream>

void Game::initializeGame(int gr_w, int gr_h) {
	graphic_width = gr_w;
	graphic_height = gr_h;
	weekCounter = 0;
	monthCounter = 0;
	otherCounter = 0;
	amountOfDates = fileSys.infoLength;
	
	fileSys.findMaxMin();

	maxValue = fileSys.maxValue;
	minValue = fileSys.minValue;

	fileLines = new LineFile[amountOfDates];
	allCandles = new Candle[amountOfDates];
	weeks_Candles = new Candle[graphic_width];
	month_Candles = new Candle[graphic_width];
	other_Candles = new Candle[graphic_width]; // array of candles with other scale

	fileSys.setGameFileLines(fileLines);

	for (int i = 0; i < amountOfDates; i++) {
		Candle candle = Candle();
		allCandles[i] = candle;
		allCandles[i].initializeCandle(graphic_height);
	}
	delete fileSys.fileLines;
}

void Game::initializeGameDates(char* startData, char* endData) {
	strcpy_s(start_data, sizeof(start_data), startData);
	strcpy_s(end_data, sizeof(end_data), endData);
}

void Game::createGameMap(char type, int scale) {
	coefficient = (maxValue - minValue) / (graphic_height - 2);
	map.initializeMap(graphic_width, graphic_height, minValue, maxValue, coefficient, total_height);
	map.createMap();
	map.drawYValues();


	for (int i = fileSys.start_data_x; i <= fileSys.end_data_x; i++) {
		strcpy_s(allCandles[i].data, sizeof(allCandles[i].data), fileLines[i].data);
		doCandle(fileLines[i].open, fileLines[i].close,
			fileLines[i].low, fileLines[i].high, allCandles[i]);
	}

	switch (type) {
	case 'd': 
		for (int i = fileSys.start_data_x; i <= fileSys.end_data_x; i++) {
			map.writeCandleToMap(i - fileSys.start_data_x, allCandles[i]);
		}
		break;
	default:
		for (int i = fileSys.start_data_x; i <= fileSys.end_data_x - scale; i++) {
			if ((i - fileSys.start_data_x) % scale == 0) groupCandles(i, i + scale, other_Candles, otherCounter);
		}
		int N = fileSys.size_data_x - scale * otherCounter;
		if (N != 0) {
			groupCandles(fileSys.start_data_x + scale * otherCounter, fileSys.end_data_x, other_Candles, otherCounter);
		}
		std::cout << otherCounter << std::endl;
		for (int i = 0; i < otherCounter; i++) {
			map.writeCandleToMap(i, other_Candles[i]);
		}
		  break;
	}


	

	// если входные данные > чем длина/высота графика, то применить масштабирование для всего графика (и для y, и для x)  
	// то применяется масштабирование по иксу или по игрику
	// по иксу: входные дни / на ширину графика 
	// курс по игрику

	// if numOfDates <= 200

	

	map.drawMap();
}
void Game::doCandle(double open, double close, double low, double high, Candle& candle) {
	candle.calcBody(open, close, coefficient, map.allYVal);
	candle.calcTopShadow(low, high, coefficient, map.allYVal);
	candle.calcDownShadow(low, high, coefficient, map.allYVal);
}


void Game::groupCandles(int start_ind, int end_ind, Candle arr[], int& arrCounter ) {
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
	arr[arrCounter] = candle;
	arrCounter++;
}

// Записывать действия пользователя в файл .log. После каждого действия закрывать файл, 
// и при новом действии открывать и дописывать данные к файлу