#include "Candle.h"
#include <iostream>

void Candle::deleteCandle() {
	delete[] top_shadow;
	delete[] body;
	delete[] bottom_shadow;
	//std::cout << data << " ";
	//std::cout << (bottom_shadow == nullptr) << std::endl;
	return;
}

void Candle::initializeCandle(short maxH) {
	max_height = maxH;
	top_shadow = new char[max_height];
	body = new char[max_height];
	bottom_shadow = new char[max_height];
	return;
}

void Candle::calcTopShadow(float low, float high, float coef, float all_gr_YValues[]) {
	candle_low = low;
	candle_high = high;
	for (short j = 0; j < max_height; j++) {
		if (candle_open < candle_close) {
			float top_shadow_difference = candle_high - candle_close;
			short topheight = ceil(top_shadow_difference / coef);
			top_shadow_height = topheight > max_height ? max_height : topheight;

			if (all_gr_YValues[j] <= candle_close && candle_close <= all_gr_YValues[j + 1]) {
				float tempLowNum = candle_close - all_gr_YValues[j];
				float tempMaxNum = all_gr_YValues[j + 1] - candle_close;

				if (tempLowNum < tempMaxNum) {
					top_gr_minY_value = all_gr_YValues[j];
					if (top_shadow_height >= 1) {
						short abs_t = abs(j + 1 + (top_shadow_height - 1));
						short temp_index = abs_t > (max_height - 2) ?
							(max_height - 2) : abs_t;
						top_gr_maxY_value = all_gr_YValues[temp_index];
					}
					else top_gr_maxY_value = all_gr_YValues[j];
					for (short k = 0; k < top_shadow_height; k++) top_shadow[k] = '|';
				}
				else {
					top_gr_minY_value = all_gr_YValues[j + 1];
					if (top_shadow_height >= 1)
					{
						short abs_t = abs(j + 1 + (top_shadow_height - 1));
						short temp_index = abs_t > (max_height - 2) ?
							(max_height - 2) : abs_t;
						top_gr_maxY_value = all_gr_YValues[temp_index];
					}
					else top_gr_maxY_value = all_gr_YValues[j + 1];

					for (short k = 0; k < top_shadow_height; k++) top_shadow[k] = '|';
				}
			}
		}
		else if (candle_open == candle_close) {}
		else {
			float top_shadow_difference = candle_high - candle_open;
			short topheight = ceil(top_shadow_difference / coef);
			top_shadow_height = topheight > max_height ? max_height : topheight;

			if (all_gr_YValues[j] <= candle_open && candle_open <= all_gr_YValues[j + 1]) {
				float tempLowNum = candle_open - all_gr_YValues[j];
				float tempMaxNum = all_gr_YValues[j + 1] - candle_open;


				if (tempLowNum < tempMaxNum) {
					top_gr_minY_value = all_gr_YValues[j];
					if (top_shadow_height >= 1)
					{
						short abs_t = abs(j + 1 + (top_shadow_height - 1));
						short temp_index = abs_t > (max_height - 2) ?
							(max_height - 2) : abs_t;
						top_gr_maxY_value = all_gr_YValues[temp_index];
					}

					else top_gr_maxY_value = all_gr_YValues[j];
					for (short k = 0; k < top_shadow_height; k++) top_shadow[k] = '|';
				}
				else {
					top_gr_minY_value = all_gr_YValues[j + 1];
					if (top_shadow_height >= 1)
					{
						short abs_t = abs(j + 1 + (top_shadow_height - 1));
						short temp_index = abs_t > (max_height - 2) ?
							(max_height - 2) : abs_t;
						top_gr_maxY_value = all_gr_YValues[temp_index];
					}
					else top_gr_maxY_value = all_gr_YValues[j + 1];

					for (short k = 0; k < top_shadow_height; k++) top_shadow[k] = '|';
				}
			}
		}
	}
	return;
}

void Candle::calcBody(float open, float close, float coef, float all_gr_YValues[]) {
	candle_open = open;
	candle_close = close;
	for (short j = 0; j < max_height - 1; j++) {
		if (open < close) {
			float tempDifference = close - open;
			short amountOfO = ceil(tempDifference / coef); // exp. 1.6 --> 2
			body_height = amountOfO;
			if (all_gr_YValues[j] <= open && open <= all_gr_YValues[j + 1]) {
				float tempLowNum = open - all_gr_YValues[j];
				float tempMaxNum = all_gr_YValues[j + 1] - open;

				if (tempLowNum < tempMaxNum) {
					body_gr_minY_value = all_gr_YValues[j];
					if (amountOfO >= 1) body_gr_maxY_value = all_gr_YValues[abs(j + (amountOfO - 1))];
					else body_gr_maxY_value = all_gr_YValues[j];
					for (short k = 0; k < amountOfO; k++) body[k] = 'O';
				}
				else {
					body_gr_minY_value = all_gr_YValues[j + 1];
					if (amountOfO >= 1) body_gr_maxY_value = all_gr_YValues[abs(j + 1 + (amountOfO - 1))];
					else body_gr_maxY_value = all_gr_YValues[j + 1];

					for (short k = 0; k < amountOfO; k++) body[k] = 'O';
				}
			}
		}
		else if (open == close) {}
		else {
			float tempDifference = open - close;
			short amountOfHash = ceil(tempDifference / coef); // exp. 1.6 --> 2
			body_height = amountOfHash;

			if (all_gr_YValues[j] <= open && open <= all_gr_YValues[j + 1]) {
				float tempLowNum = open - all_gr_YValues[j];
				float tempMaxNum = all_gr_YValues[j + 1] - open;
				if (tempLowNum < tempMaxNum) {
					body_gr_maxY_value = all_gr_YValues[j];
					if (amountOfHash >= 1) body_gr_minY_value = all_gr_YValues[abs(j - (amountOfHash - 1))];
					else body_gr_minY_value = all_gr_YValues[j];
					for (short k = 0; k < amountOfHash; k++) body[k] = '#';
				}
				else {
					body_gr_maxY_value = all_gr_YValues[j + 1];
					if (amountOfHash >= 1) body_gr_minY_value = all_gr_YValues[abs(j + 1 - (amountOfHash - 1))];
					else body_gr_minY_value = all_gr_YValues[j + 1];
					for (short k = 0; k < amountOfHash; k++) body[k] = '#';
				}
			}
		}
	}
	return;
}


void Candle::calcDownShadow(float low, float high, float coef, float all_gr_YValues[]) {
	candle_low = low;
	candle_high = high;

	for (short j = 0; j < max_height; j++) {
		if (candle_open < candle_close) {
			float bttm_shadow_diff = candle_open - candle_low;
			short btmHeight = ceil(bttm_shadow_diff / coef);
			bottom_shadow_height = btmHeight > max_height ? max_height : btmHeight;

			if (all_gr_YValues[j] <= candle_open && candle_open <= all_gr_YValues[j + 1]) {
				float tempLowNum = candle_open - all_gr_YValues[j];
				float tempMaxNum = all_gr_YValues[j + 1] - candle_open;

				if (tempLowNum < tempMaxNum) {
					bottom_gr_maxY_value = all_gr_YValues[j];
					if (bottom_shadow_height >= 1) bottom_gr_minY_value = all_gr_YValues[j - (bottom_shadow_height - 1)];
					else bottom_gr_minY_value = all_gr_YValues[j];
					for (short k = 0; k < bottom_shadow_height; k++) bottom_shadow[k] = '|';
				}
				else {
					bottom_gr_maxY_value = all_gr_YValues[j + 1];
					if (bottom_shadow_height >= 1) bottom_gr_minY_value = all_gr_YValues[j + 1 - (bottom_shadow_height - 1)];
					else bottom_gr_minY_value = all_gr_YValues[j + 1];

					for (short k = 0; k < bottom_shadow_height; k++) bottom_shadow[k] = '|';
				}
			}
		}
		else if (candle_open == candle_close) {}
		else {
			float bttm_shadow_diff = candle_close - candle_low;
			short btmHeight = ceil(bttm_shadow_diff / coef);
			bottom_shadow_height = btmHeight > max_height ? max_height : btmHeight;

			if (all_gr_YValues[j] <= candle_close && candle_close <= all_gr_YValues[j + 1]) {
				float tempLowNum = candle_close - all_gr_YValues[j];
				float tempMaxNum = all_gr_YValues[j + 1] - candle_close;

				if (tempLowNum < tempMaxNum) {
					bottom_gr_maxY_value = all_gr_YValues[j];
					if (bottom_shadow_height >= 1) bottom_gr_minY_value = all_gr_YValues[j - (bottom_shadow_height - 1)];
					else bottom_gr_minY_value = all_gr_YValues[j];
					for (short k = 0; k < bottom_shadow_height; k++) bottom_shadow[k] = '|';
				}
				else {
					bottom_gr_maxY_value = all_gr_YValues[j + 1];
					if (bottom_shadow_height >= 1) bottom_gr_minY_value = all_gr_YValues[j + 1 - (bottom_shadow_height - 1)];
					else bottom_gr_minY_value = all_gr_YValues[j + 1];

					for (short k = 0; k < bottom_shadow_height; k++) bottom_shadow[k] = '|';
				}
			}
		}
	}
	return;
}