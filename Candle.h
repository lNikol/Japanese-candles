#pragma once
struct Candle{
	char data[11];

	short max_height;

	// gr - graphic
	float top_gr_minY_value;
	float top_gr_maxY_value;
	short top_shadow_height;
	char* top_shadow;

	float body_gr_minY_value;
	float body_gr_maxY_value;
	short body_height;
	char* body;
	
	float bottom_gr_minY_value;
	float bottom_gr_maxY_value;
	short bottom_shadow_height;
	char* bottom_shadow;

	float candle_open, candle_close, candle_low, candle_high;


	void initializeCandle(short);

	void calcTopShadow(float low, float high, float coef, float all_gr_YValues[]);
	void calcBody(float open, float close, float coef, float all_gr_YValues[]);
	void calcDownShadow(float low, float high, float coef, float all_gr_YValues[]);

	void deleteCandle();
};