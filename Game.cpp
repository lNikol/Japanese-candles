#include "Game.h"
#include <iostream>

void Game::initializeGame(int gr_w, int gr_h) {
	graphic_width = gr_w;
	graphic_height = gr_h;
	weekCounter = 0;
	monthCounter = 0;
	fileSys.graphic_width = graphic_width;

	for (int i = 0; i < graphic_width; i++) {
		Candle candle = Candle();
		allCandles[i] = candle;
		allCandles[i].initializeCandle(graphic_height);
	}
}

void Game::initializeGameDates(char* startData, char* endData) {
	strcpy_s(start_data, sizeof(start_data), startData);
	strcpy_s(end_data, sizeof(end_data), endData);
}

void Game::createGameMap(Candle arr[], int graphic_w) {
	coefficient = (maxValue - minValue) / (graphic_height - 2);
	map.initializeMap(graphic_w / 5, graphic_height, minValue, maxValue, coefficient, total_height, down_height);
	map.createMap();
	map.drawYValues();

	for (int i = 0; i < graphic_width; ++i) {
		strcpy_s(allCandles[i].data, sizeof(allCandles[i].data), fileLines[i].data);
		doCandle(fileLines[i].open, fileLines[i].close,
			fileLines[i].low, fileLines[i].high, allCandles[i]);
	}

	// если входные данные > чем длина/высота графика, то применить масштабирование для всего графика (и для y, и для x)  
	// то применяется масштабирование по иксу или по игрику
	// по иксу: входные дни / на ширину графика 
	// курс по игрику

	for (int i = 0; i < graphic_width; i++) {
		if (i % 5 == 0)	groupCandles(i, i + 4, allCandles[i], allCandles[i + 4], weeks_Candles, weekCounter);
	}

	for (int i = 0; i < graphic_width; i++) {
		if (i % 20 == 0) groupCandles(i, i + 19, allCandles[i], allCandles[i + 19], month_Candles, monthCounter);
	}

	calcPixels(weeks_Candles, graphic_w / 5);
	map.drawMap();
}

void Game::calcPixels(Candle arr[], int graphic_w) {
	for (int i = 0; i < graphic_w; i++) {
		map.writeCandleToMap(i, arr[i]);
	}
}

void Game::doCandle(double open, double close, double low, double high, Candle& candle) {
	candle.calcBody(open, close, coefficient, map.allYVal);
	candle.calcTopShadow(low, high, coefficient, map.allYVal);
	candle.calcDownShadow(low, high, coefficient, map.allYVal);
	
	if(candle.top_gr_minY_value>candle.top_gr_maxY_value)std::cout << candle.top_gr_minY_value << ' ' << candle.top_gr_maxY_value << ' ' << candle.top_shadow_height << std::endl;
}


void Game::groupCandles(int start_ind, int end_ind, Candle one, Candle two, Candle arr[], int& arrCounter ) {
	double lowVal = one.candle_low;
	double maxVal = one.candle_high;
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
	candle.candle_open = one.candle_open;
	candle.candle_close = two.candle_close;
	candle.candle_low = lowVal;
	candle.candle_high = maxVal;
	strcpy_s(candle.data, sizeof(candle.data), two.data);

	doCandle(candle.candle_open, candle.candle_close, candle.candle_low, candle.candle_high, candle);
	arr[arrCounter] = candle;
	arrCounter++;
}

// Записывать действия пользователя в файл .log. После каждого действия закрывать файл, 
// и при новом действии открывать и дописывать данные к файлу