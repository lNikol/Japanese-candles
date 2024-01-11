#include "Game.h"

void Game::initializeGame(int gr_w, int gr_h) {
	graphic_width = gr_w;
	graphic_height = gr_h;
}
void Game::initializeGameDates(char* startData, char* endData) {
	strcpy_s(start_data, sizeof(start_data), startData);
	strcpy_s(end_data, sizeof(end_data), endData);
}

void Game::createGameMap() {
	fileSys.graphic_width = graphic_width;
	coefficient = (maxValue - minValue) / (graphic_height - 2);
	map.initializeMap(graphic_width, graphic_height, minValue, maxValue, coefficient);
	map.createMap();
	map.drawYValues();
	map.drawMap();
}