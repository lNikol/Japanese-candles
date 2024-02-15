#pragma once
struct Candle{
	char data[11];

	int max_height;

	// gr - graphic
	double top_gr_minY_value;
	double top_gr_maxY_value;
	int top_shadow_height;
	char* top_shadow;

	double body_gr_minY_value;
	double body_gr_maxY_value;
	int body_height;
	char* body;
	
	double bottom_gr_minY_value;
	double bottom_gr_maxY_value;
	int bottom_shadow_height;
	char* bottom_shadow;

	double candle_open, candle_close, candle_low, candle_high;


	void initializeCandle(int);

	void calcTopShadow(double low, double high, double coef, double all_gr_YValues[]);
	void calcBody(double open, double close, double coef, double all_gr_YValues[]);
	void calcDownShadow(double low, double high, double coef, double all_gr_YValues[]);

	void deleteCandle();
};