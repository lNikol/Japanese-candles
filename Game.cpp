#include "Game.h"
#include <iostream>

void Game::initializeGame(int gr_w, int gr_h) {
	graphic_width = gr_w;
	graphic_height = gr_h;

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

void Game::createGameMap() {
	fileSys.graphic_width = graphic_width;
	coefficient = (maxValue - minValue) / (graphic_height - 2);

	map.initializeMap(graphic_width, graphic_height, minValue, maxValue, coefficient, total_height, down_height);
	map.createMap();
	map.drawYValues();
	calcPixels();
	map.drawMap();
}

void Game::calcPixels() {
	for (int i = 0; i < graphic_width; ++i) {
		doCandle(fileLines[i].open, fileLines[i].close, fileLines[i].low, fileLines[i].high, allCandles[i]);
		strcpy_s(allCandles[i].data, sizeof(allCandles[i].data), fileLines[i].data);
		map.writeCandleToMap(i, allCandles[i]);
	}
}

void Game::doCandle(double open, double close, double low, double high, Candle& candle) {
	candle.calcBody(open, close, coefficient, map.allYVal);
	candle.calcTopShadow(low, high, coefficient, map.allYVal);
	candle.calcDownShadow(low, high, coefficient, map.allYVal);
	
	if(candle.top_gr_minY_value>candle.top_gr_maxY_value)std::cout << candle.top_gr_minY_value << ' ' << candle.top_gr_maxY_value << ' ' << candle.top_shadow_height << std::endl;
}